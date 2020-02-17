#ifndef CRESOURCE_SPRITE_UI_H
#define CRESOURCE_SPRITE_UI_H

#include "..\..\CResourceBase.h"

#include "..\..\..\Bord_Polygon\GameSprite\CSpriteUI.h"

/*************************************************
*	SpriteUI読み込みクラス.
**/
class CResourceSpriteUI
	: public CResourceBase
{
public:
	CResourceSpriteUI();
	~CResourceSpriteUI();

	//====================定数=======================//.
	const int           ICON_SPRITE_MAX			= 4;							//アイコンのスプライトの最大数.
	const float			ICON_SIZE				= 200.0f;						//アイコン画像元サイズ.
	const float			ICON_DISP_SIZE			= 125.0f;						//アイコン画像表示サイズ.
	const D3DXVECTOR2	TIME_BASE				= D3DXVECTOR2(500.0f, 200.0f);	//時間の画像元サイズ.		
	const D3DXVECTOR2	TIME_IMAGE_DELIMITER	= D3DXVECTOR2(5.0f, 2.0f);		//画像の区切り.
	const D3DXVECTOR2	TIME_DISP				= D3DXVECTOR2(80.0f, 80.0f);	//時間画像表示サイズ.
	const D3DXVECTOR2	BARRAGE_BASE_SIZE		= D3DXVECTOR2(552.0f, 107.0f);	//ゲージの枠の元.
	const D3DXVECTOR2	GAGE_BASE_SIZE			= D3DXVECTOR2(488.0f, 38.0f);	//ゲージの元画像サイズ.
	const float			GAGE_DISP_SIZE_W		= 800.0f;						//ゲージの表示幅の長さ.
	const float			GAGE_DISP_SIZE_H		= 80.0f;						//ゲージの表示高さの長さ.
	const int			FACE_SPRITE_MAX			= 3;
	const float			FACE_SIZE				= 600.0f;						//顔アイコン元サイズ.
	const float			FACE_DISP_SIZE			= 240.0f;						//顔アイコン表示サイズ.
	const float			FACE_AMOUNT_SIZE		= 400.0f;						//顔アイコン額縁元サイズ.
	const float			FACE_AMOUNT_DISP_SIZE	= 330.0f;						//顔アイコン額縁表示サイズ.


	//===================列挙体======================//.
	//Spriteの種類.
	enum class enSpriteUI {
		MeatIcon = 0,		//肉アイコン.
		FishIcon,			//魚アイコン.
		VegetableIcon,		//野菜アイコン.
		RiceIcon,			//米アイコン.
		TimerNum,			//時間の番号.
		GageGround,			//ゲージ下地.
		BarratGage,			//ゲージ.
		faceIcom_Normal,	//顔アイコンノーマル.
		faceIcom_Smile,		//顔アイコンスマイル.
		faceIcom_MaxSmile,	//顔アイコン最大級のスマイル.
		faceIcom_Amount,	//顔アイコン額縁.
		Goal,				//ゴール.
		Kitune,				//狐.
		No,					//の.
		kae,				//帰.
		Ri,					//り.
		Miti,				//道.
		Line,				//線.
		Maple,				//もみじ.
		PushButton,			//ボタンを押す指示.
		Clear_High,			//クリア高.
		Clear_Middle,		//クリア中.
		Clear_Low,			//クリア低.
		Bran,				//ふすま.
		Start_Char,			//スタート.
		Face_High_Back,		//顔アイコン背景.
		Face_Middle_Back,	//顔アイコン背景.
		Face_Low_Back,		//顔アイコン背景.
		Point_Bar_Back,		//ポイントバー.
		Point_BlueBar,		//青バー.
		Point_RedBar,		//赤バー.
		Point_RainbowBar,	//虹バー.

		Max,				//最大数.
		Start = MeatIcon,	//最初.
	};


	//====================関数======================//.
	HRESULT Init();													//初期設定処理関数.
	HRESULT Load();													//読み込み処理関数.
	HRESULT ReleaseCalling();										//解放処理呼び出し関数.

	//===============情報獲得処理関数================//.
	CSpriteUI*	GetSpriteUI(enSpriteUI SpriteUI);
private:
	//====================関数======================//.
	HRESULT Create(enSpriteUI SpriteUI, const char* pfileName);		//作成処理関数.
	HRESULT Release(enSpriteUI SpriteUI);							//解放処理関数.
	HRESULT Check_SpriteUIRnge(enSpriteUI SpriteUI);				//SpriteUIの範囲を調べる関数.
	CSpriteUI::SPRITE_STATE GetSpriteUIState(enSpriteUI SpriteUI);

	//===================クラス=====================//.
	CSpriteUI**	m_ppSpriteUI;										//メッシュクラス.
	CSpriteUI::SPRITE_STATE* m_pSpriteUI_State;
};

#endif	//#ifndef CRESOURCE_SPRITE_UI_H.