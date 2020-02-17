#include"CUI_Base.h"

bool g_BranOpenFlag = false;

CUI_Base::CUI_Base		 ()
	: m_mView			 ()
	, m_mProj			 ()
	, m_vCameraPos		 ()
	, m_pCResourceManager(nullptr)
	, m_pCDepth_Stencil	 (nullptr)
	, m_vPos			 (D3DXVECTOR3(0.0f,0.0f,0.0f))
	, m_PointSum		 (0)
	, m_bMoveEndFlag(false)

{
}

CUI_Base::~CUI_Base()
{
	if (m_pCDepth_Stencil != nullptr)
	{
		m_pCDepth_Stencil = nullptr;
	}
	if (m_pCResourceManager != nullptr)
	{
		m_pCResourceManager = nullptr;
	}
}

//============================================.
//		�l�ݒ菈���֐�.
//============================================.
void CUI_Base::Value_Set(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	//�ǂݍ��݃N���X.
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	//�f�v�X�X�e���V���N���X.
	m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();

	m_mView			= mView;
	m_mProj			= mProj;
	m_vCameraPos	= vCamePos;
}
