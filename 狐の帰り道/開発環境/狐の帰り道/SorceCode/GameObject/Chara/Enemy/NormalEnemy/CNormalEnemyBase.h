#ifndef CNORMAL_ENEMY_BASE_H
#define CNORMAL_ENEMY_BASE_H

#include "..\CEnemyBase.h"

/******************************************
*		通常敵の元クラス.
*********/
class CNormalEnemyBase
	: public CEnemyBase
{
public:
	CNormalEnemyBase();
	~CNormalEnemyBase();

	//================定数=====================//.
	const float			LEFT_JUMP_ROT			= 0.6f;							//左に飛ぶ時の傾き.		
	const float			RIGHT_JUMP_ROT			= -0.9f;						//右に飛ぶ時の傾き.
	const int			STANDERD_USE_COMMAND	= 0;							//基準で使うコマンド番号.
	const int			DECISION_MAX			= 2;							//判定結果の最大数.
	const int			LEFT_DIRECTION			= -1;							//左方向番号.
	const int			RIGHT_DIRECTION			= 1;							//右方向番号.
	const float			ROT_SPEED				= 0.1f;							//傾く速度.
	const D3DXVECTOR2	FLY_SPEED				= D3DXVECTOR2(0.1f, 0.15f);		//飛ぶ速度.

	//===============列挙体=====================//.
	//飛ぶ方向.
	enum class enFlyDirection {
		Left,	//左.
		Right,	//右.
	};

	//================関数======================//.
	void FlyJudge();	//飛ぶ判定処理関数.
	void FlyMove();		//飛んでいく移動処理関数.

	//～情報獲得処理関数～.
	int					GetHitNum()						{ return m_HitNum; }									//当たった回数獲得処理.	
	enInput_Decision	GetInputDecision(int num = 0)	{ return m_pCCommand_Base->GetInputDeision(num); }		//コマンド判定結果.


	//～情報置換処理関数～.
	void SetHitNum		(int Num)		{ m_HitNum = Num; }				//当たった番号.		
	void SetButtonNum	(int ButtonNum)	{ m_ButtonNum = ButtonNum; }	//ボタン番号.

	void SetInputDecision(enInput_Decision enDecision, int num = 0) { m_enInputDecision[num] = enDecision; }//コマンド判定結果.

protected:

	//===============変数==================//.
	int					m_HitNum;			//当たった回数.		
	int					m_HitMoveDirection;	//当たった時の移動方向.
	bool				m_HitFlag;			//当たったフラグ.		
	int					m_ButtonNum;		//ボタン番号.
	enInput_Decision*	m_enInputDecision;	//判定結果.


	CEnemyFlyEffect* m_pCEnemyFlyEffect;	//飛んで行くエフェクトクラス.
private:

};

#endif	//#ifndef CNORMAL_ENEMY_BASE_H.