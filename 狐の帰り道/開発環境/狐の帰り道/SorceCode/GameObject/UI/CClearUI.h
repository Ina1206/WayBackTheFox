#ifndef CCLEARUI_H
#define CCLEARUI_H

#include "CUI_Base.h"
#include "CPushButton.h"


//====================.
//	追加.
#include "..\..\Sound\CSEPlayManager.h"
//====================.



class CClearUI
	: public CUI_Base
{
public:
	CClearUI();
	~CClearUI();

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//------------------------------------------.
	//	定数.
	//------------------------------------------.
	const int SPRITEUI_MAX = 3;
	const int SPRITEUI_MAX_SMILE = 0;
	const int SPRITEUI_SMILE = 1;
	const int SPRITEUI_AMOUNT = 2;

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Release();			//解放処理関数.

	//------------------------------------------.
	//	変数.
	//------------------------------------------.
	CSpriteUI**		m_ppCClearSpriteUI;

	//=======================.
	//		追加.
	int				m_ClearNo;		//クリア番号.
	//=======================.

};

#endif//#ifndef CCLEARUI_H