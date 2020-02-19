#include "CBossBadCamera.h"

/*******************************************
*		ボス戦のカメラ.
**/
CBossBadCamera::CBossBadCamera()
{
	//最初のカメラの設定.
	m_Camera.vPos = STANDERD_CAMERA_POS;
	m_Camera.vLook = CAMERA_LOOK;
}

CBossBadCamera::~CBossBadCamera()
{
}

//===================================.
//		更新処理関数.
//===================================.
void CBossBadCamera::Update(bool CameraFlag)
{
	//移動処理関数.
	Move();
}

//===================================.
//		移動処理関数.
//===================================.
void CBossBadCamera::Move()
{
	//カメラの座標移動.
	if (m_Camera.vPos.y > BAD_BOSS_CAMERA_POS.y ||
		m_Camera.vPos.z > BAD_BOSS_CAMERA_POS.z){
		//同じタイミングで希望の位置に停止できるように.
		m_Camera.vPos.y -= MOVE_SPEED;
		m_Camera.vPos.z -= BAD_BOSS_RATIO_Z * MOVE_SPEED;
	}
	else {
		//カメラ最終地点.
		m_Camera.vPos = BAD_BOSS_CAMERA_POS;
	}
	
	//カメラの注視点移動.
	if (m_Camera.vLook.z > BOSS_CAMERA_LOOK.z) {
		//同じタイミングで希望の位置に停止できるように.
		m_Camera.vLook.z -= MOVE_SPEED * BAD_BOSS_RATIO_LOOK;
	}
	else {
		//カメラの注視点最終地点.
		m_Camera.vLook = BOSS_CAMERA_LOOK;
	}
}
