#include "CBossBadCamera.h"

/*******************************************
*		�{�X��̃J����.
**/
CBossBadCamera::CBossBadCamera()
{
	//�ŏ��̃J�����̐ݒ�.
	m_Camera.vPos = STANDERD_CAMERA_POS;
	m_Camera.vLook = CAMERA_LOOK;
}

CBossBadCamera::~CBossBadCamera()
{
}

//===================================.
//		�X�V�����֐�.
//===================================.
void CBossBadCamera::Update(bool CameraFlag)
{
	//�ړ������֐�.
	Move();
}

//===================================.
//		�ړ������֐�.
//===================================.
void CBossBadCamera::Move()
{
	//�J�����̍��W�ړ�.
	if (m_Camera.vPos.y > BAD_BOSS_CAMERA_POS.y ||
		m_Camera.vPos.z > BAD_BOSS_CAMERA_POS.z){
		//�����^�C�~���O�Ŋ�]�̈ʒu�ɒ�~�ł���悤��.
		m_Camera.vPos.y -= MOVE_SPEED;
		m_Camera.vPos.z -= BAD_BOSS_RATIO_Z * MOVE_SPEED;
	}
	else {
		//�J�����ŏI�n�_.
		m_Camera.vPos = BAD_BOSS_CAMERA_POS;
	}
	
	//�J�����̒����_�ړ�.
	if (m_Camera.vLook.z > BOSS_CAMERA_LOOK.z) {
		//�����^�C�~���O�Ŋ�]�̈ʒu�ɒ�~�ł���悤��.
		m_Camera.vLook.z -= MOVE_SPEED * BAD_BOSS_RATIO_LOOK;
	}
	else {
		//�J�����̒����_�ŏI�n�_.
		m_Camera.vLook = BOSS_CAMERA_LOOK;
	}
}
