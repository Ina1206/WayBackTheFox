#include "CDX9Mesh.h"
#include <crtdbg.h>	//_ASSERTマクロで必要.

const char SHADER_NAME[] = "Data\\Shader\\Mesh.hlsl";

//コンストラクタ.
CDX9Mesh::CDX9Mesh()
	: m_hWnd				(nullptr)
	, m_pD3d9				(nullptr)
	, m_pDevice9			(nullptr)
	, m_pDevice11			(nullptr)
	, m_pContext11			(nullptr)
	, m_pVertexShader		(nullptr)
	, m_pVertexLayout		(nullptr)
	, m_pPixelShader		(nullptr)
	, m_pCBufferPerMesh		(nullptr)
	, m_pCBufferPerMaterial	(nullptr)
	, m_pCBufferPerFrame	(nullptr)
	, m_pVertexBuffer		(nullptr)
	, m_ppIndexBuffer		(nullptr)
	, m_pSampleLinear		(nullptr)
	, m_pMesh				(nullptr)
	, m_NumMaterials		(0)
	, m_pMaterials			(nullptr)
	, m_NumAttr				(0)
	, m_AttrID				()
	, m_EnableTexture		(false)
	, m_Sphere				()
	, m_BBox				()
	, m_pMeshForRay			(nullptr)
	, m_fScale				(1.0f)
	, m_vRot				(0.0f, 0.0f, 0.0f)
	, m_vPos				(0.0f, 0.0f, 0.0f)
	, m_vPrePos				(0.0f, 0.0f, 0.0f)
	, m_pstShadow			(nullptr)
{

}

//デストラクタ.
CDX9Mesh::~CDX9Mesh()
{
	//解放処理.
	Release();
}

HRESULT CDX9Mesh::Init(
	HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11, const char* fileName)
{
	m_hWnd			= hWnd;
	m_pDevice9		= pDevice9;
	m_pDevice11		= pDevice11;
	m_pContext11	= pContext11;

	if (FAILED(LoadXMesh(fileName))) {
		return E_FAIL;
	}
	if (FAILED(InitShader())) {
		return S_OK;
	}

	return S_OK;
}

