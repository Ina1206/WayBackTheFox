#include "CCommon.h"

CCommon::CCommon()
	: m_pDevice11(nullptr)
	, m_pContext11(nullptr)
	, m_pAlphaBlend(nullptr)
	, m_pNoAlphaBlend(nullptr)
{
}

CCommon::~CCommon()
{
	SAFE_RELEASE(m_pNoAlphaBlend);
	SAFE_RELEASE(m_pAlphaBlend);
	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
}

//===================================.
//	Blendの初期化.
//===================================.
HRESULT CCommon::InitBlend()
{
	//ｱﾙﾌｧﾌﾞﾚﾝﾄﾞ用ﾌﾞﾚﾝﾄﾞｽﾃｰﾄ構造体.
	//pngﾌｧｲﾙ内にｱﾙﾌｧ情報があるので、透過するようにﾌﾞﾚﾝﾄﾞｽﾃｰﾄで設定する.
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));	//初期化.

	BlendDesc.IndependentBlendEnable
		= false;									//false:RenderTarget[0]のﾒﾝﾊﾞｰのみ使用する.
													//true:RenderTarget[0〜7]が使用できる
													// (ﾚﾝﾀﾞｰﾀｰｹﾞｯﾄ毎に独立したﾌﾞﾚﾝﾄﾞ処理).
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

//==============================.
//		透過設定の切り替え.
//==============================.
void CCommon::SetBlend(bool EnableAlpha)
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
