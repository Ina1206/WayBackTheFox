#include "CEnemyBase.h"

CEnemyBase::CEnemyBase()
	: m_vPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vInitPos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vPlayerPos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vRot			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_fSpeed			(0.0f)
	, m_pCCommand_Base	(nullptr)
	, m_enCommandType	(enCommandType::Max)
	, m_bJudgePossible	(false)
	, m_LongPushCnt		(0)
	, m_bDispFlag		(false)
	, m_pCSEPlayManager	(nullptr)
{
	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
}

CEnemyBase::~CEnemyBase()
{
}

//============================================.
//		グラウンドの動きに合わせる処理関数.
//============================================.
void CEnemyBase::FitMoveGround()
{
	m_vPos.z -= m_fSpeed;
}

//============================================.
//		表示判定処理関数.
//============================================.
void CEnemyBase::DecisionDisp()
{
	//一定の距離まで来ると表示.
	if (m_vPos.z <= m_vPlayerPos.z + DISP_DISTANCE && m_vPos.z > -2.0f) {
		m_bDispFlag = true;
	}

	//画面外に敵が出ると非表示.
	if (m_bDispFlag == true) {
		if (m_vPos.z < -3.0f || m_vPos.y >= 10.0f) {
			m_bDispFlag = false;
			m_vPos = D3DXVECTOR3(0.0f, -5.0f, -3.0f);
		}
	}
}