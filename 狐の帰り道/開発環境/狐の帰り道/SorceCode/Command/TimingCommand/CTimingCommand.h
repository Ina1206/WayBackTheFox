#ifndef CTIMENG_COMMAND_H
#define CTIMENG_COMMAND_H

#include "..\CCommand_Base.h"

/**************************************
*		�^�C�~���O�R�}���h.
**/
class CTimingCommand
	: public CCommand_Base
{
public:
	CTimingCommand();
	~CTimingCommand();
	//=======================�萔===========================//.
	const float CIRCLE_SIZE_MAX		= 1.8f;																//�ۂ̃T�C�Y�̍ő吔.
	const float CIRCLE_SIZE_MIN		= 0.4f;																//�ۂ̃T�C�Y�̍ŏ��l.
	const float START_CIRCLE_SIZE	= CIRCLE_SIZE_MIN - 0.2f;											//�X�^�[�g���̍���.
	const float DISPRY_DISTANCE		= 8.5f;																//�ۂ̕\��.
	const float CIRCLE_GREAT_SIZE	= START_CIRCLE_SIZE + ((CIRCLE_SIZE_MAX - CIRCLE_SIZE_MIN) / 3.0f);	//Great����̑傫����؂�.
	const float CIRCLE_BAD_SIZE		= CIRCLE_SIZE_MIN + 0.03f;											//Bad�̔���T�C�Y.
	const float MARU_POS_HIGH		= 0.4f;																//�ۂ̍���.
	const float HIT_SIZE_MAX		= 2.0f;																//�{�^���������Ƃ��̌��̑傫���ő�l.
	const float HIT_SIZE_MIN		= 0.0f;																//�{�^���������Ƃ��̌��̑傫���ŏ��l.
	const float HIT_ALPHA_MAX		= 0.7f;																//�{�^���������Ƃ��̌��̓��ߒl�ő�l.
	const float HIT_ALPHA_MIN		= 0.0f;																//�{�^���������Ƃ��̌��̓��ߒl�ŏ��l.
	const float START_DIFFERENCE	= 0.9f;																//�J�n�ʒu�̍���.
	const float LIGHT_ALPHA_SPEED	= 0.15f;															//���̓��ߑ��x.
	const float LIGHT_SCALE_SPEED	= 0.15f;															//���̑傫�����x.
	//=======================�֐�===========================//.
	void UpDate(enCommandType CommandType);				//�X�V�����֐�.
	void Render();										//�`�揈���֐�.

private:
	//=======================�֐�===========================//.
	void Release();										//��������֐�.
	void DispDecision();								//�\�����菈���֐�.
	void CommandDecision(enCommandType CommandType);	//�R�}���h���菈���֐�.
	void Circle_ScaleDown();							//�~�̑傫�������������鏈���֐�.
	void CircleRender();								//�ۂ̕`�揈���֐�.
	void ButtonPushCircle();							//�{�^���������Ƃ��̉~�̏����֐�.
	void ButtonPushRender();							//�{�^�����������Ƃ��̊ۂ̕`�揈���֐�.

	//=======================�萔===========================//.
	CSprite*		m_pCSpriteMaru;						//�ۂ̃X�v���C�g.
	D3DXVECTOR3		m_vMaruPos;							//�ۂ̈ʒu.
	float			m_fScale;							//�ۂ̑傫��.
	bool			m_bCircleDispry;					//�ۂ̕\���t���O.

	bool			m_bButtonPushFlag;					//�{�^���������Ƃ��̃t���O.
};

#endif	//#ifndef CTIMENG_COMMAND_H.