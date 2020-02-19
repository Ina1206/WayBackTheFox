#include "CUpCamera.h"

/*******************************************
*		��ɏオ��J����.
**/
CUpCamera::CUpCamera()
{
	//�����ʒu.
	m_Camera.vPos = STANDERD_CAMERA_POS;
	m_Camera.vLook = CAMERA_LOOK;
}

CUpCamera::~CUpCamera()
{
}

//=================================.
//		�X�V�����֐�.
//=================================.
void CUpCamera::Update(bool CameraFlag)
{
	if (CameraFlag == true) {
		//�s�������֐�.
		Move();
	}
	else if (CameraFlag == false) {
		//���ɖ߂������֐�.
		Return();
	}
}

//=================================.
//		�s�������֐�.
//=================================.
void CUpCamera::Move()
{
	//y����x���̈ړ�.
	if (m_Camera.vPos.y < UP_CAMERA_POS.y || m_Camera.vPos.z < UP_CAMERA_POS.z) {
		m_Camera.vPos.y += MOVE_SPEED;
		//�䗦���v�Z���ē����ɒ�~�ł���悤��.
		m_Camera.vPos.z += MOVE_SPEED * UP_RATIO_Z;
	}
	else {
		//�Y���h�~.
		m_Camera.vPos = UP_CAMERA_POS;
	}
	//�����_�̈ړ�.
	if (m_Camera.vLook.z > UP_CAMERA_LOOK.z) {
		m_Camera.vLook.z -= MOVE_SPEED * UP_RATIO_LOOK;
	}
	else {
		//�Y���h�~.
		m_Camera.vLook = UP_CAMERA_LOOK;
	}
	

}

//==================================.
//		���ɖ߂������֐�.
//==================================.
void CUpCamera::Return()
{
	//���ɖ߂�����.
	//y��.
	if (m_Camera.vPos.y > STANDERD_CAMERA_POS.y) {
		m_Camera.vPos.y -= MOVE_SPEED;
	}
	else {
		m_Camera.vPos.y = STANDERD_CAMERA_POS.y;
	}
	//z��.
	if (m_Camera.vPos.z > STANDERD_CAMERA_POS.z) {
		m_Camera.vPos.z -= MOVE_SPEED * UP_RATIO_LOOK;
	}
	else {
		m_Camera.vPos.z = STANDERD_CAMERA_POS.z;
	}

	//�����_�̈ړ�.
	if (m_Camera.vLook.z < CAMERA_LOOK.z) {
		m_Camera.vLook.z += MOVE_SPEED * UP_RATIO_LOOK;
	}
	else {
		m_Camera.vLook = CAMERA_LOOK;
	}

	//��J�����̕��Ɉړ�.
	//�Y���h�~.
	if (m_Camera.vPos.z == STANDERD_CAMERA_POS.z && m_Camera.vPos.y == STANDERD_CAMERA_POS.z) {
		m_CameraChangeFlag = true;
	}

}