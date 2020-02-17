#ifndef CLANDING_EFFECT_H
#define CLANDING_EFFECT_H

#include "..\CEffectBase.h"

/*************************************
*		着地エフェクトクラス.
***************/
class CLandingEffect
	: public CEffectBase
{
public:
	CLandingEffect();
	~CLandingEffect();

	//=================定数====================//.
	const int			SMOKE_MAX		= 2;							//煙の最大数.
	//大きさ.
	const float			SCALE_MAX		= 1.0f;							//煙の大きさ最大値.
	const float			SCALE_MIN		= 0.2f;							//煙の大きさ最小値.
	const float			SCALE_SPEED		= 0.008f;						//拡大速度.
	//透過.
	const float			ALPHA_MAX		= 1.0f;							//透過値の最大数.
	const float			ALPHA_MIN		= 0.0f;							//透過値の最小数.
	const float			TRANS_SPEED		= 0.01f;						//透過速度.
	//位置.
	const float			START_POS		= 0.05f;						//真ん中からの始める位置.
	const float			INTERVAL_WIDTH	= 0.08f;						//煙同士の間隔の幅.
	const D3DXVECTOR2	MOVE_SPEED		= D3DXVECTOR2(0.005f, 0.001f);	//移動速度.
	//角度.
	const float			ROTATION_MAX	= 6.5f;							//回転値最大数.
	const float			ROTATION_SPEED	= 0.05f;						//回転速度.
	

	//=================関数====================//.
	void UpDate();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.
private:
	//=================関数====================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void Position_Setting(int smoke);		//位置設定処理関数.
	void Move();							//移動処理関数.
	void Alpha_Scaling(int smoke);			//透過と拡大処理関数.

	//=================変数====================//.
	float*		m_pfAlpha;					//透過値.
};

#endif	//#ifndef CLANDING_EFFECT_H.