//メッシュ読み込み.
HRESULT CDX9Mesh::LoadXMesh(const char* fileName)
{
	//マテリアルバッファ.
	LPD3DXBUFFER pD3DXMtrlBuffer = nullptr;

	//Xファイルのロード.
	if (FAILED(D3DXLoadMeshFromX(
		fileName,				//ファイル名.
		D3DXMESH_SYSTEMMEM		//システムメモリに読み込み.
			| D3DXMESH_32BIT,	//32bit.
		m_pDevice9, nullptr,
		&pD3DXMtrlBuffer,		//(out)マテリアル情報.
		nullptr,
		&m_NumMaterials,		//(out)マテリアル数.
		&m_pMesh)))				//(out)メッシュオブジェクト.
	{
		//なんのファイルが読み込めないのか？を足す.
		_ASSERT_EXPR(false, L"Xファイル読み込み失敗");
		return E_FAIL;
	}

	//Xファイルのロード(レイと判定用に別設定で読み込む).
	if (FAILED(D3DXLoadMeshFromX(
		fileName,				//ファイル名.
		D3DXMESH_SYSTEMMEM,		//システムメモリに読み込み.
		m_pDevice9, nullptr,
		&pD3DXMtrlBuffer,		//(out)マテリアル情報.
		nullptr,
		&m_NumMaterials,		//(out)マテリアル数.
		&m_pMeshForRay)))		//(out)メッシュオブジェクト.
	{
		_ASSERT_EXPR(false, L"Xファイル読み込み失敗");
		return E_FAIL;
	}


	D3D11_BUFFER_DESC		bd;			//Dx11バッファ構造体.
	D3D11_SUBRESOURCE_DATA	InitData;	//初期化データ.
	//読み込んだ情報から必要な情報を抜き出す.
	D3DXMATERIAL* d3dxMaterials
		= static_cast<D3DXMATERIAL*>(pD3DXMtrlBuffer->GetBufferPointer());
	//マテリアル数分の領域を確保.
	m_pMaterials = new MY_MATERIAL[m_NumMaterials]();
	//ポインタを複数個作るため*がついてる.
	m_ppIndexBuffer = new ID3D11Buffer*[m_NumMaterials]();
	//マテリアル数分繰り返し.
	for (DWORD No = 0; No < m_NumMaterials; No++) 
	{
		//インデックスバッファの初期化.
		m_ppIndexBuffer[No] = nullptr;

		//マテリアル情報のコピー.
		//アンビエント.
		m_pMaterials[No].Ambient.x = d3dxMaterials[No].MatD3D.Ambient.r;
		m_pMaterials[No].Ambient.y = d3dxMaterials[No].MatD3D.Ambient.g;
		m_pMaterials[No].Ambient.z = d3dxMaterials[No].MatD3D.Ambient.b;
		m_pMaterials[No].Ambient.w = d3dxMaterials[No].MatD3D.Ambient.a;
		//ディフューズ.
		m_pMaterials[No].Diffuse.x = d3dxMaterials[No].MatD3D.Diffuse.r;
		m_pMaterials[No].Diffuse.y = d3dxMaterials[No].MatD3D.Diffuse.g;
		m_pMaterials[No].Diffuse.z = d3dxMaterials[No].MatD3D.Diffuse.b;
		m_pMaterials[No].Diffuse.w = d3dxMaterials[No].MatD3D.Diffuse.a;
		//スペキュラ.
		m_pMaterials[No].Specular.x = d3dxMaterials[No].MatD3D.Specular.r;
		m_pMaterials[No].Specular.y = d3dxMaterials[No].MatD3D.Specular.g;
		m_pMaterials[No].Specular.z = d3dxMaterials[No].MatD3D.Specular.b;
		m_pMaterials[No].Specular.w = d3dxMaterials[No].MatD3D.Specular.a;

		//（その面に）テクスチャが貼られているか？.
		if (d3dxMaterials[No].pTextureFilename != nullptr
			&& lstrlen(d3dxMaterials[No].pTextureFilename) > 0)
		{
			//テクスチャありのフラグを立てる.
			m_EnableTexture = true;

			char path[128] = "";
			int path_count = lstrlen(fileName);
			for (int k = path_count; k >= 0; k--) {
				if (fileName[k] == '\\') {
					for (int j = 0; j <= k; j++) {
						path[j] = fileName[j];
					}
					path[k + 1] = '\0';
					break;
				}
			}
			//パスとテクスチャファイル名を連結.
			strcat_s(path, sizeof(path), d3dxMaterials[No].pTextureFilename);

			//テクスチャファイル名をコピー.
			strcpy_s(m_pMaterials[No].szTextureName,
				sizeof(m_pMaterials[No].szTextureName), path);

			//テクスチャ作成.
			if (FAILED(D3DX11CreateShaderResourceViewFromFileA(
				m_pDevice11, m_pMaterials[No].szTextureName,	//テクスチャファイル名.
				nullptr, nullptr,
				&m_pMaterials[No].pTexture,						//(out)テクスチャオブジェクト.
				nullptr)))
			{
				_ASSERT_EXPR(false, L"テクスチャ作成失敗");
				return E_FAIL;
			}
			
		}	
	}

	//-------------------------------------------------------.
	//		インデックスバッファ作成.
	//-------------------------------------------------------.
	//メッシュの属性情報を得る.
	D3DXATTRIBUTERANGE* pAttrTable = nullptr;

	//メッシュの面および頂点の順番変更を制御し、パフォーマンスを最適化する.
	//D3DXMESHOPT_COMPACT : 面の順番を変更し、使用されていない頂点と面を削除する.
	//D3DXMESHOPT_ATTRSORT: パフォーマンスを上げる為、面の順番を変更して最適化を行う.
	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT,
		nullptr, nullptr, nullptr, nullptr);
	//属性テーブルの取得.
	m_pMesh->GetAttributeTable(nullptr, &m_NumAttr);
	pAttrTable = new D3DXATTRIBUTERANGE[m_NumAttr];
	if (FAILED(m_pMesh->GetAttributeTable(pAttrTable, &m_NumAttr)))
	{
		_ASSERT_EXPR(false, L"属性テーブル取得失敗");
		return E_FAIL;
	}

	//同じくLockしないと取り出せない.
	int* pIndex = nullptr;
	m_pMesh->LockIndexBuffer(
		D3DLOCK_READONLY, (void**)&pIndex);
	//属性ごとのインデックスバッファを作成.
	for (DWORD No = 0; No < m_NumAttr; No++)
	{
		m_AttrID[No] = pAttrTable[No].AttribId;
		//Dx9のインデックスバッファからの情報で、Dx11のインデックスバッファを作成.
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(int)*pAttrTable[No].FaceCount * 3;	//面数×３で頂点数.
		bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		//大きいインデックスバッファ内のオフセット(×3する).
		InitData.pSysMem = &pIndex[pAttrTable[No].FaceStart*3];

		if (FAILED(m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_ppIndexBuffer[No])))
		{
			_ASSERT_EXPR(false, L"インデックスバッファ作成失敗");
			return E_FAIL;
		}
		//面の数をコピー.
		m_pMaterials[m_AttrID[No]].dwNumFace = pAttrTable[No].FaceCount;
	}
	//属性テーブルの削除.
	delete[] pAttrTable;
	//使用済みのインデックスバッファの解放.
	m_pMesh->UnlockIndexBuffer();
	//不要になったマテリアルバッファを解放.
	SAFE_RELEASE(pD3DXMtrlBuffer);

	//-------------------------------------------------------.
	//	頂点バッファの作成.
	//-------------------------------------------------------.
	//Dx9の場合、mapではなくLockで頂点バッファからデータを取り出す.
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
	m_pMesh->GetVertexBuffer(&pVB);
	DWORD dwStride = m_pMesh->GetNumBytesPerVertex();
	BYTE*   pVertices = nullptr;
	VERTEX* pVertex = nullptr;
	if (SUCCEEDED(
		pVB->Lock(0, 0, (VOID**)&pVertices, 0)))
	{
		pVertex = (VERTEX*)pVertices;
		//Dx9の頂点バッファからの情報で、Dx11頂点バッファを作成.
		bd.Usage = D3D11_USAGE_DEFAULT;
		//頂点を格納するのに必要なバイト数.
		bd.ByteWidth = m_pMesh->GetNumBytesPerVertex()*m_pMesh->GetNumVertices();
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;
		bd.MiscFlags = 0;
		InitData.pSysMem = pVertex;
		if (FAILED(m_pDevice11->CreateBuffer(
			&bd, &InitData, &m_pVertexBuffer)))
		{
			_ASSERT_EXPR(false, L"頂点バッファ作成失敗");
			return E_FAIL;
		}
		pVB->Unlock();
	}
	SAFE_RELEASE(pVB);	//頂点バッファ解放.



	//テクスチャ用のサンプラ構造体.
	D3D11_SAMPLER_DESC	samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	//リニアフィルタ(線形補間).
							//POINT:高速だが粗い.
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		//ラッピングモード(WRAP:繰り返し).
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
							//MIRROR: 反転繰り返し.
							//CLAMP : 端の模様を引き伸ばす.
							//BORDER: 別途境界色を決める.
	//サンプラ作成.
	if (FAILED(m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear)))					//(out)サンプラ.
	{
		_ASSERT_EXPR(false, L"サンプラ作成失敗");
		return E_FAIL;
	}


	return S_OK;
}

