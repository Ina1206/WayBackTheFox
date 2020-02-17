#ifndef _CCOW_GHOST_H
#define _CCOW_GHOST_H

#include "..\CNormalEnemyBase.h"
#include "..\..\..\..\..\Command\TimingCommand\CTimingCommand.h"

class CCow_Ghost
	: public CNormalEnemyBase
{
public:
	CCow_Ghost(); 
	~CCow_Ghost();

	//=====================�萔========================//.
	const float STANDERD_HIGH			= 0.3f;		//��{����.
	const float HIGH_MAX				= 1.3f;		//�����̍ő�l.
	const int	JUMP_MAX				= 2;		//�W�����v�񐔍ő吔.
	const float CENTER_POS_X			= 0.0f;		//�^�񒆂̃��[���̈ʒu.
	const float	LANE_MIN				= -1.5f;	//���[���̍ŏ��l.
	const float LANE_MAX				= 1.5f;		//���[���̍ő�l.
	const float MOVE_WIDTH				= 1.5f;		//�ړ���.
	const float VERTICAL_SPEED			= 0.01f;	//�c�ړ��̃X�s�[�h.
	const float HORIZON_SPEED			= 0.1f;		//���ړ��̃X�s�[�h.
	const float STOP_DISTANCE			= 7.0f;		//�ړ���~����.
	const float SHADOW_DISP_UP_LIMIT	= 2.5f;		//�e�̕\�����.

	const float COMMAND_HIGH			= 1.1f;		//�R�}���h�̍���.

	const float EFFECT_DISP_POS			= 10.0f;	//�G�t�F�N�g�\������.

	//====================�񋓑�=======================//.
	//�c�ړ����.
	enum class enVerticalMove_Type {
		Up = 0,			//��.
		Down,			//��.	
		Waiting,		//�ҋ@.

		Max,			//�ő�l.
		Start = Up,		//�n�܂�.
	};

	//���ړ����.
	enum class enHorizonMove_Type {
		Right_Move,			//�E.
		Left_Move,			//��.

		Max,				//�ő�l.
		Start = Right_Move,	//�n�܂�.
	};


	//=====================�֐�========================//.
	void Init_Process();				//�����������֐�.
	void UpDate();						//�X�V�����֐�.
	void Render();						//�`�揈���֐�.
	void Release();						//��������֐�.


private:
	//=====================�֐�========================//.
	void Move();						//�ړ������֐�.
	void FarMove();						//�����Ƃ��̈ړ������֐�.
	void HorizonMove();					//���ړ������֐�.

	//=====================�ϐ�========================//.
	//�`�N���X�`.
	CDX9Mesh*				m_pStaticMesh;			//�I�u�W�F�N�g.

	enVerticalMove_Type		m_enVerticalMoveType;	//�c�ړ����.
	enHorizonMove_Type		m_enHorizonMoveType;	//���ړ����.
	int						m_JumpCnt;				//�W�����v�J�E���g.
	float					m_fOldPos_x;			//�O��̉����W.
	bool					m_bCheckSE;				//SE�̍Đ��t���O.
};

#endif	//#ifndef _CCOW_GHOST_H.