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
//	Blend�̏�����.
//===================================.
HRESULT CCommon::InitBlend()
{
	//��̧�����ޗp�����޽ðč\����.
	//pnģ�ٓ��ɱ�̧��񂪂���̂ŁA���߂���悤�������޽ðĂŐݒ肷��.
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));	//������.

	BlendDesc.IndependentBlendEnable
		= false;									//false:RenderTarget[0]�����ް�̂ݎg�p����.
													//true:RenderTarget[0�`7]���g�p�ł���
													// (���ް���ޯĖ��ɓƗ����������ޏ���).
	BlendDesc.AlphaToCoverageEnable
		= false;									//true:��̧ĩ���ڰ�ނ��g�p����.
	BlendDesc.RenderTarget[0].BlendEnable
		= true;										//true:��̧�����ނ��g�p����.
	BlendDesc.RenderTarget[0].SrcBlend				//���f�ނɑ΂���ݒ�.
		= D3D11_BLEND_SRC_ALPHA;					//��̧�����ނ��w��.
	BlendDesc.RenderTarget[0].DestBlend				//�d�˂�f�ނɑ΂���ݒ�.
		= D3D11_BLEND_INV_SRC_ALPHA;				//��̧�����ނ̔��]���w��.
	BlendDesc.RenderTarget[0].BlendOp				//�����޵�߼��.
		= D3D11_BLEND_OP_ADD;						//ADD:���Z����.
	BlendDesc.RenderTarget[0].SrcBlendAlpha			//���f�ނ̱�̧�ɑ΂���w��.
		= D3D11_BLEND_ONE;							//���̂܂܎g�p.
	BlendDesc.RenderTarget[0].DestBlendAlpha		//�d�˂�f�ނ̱�̧�ɑ΂���ݒ�.
		= D3D11_BLEND_ZERO;							//�������Ȃ��B
	BlendDesc.RenderTarget[0].BlendOpAlpha			//��̧�������޵�߼��.
		= D3D11_BLEND_OP_ADD;						//ADD:���Z����.
	BlendDesc.RenderTarget[0].RenderTargetWriteMask	//�߸�ٖ��̏�������Ͻ�.
		= D3D11_COLOR_WRITE_ENABLE_ALL;				//�S�Ă̐���(RGBA)�ւ��ް��̊i�[��������.

	//�����޽ðč쐬.
	if (FAILED(
		m_pDevice11->CreateBlendState(
			&BlendDesc, &m_pAlphaBlend)))
	{
		_ASSERT_EXPR(false, L"�����޽ðč쐬���s");
		return E_FAIL;
	}

	//�����޽ðč쐬.
	BlendDesc.RenderTarget[0].BlendEnable
		= false;		//true:��̧�����ނ��g�p���Ȃ�.
	if (FAILED(
		m_pDevice11->CreateBlendState(
			&BlendDesc, &m_pNoAlphaBlend)))
	{
		_ASSERT_EXPR(false, L"�����޽ðč쐬���s");
		return E_FAIL;
	}

	return S_OK;
}

//==============================.
//		���ߐݒ�̐؂�ւ�.
//==============================.
void CCommon::SetBlend(bool EnableAlpha)
{
	//�����޽ðĂ̐ݒ�.
	UINT mask = 0xffffffff;	//Ͻ��l.
	if (EnableAlpha == true) {
		m_pContext11->OMSetBlendState(
			m_pAlphaBlend, nullptr, mask);
	}
	else {
		m_pContext11->OMSetBlendState(
			m_pNoAlphaBlend, nullptr, mask);
	}
}
