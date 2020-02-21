#ifndef CPLAYER_H
#define CPLAYER_H

#include "..\CChara.h"
#include "..\..\..\Drawing\CCommon.h"
#include "..\..\..\Command\enumCommand_Global.h"
#include "..\..\..\Sound\CSEPlayManager.h"
//�����蔻��N���X.
#include"..\..\Collider_Detection\CCollision_Detection.h"

//�R���g���[���N���X.
#include"..\..\..\Controller\CXInput.h"

//�v���C���[�N���X.
class CPlayer
	: public CChara
{
public:
	//================�񋓑�==================//.
	//�A�N�V�������.
	enum class enPlyAct
	{
		Attack = 0,		//�U��.
		Jump,			//�W�����v.
		TwoRowJump,		//��i�W�����v.	
		Run,			//����.
		Wait,			//�ҋ@.
		Panic,			//�p�j�b�N.

		Max,			//�ő�.
		Start = Attack,	//�ŏ�.
	};


	CPlayer();	//�R���X�g���N�^.
	~CPlayer();	//�f�X�g���N�^.

	//=============�֐�==================//.
	void InitProcess();			//�����ݒ�֐�.
	void Update();					//�X�V�����֐�.
	void Render();					//�`�揈���֐�.
	void Release();					//��������֐�.
	void Progress();				//�O�i����.
	void Flashing(int count);		//�_�ŏ���.
	void SetAnim(enPlyAct Act);		//�A�j���[�V�����Đ��ݒ�;

	//�`���擾�����֐��`.
	//�ʒu.
	float GetPositionX() { return m_PlayerParam.m_vPos.x; }
	float GetPositionY() { return m_PlayerParam.m_vPos.y; }
	float GetPositionZ() { return m_PlayerParam.m_vPos.z; }
	D3DXVECTOR3 GetPosition() { return m_PlayerParam.m_vPos; }
	//�v���C���[�̏��,
	void SetPlayerAction(enPlyAct Act) { m_PlayerParam.m_Action = Act; }
	enPlyAct GetPlayerAction() { return m_PlayerParam.m_Action; }
	//�W�����v�t���O.
	void SetJumpFlag(bool flag) { m_PlayerParam.m_bJumpFlag = flag; }
	bool GetJumpFlag() { return m_PlayerParam.m_bJumpFlag; }

	//�G�̈ʒu�ݒ�֐�.
	void SetEnemyPosition(D3DXVECTOR3 vPos) { m_vEnemyPosition = vPos; }
	//����������Ă��邩.
	void SetLongCommand(bool flag) { m_bLongCommandFlag = flag; }
	//�ʒu���Œ肵�Ă�����.
	void SetFixedPosFlag(bool flag) { m_bFixedPosFlag = flag; }
	//�J�n���Ԃ͉߂�����.
	void SetStartCountFlag(bool flag) { m_bStartCountFlag = flag; }
	void SetOperation(bool flag) { m_OperationFlag = flag; }
	//�W�����v���I�������.
	bool GetJunpEndFlag() { return m_bJumpEndFlag; }
	//�Q�[���̏I�����擾.
	bool GetEndFlag() { return m_bEndFlag; }


private:
	//================�񋓑�==================//.
	//�s������p.
	enum class enOperation
	{
		Possible = 0,		//�\.
		Impossible,			//�s�\.

		Max,				//�ő�.
		Start = Possible,	//�ŏ�.
	};

	//================�\����==================//.
	//�v���C���[�p�����[�^.
	struct stPLAYER_PARAM
	{
		D3DXVECTOR3	m_vPos;			//�ʒu���.
		D3DXVECTOR3 m_vOldPos;		//�ړ��O�ʒu���.
		bool		m_bDispFlag;	//�\���t���O.
		float		m_fAcc;			//����(Acceleration).
		bool		m_bJumpFlag;	//�W�����v�t���O.
		enPlyAct	m_Action;		//�A�N�V����.
		enPlyAct	m_Old_Action;	//�ߋ��A�N�V����.
		int			m_MoveCount_R;	//�ړ�����p�J�E���g.
		int			m_MoveCount_L;	//�ړ�����p�J�E���g.
		bool		m_SetAnimFlag;	//�A�j���[�V�����Z�b�g�p�t���O.
		int			m_Count;		//�J�E���g.
		float		m_AnimSpeed;	//�A�j���[�V�����̑���.

		stPLAYER_PARAM()
			: m_vPos(0.0f, 0.0f, 4.0f)
			, m_vOldPos()
			, m_bDispFlag(false)
			, m_fAcc(0.0f)
			, m_bJumpFlag(false)
			, m_Action(enPlyAct::Max)
			, m_Old_Action(enPlyAct::Max)
			, m_MoveCount_R(0)
			, m_MoveCount_L(0)
			, m_SetAnimFlag(false)
			, m_Count(0)
			, m_AnimSpeed(0.0f)
		{}
	};

	//=====================�萔======================//.
	const float POISITION_Z		= 4.0f;		//z���W.
	const float JUMP_POWER		= 0.13f;	//�W�����v��.
	const float GRAVITY			= 0.01f;	//�d��(�����x).
	const float	MOVING_RANGE	= 1.5f;		//�ړ��͈�.
	const float MOVE_SPEED		= 0.035f;	//�ړ����x.
	const float ROTATION		= 3.15f;	//��]�l.
	const float ANIM_SPEED		= 0.02f;	//�A�j���[�V�����Đ����x.
	const int   FIRST_MOVETIME	= 1;		//�ړ����鎞��.
	const int   SECOND_MOVETIME = 10;		//�ړ����鎞��.
	const int   ANIM_RUN		= 4;		//����A�j���[�V����.
	const int   ANIM_JUMP		= 3;		//�W�����v�A�j���[�V����.
	const int   ANIM_WAIT		= 1;		//�ҋ@�A�j���[�V����.
	const int   ANIM_ATTACK		= 2;		//�U���A�j���[�V����.
	const int   ANIM_PANIC		= 0;		//�U���A�j���[�V����.
	const int	SECONDS_COUNT	= 60;		//60�t���[���Ŋ���.
	const int   FLASH_DIVIDE	= 120;		//�_�Ŏ��Ԃ�����t���[��.
	const int   TWO_DIVIDE		= 2;		//2�Ŋ���.
	const int   WAIT_END		= 8;		//�ҋ@��̏I��莞��.
	const int	GAME_END		= 10;		//�Q�[���I��莞��.
	const float POSITION_ADJ	= 0.5f;		//�ʒu����.
	const int	EFFECT_MAX		= 2;		//�G�t�F�N�g�ő吔.
	const int	STEP_EFFECT_NUM = 0;		//�^�k�L�𓥂ނƂ��̃G�t�F�N�g�ԍ�.
	const int	LAND_EFFECT_NUM = 1;		//�n�ʂɒ��n�����Ƃ��̃G�t�F�N�g�ԍ�.
	const float	ENEMY_DEPTH		= 1.5f;		//�G�̍���.
	const int   MOVE_START		= 240;		//�����n�߂鎞��.
	//============================.
	//		�ǉ�.
	const float	SHADOW_HIGHT = 0.03f;		//�e�̍���.

	//=====================�֐�======================//.
	void Move(float range, int count);					//�ړ��֐�.
	void Jump();										//�W�����v����.

	//=====================�ϐ�======================//.
	clsXInput*								m_pCInput;				//�R���g���[���N���X.
	stPLAYER_PARAM							m_PlayerParam;
	CDX9SkinMesh*							m_pCPlayerAnim;			//�v���C���[�A�j���[�V����.
	CResourceManager*						m_pCResourceManager;
	CSEPlayManager*							m_pCSEPlayManager;
	enOperation								m_enOperation;
	CDX9SkinMesh::CHANGE_TEXTURE*			m_pChangeTexture;		//�e�N�X�`���؂�ւ�.

	D3DXVECTOR3								m_vEnemyPosition;		//�G�ʒu.
	bool									m_bEndFlag;				//�Q�[���I���t���O.
	int										m_frame;				//�o�ߎ���.
	int										m_WaitTime;				//�ҋ@����.
	bool									m_bFixedPosFlag;		//�ʒu�Œ�t���O.
	bool									m_bLongCommandFlag;		//����������Ă��邩.
	bool									m_OperationFlag;		//����t���O.
	bool									m_bJumpEndFlag;			//�W�����v���I�������.
	bool									m_bStartCountFlag;		//�Q�[���J�n�t���O.
	int										m_StartCount;			//�J�n����.
	int										m_FlashTime;			//�_�Ŏ���.
	//===============.
	//		�ǉ�.
	CSprite*								m_pCShadow;				//�e.
};

#endif	//#ifndef CPLAYER_H