//解放関数.
void CDX9Mesh::Release()
{
	//インデックスバッファ解放.	
	if (m_ppIndexBuffer != nullptr) {
		for (int No = m_NumMaterials - 1; No >= 0; No--) {
			if (m_ppIndexBuffer[No] != nullptr) {
				SAFE_RELEASE(m_ppIndexBuffer[No]);
			}
		}
		delete[] m_ppIndexBuffer;
		m_ppIndexBuffer = nullptr;
	}

	//マテリアル解放.
	//もしこれが何回か使われていったら SAFE_RELEASE_ARYのマクロを作る.
	if (m_pMaterials != nullptr) {
		//deleteのタイミングで中身のポインタがマクロで自動で消してくれる.
		delete[] m_pMaterials;
		m_pMaterials = nullptr;
	}

	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pCBufferPerMaterial);
	SAFE_RELEASE(m_pCBufferPerMesh);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);

	SAFE_RELEASE(m_pDevice9);
	SAFE_RELEASE(m_pD3d9);

	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
	m_hWnd = nullptr;
}

//==================================================================.
//	HLSLファイルを読み込みシェーダを作成する.
//	HLSL : High Level Shading Language の略.
//==================================================================.
HRESULT CDX9Mesh::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT	  uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif	//#ifdef _DEBUG.

	//HLSLからバーテックスシェーダのブロブを作成.
	if (m_EnableTexture == true){
		if (FAILED(
			D3DX11CompileFromFile(
				SHADER_NAME,		//シェーダファイル名(HLSLファイル).
				nullptr,			//マクロ定義の配列へのポインタ(未使用).
				nullptr,			//インクルードファイルを扱うインターフェイスへのポインタ(未使用).
				"VS_Main",			//シェーダエントリーポイント関数の名前.				//""はプロパティの設定項目と一緒.
				"vs_5_0",			//シェーダのモデルを指定する文字列(プロファイル).
				uCompileFlag,		//シェーダコンパイルフラグ.
				0,					//エフェクトコンパイルフラグ(未使用).
				nullptr,			//スレッドポンプインターフェイスへのポインタ(未使用).
				&pCompiledShader,	//ブロブを格納するメモリへのポインタ.
				&pErrors,			//エラーと警告一覧を格納するメモリへのポインタ.
				nullptr)))			//戻り値へのポインタ(未使用).
		{
			_ASSERT_EXPR(false, L"hlsl読み込み失敗");
			return E_FAIL;
		}
	}
	else {
		if (FAILED(
			D3DX11CompileFromFile(
				SHADER_NAME,		//シェーダファイル名(HLSLファイル).
				nullptr,			//マクロ定義の配列へのポインタ(未使用).
				nullptr,			//インクルードファイルを扱うインターフェイスへのポインタ(未使用).
				"VS_NoTex",			//シェーダエントリーポイント関数の名前.				//""はプロパティの設定項目と一緒.
				"vs_5_0",			//シェーダのモデルを指定する文字列(プロファイル).
				uCompileFlag,		//シェーダコンパイルフラグ.
				0,					//エフェクトコンパイルフラグ(未使用).
				nullptr,			//スレッドポンプインターフェイスへのポインタ(未使用).
				&pCompiledShader,	//ブロブを格納するメモリへのポインタ.
				&pErrors,			//エラーと警告一覧を格納するメモリへのポインタ.
				nullptr)))			//戻り値へのポインタ(未使用).
		{
			_ASSERT_EXPR(false, L"hlsl読み込み失敗");
			return E_FAIL;
		}
	}
	SAFE_RELEASE(pErrors);

	//上記で作成したブロブから「バーテックスシェーダ」を作成.
	if (FAILED(
		m_pDevice11->CreateVertexShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShader)))	//(out)バーテックスシェーダ.
	{
		_ASSERT_EXPR(false, L"バーテックスシェーダ作成失敗");
		return E_FAIL;
	}

	//頂点インプットレイアウトを定義.
	D3D11_INPUT_ELEMENT_DESC layout[3];

	//頂点インプットレイアウトの配列要素数を算出.
	UINT numElements = 0;
	if (m_EnableTexture == true) {
		D3D11_INPUT_ELEMENT_DESC tmp[] =
		{
			{
				"POSITION",						//位置.
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,	//DXGIのフォーマット(32bit float型*3).
				0,
				0,								//データの開始位置.
				D3D11_INPUT_PER_VERTEX_DATA, 0
			},
			{
				"NORMAL",						//法線.
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,	//DXGIのフォーマット(32bit float型*3).
				0,
				12,								//データの開始位置.
				D3D11_INPUT_PER_VERTEX_DATA, 0
			},
			{
				"TEXCOORD",						//テクスチャ位置.
				0,
				DXGI_FORMAT_R32G32_FLOAT,		//DXGIのフォーマット(32bit float型*2).
				0,
				24,								//データの開始位置←上のデータが4バイトが3つあるから12この開始位置は間違えてはいけない.
				D3D11_INPUT_PER_VERTEX_DATA, 0
			}
			
		};
		numElements = sizeof(tmp) / sizeof(tmp[0]);	//要素数算出.
		memcpy_s(layout, sizeof(layout), tmp, sizeof(D3D11_INPUT_ELEMENT_DESC)*numElements);
	}
	else
	{
		D3D11_INPUT_ELEMENT_DESC tmp[] =
		{
			{
				"POSITION",						//位置.
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,	//DXGIのフォーマット(32bit float型*3).
				0,
				0,								//データの開始位置.
				D3D11_INPUT_PER_VERTEX_DATA, 0
			},
			{
				"NORMAL",						//法線.
				0,
				DXGI_FORMAT_R32G32B32_FLOAT,	//DXGIのフォーマット(32bit float型*3).
				0,
				12,								//データの開始位置.
				D3D11_INPUT_PER_VERTEX_DATA, 0
			}
		};
		numElements = sizeof(tmp) / sizeof(tmp[0]);	//要素数算出.
		memcpy_s(layout, sizeof(layout), tmp, sizeof(D3D11_INPUT_ELEMENT_DESC)*numElements);
	}

	//頂点インプットレイアウトを作成.
	if (FAILED(
		m_pDevice11->CreateInputLayout(
			layout,
			numElements,
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			&m_pVertexLayout)))	//(out)頂点インプットレイアウト.
	{
		_ASSERT_EXPR(false, L"頂点インプットレイアウト作成失敗");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//HLSLからピクセルシェーダのブロブを作成.
	if (m_EnableTexture == true) {
		if (FAILED(
			D3DX11CompileFromFile(
				SHADER_NAME,		//シェーダファイル名(HLSLファイル).
				nullptr,			//マクロ定義の配列へのポインタ(未使用).
				nullptr,			//インクルードファイルを扱うインターフェイスへのポインタ(未使用).
				"PS_Main",			//シェーダエントリーポイント関数の名前.
				"ps_5_0",			//シェーダのモデルを指定する文字列(プロファイル).
				uCompileFlag,		//シェーダコンパイルフラグ.
				0,					//エフェクトコンパイルフラグ(未使用).
				nullptr,			//スレッドポンプインターフェイスへのポインタ(未使用).
				&pCompiledShader,	//ブロブを格納するメモリへのポインタ.
				&pErrors,			//エラーと警告一覧を格納するメモリへのポインタ.
				nullptr)))			//戻り値へのポインタ(未使用).
		{
			_ASSERT_EXPR(false, L"hlsl読み込み失敗");
			return E_FAIL;
		}
	}
	else {
		if (FAILED(
			D3DX11CompileFromFile(
				SHADER_NAME,		//シェーダファイル名(HLSLファイル).
				nullptr,			//マクロ定義の配列へのポインタ(未使用).
				nullptr,			//インクルードファイルを扱うインターフェイスへのポインタ(未使用).
				"PS_NoTex",			//シェーダエントリーポイント関数の名前.
				"ps_5_0",			//シェーダのモデルを指定する文字列(プロファイル).
				uCompileFlag,		//シェーダコンパイルフラグ.
				0,					//エフェクトコンパイルフラグ(未使用).
				nullptr,			//スレッドポンプインターフェイスへのポインタ(未使用).
				&pCompiledShader,	//ブロブを格納するメモリへのポインタ.
				&pErrors,			//エラーと警告一覧を格納するメモリへのポインタ.
				nullptr)))			//戻り値へのポインタ(未使用).
		{
			_ASSERT_EXPR(false, L"hlsl読み込み失敗");
			return E_FAIL;
		}
	}
	SAFE_RELEASE(pErrors);

	//上記で作成したブロブから「ピクセルシェーダ」を作成.
	if (FAILED(
		m_pDevice11->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pPixelShader)))	//(out)ピクセルシェーダ.
	{
		_ASSERT_EXPR(false, L"ピクセルシェーダ作成失敗");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//コンスタント(定数)バッファ作成.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//コンスタントバッファを指定.
	cb.ByteWidth = sizeof(CBUFFER_PER_MESH);		//コンスタントバッファのサイズ.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//書き込みでアクセス.
	cb.MiscFlags = 0;								//その他のフラグ(未使用).
	cb.StructureByteStride = 0;						//構造体のサイズ().
	cb.Usage = D3D11_USAGE_DYNAMIC;					//使用方法：直接書き込み.

	//コンスタントバッファの作成.
	if (FAILED(
		m_pDevice11->CreateBuffer(&cb,nullptr,&m_pCBufferPerMesh)))
	{
		_ASSERT_EXPR(false, L"コンスタントバッファ作成失敗");
		return E_FAIL;
	}

	//コンスタントバッファ マテリアル用.
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//コンスタントバッファを指定.
	cb.ByteWidth = sizeof(CBUFFER_PRE_MATERIAL);	//コンスタントバッファのサイズ.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//書き込みでアクセス.
	cb.MiscFlags = 0;								//その他のフラグ(未使用).
	cb.StructureByteStride = 0;						//構造体のサイズ().
	cb.Usage = D3D11_USAGE_DYNAMIC;					//使用方法：直接書き込み.

	//コンスタントバッファの作成.
	if (FAILED(
		m_pDevice11->CreateBuffer(&cb,nullptr,&m_pCBufferPerMaterial)))
	{
		_ASSERT_EXPR(false, L"コンスタントバッファ作成失敗");
		return E_FAIL;
	}

	//コンスタントバッファ フレーム用.
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//コンスタントバッファを指定.
	cb.ByteWidth = sizeof(CBUFFER_PER_FRAME);		//コンスタントバッファのサイズ.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//書き込みでアクセス.
	cb.MiscFlags = 0;								//その他のフラグ(未使用).
	cb.StructureByteStride = 0;						//構造体のサイズ().
	cb.Usage = D3D11_USAGE_DYNAMIC;					//使用方法：直接書き込み.

	//コンスタントバッファの作成.
	if (FAILED(
		m_pDevice11->CreateBuffer(&cb, nullptr, &m_pCBufferPerFrame)))
	{
		_ASSERT_EXPR(false, L"コンスタントバッファ作成失敗");
		return E_FAIL;
	}


	return S_OK;
}

