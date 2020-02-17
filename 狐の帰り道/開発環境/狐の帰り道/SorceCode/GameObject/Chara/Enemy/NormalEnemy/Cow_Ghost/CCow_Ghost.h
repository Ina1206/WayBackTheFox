#ifndef _CCOW_GHOST_H
#define _CCOW_GHOST_H

#include "..\CNormalEnemyBase.h"
#include "..\..\..\..\..\Command\TimingCommand\CTimingCommand.h"

class CCow_Ghost
	: public CNormalEnemyBase
{
public:
	CCow_Ghost(); 
	~CCow_Ghost();

	//=====================定数========================//.
	const float STANDERD_HIGH			= 0.3f;		//基本高さ.
	const float HIGH_MAX				= 1.3f;		//高さの最大値.
	const int	JUMP_MAX				= 2;		//ジャンプ回数最大数.
	const float CENTER_POS_X			= 0.0f;		//真ん中のレーンの位置.
	const float	LANE_MIN				= -1.5f;	//レーンの最小値.
	const float LANE_MAX				= 1.5f;		//レーンの最大値.
	const float MOVE_WIDTH				= 1.5f;		//移動幅.
	const float VERTICAL_SPEED			= 0.01f;	//縦移動のスピード.
	const float HORIZON_SPEED			= 0.1f;		//横移動のスピード.
	const float STOP_DISTANCE			= 7.0f;		//移動停止距離.
	const float SHADOW_DISP_UP_LIMIT	= 2.5f;		//影の表示上限.

	const float COMMAND_HIGH			= 1.1f;		//コマンドの高さ.

	const float EFFECT_DISP_POS			= 10.0f;	//エフェクト表示距離.

	//====================列挙体=======================//.
	//縦移動種類.
	enum class enVerticalMove_Type {
		Up = 0,			//上.
		Down,			//下.	
		Waiting,		//待機.

		Max,			//最大値.
		Start = Up,		//始まり.
	};

	//横移動種類.
	enum class enHorizonMove_Type {
		Right_Move,			//右.
		Left_Move,			//左.

		Max,				//最大値.
		Start = Right_Move,	//始まり.
	};


	//=====================関数========================//.
	void Init_Process();				//初期化処理関数.
	void UpDate();						//更新処理関数.
	void Render();						//描画処理関数.
	void Release();						//解放処理関数.


private:
	//=====================関数========================//.
	void Move();						//移動処理関数.
	void FarMove();						//遠いときの移動処理関数.
	void HorizonMove();					//横移動処理関数.

	//=====================変数========================//.
	//～クラス～.
	CDX9Mesh*				m_pStaticMesh;			//オブジェクト.

	enVerticalMove_Type		m_enVerticalMoveType;	//縦移動種類.
	enHorizonMove_Type		m_enHorizonMoveType;	//横移動種類.
	int						m_JumpCnt;				//ジャンプカウント.
	float					m_fOldPos_x;			//前回の横座標.
	bool					m_bCheckSE;				//SEの再生フラグ.
};

#endif	//#ifndef _CCOW_GHOST_H.