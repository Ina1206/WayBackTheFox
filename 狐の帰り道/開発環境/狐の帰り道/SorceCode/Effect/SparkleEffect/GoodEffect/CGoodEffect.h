#ifndef CGOOD_EFFECT_H
#define CGOOD_EFFECT_H

#include "..\CSparkleEffect.h"

/*********************************************
*		Good判定のエフェクト.
***/
class CGoodEffect
	: public CSparkleEffect
{
public:
	CGoodEffect();
	~CGoodEffect();

	//================定数=====================//.
	const int	SPARKLE_MAX			= 4;	//キラキラの総合最大数.   
	const int	ROW_MAX				= 2;	//横列のキラキラの最大数.
	const float	CENTER_DIFFECENCIAL = 1.0f;	//中央から始める高さの差分.
	const float	HEIGHT_WIDHT		= 0.5f;	//高さの幅.
	const float	LEFT_INTERVAL		= 0.2f;	//左側の間隔.
	const float RIGHT_INTERVAL		= 0.4f;	//右側の間隔.
	const float LEFT_MOST			= -0.5f;//左端.
	const float	RIGHT_MOST			= 0.9f;	//右端.
	const float SCALE_MAX			= 0.8f;	//大きさ.

	//================関数=====================//.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.
private:
	//================関数=====================//.
	void Init();															//初期化処理関数.
	void Release();															//解放処理関数.
};

#endif	//#ifndef CGOOD_EFFECT_H.