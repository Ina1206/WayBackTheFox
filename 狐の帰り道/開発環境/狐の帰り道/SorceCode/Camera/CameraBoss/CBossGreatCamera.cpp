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
	//�J�����̏����ʒu.
	m_Camera.vLook		= CAMERA_LOOK;
	m_Camera.vPos		= STANDERD_CAMERA_POS;
	//�h���O�̃J�����ʒu.
	m_vSwingBeforePos	= m_Camera.vPos;
}

CBossGreatCamera::~CBossGreatCamera()
{
}

//======================================.
//		�X�V�����֐�.
//======================================.
void CBossGreatCamera::UpDate(bool CameraFlag)
{
	//�ړ������֐�.
	Move();
}

//======================================.
//		�ړ������֐�.
//======================================.
void CBossGreatCamera::Move()
{	
	//�J�����̎�ނ��ƂɌ�����̂̕ύX.
	switch (m_enCameraType) {
	//�{�X�����Ă���Ƃ�.
	case enCameraType::Boss:
		//�{�X����Ԏ��̃J�����ړ�.
		BossFlyMove();
		break;
	//�v���C���[�����Ă���Ƃ�.
	case enCameraType::Player:
		//�v���C���[������J�����ړ�.
		PlayerLook();
		break;
	//�J������߂�.
	case enCameraType::Return:
		//�߂鏈���֐�.
		Return();
		break;
	}
}

//======================================.
//		�߂鏈���֐�.
//======================================.
void CBossGreatCamera::Return()
{
	//�J�����ړ�.
	m_Camera.vPos.y += (STANDERD_CAMERA_POS.y / m_fTargetLook) * RETURN_SPEED;
	//�����_�ړ�.
	m_Camera.vLook.y -= RETURN_SPEED;
	//���̃J�����ړ���.
	if (m_Camera.vPos.y > STANDERD_CAMERA_POS.y) {
		//�l��ݒ肵�Ă���.
		m_Camera.vPos = STANDERD_CAMERA_POS;
		m_Camera.vLook = CAMERA_LOOK;
		
		//�����҂�.
		m_WaitTime++;
		if (m_WaitTime > WAIT_TIME) {
			//Player������J������.
			m_enCameraType = enCameraType::Player;
		}

	}
}

//======================================.
//		�{�X����Ԏ��̃J�����ړ�.
//======================================.
void CBossGreatCamera::BossFlyMove()
{
	//�ڕW�����̈ʒu�܂ŏオ������ǂ�������.
	if (m_vTargetPos.y >= MOVE_START_HEIGHT) {
		//��ʒ����ɖڕW���ڂ�悤�ɖڕW��菭�������ڂ�.
		m_Camera.vLook.y = m_vTargetPos.y - TARGET_DIFFERENCE;
		//�n�ʂ̉����J�����������Ȃ�.
		if (m_Camera.vPos.y > MOVE_HEIGHT_MIN) {
			//�����_���ړ������������J������������.
			m_Camera.vPos.y = STANDERD_CAMERA_POS.y - (m_Camera.vLook.y - CAMERA_LOOK.y);
		}
	}
	else{
		//�{�X����Ԏ��̗h��鏈��.
		m_bSwingFinish = BossFlySwing();
	}

	//�ڕW�����ړ����I���΃J������߂�.
	if (m_vTargetPos == m_vOldTargetPos) {
		m_fTargetLook = m_Camera.vLook.y - CAMERA_LOOK.y;
		m_enCameraType = enCameraType::Return;
	}
	
	//�O��̃J�����̈ʒu�ݒ�.
	m_vOldTargetPos = m_vTargetPos;
}

//======================================.
//		�v���C���[������J�����ړ�.
//======================================.
void CBossGreatCamera::PlayerLook()
{
	//�J�����ړ�.
	if (m_Camera.vPos.x < PLAYER_CAMERA_POS.x ) {
		m_Camera.vPos += D3DXVECTOR3(PLAYER_RATIO_HORIZON, -PLAYER_RATIO_HEIGHT, PLAYER_RATIO_BACK) * 0.02f;
	}
	//�����_�ړ�.
	if (m_Camera.vLook.y < m_vTargetPos.y + PLAYER_LOOK_ASSIST.y) {
		m_Camera.vLook.y -= ((m_vTargetPos.y + PLAYER_LOOK_ASSIST.y) / CAMERA_MOVE_ORIGIN) * 0.02f;
	}
	else {
		//�v���C���[��ǂ�.
		m_Camera.vLook = m_vTargetPos + PLAYER_LOOK_ASSIST;
	}
}

//=======================================.
//		�{�X����Ԏ��̗h��鏈���֐�.
//=======================================.
bool CBossGreatCamera::BossFlySwing()
{
	//�J�������W�ړ�.
	m_Camera.vPos.y += SWING_CAMERA_SPEED * m_SwingDirection;
	//�����_�ړ�.
	m_Camera.vLook.y += SWING_CAMERA_SPEED * m_SwingDirection;

	//�i�s�����ύX����.
	if (m_bCenterPassing == true) {
		if (fabsf(m_Camera.vPos.y - m_vSwingBeforePos.y) > m_SwingDistanceMax) {
			m_SwingDirection *= CHANGE_DIRECTION_NUM;
			m_bCenterPassing = false;
		}
	}

	//���ɗh��Ă���Ƃ��̏���.
	if (m_SwingDirection < 0) {
		if (m_Camera.vPos.y - m_vSwingBeforePos.y < 0) {
			m_bCenterPassing = true;
		}
		return false;
	}

	//��ɗh��Ă���Ƃ��̏���.
	if (m_Camera.vPos.y - m_vSwingBeforePos.y > 0) {
		m_bCenterPassing = true;
	}

	return false;
}