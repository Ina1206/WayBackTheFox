#ifndef CBIG_RACCOON_DOG_H
#define CBIG_RACCOON_DOG_H

#include "..\..\CEnemyBase.h"
#include "..\..\..\..\..\Command\BarrageCommand\CBarrageCommand.h"

/***************************************
*	�f�J�^�k�L�N���X.
**/
class CBig_Raccoon_Dog
	: public CEnemyBase
{
public:
	CBig_Raccoon_Dog();
	~CBig_Raccoon_Dog();

	//=======================�萔========================//.
	//�^�C��.
	const float			MAX_TIME			= 15.0f;							//�^�C���̍ő�l.
	const float			FRAME				= 60.0f;							//�t���[��.
	//����.
	const int			WAIT_TIME			= 120;								//�ҋ@����.
	const float			STANDERD_POS_H		= 0.8f;								//�f�J�^�k�L�̊����.
	const float			BEHINE_DOWN_SPEED	= 0.002f;							//���ɓ|��鑬�x.
	const float			PREVIOUS_DOWN_SPEED = 0.005f;							//�O�ɓ|��鑬�x.
	const float			ADJUSTMENT_HIGHT	= 0.003f;							//��������.
	const float			ROTATION_MIN		= -1.7f;							//��]�p�x�̍ŏ��l.
	const float			ROTATION_MAX		= -1.2f;							//��]�p�x�̍ő�l.
	const float			START_ROTATION		= -1.5f;							//���߂̊p�x.
	const float			ANIM_CHANGE_ROT		= -1.6f;							//�A�j���[�V������ύX����p�x.
	const float			ANIM_SPEED_MAX		= 0.005f;							//�A�j���[�V�������x�̍ő�l.
	const float			ANIM_SPEED_MIN		= 0.0f;								//�A�j���[�V�������x�ŏ��l.
	//�|�R�|�R�炷�p.
	const int			HANDLE_MAX			= 2;								//��̍��v��.
	const int			LEFT_HANDLE_NUM		= 0;								//����̔ԍ�.
	const int			RIGHT_HANDLE_NUM	= 1;								//�E��̔ԍ�.
	const int			HIT_TARGET_MAX		= 1;								//�����鑊�葤�̍ő�l.
	const int			HIT_TARGET_NUM		= 2;								//�����鑊�葤�̔ԍ�.
	const float			PLAYER_HIT_SCALE	= 0.2f;								//�v���C���[�̎�̓����蔻��̑傫��.
	const float			BOSS_HIT_SCALE		= 1.5f;								//�{�X�̓����蔻��̑傫��.
	const D3DXVECTOR3	HIT_BOSSPOS_ADJUST	= D3DXVECTOR3(0.0f, 1.0f, -1.5f);	//�{�X���̓����蔻��̔�����.
	//�������ĉ�]���Ă���.
	const float			HIT_ROTATION_SPEED	= 0.01f;							//�������ĉ�]���鑬�x.
	const float			HIT_ROT_SPEED_UP	= 0.005f;							//��]���x�𑝂₷.
	const float			HIT_MOVE_SPEED		= 0.04f;							//�������Ĕ��ł����X�s�[�h.
	const float			FLY_MAX				= 5.5f;								//��ԍ����ő吔.
	const float			CENTER_AXIS_DIFF	= -50.0f;							//���݂̒��S���Ɗ�]���Ă��钆�S���̍�.
	const float			ONE_ROTATION_MIN	= 6.2f;							//���]�̍ŏ��l.
	const float			BACK_SPEED			= 0.0001f;							//�������Ɉړ����鑬�x.
	//�|���Ƃ�.
	const int			FALL_DOWN_WAIT_TIME = 50;								//�|���Ƃ��̑҂�����.
	const float			FALL_DOWN_ROT_MIN	= -3.5f;							//�|���Ƃ��̊p�x�ŏ��l.
	const D3DXVECTOR3	ADJUST_MOVE_SPEED	= D3DXVECTOR3(0.0f, 0.025f, 0.15f);	//�|���Ƃ��̒������x.
	const float			FALL_DOWN_SPEED_UP	= 0.012f;							//�|���Ƃ��̑��x���グ�Ă������x.
	//�G�t�F�N�g.
	const int			EFFECT_MAX			= 3;								//�G�t�F�N�g�̍ő吔.
	const int			HIT_FLY_EFFECT_NUM	= 0;								//���ł����G�t�F�N�g�ԍ�.
	const int			FALLDOWN_EFFECT_NUM = 1;								//�|���Ƃ��̃G�t�F�N�g�ԍ�.
	const int			PUNCH_EFFECT_NUM	= 2;								//�p���`�������������̃G�t�F�N�g.
	const float			ALPHA_MAX			= 1.0f;								//���ߒl�ő吔.
	const float			STAR_SCALE_SPEED	= 0.07f;								//���̊g�k���x.
	const float			STAR_MAX			= 1.2f;								//���̑傫���̍ő�l.
	const float			STAR_MIN			= 0.0f;								//���̑傫���̍ŏ��l.
	//�R�}���h.
	const int			COMMAND_BUTTON_MAX	= 3;								//�R�}���h�{�^���ő�l.

	//======================�񋓑�=======================//.
	//�f�J�^�k�L�̃A�j���[�V�������.
	enum class enAnimType {
		Finish = 0,		//�I����.
		Swing,			//�h���.
		Noting,			//����.

		Max,			//�ő�.
		Start = Finish,	//�J�n.
	};
	//��]����Z�ړ�.
	enum class enRotation_Move {
		Previous = 0,		//�O.
		Behind,				//���.

		Max,				//�ő�l.
		Start = Previous,	//�n�܂�.
	};
	//���̊g�k.
	enum class enStarScaling {
		Scale = 0,	//�g��.
		Scale_Down,	//�k��.
		Finish,		//�I��.
	};

	//=======================�֐�========================//.
	void InitProcess();	//�����������֐�.
	void Update();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.
	void Release();			//��������֐�.

	//�`���l�������֐��`.
	D3DXVECTOR3			GetRotation() { return m_vRot; }										//�p�x�l������.
	bool				GetCommandStart() { return m_bCommandDispStart; }						//�R�}���h�\���J�n�t���O�l������.
	enInput_Decision	GetInputDecision() { return m_pCCommand_Base->GetInputDeision(); }		//�R�}���h���茋��.
	bool				GetMoveStart() { return m_bMoveStart; }									//�s���J�n�t���O�l������.

	//�`���u�������֐��`.
	void SetMove(bool flag) { m_bMoveStart = flag; }											//�s���J�n�t���O.	
	void SetUpDistance(float Distance) { m_fUpDistance = Distance; }							//��ɏオ�鋗��.	
	void SetButtonNum(int ButtonNum, int Num) { m_pButtonNum[Num] = ButtonNum; }				//�{�^���ԍ�.

	void SetInputDecision(enInput_Decision InputDecision) { m_enInputDecision = InputDecision; }

private:
	//=======================�萔========================//.
	void MoveJudgement();			//�s�������֐�.
	void MoveHit();					//�����������̏����֐�.
	void Falldown();				//�|���Ƃ��̏����֐�.
	void HitSound();				//����ꂽ���̉������֐�.
	void FlyAfter();				//��񂾂��Ƃ̏����֐�.

	//=======================�ϐ�========================//.
	CDX9Mesh*			m_pCStaticMesh;		//���b�V��.
	CDX9Mesh*			m_pCMesh;			//���b�V��.
	CDX9SkinMesh*		m_pCSkinMesh;		//�A�j���[�V�������b�V��.
	CSprite*			m_pCStar;			//���̃X�v���C�g�p�N���X.

	int*				m_pButtonNum;		//�{�^���ԍ�.
	enInput_Decision	m_enInputDecision;	//���͌���.
	enInput_Decision	m_enOldInDecision;	//�O��̓��͌���.
	bool				m_bCommandDispStart;//�R�}���h�\���J�n�t���O.

	enRotation_Move		m_enRotation_Move;	//��]���̈ړ�.
	enRotation_Move		m_enRotationType;	//�X�����.
	float				m_fFall_Down_Speed;	//�|��鑬�x.
	D3DXVECTOR3			m_vSwingBefore_Pos;	//�n�ʂ��h���O�̍��W.
	float				m_fScale;			//�傫��.

	bool				m_bInputSE_Check;	//�R�}���h���͏I������SE.
	bool				m_bMoveStart;		//�^�C�}�[.				
	float				m_fUpDistance;		//��ɏオ�鋗��.			
	float				m_fAnimSpeed;		//�A�j���[�V�������x.
	enAnimType			m_enAnimType;		//�A�j���[�V�����̎��.
	bool				m_bAnimChange;		//�A�j���[�V�����ύX�t���O.

	D3DXVECTOR3*		m_pvPlayerHandlePos;//�v���C���[�̎�̈ʒu.
	bool*				m_pbHitHandleFlag;	//�肪�����������̃t���O.

	int					m_Cnt;				//�J�E���g.
	int					m_WaitCnt;			//���Ԃ̃J�E���g.

	float				m_fHitRotation;		//��].

	D3DXVECTOR3			m_vStarPos;			//���̈ʒu.
	float				m_fStarScale;		//���̑傫��.
	enStarScaling		m_enStarScaling;	//���̊g�k�^�C�v.
	D3DXVECTOR3			m_vPrePos;			//�\���Y��.
};

#endif	//#ifndef CBIG_RACCOON_DOG_H.