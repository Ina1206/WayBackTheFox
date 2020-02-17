#ifndef CPUSH_BUTTON_H
#define CPUSH_BUTTON_H

#include "CUI_Base.h"

class CPushButton
	: public CUI_Base
{
public:
	CPushButton();
	~CPushButton();

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
	const D3DXVECTOR3	BUTTON_POS = D3DXVECTOR3(195.0f, 500.0f, 0.0f);//�{�^���ʒu.
	const float			BUTTON_ALPHA_SPEED = 0.02f;						//�{�^�����ߑ��x.
	const float			BUTTON_ALPHA_MAX = 1.0f;						//�{�^�����ߍő�.
	const int			BUTTON_WAITTIME = 50;							//�{�^���ҋ@����.

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Release();			//��������֐�.
	void ButtonFade();		//�{�^���t�F�[�h�����֐�.

	//------------------------------------------.
	//	�ϐ�.
	//------------------------------------------.
	CSpriteUI*		m_pCPushButton;
	enFade			m_enButtonFade;
	float			m_fPushButtonAlpha;		//�{�^���w���̓��ߒl.
	int				m_FadeTime;				//�t�F�[�h����.

};


#endif //#ifndef CPUSH_BUTTON_H.