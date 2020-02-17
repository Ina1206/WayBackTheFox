#ifndef CENEMY_FLY_EFFECT_H
#define CENEMY_FLY_EFFECT_H

#include "..\CFlyEffect.h"

/*************************************
*		敵が飛ぶ時のエフェクト.
*******/
class CEnemyFlyEffect
	: public CFlyEffect
{
public:
	CEnemyFlyEffect();
	~CEnemyFlyEffect();

	//====================定数======================//.
	const int	SMOKE_MAX			= 30;		//煙の最大数.
	const int	ROW_MAX				= 2;		//煙の横の列の最大数.
	const float	START_POSITION_X	= -0.8f;	//左端の位置.
	const float	FOOT_DIFFERENCIAL	= 0.1f;		//中心から足元までの差分.
	const float	INTERVAL_WIDTH		= 0.8f;		//煙どうしの幅の間隔.
	const float MAX_SCALE			= 1.0f;		//大きさの最大値.
	const float ALPHA_MAX			= 1.0f;		//透過値の最大値.

	//====================関数======================//.
	void UpDate();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.

private:
	//====================関数======================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.


};


#endif	//#ifndef CENEMY_FLY_EFFECT_H.