//レンダリング用.
void CDX9Mesh::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj,
	D3DXVECTOR3& vLight, D3DXVECTOR3& vCamPos)
{
	D3DXMATRIX PreTran;
	//ワールド行列、スケール行列、回転行列、平行移動行列.
	D3DXMATRIX mWorld, mScale, mRot, mTran;
	D3DXMATRIX mYaw, mPitch, mRoll;


	//拡大縮小行列作成.
	D3DXMatrixScaling(
		&mScale,						//(out)計算結果.
		m_fScale, m_fScale, m_fScale);	//x,y,zそれぞれの拡縮値.
	//Y軸回転行列作成.
	D3DXMatrixRotationY(&mYaw,m_vRot.y);
	//X軸回転行列作成.
	D3DXMatrixRotationX(&mPitch,m_vRot.x);
	//Z軸回転行列作成.
	D3DXMatrixRotationZ(&mRoll,m_vRot.z);
	//平行移動行列作成.
	D3DXMatrixTranslation(
		&mTran,							//(out)計算結果.
		m_vPos.x, m_vPos.y, m_vPos.z);	//x,y,z座標.

	D3DXMatrixTranslation(
		&PreTran,							//(out)計算結果.
		m_vPrePos.x, m_vPrePos.y, m_vPrePos.z);	//x,y,z座標.

	//回転行列を作成.
	mRot = mYaw * mPitch * mRoll;

	//D3DXMatrixTranslationのx,y,zで世界の位置に置くことができる.
	//ワールド行列作成.
	mWorld = PreTran * mScale * mRot * mTran;

	//使用するシェーダのセット.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);		//頂点シェーダ.
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);		//ピクセルシェーダ.

	//シェーダのコンスタントバッファに各種データを渡す.
	D3D11_MAPPED_SUBRESOURCE	pData;
	//バッファ内のデータの書き換え開始時にMap.
	if (SUCCEEDED(m_pContext11->Map(
		m_pCBufferPerFrame, 0,
		D3D11_MAP_WRITE_DISCARD,
		0, &pData)))
	{
		CBUFFER_PER_FRAME cb;						//コンスタントバッファ.

		//カメラ位置.
		cb.vCamPos = D3DXVECTOR4(vCamPos.x, vCamPos.y, vCamPos.z, 0.0f);
		cb.vLightDir = D3DXVECTOR4(0.0f, 1.0f, 0.0f, 0.0f);

		//ライト方向の正規化(ノーマライズ).
		D3DXVec4Normalize(&cb.vLightDir, &cb.vLightDir);

		//影.
		cb.vCasterToLight = cb.vLightDir;
		for (int shadow = 0; shadow < SHADOW_MAX; shadow++) {
			cb.vCasterPos[shadow] = D3DXVECTOR4(0.0f, -100.0f, 0.0f, 0.0f);

			//外部設定されている数のほうが少ない場合は、それ以降をスキップ.
			if (shadow >= /*m_ShadowMax*/10) {
				continue;
			}

			//影情報が入っていれば処理.
			if (m_pstShadow != nullptr) {
				if (m_pstShadow[shadow].bDispFlag == true) {
					cb.vCasterPos[shadow] = static_cast<D3DXVECTOR4>(m_pstShadow[shadow].vCasterPos);
					//cb.vCasterPos[shadow] = D3DXVECTOR4(0.0f, 0.8f, 4.0f + (shadow * 0.1f), 1.0f);
					cb.vCasterPos[shadow].w = 1.0f;
				}
			}
		}

		memcpy_s(
			pData.pData,		//コピー先のバッファ.
			pData.RowPitch,		//コピー先のバッファサイズ.
			(void*)(&cb),		//コピー元のバッファ.
			sizeof(cb));		//コピー元のサイズ.

		//バッファ内のデータの書き換え終了時にUnmap.
		m_pContext11->Unmap(m_pCBufferPerFrame, 0);
	}

	//このコンスタントバッファをどのシェーダで使用するか？.
	m_pContext11->VSSetConstantBuffers(
		2, 1, &m_pCBufferPerFrame);			//頂点シェーダ.
	m_pContext11->PSSetConstantBuffers(
		2, 1, &m_pCBufferPerFrame);			//ピクセルシェーダ.

	//メッシュのレンダリング.
	RenderMesh(mWorld, mView, mProj);
}

