#include "CEffectBase.h"

/***********************************************
*		エフェクト元クラス.
**/
CEffectBase::CEffectBase()
	: m_vCenterPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_pvPos				(nullptr)
	, m_pvRot				(nullptr)
	, m_pfScale				(nullptr)
	, m_bDispFlag			(false)
	, m_bOldDispFlag		(false)
	, m_ppCSprite			(nullptr)
	, m_pCResourceManager	(nullptr)
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
}

CEffectBase::~CEffectBase()
{
}

