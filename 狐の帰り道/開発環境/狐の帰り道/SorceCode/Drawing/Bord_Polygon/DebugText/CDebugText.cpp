#include "CDebugText.h"
#include <crtdbg.h>

//シェーダファイル名.
const char SHADER_NAME[] = "Data\\Shader\\DebugText.hlsl";

//コンストラクタ.
CDebugText::CDebugText()
	: m_pDevice11		(nullptr)
	, m_pContext11		(nullptr)
	, m_pVertexShader	(nullptr)
	, m_pVertexLayout	(nullptr)
	, m_pPixelShader	(nullptr)
	, m_pConstantBuffer	(nullptr)
	, m_pVertexBuffer	()
	, m_pSampleLinear	(nullptr)
	, m_pAsciiTexture	(nullptr)
	, m_pAlphaBlend		(nullptr)
	, m_pNoAlphaBlend	(nullptr)
	, m_fKerning		()
	, m_fAlpha			(0.0f)
	, m_fScale			(1.0f)
	, m_vColor			(0.0f, 0.0f, 0.0f, 0.0f)
	, m_vPos			()
{
}

//デストラクタ.
CDebugText::~CDebugText()
{
}

//初期化関数.
HRESULT CDebugText::Init(ID3D11DeviceContext* pContext11,
	DWORD Width, DWORD Height,
	float Scale, D3DXVECTOR4 vColor)
{
	m_fAlpha = vColor.w;
	m_vColor = vColor;
	m_fScale = Scale / 25.0f;

	//95文字分繰り返し.
	for (int i = 0; i < 95; i++) {
		m_fKerning[i] = 10.0f;
	}
	//デバイスコンテキストをコピー.
	m_pContext11 = pContext11;
	//デバイスコンテキストからデバイスを取得.
	m_pContext11->GetDevice(&m_pDevice11);

	//Windowsサイズ.
	m_dwWindowHeight = Height;
	m_dwWindowWidth  = Width;

	//===フォント毎にクアッド（矩形）作成===.
	float left = 0.0f, top = 0.0f, right = 0.0f, bottom = 0.0f;
	int cnt = 0;
	//2重ループで1文字ずつ指定する.
	for (int k = 0; k < 10; k++) {
		for (int i = 0; i < 10; i++) {
			left	= k * WDIMENSION;
			top		= i * DIMENSION;
			right	= left + m_fKerning[cnt];
			bottom	= top + DIMENSION;

			left	/= TEX_DIMENSION;
			top		/= TEX_DIMENSION;
			right	/= TEX_DIMENSION;
			bottom	/= TEX_DIMENSION;

			VERTEX vertices[] = 
			{
				D3DXVECTOR3(0.0f,       DIMENSION, 0.0f), D3DXVECTOR2(left, bottom),
				D3DXVECTOR3(0.0f, 		0.0f,	   0.0f), D3DXVECTOR2(left, top),
				D3DXVECTOR3(WDIMENSION, DIMENSION, 0.0f), D3DXVECTOR2(right, bottom),
				D3DXVECTOR3(WDIMENSION, 0.0f,      0.0f), D3DXVECTOR2(right, top),
			};

			//最大要素数を算出する.
			UINT uVerMax = sizeof(vertices) / sizeof(vertices[0]);

			//バッファ構造体.
			D3D11_BUFFER_DESC bd;
			bd.Usage = D3D11_USAGE_DEFAULT;				//使用方法(デフォルト).
			bd.ByteWidth = sizeof(VERTEX) * uVerMax;	//頂点のサイズ.
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;	//頂点バッファとして扱う.
			bd.CPUAccessFlags = 0;						//CPUからはアクセスしない.
			bd.MiscFlags = 0;							//その他のフラグ(未使用).
			bd.StructureByteStride = 0;					//構造体のサイズ(未使用).

			//サブリソースデータ構造体.
			D3D11_SUBRESOURCE_DATA InitData;
			InitData.pSysMem = vertices;				//板ポリの頂点をセット.

			//頂点バッファの作成.
			if (FAILED(m_pDevice11->CreateBuffer(
				&bd, &InitData, &m_pVertexBuffer[cnt])))
			{
				_ASSERT_EXPR(false, L"頂点バッファ作成失敗");
				return E_FAIL;
			}
			cnt++;
		}
	}

	//テクスチャ用のサンプラ構造体.
	D3D11_SAMPLER_DESC	samDesc;
	ZeroMemory(&samDesc, sizeof(samDesc));
	samDesc.Filter	 = D3D11_FILTER_MIN_MAG_MIP_POINT;	//POINT:高速だが粗い.
	samDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		//ラッピングモード(WRAP:繰り返し).
	samDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	//サンプラ作成.
	if (FAILED(m_pDevice11->CreateSamplerState(
		&samDesc, &m_pSampleLinear)))					//(out)サンプラ.
	{
		_ASSERT_EXPR(false, L"サンプラ作成失敗");
		return E_FAIL;
	}

	//テクスチャ作成.
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice11,									//リソースを使用するデバイスのポインタ.
		"Data\\Texture\\DebugText\\ascii.png",			//ファイル名.
		nullptr, nullptr,
		&m_pAsciiTexture,								//(out)テクスチャ.
		nullptr)))
	{
		_ASSERT_EXPR(false, L"テクスチャ作成失敗");
		return E_FAIL;
	}

	//シェーダ作成.
	if (FAILED(InitShader())) {
		return E_FAIL;
	}
	//ブレンドステート作成.
	if (FAILED(InitBlend())) {
		return E_FAIL;
	}

	return S_OK;
}

