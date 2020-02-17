#include "CDepth_Stencil.h"

CDepth_Stencil::CDepth_Stencil()
	: m_pDevice11				(nullptr)
	, m_pContext11				(nullptr)
	, m_pDepthStencilState		(nullptr)
	, m_pDepthStencilStateOff	(nullptr)
{
}

CDepth_Stencil::~CDepth_Stencil()
{
	//解放処理.
	Destroy();
}

//=============================================.
//		設定処理関数.
//=============================================.
HRESULT CDepth_Stencil::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	//深度テスト（Zテスト）を有効にする.
	D3D11_DEPTH_STENCIL_DESC	dsDesc;
	dsDesc.DepthEnable = TRUE;		//有効.
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = FALSE;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	//深度設定作成.
	if (FAILED(
		m_pDevice11->CreateDepthStencilState(
			&dsDesc, &m_pDepthStencilState)))
	{
		_ASSERT_EXPR(false, L"深度設定作成失敗");
		return E_FAIL;
	}
	//深度テスト(Zテスト)を無効にする.
	dsDesc.DepthEnable = FALSE;		//無効.
	//深度設定作成.
	if (FAILED(
		m_pDevice11->CreateDepthStencilState(
			&dsDesc, &m_pDepthStencilStateOff)))
	{
		_ASSERT_EXPR(false, L"深度設定作成失敗");
		return E_FAIL;
	}

	return S_OK;
}

//==============================================.
//		深度(Z)テストON/OFF切り替え.
//==============================================.
void CDepth_Stencil::SetDepth(bool flag)
{
	ID3D11DepthStencilState* pTmp = (flag == true) ? m_pDepthStencilState : m_pDepthStencilStateOff;

	//深度設定をセット.
	m_pContext11->OMSetDepthStencilState(pTmp, 1);
}

//==============================================.
//		解放処理.
//==============================================.
void CDepth_Stencil::Destroy()
{
	SAFE_RELEASE(m_pDepthStencilStateOff);
	SAFE_RELEASE(m_pDepthStencilState);

	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
}