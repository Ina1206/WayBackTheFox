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
//	Blend‚Ì‰Šú‰».
//===================================.
HRESULT CCommon::InitBlend()
{
	//±ÙÌ§ÌÞÚÝÄÞ—pÌÞÚÝÄÞ½Ã°Ä\‘¢‘Ì.
	//pngÌ§²Ù“à‚É±ÙÌ§î•ñ‚ª‚ ‚é‚Ì‚ÅA“§‰ß‚·‚é‚æ‚¤‚ÉÌÞÚÝÄÞ½Ã°Ä‚ÅÝ’è‚·‚é.
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));	//‰Šú‰».

	BlendDesc.IndependentBlendEnable
		= false;									//false:RenderTarget[0]‚ÌÒÝÊÞ°‚Ì‚ÝŽg—p‚·‚é.
													//true:RenderTarget[0`7]‚ªŽg—p‚Å‚«‚é
													// (ÚÝÀÞ°À°¹Þ¯Ä–ˆ‚É“Æ—§‚µ‚½ÌÞÚÝÄÞˆ—).
	BlendDesc.AlphaToCoverageEnable
		= false;									//true:±ÙÌ§Ä©¶ÊÞÚ°¼Þ‚ðŽg—p‚·‚é.
	BlendDesc.RenderTarget[0].BlendEnable
		= true;										//true:±ÙÌ§ÌÞÚÝÄÞ‚ðŽg—p‚·‚é.
	BlendDesc.RenderTarget[0].SrcBlend				//Œ³‘fÞ‚É‘Î‚·‚éÝ’è.
		= D3D11_BLEND_SRC_ALPHA;					//±ÙÌ§ÌÞÚÝÄÞ‚ðŽw’è.
	BlendDesc.RenderTarget[0].DestBlend				//d‚Ë‚é‘fÞ‚É‘Î‚·‚éÝ’è.
		= D3D11_BLEND_INV_SRC_ALPHA;				//±ÙÌ§ÌÞÚÝÄÞ‚Ì”½“]‚ðŽw’è.
	BlendDesc.RenderTarget[0].BlendOp				//ÌÞÚÝÄÞµÌß¼®Ý.
		= D3D11_BLEND_OP_ADD;						//ADD:‰ÁŽZ‡¬.
	BlendDesc.RenderTarget[0].SrcBlendAlpha			//Œ³‘fÞ‚Ì±ÙÌ§‚É‘Î‚·‚éŽw’è.
		= D3D11_BLEND_ONE;							//‚»‚Ì‚Ü‚ÜŽg—p.
	BlendDesc.RenderTarget[0].DestBlendAlpha		//d‚Ë‚é‘fÞ‚Ì±ÙÌ§‚É‘Î‚·‚éÝ’è.
		= D3D11_BLEND_ZERO;							//‰½‚à‚µ‚È‚¢B
	BlendDesc.RenderTarget[0].BlendOpAlpha			//±ÙÌ§‚ÌÌÞÚÝÄÞµÌß¼®Ý.
		= D3D11_BLEND_OP_ADD;						//ADD:‰ÁŽZ‡¬.
	BlendDesc.RenderTarget[0].RenderTargetWriteMask	//Ëß¸¾Ù–ˆ‚Ì‘‚«ž‚ÝÏ½¸.
		= D3D11_COLOR_WRITE_ENABLE_ALL;				//‘S‚Ä‚Ì¬•ª(RGBA)‚Ö‚ÌÃÞ°À‚ÌŠi”[‚ð‹–‰Â‚·‚é.

	//ÌÞÚÝÄÞ½Ã°Äì¬.
	if (FAILED(
		m_pDevice11->CreateBlendState(
			&BlendDesc, &m_pAlphaBlend)))
	{
		_ASSERT_EXPR(false, L"ÌÞÚÝÄÞ½Ã°Äì¬Ž¸”s");
		return E_FAIL;
	}

	//ÌÞÚÝÄÞ½Ã°Äì¬.
	BlendDesc.RenderTarget[0].BlendEnable
		= false;		//true:±ÙÌ§ÌÞÚÝÄÞ‚ðŽg—p‚µ‚È‚¢.
	if (FAILED(
		m_pDevice11->CreateBlendState(
			&BlendDesc, &m_pNoAlphaBlend)))
	{
		_ASSERT_EXPR(false, L"ÌÞÚÝÄÞ½Ã°Äì¬Ž¸”s");
		return E_FAIL;
	}

	return S_OK;
}

//==============================.
//		“§‰ßÝ’è‚ÌØ‚è‘Ö‚¦.
//==============================.
void CCommon::SetBlend(bool EnableAlpha)
{
	//ÌÞÚÝÄÞ½Ã°Ä‚ÌÝ’è.
	UINT mask = 0xffffffff;	//Ï½¸’l.
	if (EnableAlpha == true) {
		m_pContext11->OMSetBlendState(
			m_pAlphaBlend, nullptr, mask);
	}
	else {
		m_pContext11->OMSetBlendState(
			m_pNoAlphaBlend, nullptr, mask);
	}
}
