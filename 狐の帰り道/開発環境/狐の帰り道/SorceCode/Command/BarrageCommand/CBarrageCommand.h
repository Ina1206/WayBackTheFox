#ifndef CBARRAGE_COMMAND_H
#define CBARRAGE_COMMAND_H

#include "..\CCommand_Base.h"

#include "..\..\Effect\HitEffect\CHitEffect.h"

/****************************************
*		連打コマンドクラス.
***************/
class CBarrageCommand
	: public CCommand_Base
{
public:
	CBarrageCommand();
	~CBarrageCommand();

	//==========================定数=============================//.
	const float			BUTTON_POS_Y		= 2.0f;									//ボタンの配置y軸.
	const float			BUTTON_POS_Z		= 1.4f;									//ボタンの配置z軸.
	const int			GAGE_GROUN_NUM		= 0;									//ゲージ下地番号.
	const int			GAGE_NUM			= 1;									//ゲージ番号.
	const int			GAGE_SPRITE_MAX		= 2;									//ゲージのスプライト最大数.
	const D3DXVECTOR3	GAGE_POS			= D3DXVECTOR3(400.0f, 550.0f, 0.01f);	//ゲージの位置.
	const D3DXVECTOR3	GAGE_POS_ADJUST		= D3DXVECTOR3(34.0f, 32.0f, 0.01f);		//ゲージの中の位置の調整.
	const float			GAGE_LENGTH_MAX		= 5.0f;									//ゲージの長さ最大値.
	const float			GAGE_HALF			= 2.0f;									//ゲージの半分.
	const float			GAGE_POS_START		= 2.5f;									//ゲージの開始位置調整.

	const int			BARRAGE_MAX			= 50;									//連打の最大数.
	const int			MAX_TIME			= 15;									//制限時間.
	const int			SOUND_TIME			= 5;									//音を鳴らしだす制限時間.
	const int			FRAME				= 60;									//フレーム.
	const int			TIME_SPRITE_MAX		= 2;									//時間のスプライト最大数.
	const int			TIME_TENS_PLACE		= 0;									//制限時間の10の位のスプライト.
	const int			TIME_ONE_RANK		= 1;									//制限時間の1の位のスプライト.
	const int			TIME_TENS			= 10;									//十の位.
	const int			IMAGE_WIDTH_MAX		= 5;									//画像内の区切り(横)最大数.
	const int			IMAGE_HIGH_MAX		= 5;									//画像内の区切り(縦)最大数.
	const float			TIME_WIDTH			= 100.0f;								//時間の描画幅.
	const float			TIME_SCALE_MAX		= 2.0f;									//時間の描画時の大きさ最大値.
	const float			TIME_SCALE_MIN		= 1.0f;									//時間の描画時の大きさ最小値.
	const D3DXVECTOR3	TIME_DISP_POS		= D3DXVECTOR3(550.0f, 90.0f, 0.0f);		//時間の表示位置.
	const float			TIME_SCALE_SPEED	= 0.1f;									//時間のスプライト拡縮速度.
	const float			MAX_ALPHA			= 1.0f;									//透過値最大値.
	const float			MIN_ALPHA			= 0.5f;									//透過値最小値.
	const int			USE_BUTTON_MAX		= 3;									//使われるボタン最大数.
	const float			BUTTONSCALE_MAX		= 2.0f;									//ボタンの大きさ最大値.
	const float			BUTTONSCALE_MIN		= 1.0f;									//ボタンの大きさ最小値.
	const float			SCALE_SPEED_BUT		= 0.1f;									//ボタンの縮小速度.

	const float			PUSH_ALPHA_MAX		= 1.0f;									//ボタン押したときの透過値最大数.
	const float			PUSH_ALPHA_MIN		= 0.0f;									//ボタン押したときの透過値最小数.
	const float			PUSH_SCALE_MAX		= 1.5f;									//ボタン押したときの大きさ最大数.
	const float			PUSH_SCALE_MIN		= 0.5f;									//ボタン押したときの大きさ最小値.
	const float			PUSH_SCALE_SPEED	= 0.2f;									//ボタン押したときの拡縮スピード.
	const float			PUSH_ALPHA_SPEED	= 0.15f;								//ボタン押したときの透過速度.

	const int			CHANGE_WAIT_TIME	= 60;									//ボタン変更後の猶予時間.

	const float			HIT_EFFECT_SCALE	= 0.5f;									//押したときのエフェクトの大きさ.
	const float			EFFECT_HIGH			= 0.25f;								//エフェクトの表示高さ.

	//==========================関数=============================//.
	void Update(enCommandType CommandType);				//更新処理関数.
	void Render();										//描画処理関数.
private:
	//==========================関数=============================//.
	void Release();										//解放処理関数.
	void DecisionCommand(enCommandType CommandType);	//コマンド判定処理関数.
	void Time();										//時間処理判定.
	void RenderTime();									//時間描画処理関数.
	void ChangeButton();								//ボタン変更処理関数.
	void RenderButton();								//ボタンの描画.
	void RenderGage();									//ゲージの描画.
	void RenderPushButton();							//ボタンを押したときの描画処理関数.
	void DecisionDisp();								//表示判定処理関数.

	//==========================変数=============================//.
	float			m_fAlpha;				//透過値.
	CSpriteUI**		m_ppCGageSprite;		//ゲージのスプライト.
	D3DXVECTOR3*	m_pvGagePos;			//ゲージの位置.
	int				m_fPushCnt;				//押すカウント.
	int				m_BarrageButtonNum;		//連打ボタン番号.
	int				m_OldBarrageButtonNum;	//連打ボタン番号前回.
	int				m_ChangeButtonCnt;		//変更前の連打数.
	int				m_ChangeAfterCnt;		//変更後のカウント.

	CSprite*		m_pCPushButtonSprite;	//ボタンを押したスプライトクラス.
	float			m_fPushButtonAlpha;		//ボタンを押したスプライトの透過値.
	float			m_fPushButtonSize;		//ボタンを押したスプライトの大きさ.

	bool			m_bButtonChangeSE;		//連打ボタン変更時の鳴らすかのSEフラグ.
	int				m_BarrageCheckCnt;		//連打確認処理関数.
	float			m_fButtonScale;			//ボタンのスケール.
	int				m_Timer;				//制限時間.
	int				m_Timer_num;			//フレーム計算用.
	CSpriteUI**		m_ppCTimeSprite;		//タイムのスプライト.

	CHitEffect*		m_pCHitEffect;			//連打時のエフェクト.

	bool			m_bBGMChange;			//BGM変更フラグ.
};

#endif	//#ifndef CBARRAGE_COMMAND_H.