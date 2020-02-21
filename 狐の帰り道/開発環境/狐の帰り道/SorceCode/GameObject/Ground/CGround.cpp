#include "CGround.h"

CGround::CGround()
	: m_ppGround			(nullptr)
	, m_pvPos				(nullptr)
	, m_fScroll_Speed		(0.0f)
	, m_bDeceleration_Start	(false)
	, m_bMoveCamera			(false)
	, m_fMoving_Distance	(0.0f)
	, m_BackCnt				(0)
	, m_BackNum				(0)
	, m_fSwingUpMax			(0.0f)
	, m_vBossRot			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_enSwingType			(enSwingType::Up)
	, m_fUpDistance			(0.0f)
	, m_SwingCount			(0)
	, m_enInputDecision		(enInput_Decision::Max)
	, m_vGatePos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vInitGatePos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

CGround::~CGround()
{
	Release();
}

//=====================================.
//		初期化処理関数.
//=====================================.
void CGround::InitProcess()
{
	//要素数動的確保.
	m_ppGround	= new CDX9Mesh*[STAGE_MAX_BACK * STAGE_MAX_HORIZON];		//メッシュ.
	m_pvPos		= new D3DXVECTOR3[STAGE_MAX_BACK * STAGE_MAX_HORIZON];	//座標.
	//初期化.
	for (int stage = 0; stage < STAGE_MAX_BACK * STAGE_MAX_HORIZON; stage++) {
		m_ppGround[stage] = nullptr;
		m_pvPos[stage].x = ((stage % STAGE_MAX_HORIZON) * GROUND_WIDTH ) - GROUND_WIDTH;
		m_pvPos[stage].y = GROUND_HIGHT_ADJUSTMENT * (stage / STAGE_MAX_HORIZON);
		m_pvPos[stage].z = STAGE_START_POS +((stage / STAGE_MAX_HORIZON) * GROUND_WIDTH);
	}

	//スクロール速度.
	if (m_bMoveCamera == false) {
		m_fScroll_Speed = STANDERD_SPEED;
	}
	else {
		m_fScroll_Speed = UP_LOOK_SPEED;
	}
	//減速開始.
	m_bDeceleration_Start = false;
	//揺れる最大数.
	m_fSwingUpMax = SWING_UP_MAX;

	//一番後ろの番号の設定.
	m_BackNum = (STAGE_MAX_BACK * STAGE_MAX_HORIZON) - STAGE_MAX_HORIZON;

	//ゲートの初期位置.
	//m_vGatePos.z = GOAL_DISTANCE;
}

//=====================================.
//		更新処理関数.
//=====================================.
void CGround::Update()
{
	//全体の移動距離.
	m_fMoving_Distance += m_fScroll_Speed;

	//地面の移動.
	Move();

	//揺れる処理関数.
	if (m_enInputDecision == enInput_Decision::Bad) {
		if (m_vBossRot.x <= SWING_START_ROTATION && m_SwingCount <= SWING_MAX) {
			Swing();
			//地面を揺らす.
			for (int stage = 0; stage < STAGE_MAX_BACK * STAGE_MAX_HORIZON; stage++) {
				m_pvPos[stage].y = STANDERD_POS_HIGHT + m_fUpDistance;
			}
			//ゲートを揺らす.
			m_vGatePos.y = STANDERD_POS_HIGHT + m_fUpDistance;
		}
	}

}

