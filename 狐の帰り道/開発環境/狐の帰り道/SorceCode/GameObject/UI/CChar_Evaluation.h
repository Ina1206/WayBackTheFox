#ifndef CCHAR_EVALUATION_H
#define CCHAR_EVALUATION_H

#include "CUI_Base.h"
#include "..\..\Sound\CSEPlayManager.h"
//�R���g���[���N���X.
#include"..\..\Controller\CXInput.h"

class CChar_Evaluation
	: public CUI_Base
{
public:
	CChar_Evaluation();
	~CChar_Evaluation();

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Init_Process();	//�����ݒ菈���֐�.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

private:
	//------------------------------------------.
	//	�萔.
	//------------------------------------------.
	const D3DXVECTOR3 EVALUATION_POS	= D3DXVECTOR3(-0.055f, 2.5f,0.1f);		//�]���̈ʒu.
	const D3DXVECTOR3 CHAR_POS			= D3DXVECTOR3(-0.028f, 2.498f,0.1f);	//������̈ʒu.
	const int SPRITE_MAX				= 4;									//�X�v���C�g�̍ő吔.
	const int CHAR_HIGH					= 0;									//�������ԍ�.
	const int CHAR_MIDDLE				= 1;									//�������ԍ�.
	const int CHAR_LOW					= 2;									//�ᕶ���ԍ�.
	const int CHAR_EVALUATION			= 3;									//�]�������ԍ�.
	const float SCALE_STANDARD			= 1.0f;									//�傫���W��.
	const float SCALE_MIN				= 0.0f;									//�傫���ŏ�.
	const float SCALE_MAX				= 2.0f;									//�傫���ő�.
	const float SCALE_SPEED				= 0.3f;									//�傫�����x.
	const float SCALE_SPEED_CHAR		= 0.05f;								//�傫�����x.
	const float ROTAITON_MAX			= 6.3f;									//��]�l�ő�.
	const float ROTAITON_SPEED			= 0.3f;									//��]���x.
	const int   EVALUATION_DISP_TIME	= 60;									//�]���`�掞��.
	const int	CHAR_DISP_TIME			= 120;
	const int	INPUT_OK				= 5;									//����\����.

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Release();												//��������֐�.
	void SetScale_Dowm(int num);								//�k���ݒ�.
	void SetRotation(int num);									//��]�l�ݒ�.

	//------------------------------------------.
	//	�ϐ�.
	//------------------------------------------.
	CSprite**		m_ppCCharSprite;	//Sprite�N���X.
	CSEPlayManager*	m_pCSEPlayManager;	//CSEPlayManager�N���X.
	enClear_Status	m_enClear_Status;	//�N���A�̏��.
	clsXInput*		m_pCInput;			//�R���g���[���N���X.

	D3DXVECTOR3		m_vRot;
	float*			m_fScale;			//�ʒu.
	float			m_fRot;				//��]�l.
	bool*			m_pbDispFlag;		//�`��t���O.
	int				m_frame;			//�o�ߎ���.
	int				m_WaitTime;			//�ҋ@����.
	bool			m_bCheckSE_Eva;		//�]������SE�`�F�b�N�p.
	bool			m_bCheckSE_Char;	//����SE�`�F�b�N�p.


};

#endif//#ifndef CCHAR_EVALUATION_H.
