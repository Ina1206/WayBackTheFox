#ifndef CCLEARUI_H
#define CCLEARUI_H

#include "CUI_Base.h"
#include "CPushButton.h"


//====================.
//	�ǉ�.
#include "..\..\Sound\CSEPlayManager.h"
//====================.



class CClearUI
	: public CUI_Base
{
public:
	CClearUI();
	~CClearUI();

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
	const int SPRITEUI_MAX = 3;
	const int SPRITEUI_MAX_SMILE = 0;
	const int SPRITEUI_SMILE = 1;
	const int SPRITEUI_AMOUNT = 2;

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Release();			//��������֐�.

	//------------------------------------------.
	//	�ϐ�.
	//------------------------------------------.
	CSpriteUI**		m_ppCClearSpriteUI;

	//=======================.
	//		�ǉ�.
	int				m_ClearNo;		//�N���A�ԍ�.
	//=======================.

};

#endif//#ifndef CCLEARUI_H