#include "CBossGreatCamera.h"

CBossGreatCamera::CBossGreatCamera()
	: m_enCameraType		(enCameraType::Boss)
	, m_vOldTargetPos		(0.0f, 0.0f, 0.0f)
	, m_fCameraChangeBefore	(0.0f, 0.0f, 0.0f)
	, m_fTargetLook			(0.0f)
	, m_WaitTime			(0)
	, m_vSwingBeforePos		(0.0f, 0.0f, 0.0f)
	, m_vSwingBeforeLook	(0.0f, 0.0f, 0.0f)
	, m_SwingDirection		(UP_DIRECTION_NUM)
	, m_SwingDistanceMax	(START_SWING_MAX)
	, m_bSwingFinish		(false)
	, m_bCenterPassing		(false)
{
	//カメラの初期位置.
	m_Camera.vLook		= CAMERA_LOOK;
	m_Camera.vPos		= STANDERD_CAMERA_POS;
	//揺れる前のカメラ位置.
	m_vSwingBeforePos	= m_Camera.vPos;
}

CBossGreatCamera::~CBossGreatCamera()
{
}

//======================================.
//		更新処理関数.
//======================================.
void CBossGreatCamera::UpDate(bool CameraFlag)
{
	//移動処理関数.
	Move();
}

//======================================.
//		移動処理関数.
//======================================.
void CBossGreatCamera::Move()
{	
	//カメラの種類ごとに見るものの変更.
	switch (m_enCameraType) {
	//ボスを見ているとき.
	case enCameraType::Boss:
		//ボスが飛ぶ時のカメラ移動.
		BossFlyMove();
		break;
	//プレイヤーを見ているとき.
	case enCameraType::Player:
		//プレイヤーを見るカメラ移動.
		PlayerLook();
		break;
	//カメラを戻す.
	case enCameraType::Return:
		//戻る処理関数.
		Return();
		break;
	}
}

//======================================.
//		戻る処理関数.
//======================================.
void CBossGreatCamera::Return()
{
	//カメラ移動.
	m_Camera.vPos.y += (STANDERD_CAMERA_POS.y / m_fTargetLook) * RETURN_SPEED;
	//注視点移動.
	m_Camera.vLook.y -= RETURN_SPEED;
	//次のカメラ移動へ.
	if (m_Camera.vPos.y > STANDERD_CAMERA_POS.y) {
		//値を設定しておく.
		m_Camera.vPos = STANDERD_CAMERA_POS;
		m_Camera.vLook = CAMERA_LOOK;
		
		//少し待つ.
		m_WaitTime++;
		if (m_WaitTime > WAIT_TIME) {
			//Playerを見るカメラへ.
			m_enCameraType = enCameraType::Player;
		}

	}
}

//======================================.
//		ボスが飛ぶ時のカメラ移動.
//======================================.
void CBossGreatCamera::BossFlyMove()
{
	//目標が一定の位置まで上がったら追いかける.
	if (m_vTargetPos.y >= MOVE_START_HEIGHT) {
		//画面中央に目標が移るように目標より少し下を移す.
		m_Camera.vLook.y = m_vTargetPos.y - TARGET_DIFFERENCE;
		//地面の下よりカメラを下さない.
		if (m_Camera.vPos.y > MOVE_HEIGHT_MIN) {
			//注視点が移動した分だけカメラも下げる.
			m_Camera.vPos.y = STANDERD_CAMERA_POS.y - (m_Camera.vLook.y - CAMERA_LOOK.y);
		}
	}
	else{
		//ボスが飛ぶ時の揺れる処理.
		m_bSwingFinish = BossFlySwing();
	}

	//目標物が移動し終わればカメラを戻す.
	if (m_vTargetPos == m_vOldTargetPos) {
		m_fTargetLook = m_Camera.vLook.y - CAMERA_LOOK.y;
		m_enCameraType = enCameraType::Return;
	}
	
	//前回のカメラの位置設定.
	m_vOldTargetPos = m_vTargetPos;
}

//======================================.
//		プレイヤーを見るカメラ移動.
//======================================.
void CBossGreatCamera::PlayerLook()
{
	//カメラ移動.
	if (m_Camera.vPos.x < PLAYER_CAMERA_POS.x ) {
		m_Camera.vPos += D3DXVECTOR3(PLAYER_RATIO_HORIZON, -PLAYER_RATIO_HEIGHT, PLAYER_RATIO_BACK) * 0.02f;
	}
	//注視点移動.
	if (m_Camera.vLook.y < m_vTargetPos.y + PLAYER_LOOK_ASSIST.y) {
		m_Camera.vLook.y -= ((m_vTargetPos.y + PLAYER_LOOK_ASSIST.y) / CAMERA_MOVE_ORIGIN) * 0.02f;
	}
	else {
		//プレイヤーを追う.
		m_Camera.vLook = m_vTargetPos + PLAYER_LOOK_ASSIST;
	}
}

//=======================================.
//		ボスが飛ぶ時の揺れる処理関数.
//=======================================.
bool CBossGreatCamera::BossFlySwing()
{
	//カメラ座標移動.
	m_Camera.vPos.y += SWING_CAMERA_SPEED * m_SwingDirection;
	//注視点移動.
	m_Camera.vLook.y += SWING_CAMERA_SPEED * m_SwingDirection;

	//進行方向変更処理.
	if (m_bCenterPassing == true) {
		if (fabsf(m_Camera.vPos.y - m_vSwingBeforePos.y) > m_SwingDistanceMax) {
			m_SwingDirection *= CHANGE_DIRECTION_NUM;
			m_bCenterPassing = false;
		}
	}

	//下に揺れているときの処理.
	if (m_SwingDirection < 0) {
		if (m_Camera.vPos.y - m_vSwingBeforePos.y < 0) {
			m_bCenterPassing = true;
		}
		return false;
	}

	//上に揺れているときの処理.
	if (m_Camera.vPos.y - m_vSwingBeforePos.y > 0) {
		m_bCenterPassing = true;
	}

	return false;
}