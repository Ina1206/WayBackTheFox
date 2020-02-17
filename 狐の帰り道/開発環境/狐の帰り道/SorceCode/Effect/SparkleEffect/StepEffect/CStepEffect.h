#ifndef CSTEP_EFFECT_H
#define CSTEP_EFFECT_H

#include "..\CSparkleEffect.h"

/**************************************
*	敵を踏むときのエフェクトクラス.
******/
class CStepEffect
	: public CSparkleEffect
{
public:
	CStepEffect();
	~CStepEffect();	

	//=====================定数========================//.
	const int			SPARKLE_MAX				= 6;						//キラキラの最大数.
	const D3DXVECTOR2	START_POSITION			= D3DXVECTOR2(0.3f, 0.35f);	//中心からの開始位置.
	const int			HORIZON_SPARKLE			= 2;						//横のキラキラの数.
	const int			USE_SPARKLE_MAX			= 3;						//使われるキラキラの種類最大数.
	const D3DXVECTOR2	ARRANGEMENT_INTERVAL	= D3DXVECTOR2(0.25f, 0.15f);//配置間隔.
	const float			SCALE_MAX				= 0.5f;						//大きさの最大数.
	const D3DXVECTOR2	INTERVAL				= D3DXVECTOR2(0.2f, 0.3f);	//左右の間隔(x:左の間隔,	y:右の間隔).
	const D3DXVECTOR2	MOST					= D3DXVECTOR2(-0.3f, 0.5f);	//左右の両端(x:左の端,	y:右の端).

	//=====================関数========================//.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.
private:

	//=====================関数========================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.

};

#endif	//#ifndef CSTEP_EFFECT_H.