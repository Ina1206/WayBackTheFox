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
	//�������.
	Destroy();
}

//=============================================.
//		�ݒ菈���֐�.
//=============================================.
HRESULT CDepth_Stencil::Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pDevice11 = pDevice11;
	m_pContext11 = pContext11;

	//�[�x�e�X�g�iZ�e�X�g�j��L���ɂ���.
	D3D11_DEPTH_STENCIL_DESC	dsDesc;
	dsDesc.DepthEnable = TRUE;		//�L��.
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	dsDesc.StencilEnable = FALSE;
	dsDesc.StencilReadMask = D3D11_DEFAULT_STENCIL_READ_MASK;
	dsDesc.StencilWriteMask = D3D11_DEFAULT_STENCIL_WRITE_MASK;

	//�[�x�ݒ�쐬.
	if (FAILED(
		m_pDevice11->CreateDepthStencilState(
			&dsDesc, &m_pDepthStencilState)))
	{
		_ASSERT_EXPR(false, L"�[�x�ݒ�쐬���s");
		return E_FAIL;
	}
	//�[�x�e�X�g(Z�e�X�g)�𖳌��ɂ���.
	dsDesc.DepthEnable = FALSE;		//����.
	//�[�x�ݒ�쐬.
	if (FAILED(
		m_pDevice11->CreateDepthStencilState(
			&dsDesc, &m_pDepthStencilStateOff)))
	{
		_ASSERT_EXPR(false, L"�[�x�ݒ�쐬���s");
		return E_FAIL;
	}

	return S_OK;
}

//==============================================.
//		�[�x(Z)�e�X�gON/OFF�؂�ւ�.
//==============================================.
void CDepth_Stencil::SetDepth(bool flag)
{
	ID3D11DepthStencilState* pTmp = (flag == true) ? m_pDepthStencilState : m_pDepthStencilStateOff;

	//�[�x�ݒ���Z�b�g.
	m_pContext11->OMSetDepthStencilState(pTmp, 1);
}

//==============================================.
//		�������.
//==============================================.
void CDepth_Stencil::Destroy()
{
	SAFE_RELEASE(m_pDepthStencilStateOff);
	SAFE_RELEASE(m_pDepthStencilState);

	m_pContext11 = nullptr;
	m_pDevice11 = nullptr;
}