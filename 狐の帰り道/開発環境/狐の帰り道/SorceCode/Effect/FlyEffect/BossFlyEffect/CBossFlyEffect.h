#ifndef CBOSS_FLY_EFFECT_H
#define CBOSS_FLY_EFFECT_H

#include "..\CFlyEffect.h"

/****************************************
*		ボスが飛ぶ時のエフェクト.
****/
class CBossFlyEffect
	: public CFlyEffect
{
public:
	CBossFlyEffect();
	~CBossFlyEffect();

	//================定数==================//.
	const int	SMOKE_MAX			= 40;				//煙の最大数.
	const float	SMOKE_HALF			= SMOKE_MAX / 2.0f;	//煙の半分.
	const float SMOKE_QUATER		= SMOKE_HALF / 2.0f;//煙の4分の１.
	const float	START_POSITION_X	= -1.8f;			//左端の位置.
	const float	FOOT_DIFFERENCIAL	= 1.0f;				//中心から足元までの差分.
	const float	INTERVAL_WIDTH		= 0.2f;				//煙どうしの幅の間隔.
	const float INTERVAL_HEIGHT		= 0.5f;				//煙同士の高さの間隔.
	const float POS_UP_SPEED		= 0.00055f;			//上に上昇する速度.
	const float SPEED_UP			= 0.00005f;			//速度が上がる速度.
	const float	SCALE_SIZE_MIN		= 0.1f;				//大きさの最小値.
	const float	SCALE_UP_SPEED		= 0.01f;			//大きさが増える速度.
	const float STANDERD_TRAN_SPEED = 0.005f;			//基準の透過速度.
	const float TRANS_EXTRA_SPEED	= 0.0005f;			//それぞれの煙に上乗せする透過速度.
	const float ALPHA_MAX			= 1.0f;				//透過値最大数.
	const float	ROTATION_SPEED		= 0.05f;			//回転速度.
	const float ROTATION_MAX		= 3.5f;				//回転上限.
	const float	RIGHT_ROTATION_NUM	= -1.0f;			//左回転方向.
	const float MOVE_UPPER_LIMIT	= 0.7f;				//移動上限値.

	//================関数==================//.
	void UpDate();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.
private:
	//================関数==================//.
	void Init();				//初期化処理関数.
	void Release();				//解放処理関数.
	void Disp();				//表示判定処理関数.
	void Move();				//移動処理関数.
	void Scaling();				//スケールの変更処理関数.
	void TransparetProcess();	//透過処理関数.
	void Rotation();			//回転処理関数.

	//================変数===================//.
	float*	m_pfMoveSpeed;		//移動速度.
	bool*	m_pbIndiviDispFlag;	//個別表示フラグ.
	bool	m_bMoveFlag;		//移動フラグ.
	bool	m_bCheckFlag;		//確認フラグ.
};

#endif	//#ifndef CBOSS_FLY_EFFECT_H.