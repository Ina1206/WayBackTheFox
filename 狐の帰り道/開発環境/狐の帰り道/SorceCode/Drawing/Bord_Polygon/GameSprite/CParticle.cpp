#include "CParticle.h"
#include <crtdbg.h>

//シェーダネーム.
const char SHADER_NAME[] = "Data\\Shader\\Particle.hlsl";

CParticle::CParticle()
	: m_pVertexShader(nullptr)
	, m_pVertexLayout(nullptr)
	, m_GeometryShader(nullptr)
	, m_pPixelShader(nullptr)
	, m_pConstantBuffer(nullptr)
	, m_pVertexBuffer(nullptr)
	, m_pSampleLinear(nullptr)
	, m_pTexture(nullptr)
	, m_AnimCount(0)
	, m_UV(0.0f, 0.0f)
	, m_vPos()
	, m_Scale(1.0f)
	, m_pParticleArray(nullptr)
	, m_Frame(0)
	, m_vRot(0.0f, 0.0f, 0.0f)
{
}

//デストラクタ.
CParticle::~CParticle()
{
	Release();
}

//初期化.
HRESULT CParticle::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContex11, const char* fileName)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContex11;

	//ブレンドステート.
	if (FAILED(InitBlend()))
	{
		return E_FAIL;
	}

	//シェーダ作成.
	if (FAILED(InitShader()))
	{
		return E_FAIL;
	}
	//板ポリゴン作成.
	if (FAILED(InitModel()))
	{
		return E_FAIL;
	}
	//テクスチャ作成
	if(FAILED(InitTexture(fileName)))
	{
		return E_FAIL;
	}

	return S_OK;
}

//解放.
void CParticle::Release()
{
	//テンプレートクラスというものがある.
	//↑を使えるようになると便利.
	SAFE_RELEASE(m_pAlphaBlend);
	SAFE_RELEASE(m_pNoAlphaBlend);

	SAFE_RELEASE(m_pSampleLinear);
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pConstantBuffer);
	SAFE_RELEASE(m_pPixelShader);
	SAFE_RELEASE(m_pVertexLayout);
	SAFE_RELEASE(m_pVertexShader);

	m_pContext11	= nullptr;
	m_pDevice11		= nullptr;

	SAFE_DELETE_ARRAY(m_pParticleArray);
}

//==================================================================.
//	HLSLファイルを読み込みシェーダを作成する.
//	HLSL : High Level Shading Language の略.
//==================================================================.
HRESULT CParticle::InitShader()
{
	ID3DBlob* pCompiledShader = nullptr;
	ID3DBlob* pErrors = nullptr;
	UINT	  uCompileFlag = 0;
#ifdef _DEBUG
	uCompileFlag =
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION;
#endif	//#ifdef _DEBUG.

	//HLSLからバーテックスシェーダのブロブを作成.
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
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{
			"POSITION",						//位置.
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,	//DXGIのフォーマット(32bit float型*3).
			0,
			0,								//データの開始位置.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		},
//		{
//			"TEXCOORD",						//テクスチャ位置.
//			0,
//			DXGI_FORMAT_R32G32_FLOAT,		//DXGIのフォーマット(32bit float型*2).
//			0,
//			12,								//データの開始位置←上のデータが4バイトが3つあるから12この開始位置は間違えてはいけない.
//			D3D11_INPUT_PER_VERTEX_DATA, 0
//		}

	};
	//頂点インプットレイアウトの配列要素数を算出.
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

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

	//HLSLからジオメトリシェーダのブロブを作成.
	if (FAILED(
		D3DX11CompileFromFile(
			SHADER_NAME,		//シェーダファイル名(HLSLファイル).
			nullptr,			//マクロ定義の配列へのポインタ(未使用).
			nullptr,			//インクルードファイルを扱うインターフェイスへのポインタ(未使用).
			"GS_Point",			//シェーダエントリーポイント関数の名前.
			"gs_5_0",			//シェーダのモデルを指定する文字列(プロファイル).
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
	SAFE_RELEASE(pErrors);

	//上記で作成したブロブから「ジオメトリシェーダ」を作成.
	if (FAILED(
		m_pDevice11->CreateGeometryShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_GeometryShader)))	//(out)ジオメトリシェーダ.
	{
		_ASSERT_EXPR(false, L"ジオメトリシェーダ作成失敗");
		return E_FAIL;
	}
	SAFE_RELEASE(pCompiledShader);

	//HLSLからピクセルシェーダのブロブを作成.
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
	//シェーダに特定の数値を送るバッファ.
	//ここでは変換行列渡し用.
	//シェーダに World, View, Projection 行列を渡す.
	D3D11_BUFFER_DESC cb;
	cb.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		//コンスタントバッファを指定.
	cb.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);	//コンスタントバッファのサイズ.
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;			//書き込みでアクセス.
	cb.MiscFlags = 0;								//その他のフラグ(未使用).
	cb.StructureByteStride = 0;								//構造体のサイズ().
	cb.Usage = D3D11_USAGE_DYNAMIC;				//使用方法：直接書き込み.

	//コンスタントバッファの作成.
	if (FAILED(
		m_pDevice11->CreateBuffer(
			&cb,
			nullptr,
			&m_pConstantBuffer)))
	{
		_ASSERT_EXPR(false, L"コンスタントバッファ作成失敗");
		return E_FAIL;
	}

	return S_OK;
}


//モデル作成.
HRESULT CParticle::InitModel()
{
	//頂点を作成.
	VERTEX vertices[] =
	{
		//頂点座標(x,y,z).
		D3DXVECTOR3(-0.5f, 0.5f, 0.0f),
	};
	//最大要素数を算出する.
	UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

	//バッファ構造体.
	D3D11_BUFFER_DESC bd;
	bd.Usage				= D3D11_USAGE_DEFAULT;		//使用方法(デフォルト).
	bd.ByteWidth			= sizeof(VERTEX) * uVerMax;	//頂点のサイズ.
	bd.BindFlags			= D3D11_BIND_VERTEX_BUFFER;	//頂点バッファとして扱う.
	bd.CPUAccessFlags		= 0;						//CPUからはアクセスしない.
	bd.MiscFlags			= 0;						//その他のフラグ(未使用).
	bd.StructureByteStride	= 0;						//構造体のサイズ(未使用).

	//サブリソースデータ構造体.
	D3D11_SUBRESOURCE_DATA InitData;
	InitData.pSysMem		= vertices;					//板ポリの頂点をセット.

	//頂点バッファの作成.
	if (FAILED(m_pDevice11->CreateBuffer(
		&bd, &InitData, &m_pVertexBuffer)))
	{
		_ASSERT_EXPR(false, L"頂点バッファ作成失敗");
		return E_FAIL;
	}

	//頂点バッファをセット.
	UINT stride = sizeof(VERTEX);	//データ間隔.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(
		0, 1,
		&m_pVertexBuffer, &stride, &offset);


	return S_OK;
}

