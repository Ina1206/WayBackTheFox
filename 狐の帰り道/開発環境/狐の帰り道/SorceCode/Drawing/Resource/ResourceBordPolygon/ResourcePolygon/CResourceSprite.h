#ifndef CRESOURCE_SPRITE_H
#define CRESOURCE_SPRITE_H

#include "..\..\..\Bord_Polygon\GameSprite\CSprite.h"

#include "..\..\CResourceBase.h"

/**********************************************************
*		スプライトクラス.
***/
class CResourceSprite 
	: public CResourceBase
{
public:
	CResourceSprite();
	~CResourceSprite();

	//====================定数=======================//.
	const float			BUTTON_BASE_SIZE	= 250.0f;						//ボタンベースの一辺の長さ.
	const float			BUTTON_DISP_SIZE	= 0.5f;							//ボタン表示時の一辺の長さ.
	const float			MARU_BASE_SIZE		= 800.0f;						//丸ベースの一辺の長さ.
	const float			MARU_DISP_SIZE		= 1.0f;							//丸表示時の一辺の長さ.
	const D3DXVECTOR2	HIT_BASE_SIZE		= D3DXVECTOR2(100.0f, 200.0f);	//当たった時の元画像の大きさ.
	const D3DXVECTOR2	HIT_DISP_SIZE		= D3DXVECTOR2(1.0f, 2.0f);		//当たった時の表示画像の大きさ.
	const float			EFFECT_BASE_SIZE	= 200.0f;						//エフェクトの画像のサイズ.
	const float			EFFECT_DISP_SIZE	= 0.8f;							//エフェクトの表示サイズ.
	const float			CCHAR_DISP_SIZE		= 0.025f;							//文字の表示サイズ.	
	const float			CCHAR_HIGH_DISP_SIZE = 0.020f;						//文字の表示サイズ.	
	const D3DXVECTOR2	LONG_SQUARE_BASE	= D3DXVECTOR2(600.0f, 1200.0f);	//通常の長押し四角スプライトの一辺の長さ.
	const D3DXVECTOR2	LONG_SQUARE_DISP	= D3DXVECTOR2(1.0f, 5.0f);		//長押し四角の表示長さ.
	const float			SHADOW_BASE_SIZE	= 250.0f;						//影の元のサイズ.
	const float			SHADOW_DISP_SIZE	= 1.0f;							//影の表示サイズ.

	//===================列挙体======================//.
	//Spriteの種類.
	enum class enSprite {
		Vegetable = 0,			//野菜.
		Meat,					//肉.
		Fish,					//魚.
		Rice,					//米.
		TimingCommand,			//タイミングコマンド用.
		LongPushCircle,			//長押しコマンドの円.
		Long_Square,			//長押しコマンド中央の真ん中四角.
		AButton,				//Aボタン.
		BButton,				//Bボタン.
		XButton,				//Xボタン.
		YButton,				//Yボタン.
		HitButton,				//ボタンを押したとき.
		Hit,					//当たる時.
		Punch,					//パンチ.
		Sparkle,				//キラキラ.
		Sparkle_Blue,			//キラキラ(青).
		Smoke,					//煙.
		Char_High,				//高.
		Char_Middle,			//中.
		Char_Low,				//低.
		Char_Evaluation,		//評価.
		Shadow,					//影.

		Max,					//最大数.
		Start = Vegetable,		//地面2つ目.//最初.
		ItemStart = Vegetable,	//アイテム画像の最初.
		CommandStart = AButton, //コマンドの画像の最初.
	};

	//====================関数======================//.
	HRESULT Init();													//初期設定処理関数.
	HRESULT Load();													//読み込み処理関数.
	HRESULT ReleaseCalling();										//解放処理呼び出し関数.

	//===============情報獲得処理関数================//.
	CSprite*	GetSprite(enSprite Sprite);
private:
	//====================関数======================//.
	HRESULT Create(enSprite Sprite, const char* pfileName);	//作成処理関数.
	HRESULT Release(enSprite Sprite);						//解放処理関数.
	HRESULT Check_SpriteRnge(enSprite Sprite);				//スプライトの範囲を調べる関数.
	CSprite::SPRITE_STATE stSpriteState(enSprite Sprite);		//スプライト情報設定.

	//===================クラス=====================//.
	CSprite**	m_ppSprite;										//スプライトクラス.
	CSprite::SPRITE_STATE* m_pSprite_State;						//スプライトの状態.

};

#endif //#ifndef CRESOURCE_SPRITE_H.