//==================================================================.
//	HLSLファイルを読み込みシェーダを作成する.
//	HLSL : High Level Shading Language の略.
//==================================================================.
HRESULT CDebugText::InitShader()
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
		{
			"TEXCOORD",						//テクスチャ位置.
			0,
			DXGI_FORMAT_R32G32_FLOAT,		//DXGIのフォーマット(32bit float型*2).
			0,
			12,								//データの開始位置←上のデータが4バイトが3つあるから12この開始位置は間違えてはいけない.
			D3D11_INPUT_PER_VERTEX_DATA, 0
		}

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
	cb.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		//書き込みでアクセス.
	cb.MiscFlags = 0;								//その他のフラグ(未使用).
	cb.StructureByteStride = 0;						//構造体のサイズ().
	cb.Usage = D3D11_USAGE_DYNAMIC;					//使用方法：直接書き込み.

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

HRESULT CDebugText::InitBlend()
{
	//ｱﾙﾌｧﾌﾞﾚﾝﾄﾞ用ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ構造体.
	//pngﾌｧｲﾙ内にｱﾙﾌｧ情報があるので、透過するようにﾌﾞﾚﾝﾄﾞｽﾃｰﾄで設定する.
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));	//初期化.

	BlendDesc.IndependentBlendEnable
		= false;
	BlendDesc.AlphaToCoverageEnable
		= false;									//true:ｱﾙﾌｧﾄｩｶﾊﾞﾚｰｼﾞを使用する.
	BlendDesc.RenderTarget[0].BlendEnable
		= true;										//true:ｱﾙﾌｧﾌﾞﾚﾝﾄﾞを使用する.
	BlendDesc.RenderTarget[0].SrcBlend				//元素材に対する設定.
		= D3D11_BLEND_SRC_ALPHA;					//ｱﾙﾌｧﾌﾞﾚﾝﾄﾞを指定.
	BlendDesc.RenderTarget[0].DestBlend				//重ねる素材に対する設定.
		= D3D11_BLEND_INV_SRC_ALPHA;				//ｱﾙﾌｧﾌﾞﾚﾝﾄﾞの反転を指定.
	BlendDesc.RenderTarget[0].BlendOp				//ﾌﾞﾚﾝﾄﾞｵﾌﾟｼｮﾝ.
		= D3D11_BLEND_OP_ADD;						//ADD:加算合成.
	BlendDesc.RenderTarget[0].SrcBlendAlpha			//元素材のｱﾙﾌｧに対する指定.
		= D3D11_BLEND_ONE;							//そのまま使用.
	BlendDesc.RenderTarget[0].DestBlendAlpha		//重ねる素材のｱﾙﾌｧに対する設定.
		= D3D11_BLEND_ZERO;							//何もしない。
	BlendDesc.RenderTarget[0].BlendOpAlpha			//ｱﾙﾌｧのﾌﾞﾚﾝﾄﾞｵﾌﾟｼｮﾝ.
		= D3D11_BLEND_OP_ADD;						//ADD:加算合成.
	BlendDesc.RenderTarget[0].RenderTargetWriteMask	//ﾋﾟｸｾﾙ毎の書き込みﾏｽｸ.
		= D3D11_COLOR_WRITE_ENABLE_ALL;				//全ての成分(RGBA)へのﾃﾞｰﾀの格納を許可する.

	//ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ作成.
	if (FAILED(
		m_pDevice11->CreateBlendState(
			&BlendDesc, &m_pAlphaBlend)))
	{
		_ASSERT_EXPR(false, L"ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ作成失敗");
		return E_FAIL;
	}

	//ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ作成.
	BlendDesc.RenderTarget[0].BlendEnable
		= false;		//true:ｱﾙﾌｧﾌﾞﾚﾝﾄﾞを使用しない.
	if (FAILED(
		m_pDevice11->CreateBlendState(
			&BlendDesc, &m_pNoAlphaBlend)))
	{
		_ASSERT_EXPR(false, L"ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ作成失敗");
		return E_FAIL;
	}

	return S_OK;
}

