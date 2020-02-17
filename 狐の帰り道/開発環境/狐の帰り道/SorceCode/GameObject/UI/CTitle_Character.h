#ifndef CTITLE_CHARACTER_H
#define CTITLE_CHARACTER_H

#include"CUI_Base.h"
//コントローラクラス.
#include"..\..\Controller\CXInput.h"

class CTitle_Character
	: public CUI_Base
{
public:
	//------------------------------------------.
	//	定数.
	//------------------------------------------.
	const float		TITLE_MOVE_SPEED	= 0.1f;		//タイトル移動速度.
	const float		TITLE_ALPHA_SPEED	= 0.01f;	//タイトル透過速度.
	const float		TITLE_ALPHA_MAX		= 1.0f;		//タイトル透過最大.
	const int		SPRITEUI_MAX		= 7;		//spriteUIの最大数.
	const int		KITUNE_NUM			= 1;
	const int		NO_NUM				= 2;
	const int		KAE_NUM				= 3;
	const int		RI_NUM				= 4;
	const int		MITI_NUM			= 5;
	const int		LINE_NUM			= 6;
	const int		MAPLE_NUM			= 0;
	const float     SCALE_MAX			= 1.0f;
	const float		SCALE_SPEED			= 0.007f;
	const float		POSITION_Y			= 5.0f;
	const int		INPUT_OK			= 3;		//操作可能時間.
	const int		DISPLAY_TIME		= 20;		//タイトル文字表示時間.

	const D3DXVECTOR2 KITUNE_POS	= D3DXVECTOR2(180.0f, 85.0f);
	const D3DXVECTOR2 NO_POS		= D3DXVECTOR2(510.0f, 180.0f);
	const D3DXVECTOR2 KAE_POS		= D3DXVECTOR2(620.0f, 200.0f);
	const D3DXVECTOR2 RI_POS		= D3DXVECTOR2(785.0f, 230.0f);
	const D3DXVECTOR2 MITI_POS		= D3DXVECTOR2(880.0f, 150.0f);
	const D3DXVECTOR2 LINE_POS		= D3DXVECTOR2(160.0f, 370.0f);
	const D3DXVECTOR2 MAPLE_POS		= D3DXVECTOR2(650.0f, -15.0f);

	const double PI					= 3.14159265358979;

	CTitle_Character();
	~CTitle_Character();

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//------------------------------------------.
	//	列挙体.
	//------------------------------------------.
	enum class enTitle_Status
	{
		Character_Display = 0,	//文字表示.
		Draw_Line,				//線を引く.
		Maple_Display,			//もみじ表示.
	};

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Release();					//解放処理関数.
	void TitleMove();				//タイトル文字動作処理関数.
	void TitleFade(int num);		//タイトル文字透過処理関数.

	//------------------------------------------.
	//	変数.
	//------------------------------------------.
	clsXInput*		m_pCInput;				//コントローラクラス.
	CSpriteUI**		m_ppCTitleSpriteUI;
	enTitle_Status	m_enTitle_Status;		//タイトルの状態.
	D3DXVECTOR2*	m_vTitlePos;			//タイトル位置.
	float*			m_fTitleAlpha;			//タイトルの透過値.
	int				m_Frame;				//タイトルフェード時間.
	bool			*m_DispFlag;			//描画フラグ.
	int				m_DispNum;				//描画番号.
	float			m_LineSCale;			//線の大きさ.
};

#endif //#ifndef CTITLE_CHARACTER_H