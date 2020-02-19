#include "CUpCamera.h"

/*******************************************
*		上に上がるカメラ.
**/
CUpCamera::CUpCamera()
{
	//初期位置.
	m_Camera.vPos = STANDERD_CAMERA_POS;
	m_Camera.vLook = CAMERA_LOOK;
}

CUpCamera::~CUpCamera()
{
}

//=================================.
//		更新処理関数.
//=================================.
void CUpCamera::Update(bool CameraFlag)
{
	if (CameraFlag == true) {
		//行動処理関数.
		Move();
	}
	else if (CameraFlag == false) {
		//元に戻す処理関数.
		Return();
	}
}

//=================================.
//		行動処理関数.
//=================================.
void CUpCamera::Move()
{
	//y軸とx軸の移動.
	if (m_Camera.vPos.y < UP_CAMERA_POS.y || m_Camera.vPos.z < UP_CAMERA_POS.z) {
		m_Camera.vPos.y += MOVE_SPEED;
		//比率を計算して同時に停止できるように.
		m_Camera.vPos.z += MOVE_SPEED * UP_RATIO_Z;
	}
	else {
		//ズレ防止.
		m_Camera.vPos = UP_CAMERA_POS;
	}
	//注視点の移動.
	if (m_Camera.vLook.z > UP_CAMERA_LOOK.z) {
		m_Camera.vLook.z -= MOVE_SPEED * UP_RATIO_LOOK;
	}
	else {
		//ズレ防止.
		m_Camera.vLook = UP_CAMERA_LOOK;
	}
	

}

//==================================.
//		元に戻す処理関数.
//==================================.
void CUpCamera::Return()
{
	//元に戻す処理.
	//y軸.
	if (m_Camera.vPos.y > STANDERD_CAMERA_POS.y) {
		m_Camera.vPos.y -= MOVE_SPEED;
	}
	else {
		m_Camera.vPos.y = STANDERD_CAMERA_POS.y;
	}
	//z軸.
	if (m_Camera.vPos.z > STANDERD_CAMERA_POS.z) {
		m_Camera.vPos.z -= MOVE_SPEED * UP_RATIO_LOOK;
	}
	else {
		m_Camera.vPos.z = STANDERD_CAMERA_POS.z;
	}

	//注視点の移動.
	if (m_Camera.vLook.z < CAMERA_LOOK.z) {
		m_Camera.vLook.z += MOVE_SPEED * UP_RATIO_LOOK;
	}
	else {
		m_Camera.vLook = CAMERA_LOOK;
	}

	//基準カメラの方に移動.
	//ズレ防止.
	if (m_Camera.vPos.z == STANDERD_CAMERA_POS.z && m_Camera.vPos.y == STANDERD_CAMERA_POS.z) {
		m_CameraChangeFlag = true;
	}

}