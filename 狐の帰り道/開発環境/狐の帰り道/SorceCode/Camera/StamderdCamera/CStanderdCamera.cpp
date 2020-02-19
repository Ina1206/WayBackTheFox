#include "CStanderdCamera.h"


/*******************************************
*	基準のカメラ.
**/
CStanderdCamera::CStanderdCamera()
{
	//初期位置.
	m_Camera.vPos = STANDERD_CAMERA_POS;
	m_Camera.vLook = CAMERA_LOOK;
}

CStanderdCamera::~CStanderdCamera()
{
}

//=======================================.
//		更新処理関数.
//=======================================.
void CStanderdCamera::Update(bool CameraFlag)
{
	//行動処理関数.
	Move();
}

//=======================================.
//		行動処理関数.
//=======================================.
void CStanderdCamera::Move()
{
	m_Camera.vPos = STANDERD_CAMERA_POS;	//カメラ位置設定.
	m_Camera.vLook = BOSS_CAMERA_LOOK;		//注視点.
}