//レンダリング関数(クラス内でのみ使用する).
void CDX9Mesh::RenderMesh(
	D3DXMATRIX& mWorld, D3DXMATRIX& mView, D3DXMATRIX& mProj)
{
	//シェーダのコンスタントバッファに各種データを渡す.
	D3D11_MAPPED_SUBRESOURCE	pData;
	//バッファ内のデータの書き換え開始時にMap.
	if (SUCCEEDED(m_pContext11->Map(
		m_pCBufferPerMesh, 0,
		D3D11_MAP_WRITE_DISCARD,
		0, &pData)))
	{
		CBUFFER_PER_MESH cb;						//コンスタントバッファ.

		//ワールド行列を渡す.
		cb.mW = mWorld;
		D3DXMatrixTranspose(&cb.mW, &cb.mW);		//ワールドに直接書き換えないのは下でも使うから.

		//ワールド,ビュー,プロジェクション行列を渡す.
		D3DXMATRIX mWVP = mWorld * mView * mProj;
		D3DXMatrixTranspose(&mWVP, &mWVP);			//行列を転置する.
		//※行列の計算方法がDirectXとGPUに異なるため転置が必要.
		cb.mWVP = mWVP;

		memcpy_s(
			pData.pData,		//コピー先のバッファ.
			pData.RowPitch,		//コピー先のバッファサイズ.
			(void*)(&cb),		//コピー元のバッファ.
			sizeof(cb));		//コピー元のサイズ.

		//バッファ内のデータの書き換え終了時にUnmap.
		m_pContext11->Unmap(m_pCBufferPerMesh, 0);
	}

	//このコンスタントバッファをどのシェーダで使用するか？.
	m_pContext11->VSSetConstantBuffers(
		0, 1, &m_pCBufferPerMesh);			//頂点シェーダ.
	m_pContext11->PSSetConstantBuffers(
		0, 1, &m_pCBufferPerMesh);			//ピクセルシェーダ.

	//頂点インプットレイアウトをセット.
	m_pContext11->IASetInputLayout(m_pVertexLayout);

	//プリミティブ・トポロジーをセット.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//頂点バッファをセット.
	UINT stride = m_pMesh->GetNumBytesPerVertex();
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(
		0, 1, &m_pVertexBuffer, &stride, &offset);

	//属性の数だけ、それぞれの属性のインデックスバッファを描画.
	for (DWORD No = 0; No < m_NumAttr; No++) {
		//使用されていないマテリアル対策.
		if (m_pMaterials[m_AttrID[No]].dwNumFace == 0) {
			continue;
		}
		//インデックスバッファ.
		m_pContext11->IASetIndexBuffer(
			m_ppIndexBuffer[No], DXGI_FORMAT_R32_UINT, 0);
		//マテリアルの各要素をシェーダに渡す.
		D3D11_MAPPED_SUBRESOURCE pDataMat;
		if (SUCCEEDED(
			m_pContext11->Map(m_pCBufferPerMaterial,
				0, D3D11_MAP_WRITE_DISCARD, 0, &pDataMat)))
		{
			CBUFFER_PRE_MATERIAL cb;
			//アンビエント,ディフューズ,スペキュラをシェーダに渡す.
			cb.vAmbient = m_pMaterials[m_AttrID[No]].Ambient;
			cb.vDiffuse = m_pMaterials[m_AttrID[No]].Diffuse;
			cb.vSpecular = m_pMaterials[m_AttrID[No]].Specular;

			memcpy_s(pDataMat.pData, pDataMat.RowPitch, (void*)&cb, sizeof(cb));

			m_pContext11->Unmap(m_pCBufferPerMaterial, 0);
		}

		//このコンスタントバッファをどのシェーダで使うか？.
		//シェーダでのregister番号と第一引数が連動している.
		m_pContext11->VSSetConstantBuffers(1, 1, &m_pCBufferPerMaterial);
		m_pContext11->PSSetConstantBuffers(1, 1, &m_pCBufferPerMaterial);

		//テクスチャをシェーダに渡す.
		if (m_pMaterials[m_AttrID[No]].pTexture != nullptr) {
			//テクスチャがあるとき.
			m_pContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
			m_pContext11->PSSetShaderResources(0, 1, &m_pMaterials[m_AttrID[No]].pTexture);
		}
		else {
			//テクスチャがないとき.
			ID3D11ShaderResourceView* pNothing[1] = { 0 };
			m_pContext11->PSSetShaderResources(0, 1, pNothing);
		}

		//プリミティブ(ポリゴン)をレンダリング.
		m_pContext11->DrawIndexed(m_pMaterials[m_AttrID[No]].dwNumFace * 3, 0, 0);
	}

}
