#include "CItem_Base.h"

CItem_Base::CItem_Base()
	: m_mView()
	, m_mProj()
	, m_vCameraPos()
	, m_pCResourceManager	(nullptr)
	, m_pCSprite			(nullptr)
	, m_pCDepth_Stencil		(nullptr)
	, m_vPos				(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vInitPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vPlayerPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vIconPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_enInputDecision		(enInput_Decision::Max)
	, m_enItemJudge			(enItemJudge::Max)
	, m_DropNum				(0)
	, m_CollitionNum		(0)
	, m_bDispFlag			(false)
	, m_Sum					(0)
	, m_Point				(0)
	, m_BossFlag			(false)
	, m_bCheckBossFlag		(false)
{
}

CItem_Base::~CItem_Base()
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
//		値設定処理関数.
//============================================.
void CItem_Base::Value_Set(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	//読み込みクラス.
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	//デプスステンシルクラス.
	m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();

	m_mView = mView;
	m_mProj = mProj;
	m_vCameraPos = vCamePos;
}

