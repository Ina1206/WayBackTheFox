#include "CStanderdCamera.h"


/*******************************************
*	��̃J����.
**/
CStanderdCamera::CStanderdCamera()
{
	//�����ʒu.
	m_Camera.vPos = STANDERD_CAMERA_POS;
	m_Camera.vLook = CAMERA_LOOK;
}

CStanderdCamera::~CStanderdCamera()
{
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CStanderdCamera::Update(bool CameraFlag)
{
	//�s�������֐�.
	Move();
}

//=======================================.
//		�s�������֐�.
//=======================================.
void CStanderdCamera::Move()
{
	m_Camera.vPos = STANDERD_CAMERA_POS;	//�J�����ʒu�ݒ�.
	m_Camera.vLook = BOSS_CAMERA_LOOK;		//�����_.
}
