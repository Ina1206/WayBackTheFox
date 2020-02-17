#ifndef CLONG_PUSH_COMMAND_H
#define CLONG_PUSH_COMMAND_H

#include "..\CCommand_Base.h"
#include "..\..\Drawing\Bord_Polygon\DebugText\CDebugText.h"
#include "..\..\Effect\SparkleEffect\CFootEffect\CFootEffect.h"
#include "..\..\Effect\SparkleEffect\LongPushEffect\CLongPushEffect.h"

/***************************************
*		長押しコマンドクラス.
***********/
class CLongPushCommand
	: public CCommand_Base
{
public:
	CLongPushCommand();
	~CLongPushCommand();

	//===================定数======================//.
	const float COMMAND_POS_Z		= 1.4f;		//コマンドのz軸位置.
	const float DISP_ALPHA			= 20.0f;	//コマンド半透明表示.
	const float DISP_DEPTH			= 16.5f;	//コマンド表示奥行.
	const float ALPHA_MAX			= 1.0f;		//透過値の最大値.
	const float BUTTON_ALPHA		= 0.25f;	//ボタンの半透明時.
	const float ALPHA_SPEED			= 0.1f;		//透過値変更スピード.
	const float COMMAND_LENGHT		= 5.0f;		//コマンドの長さ.
	const float GREAT_RANGE			= 0.3f;		//Great範囲.
	const float GOOD_RANGE			= 0.8f;		//Good範囲.
	const float BAD_RANGE			= 1.5f;		//Bad範囲.
	const int	StartDecisionNum	= 0;		//開始位置の判定番号.
	const int	EndDecisionNum		= 1;		//終了位置の判定番号.
	const int	DECISION_TERMIN		= -1;		//判定終了番号.
	const float START_DISP_HEIGH	= 0.02f;	//初めのスプライトの表示調整の高かさ.
	const float DISP_HEIGH_ADJUST	= 0.01f;	//表示高さ調整.
	const float DEPTH_ADJUST		= 0.55f;	//表示奥行調整.
	const float	BUTTON_DISP_POS_MAX = 2.0f;		//ボタン表示高さ最大値.
	const float BUTTON_DISP_POS_MIN = 1.7f;		//ボタン表示高さ最小値.
	const float	BUTTON_DOWN_SPEED	= 0.05f;	//ボタンが下がる速さ.

	//==================列挙体=====================//.
	enum class enCommandSpriteType {
		CommandEnd,								//コマンドの最後の位置.
		Intermediate,							//コマンドの中間.
		CommandStart,							//コマンドの開始場所.

		Max,									//最大値.
		Start = CommandStart,					//開始位置.
	};

	//===================関数======================//.
	void UpDate(enCommandType CommandType);				//更新処理関数.
	void Render();										//描画処理関数.

private:
	//===================関数======================//.
	void Release();										//解放処理関数.
	void DispDecision();								//描画判定処理関数.
	void CommandDecision(enCommandType CommandType);	//コマンド判定処理関数.
	void CommandStartDecision();						//コマンドスタート地点判定処理関数.
	void CommandEndDecision();							//コマンド終了地点の判定処理関数.
	void CommandRender();								//コマンド画像の描画.

	//===================変数======================//.
	CSprite**		m_ppCCommandSprite;					//コマンドスプライト.
	D3DXVECTOR3*	m_pvCommandPos;						//長押しコマンド画像の位置.
	int				m_PushCount;						//押している間のカウント.
	bool			m_bSoundCheck;						//音を一回再生したかチェック.
	CEffectBase*	m_pCEffectBase;						//エフェクトクラス.
	float			m_fButtonHigh;						//ボタン表示高さ.
	D3DXVECTOR3		m_vOldPos;							//前回のボタン座標.
};

#endif	//#ifndef CLONG_PUSH_COMMAND_H.