//透過設定の切り替え.
void CDebugText::SetBlend(bool EnableAlpha)
{
	//ﾌﾞﾚﾝﾄﾞｽﾃｰﾄの設定.
	UINT mask = 0xffffffff;	//ﾏｽｸ値.
	if (EnableAlpha == true) {
		m_pContext11->OMSetBlendState(
			m_pAlphaBlend, nullptr, mask);
	}
	else {
		m_pContext11->OMSetBlendState(
			m_pNoAlphaBlend, nullptr, mask);
	}
}

//レンダリング関数.
void CDebugText::Render(const char* text, int x, int y)
{
	//ビュートランスフォーム.
	D3DXVECTOR3 vEye (0.0f, 0.0f, -1.0f);
	D3DXVECTOR3 vLook(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUp	 (0.0f, 1.0f, 0.0f);
	D3DXMatrixLookAtLH(
		&m_mView, &vEye, &vLook, &vUp);

#if 0
	//プロジェクショントランスフォーム(固定).
	D3DMATRIX mOtho = {
		2.0f / static_cast<float>(m_dwWindowWidth), 0.0f, 0.0f, 0.0f,
		0.0f, -2.0f / static_cast<float>(m_dwWindowHeight), 0.0f, 0.0f,
		0.0f,  0.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f, 1.0f
	};
#else
	D3DXMATRIX mOtho;
	D3DXMatrixIdentity(&mOtho);		//単位行列作成.
	mOtho._11 =  2.0f / static_cast<float>(m_dwWindowWidth);
	mOtho._22 = -2.0f / static_cast<float>(m_dwWindowHeight);
	mOtho._41 = -1.0f;
	mOtho._42 =  1.0f;
#endif
	m_mProj = mOtho;

	//プリミティブ・トポロジー.
	m_pContext11->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//頂点インプットレイアウトをセット.
	m_pContext11->IASetInputLayout(m_pVertexLayout);

	//使用するシェーダの登録.
	m_pContext11->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pContext11->PSSetShader(m_pPixelShader, nullptr, 0);

	//コンスタントバッファを登録.
	m_pContext11->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pContext11->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//サンプラとテクスチャをピクセルシェーダに渡す.
	m_pContext11->PSSetSamplers(0, 1, &m_pSampleLinear);
	m_pContext11->PSSetShaderResources(0, 1, &m_pAsciiTexture);

	//文字数分ループ.
	for (int i = 0; i < static_cast<int>(strlen(text)); i++) 
	{
		char font = text[i];
		int index = font - 32;	//フォントインデックス作成.

		//フォントレンダリング.
		RenderFont(index, x, y);
		x += static_cast<int>(m_fKerning[index]);
	}
}

//フォントレンダリング関数.
void CDebugText::RenderFont(int FontIndex, int x, int y)
{
	//ワールド変換.
	D3DXMATRIX mWorld;
	D3DXMatrixIdentity(&mWorld);
	D3DXMatrixTranslation(&mWorld, static_cast<FLOAT>(x), static_cast<FLOAT>(y), -100.0f);

	//シェーダのコンスタントバッファに各種データを渡す.
	D3D11_MAPPED_SUBRESOURCE	pData;
	SHADER_CONSTANT_BUFFER		cb;		//コンスタントバッファ.

	//バッファ内のデータの書き換え開始時にmap.
	if (SUCCEEDED(
		m_pContext11->Map(m_pConstantBuffer,
			0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		//ワールド，ビュー，プロジェクション行列を渡す.
		D3DXMATRIX m = mWorld * m_mView * m_mProj;
		D3DXMatrixTranspose(&m, &m);			//行列を転置する.
		cb.mWVP = m;

		//カラー.
		cb.vColor = m_vColor;

		//透過値.
		cb.fAlpha.x = m_fAlpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&cb), sizeof(cb));

		m_pContext11->Unmap(m_pConstantBuffer, 0);
	}

	//頂点バッファをセット.
	UINT stride = sizeof(VERTEX);	//データの間隔.
	UINT offset = 0;
	m_pContext11->IASetVertexBuffers(0, 1, &m_pVertexBuffer[FontIndex], &stride, &offset);

	SetBlend(true);
	//描画.
	m_pContext11->Draw(4, 0);

	SetBlend(false);

}