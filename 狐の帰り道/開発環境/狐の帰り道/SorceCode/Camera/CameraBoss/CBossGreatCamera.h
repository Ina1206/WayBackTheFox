#ifndef CBOSS_GREAT_CAMERA_H
#define CBOSS_GREAT_CAMERA_H

#include "..\CCameraBase.h"

/*********************************************
*		�{�X��Great���莞�̃N���X.s
**************/
class CBossGreatCamera
	: public CCameraBase
{
public:
	CBossGreatCamera();
	~CBossGreatCamera();

	//==================�萔====================//.
	const float			RETURN_SPEED			= 0.05f;										//�߂鑬�x.
	const float			MOVE_START_HEIGHT		= 3.0f;											//�J�����̒����_�������o������.
	const float			TARGET_DIFFERENCE		= 2.0f;											//�f���ڕW�̍����������Ⴍ����.
	const float			MOVE_HEIGHT_MIN			= 0.1f;											//�ړ�����J�����̍����̍ŏ��l.
	const D3DXVECTOR3	PLAYER_CAMERA_POS		= D3DXVECTOR3(2.0f, 1.3f, 6.0f);				//�v���C���[�Ɍ����Ƃ��̃J�������W.
	const D3DXVECTOR3	PLAYER_LOOK_ASSIST		= D3DXVECTOR3(0.0f, 1.0f, 0.0f);				//�v���C���[�Ɍ��������_�̕⏕.
	const float			CAMERA_MOVE_ORIGIN		= PLAYER_CAMERA_POS.x - STANDERD_CAMERA_POS.x;	//�J�����ړ��̊����̌�.
	const float			PLAYER_RATIO_HORIZON	= PLAYER_CAMERA_POS.x / CAMERA_MOVE_ORIGIN;		//�J������x���̈ړ�����.
	const float			PLAYER_RATIO_HEIGHT		= PLAYER_CAMERA_POS.y / CAMERA_MOVE_ORIGIN;		//�J������y���̈ړ�����.
	const float			PLAYER_RATIO_BACK		= PLAYER_CAMERA_POS.z / CAMERA_MOVE_ORIGIN;		//�J������z���̈ړ�����.
	const int			WAIT_TIME				= 120;											//�ҋ@���鎞��.
	const float			START_SWING_MAX			= 0.05f;										//�h��鋗���̏��߂̍ő�l.
	const float			SWING_CAMERA_SPEED		= 0.05f;										//�J�������h��鑬�x.
	const int			UP_DIRECTION_NUM		= 1;											//������̔ԍ�.
	const int			CHANGE_DIRECTION_NUM	= -1;											//�J�����̕����ύX���l.
	const float			PLAYER_LOOK_SPEED		= 0.02f;										//�v���C���[�̌��鑬�x.

	//=================�񋓑�===================//.
	//�J�����̎��.
	enum class enCameraType {
		Boss,		//�{�X�����Ă���Ƃ�.
		Player,		//�v���C���[�����Ă���Ƃ�.
		Return,		//�J������߂�.
	};

	//=================�֐�====================//.
	void UpDate(bool CameraFlag);	//�X�V�����֐�.
private:
	//=================�֐�====================//.
	void Move();					//�ړ������֐�.
	void Return();					//�߂鏈��.
	void BossFlyMove();				//�{�X����Ԏ��̃J�����ړ�.
	void PlayerLook();				//�v���C���[������J�����ړ�.
	bool BossFlySwing();			//�{�X����Ԏ��̗h��.

	//=================�ϐ�====================//.
	enCameraType	m_enCameraType;			//�J�����̎��.
	D3DXVECTOR3		m_vOldTargetPos;		//�O��̉f������̍��W.
	D3DXVECTOR3		m_fCameraChangeBefore;	//�J�������ړ�����O�̍��W.
	float			m_fTargetLook;			//�ڕW�̒����_.
	int				m_WaitTime;				//�ҋ@����.
	
	D3DXVECTOR3		m_vSwingBeforePos;		//�h���O�̈ʒu.
	D3DXVECTOR3		m_vSwingBeforeLook;		//�h���O�̒����_.
	int				m_SwingDirection;		//�h������.
	float			m_SwingDistanceMax;		//�h��鋗���̍ő吔.
	bool			m_bSwingFinish;			//�h���̏I��.
	bool			m_bCenterPassing;		//���S��ʉ߂����t���O.
};

#endif	//#ifndef CBOSS_GREAT_CAMERA_H.