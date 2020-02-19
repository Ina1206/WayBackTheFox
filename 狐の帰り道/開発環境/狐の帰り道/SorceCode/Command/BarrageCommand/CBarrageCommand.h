#ifndef CBARRAGE_COMMAND_H
#define CBARRAGE_COMMAND_H

#include "..\CCommand_Base.h"

#include "..\..\Effect\HitEffect\CHitEffect.h"

/****************************************
*		�A�ŃR�}���h�N���X.
***************/
class CBarrageCommand
	: public CCommand_Base
{
public:
	CBarrageCommand();
	~CBarrageCommand();

	//==========================�萔=============================//.
	const float			BUTTON_POS_Y		= 2.0f;									//�{�^���̔z�uy��.
	const float			BUTTON_POS_Z		= 1.4f;									//�{�^���̔z�uz��.
	const int			GAGE_GROUN_NUM		= 0;									//�Q�[�W���n�ԍ�.
	const int			GAGE_NUM			= 1;									//�Q�[�W�ԍ�.
	const int			GAGE_SPRITE_MAX		= 2;									//�Q�[�W�̃X�v���C�g�ő吔.
	const D3DXVECTOR3	GAGE_POS			= D3DXVECTOR3(400.0f, 550.0f, 0.01f);	//�Q�[�W�̈ʒu.
	const D3DXVECTOR3	GAGE_POS_ADJUST		= D3DXVECTOR3(34.0f, 32.0f, 0.01f);		//�Q�[�W�̒��̈ʒu�̒���.
	const float			GAGE_LENGTH_MAX		= 5.0f;									//�Q�[�W�̒����ő�l.
	const float			GAGE_HALF			= 2.0f;									//�Q�[�W�̔���.
	const float			GAGE_POS_START		= 2.5f;									//�Q�[�W�̊J�n�ʒu����.

	const int			BARRAGE_MAX			= 50;									//�A�ł̍ő吔.
	const int			MAX_TIME			= 15;									//��������.
	const int			SOUND_TIME			= 5;									//����炵������������.
	const int			FRAME				= 60;									//�t���[��.
	const int			TIME_SPRITE_MAX		= 2;									//���Ԃ̃X�v���C�g�ő吔.
	const int			TIME_TENS_PLACE		= 0;									//�������Ԃ�10�̈ʂ̃X�v���C�g.
	const int			TIME_ONE_RANK		= 1;									//�������Ԃ�1�̈ʂ̃X�v���C�g.
	const int			TIME_TENS			= 10;									//�\�̈�.
	const int			IMAGE_WIDTH_MAX		= 5;									//�摜���̋�؂�(��)�ő吔.
	const int			IMAGE_HIGH_MAX		= 5;									//�摜���̋�؂�(�c)�ő吔.
	const float			TIME_WIDTH			= 100.0f;								//���Ԃ̕`�敝.
	const float			TIME_SCALE_MAX		= 2.0f;									//���Ԃ̕`�掞�̑傫���ő�l.
	const float			TIME_SCALE_MIN		= 1.0f;									//���Ԃ̕`�掞�̑傫���ŏ��l.
	const D3DXVECTOR3	TIME_DISP_POS		= D3DXVECTOR3(550.0f, 90.0f, 0.0f);		//���Ԃ̕\���ʒu.
	const float			TIME_SCALE_SPEED	= 0.1f;									//���Ԃ̃X�v���C�g�g�k���x.
	const float			MAX_ALPHA			= 1.0f;									//���ߒl�ő�l.
	const float			MIN_ALPHA			= 0.5f;									//���ߒl�ŏ��l.
	const int			USE_BUTTON_MAX		= 3;									//�g����{�^���ő吔.
	const float			BUTTONSCALE_MAX		= 2.0f;									//�{�^���̑傫���ő�l.
	const float			BUTTONSCALE_MIN		= 1.0f;									//�{�^���̑傫���ŏ��l.
	const float			SCALE_SPEED_BUT		= 0.1f;									//�{�^���̏k�����x.

	const float			PUSH_ALPHA_MAX		= 1.0f;									//�{�^���������Ƃ��̓��ߒl�ő吔.
	const float			PUSH_ALPHA_MIN		= 0.0f;									//�{�^���������Ƃ��̓��ߒl�ŏ���.
	const float			PUSH_SCALE_MAX		= 1.5f;									//�{�^���������Ƃ��̑傫���ő吔.
	const float			PUSH_SCALE_MIN		= 0.5f;									//�{�^���������Ƃ��̑傫���ŏ��l.
	const float			PUSH_SCALE_SPEED	= 0.2f;									//�{�^���������Ƃ��̊g�k�X�s�[�h.
	const float			PUSH_ALPHA_SPEED	= 0.15f;								//�{�^���������Ƃ��̓��ߑ��x.

	const int			CHANGE_WAIT_TIME	= 60;									//�{�^���ύX��̗P�\����.

	const float			HIT_EFFECT_SCALE	= 0.5f;									//�������Ƃ��̃G�t�F�N�g�̑傫��.
	const float			EFFECT_HIGH			= 0.25f;								//�G�t�F�N�g�̕\������.

	//==========================�֐�=============================//.
	void Update(enCommandType CommandType);				//�X�V�����֐�.
	void Render();										//�`�揈���֐�.
private:
	//==========================�֐�=============================//.
	void Release();										//��������֐�.
	void DecisionCommand(enCommandType CommandType);	//�R�}���h���菈���֐�.
	void Time();										//���ԏ�������.
	void RenderTime();									//���ԕ`�揈���֐�.
	void ChangeButton();								//�{�^���ύX�����֐�.
	void RenderButton();								//�{�^���̕`��.
	void RenderGage();									//�Q�[�W�̕`��.
	void RenderPushButton();							//�{�^�����������Ƃ��̕`�揈���֐�.
	void DecisionDisp();								//�\�����菈���֐�.

	//==========================�ϐ�=============================//.
	float			m_fAlpha;				//���ߒl.
	CSpriteUI**		m_ppCGageSprite;		//�Q�[�W�̃X�v���C�g.
	D3DXVECTOR3*	m_pvGagePos;			//�Q�[�W�̈ʒu.
	int				m_fPushCnt;				//�����J�E���g.
	int				m_BarrageButtonNum;		//�A�Ń{�^���ԍ�.
	int				m_OldBarrageButtonNum;	//�A�Ń{�^���ԍ��O��.
	int				m_ChangeButtonCnt;		//�ύX�O�̘A�Ő�.
	int				m_ChangeAfterCnt;		//�ύX��̃J�E���g.

	CSprite*		m_pCPushButtonSprite;	//�{�^�����������X�v���C�g�N���X.
	float			m_fPushButtonAlpha;		//�{�^�����������X�v���C�g�̓��ߒl.
	float			m_fPushButtonSize;		//�{�^�����������X�v���C�g�̑傫��.

	bool			m_bButtonChangeSE;		//�A�Ń{�^���ύX���̖炷����SE�t���O.
	int				m_BarrageCheckCnt;		//�A�Ŋm�F�����֐�.
	float			m_fButtonScale;			//�{�^���̃X�P�[��.
	int				m_Timer;				//��������.
	int				m_Timer_num;			//�t���[���v�Z�p.
	CSpriteUI**		m_ppCTimeSprite;		//�^�C���̃X�v���C�g.

	CHitEffect*		m_pCHitEffect;			//�A�Ŏ��̃G�t�F�N�g.

	bool			m_bBGMChange;			//BGM�ύX�t���O.
};

#endif	//#ifndef CBARRAGE_COMMAND_H.