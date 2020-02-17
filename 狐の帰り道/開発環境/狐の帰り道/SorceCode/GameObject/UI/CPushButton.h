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
	//	関数.
	//------------------------------------------.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//------------------------------------------.
	//	定数.
	//------------------------------------------.
	const D3DXVECTOR3	BUTTON_POS = D3DXVECTOR3(195.0f, 500.0f, 0.0f);//ボタン位置.
	const float			BUTTON_ALPHA_SPEED = 0.02f;						//ボタン透過速度.
	const float			BUTTON_ALPHA_MAX = 1.0f;						//ボタン透過最大.
	const int			BUTTON_WAITTIME = 50;							//ボタン待機時間.

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Release();			//解放処理関数.
	void ButtonFade();		//ボタンフェード処理関数.

	//------------------------------------------.
	//	変数.
	//------------------------------------------.
	CSpriteUI*		m_pCPushButton;
	enFade			m_enButtonFade;
	float			m_fPushButtonAlpha;		//ボタン指示の透過値.
	int				m_FadeTime;				//フェード時間.

};


#endif //#ifndef CPUSH_BUTTON_H.