//=====================================.
//		描画処理関数.
//=====================================.
void CGround::Render()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	
	////影の座標を少し高くする.
	////タイトルでは処理しない.
	//if (m_vPlayerShadowPos.z > 0) {
	//	m_vPlayerShadowPos.y += 0.9f;
	//	for (int enemy = 0; enemy < 9; enemy++) {
	//		m_pvEnemyShadowPos[enemy].y += 1.0f;
	//	}
	//}

	//-------地面--------//.
	for (int stage = 0; stage < STAGE_MAX_BACK *STAGE_MAX_HORIZON; stage++) {
		m_ppGround[stage] = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::AroundGround);
		//中央だけオブジェクトが違う.
		if (stage % STAGE_MAX_HORIZON == CENTER_GROUND_NUM) {
			m_ppGround[stage] = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Ground);
		}
		if (stage % 6 == 4) {
			m_ppGround[stage] = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Ground2);
		}
		//確認.
		_ASSERT_EXPR(m_ppGround[stage] != nullptr, L"m_pGround == nullptr");
		//描画での設定.
		//大きさ.
		m_ppGround[stage]->SetScale(SCALE_SIZE);									//大きさ.
		//座標.
		m_ppGround[stage]->SetPosition(m_pvPos[stage]);								//座標.
		//角度.
		m_ppGround[stage]->SetRotation(D3DXVECTOR3(0.0f, STANDERD_ROT_Y, 0.0f));	//角度.
		//影.
		//タイトルは処理しない.
		//if (m_vPlayerShadowPos.z > 0) {
		//	SHADOW m_shadow[10];
		//	m_shadow[0] = { m_vPlayerShadowPos, true };
		//	for (int enemy = 0; enemy < 9; enemy++) {
		//		m_shadow[enemy + 1] = { m_pvEnemyShadowPos[enemy], true };
		//		if (m_pvEnemyShadowPos[enemy].y > 10) {
		//			m_shadow[enemy + 1].bDispFlag = false;
		//		}
		//	}

		//	
		//	//SHADOW m_ss[] = {
		//	//	{D3DXVECTOR3(m_vPlayerShadowPos), true},
		//	//	
		//	//};
		//	m_ppGround[stage]->SetShadow(m_shadow, 10);
		//}
		//描画.
		m_ppGround[stage]->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);
	}

	//-------鳥居--------//.
	if (m_vGatePos.z < GAET_DISP_DISTANCE) {
		m_pCGate = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Gate);
		_ASSERT_EXPR(m_pCGate != nullptr, L"m_pCGate == nullptr");
		m_pCGate->SetScale(SCALE_SIZE);
		m_pCGate->SetPosition(m_vGatePos);
		m_pCGate->SetRotation(D3DXVECTOR3(0.0f, 3.2f, 0.0f));
		m_pCGate->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);
	}
}

//=====================================.
//		解放処理関数.
//=====================================.
void CGround::Release()
{	

	//-----メッシュ------//.
	for (int stage = 0; stage < STAGE_MAX_BACK * STAGE_MAX_HORIZON; stage++) {
		if (m_ppGround[stage] != nullptr) {
			m_ppGround[stage] = nullptr;
		}
	}

	//要素数解放.
	SAFE_DELETE_ARRAY(m_pvPos);		//座標.
	SAFE_DELETE_ARRAY(m_ppGround);	//メッシュ.
}

//=====================================.
//		移動処理関数.
//=====================================.
void CGround::Move()
{
	for (int stage = 0; stage < STAGE_MAX_BACK * STAGE_MAX_HORIZON; stage++) {
		//移動速度.
		m_pvPos[stage].z -= m_fScroll_Speed;

		//戻る.
		if (m_pvPos[stage].z <= GROUND_BACK_POSITION) {
			
			if (m_BackCnt >= STAGE_MAX_HORIZON) {
				//一番奥にいる地面の番号を設定.
				m_BackNum = stage - STAGE_MAX_HORIZON;
				if (m_BackNum < 0) {
					m_BackNum = (STAGE_MAX_BACK * STAGE_MAX_HORIZON) - STAGE_MAX_HORIZON;
				}
				m_BackCnt = 0;
			}
			//後ろに移動.
			m_pvPos[stage].z = m_pvPos[m_BackNum].z + STAGE_DEPTH_WIDTH;
			m_BackCnt++;
		}
	}

	//スクロール速度.
	if (m_bDeceleration_Start == true) {
		ScrollSpeedDeceleration();
	}
	else {
		if (m_bMoveCamera == false) {
			//通常時の速度.
			m_fScroll_Speed = STANDERD_SPEED;
		}
		else {
			//上視点時の速度.
			m_fScroll_Speed = UP_LOOK_SPEED;
		}
	}

	//ゲートの移動.
	m_vGatePos.z = m_vInitGatePos.z - m_fMoving_Distance;
}

//=====================================.
//	スクロールスピードの減速処理関数.
//=====================================.
void CGround::ScrollSpeedDeceleration()
{
	//減速処理.
	if (m_fScroll_Speed > 0.0f) {
		m_fScroll_Speed -= SCROLL_DECELETARATION;
	}
	//負の数にならないように止める.
	else if (m_fScroll_Speed < 0.0f) {
		m_fScroll_Speed = 0.0f;
	}
}

//=====================================.
//		揺れる処理関数.
//=====================================.
void CGround::Swing()
{
	switch (m_enSwingType) {
		//上に上がる.
	case enSwingType::Up:
		m_fUpDistance += SWING_SPEED;
		//上限まで移動.
		if (m_fUpDistance > m_fSwingUpMax) {
			m_enSwingType = enSwingType::Down;
		}
		break;
		//下に下がる.
	case enSwingType::Down:
		m_fUpDistance -= SWING_SPEED;
		//下まで移動.
		if (m_fUpDistance < STANDERD_POS_HIGHT) {
			m_enSwingType = enSwingType::Up;
			//カウント.
			m_SwingCount++;
			//上に移動する最大数変更.
			m_fSwingUpMax = SWING_REDUCE_SPEED - (SWING_REDUCE_ADJU * (m_SwingCount/2));
		}
		break;
	}
}