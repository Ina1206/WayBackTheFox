#ifndef CGREAT_EFFECT_H
#define CGREAT_EFFECT_H

#include "..\CSparkleEffect.h"
#include "..\..\..\Drawing\Bord_Polygon\CDepth_Stencil.h"

/***************************************************
*		Great判定のエフェクト.
*****/
class CGreatEffect
	: public CSparkleEffect
{
public:
	CGreatEffect();
	~CGreatEffect();

	//==================定数=======================//.
	const int	SPARKLE_MAX			= 10;			//キラキラの最大数.
	const int	ROW_MAX				= 2;			//横列の最大数.
	const float	CENTER_DIFFERENCIAL = 1.5f;			//中心から上に対する差分.
	const float	HEIGHT_WIDTH		= 0.3f;			//高さの幅.
	const float LEFT_INTERVAL		= 0.2f;			//左の幅の間隔.
	const float RIGHT_INTERVAL		= 0.4f;			//右の幅の間隔.
	const float LEFTMOST			= -0.7f;		//左端.
	const float RIGHTMOST			= 1.3f;			//右端.
	const int	USE_SPARKLE_MAX		= 3;			//使用するキラキラ画像の最大数.
	const float SCALE_MAX			= 0.75f;		//大きさ.

	//==================関数=======================//.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.

private:
	//==================関数======================//.
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.
};

#endif //#ifndef CGREAT_EFFECT_H.