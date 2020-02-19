#include "CCameraManager.h"

CCameraManager::CCameraManager()
	: m_pCCamera			(nullptr)
	, m_vPos				(0.0f, 0.0f, 0.0f)
	, m_mView				()
	, m_bLongPush			(false)
	, m_bOldLongPush		(false)
	, m_enInput_Decision	(enInput_Decision::Max)
	, m_enOldInput_Decision	(enInput_Decision::Max)
	, m_bChangeMove			(false)
	, m_vTargetPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//開始時は標準カメラで.
	m_pCCamera = new CStanderdCamera();
}

CCameraManager::~CCameraManager()
{
	Release();
}

//================================.
//		カメラ変更処理関数.
//================================.
void CCameraManager::ChangeCamera()
{
	//==================長押し時のカメラ移動====================//.
	if (m_bLongPush != m_bOldLongPush) {
		//長押ししたときにカメラが上に移動するクラスへ.
		if (m_bLongPush == true) {
			SAFE_DELETE(m_pCCamera);
			m_pCCamera = new CUpCamera();
		}
	}

	//===================ボス戦時のカメラ移動====================//.
	if (m_enInput_Decision == enInput_Decision::Bad && m_enInput_Decision != m_enOldInput_Decision) {
		SAFE_DELETE(m_pCCamera);
		m_pCCamera = new CBossBadCamera();
	}
	if (m_enInput_Decision == enInput_Decision::Great && m_enInput_Decision != m_enOldInput_Decision) {
		SAFE_DELETE(m_pCCamera);
		m_pCCamera = new CBossGreatCamera();
	}

	//======================通常時のクラスへ=====================//.
	if (m_pCCamera->GetCameraChangeFlag() == true && m_enInput_Decision == enInput_Decision::Max) {
		SAFE_DELETE(m_pCCamera);
		m_pCCamera = new CStanderdCamera();
	}

	//フラグ差分.
	m_bOldLongPush = m_bLongPush;				//長押し用フラグ.
	m_enOldInput_Decision = m_enInput_Decision;	//判定処理.
}

//================================.
//		更新処理関数.
//================================.
void CCameraManager::UpDate()
{
	//ビュー行列変換処理関数.
	m_pCCamera->Change_mView();

	m_pCCamera->SetTargetPos(m_vTargetPos);
	m_pCCamera->UpDate(m_bChangeMove);

	//値取得.
	m_vPos = m_pCCamera->GetCameraPos();
	m_mView = m_pCCamera->GetMATRIX_View();
}

//================================.
//		解放処理関数.
//================================.
void CCameraManager::Release()
{
	SAFE_DELETE(m_pCCamera);
}