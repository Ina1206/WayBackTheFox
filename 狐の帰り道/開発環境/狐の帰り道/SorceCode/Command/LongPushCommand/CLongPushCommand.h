#ifndef CLONG_PUSH_COMMAND_H
#define CLONG_PUSH_COMMAND_H

#include "..\CCommand_Base.h"
#include "..\..\Drawing\Bord_Polygon\DebugText\CDebugText.h"
#include "..\..\Effect\SparkleEffect\CFootEffect\CFootEffect.h"
#include "..\..\Effect\SparkleEffect\LongPushEffect\CLongPushEffect.h"

/***************************************
*		�������R�}���h�N���X.
***********/
class CLongPushCommand
	: public CCommand_Base
{
public:
	CLongPushCommand();
	~CLongPushCommand();

	//===================�萔======================//.
	const float COMMAND_POS_Z		= 1.4f;		//�R�}���h��z���ʒu.
	const float DISP_ALPHA			= 20.0f;	//�R�}���h�������\��.
	const float DISP_DEPTH			= 16.5f;	//�R�}���h�\�����s.
	const float ALPHA_MAX			= 1.0f;		//���ߒl�̍ő�l.
	const float BUTTON_ALPHA		= 0.25f;	//�{�^���̔�������.
	const float ALPHA_SPEED			= 0.1f;		//���ߒl�ύX�X�s�[�h.
	const float COMMAND_LENGHT		= 5.0f;		//�R�}���h�̒���.
	const float GREAT_RANGE			= 0.3f;		//Great�͈�.
	const float GOOD_RANGE			= 0.8f;		//Good�͈�.
	const float BAD_RANGE			= 1.5f;		//Bad�͈�.
	const int	StartDecisionNum	= 0;		//�J�n�ʒu�̔���ԍ�.
	const int	EndDecisionNum		= 1;		//�I���ʒu�̔���ԍ�.
	const int	DECISION_TERMIN		= -1;		//����I���ԍ�.
	const float START_DISP_HEIGH	= 0.02f;	//���߂̃X�v���C�g�̕\�������̍�����.
	const float DISP_HEIGH_ADJUST	= 0.01f;	//�\����������.
	const float DEPTH_ADJUST		= 0.55f;	//�\�����s����.
	const float	BUTTON_DISP_POS_MAX = 2.0f;		//�{�^���\�������ő�l.
	const float BUTTON_DISP_POS_MIN = 1.7f;		//�{�^���\�������ŏ��l.
	const float	BUTTON_DOWN_SPEED	= 0.05f;	//�{�^���������鑬��.

	//==================�񋓑�=====================//.
	enum class enCommandSpriteType {
		CommandEnd,								//�R�}���h�̍Ō�̈ʒu.
		Intermediate,							//�R�}���h�̒���.
		CommandStart,							//�R�}���h�̊J�n�ꏊ.

		Max,									//�ő�l.
		Start = CommandStart,					//�J�n�ʒu.
	};

	//===================�֐�======================//.
	void UpDate(enCommandType CommandType);				//�X�V�����֐�.
	void Render();										//�`�揈���֐�.

private:
	//===================�֐�======================//.
	void Release();										//��������֐�.
	void DispDecision();								//�`�攻�菈���֐�.
	void CommandDecision(enCommandType CommandType);	//�R�}���h���菈���֐�.
	void CommandStartDecision();						//�R�}���h�X�^�[�g�n�_���菈���֐�.
	void CommandEndDecision();							//�R�}���h�I���n�_�̔��菈���֐�.
	void CommandRender();								//�R�}���h�摜�̕`��.

	//===================�ϐ�======================//.
	CSprite**		m_ppCCommandSprite;					//�R�}���h�X�v���C�g.
	D3DXVECTOR3*	m_pvCommandPos;						//�������R�}���h�摜�̈ʒu.
	int				m_PushCount;						//�����Ă���Ԃ̃J�E���g.
	bool			m_bSoundCheck;						//�������Đ��������`�F�b�N.
	CEffectBase*	m_pCEffectBase;						//�G�t�F�N�g�N���X.
	float			m_fButtonHigh;						//�{�^���\������.
	D3DXVECTOR3		m_vOldPos;							//�O��̃{�^�����W.
};

#endif	//#ifndef CLONG_PUSH_COMMAND_H.