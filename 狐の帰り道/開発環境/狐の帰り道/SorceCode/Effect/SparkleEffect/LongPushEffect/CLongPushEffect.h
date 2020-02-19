#ifndef CLONGPUSH_EFFECT_H
#define CLONGPUSH_EFFECT_H

#include "..\..\CEffectBase.h"

/*****************************************
*		長押し時のエフェクトクラス.
***/
class CLongPushEffect
	: public CEffectBase
{
public:
	CLongPushEffect();
	~CLongPushEffect();

	//====================定数========================//.
	const int			SPARKLE_MAX			= 40;							//キラキラの最大数.
	const int			USE_SPARKLE_MAX		= 3;							//使用するキラキラの種類の最大数.
	const int			SPARKLE_HORIZON_MAX = 2;							//星の横列の最大数.
	const int			SPARKLE_POP_TIME	= 7;							//キラキラの出現時間.
	const D3DXVECTOR2	INTERVAL			= D3DXVECTOR2(0.2f, 0.4f);		//左右の間隔(x: 左側	y:右側).
	const D3DXVECTOR2	MOST				= D3DXVECTOR2(-0.5f, 0.9f);		//左右の端(x:左, y右).
	const float			STANDERD_HEIGHT		= 0.01f;						//基準の高さ.
	const float			FLOW_SPEED			= 0.05f;						//流れる速度.
	const float			SCALE_MAX			= 1.0f;							//大きさの最大値.
	const float			SCALE_MIN			= 0.0f;							//大きさの最小値.
	const float			SCALING_SPEED		= 0.02f;						//拡縮の速度.

	//====================関数========================//.
	void Update();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.
private:
	//====================関数=======================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void Disp();							//表示処理関数.
	void SettingPosition(int sparkle);		//位置座標設定関数.
	void Move();							//移動処理関数.
	void Scaling(int sparkle);				//拡縮処理関数.

	//====================変数=======================//.
	int				m_PopTime_Cnt;			//出現カウント.
	bool*			m_pbIndividual_Disp;	//個別表示フラグ.
	
};

#endif	//#ifndef CLONGPUSH_EFFECT_H.