//テクスチャ読み込み＆作成.
HRESULT CParticle::InitTexture(const char* fileName)
{
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

	//テクスチャ作成.
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,		//リソースを使用するデバイスのポインタ.
		fileName,			//ファイル名.
		nullptr, nullptr,
		&m_pTexture,		//(out)テクスチャ.
		nullptr)))
	{
		_ASSERT_EXPR(false, L"テクスチャ作成失敗");
		return E_FAIL;
	}


	return S_OK;
}

//レンダリング用.
void CParticle::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vCamPos)
{
	//ワールド行列.
	D3DXMATRIX mWorld, mScale, mRot, mTrans;
	D3DXMATRIX mYaw, mPitch, mRoll;

	//拡大・縮小.
	D3DXMatrixScaling(&mScale,
		m_Scale, m_Scale, m_Scale);

	//Y軸回転行列作成.
	D3DXMatrixRotationY(&mYaw, m_vRot.y);
	//X軸回転行列作成.
	D3DXMatrixRotationX(&mPitch, m_vRot.x);
	//Z軸回転行列作成.
	D3DXMatrixRotationZ(&mRoll, m_vRot.z);

	//平行移動.
	D3DXMatrixTranslation(&mTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	//回転行列を作成.
	mRot = mYaw * mPitch * mRoll;

	//ワールド行列.
	mWorld = mScale * mRot * mTrans;

	//使用するシェーダの登録.
	//使うシェーダをそれぞれ.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pContext11->GSSetShader(m_GeometryShader, nullptr, 0);
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);

	//シェーダのコンスタントバッファに各種データを渡す.
	D3D11_MAPPED_SUBRESOURCE	pData;
	SHADER_CONSTANT_BUFFER		cb;		//コンスタントバッファ.
	//バッファ内のデータの書き換え開始時にmap.
	if (SUCCEEDED(
		m_pContext11->Map(m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド，ビュー，プロジェクション行列を渡す.
		D3DXMATRIX m = mWorld * mView * mProj;
		D3DXMatrixTranspose(&m, &m);			//行列を転置する.
		cb.mWVP = m;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));

		m_pContext11->Unmap(m_pConstantBuffer, 0);
	}

	//このコンスタントバッファをどのシェーダで使うか？.
	//registarのb2の2と連動している.
	m_pContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->GSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//頂点バッファをセット.
	UINT stride = sizeof(VERTEX);	//データの間隔.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);

	//頂点インプットレイアウトをセット.
	m_pContext11->IASetInputLayout(m_pVertexLayout);
	//プリミティブ・トポロジーをセット.
	m_pContext11->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	//テクスチャーをシェーダに渡す.
	m_pContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pContext11->PSSetShaderResources(0, 1, &m_pTexture);

	//アルファブレンド有効にする.
	SetBlend(true);

	//プリミティブをレンダリング.
	//バックバッファにセットされる.
	m_pContext11->Draw(1, 0);	//ポイントスプライトなので頂点は1つ.
								//残りの頂点はシェーダで表示する.

	//ジオメトリシェーダを無効にする.
	m_pContext11->GSSetShader(nullptr, nullptr, 0);

	//アルファブレンド無効にする.
	SetBlend(false);
}



//シェーダを外す関数.
void CParticle::DetachShader() 
{
	//各シェーダをデタッチする.

	m_pContext11->VSSetShader(nullptr, nullptr, 0);	//頂点シェーダ.
	m_pContext11->HSSetShader(nullptr, nullptr, 0);	//ハルシェーダ.

	//～～～～～テッセレータ～～～～～～（上下の間処理）.

	m_pContext11->DSSetShader(nullptr, nullptr, 0);	//ドメインシェーダ.
	m_pContext11->GSSetShader(nullptr, nullptr, 0);	//ジオメトリシェーダ.

	//～～～～～～～ラスタライザ～～～～～(上下の間処理).

	m_pContext11->PSSetShader(nullptr, nullptr, 0);	//ピクセルシェーダ.
}

