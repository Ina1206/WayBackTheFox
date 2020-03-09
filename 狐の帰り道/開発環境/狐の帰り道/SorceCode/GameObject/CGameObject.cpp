#include "CGameObject.h"

/***************************************
*		ゲームオブジェクトクラス.
**/
CGameObject::CGameObject()
	: m_vLight					(0.0f, 0.0f, 0.0f)
	, m_vCameraPos				(0.0f, 0.0f, 0.0f)
	, m_mView					()
	, m_mProj					()
	, m_pCSEPlayManager			(nullptr)
	, m_pCEffectBase			(nullptr)
	, m_ppCEffectBase			(nullptr)
{
	//取得.
	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
}

CGameObject::~CGameObject()
{
}

//=====================================.
//		値設定処理関数.
//=====================================.
void CGameObject::Value_Set(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos)
{
	m_vLight		= vLight;
	m_vCameraPos	= vCameraPos;
	m_mView			= mView;
	m_mProj			= mProj;
}
