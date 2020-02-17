#ifndef CHORIZON_MOVE_EFFECT_H
#define CHORIZON_MOVE_EFFECT_H

#include "..\CEffectBase.h"

/****************************************
*		横移動時のエフェクトクラス.
******/
class CHorizonMoveEffect
	: public CEffectBase
{
public:
	CHorizonMoveEffect();
	~CHorizonMoveEffect();

	//================定数===================//.
	const int	SMOKE_MAX		= 3;		//煙の最大数.
	const float	DISP_HEIGHT		= 0.1f;		//煙の表示高さ.
	const int	POP_TIME		= 5;		//表示する間隔.
	const float SCALE_MIN		= 0.2f;		//大きさの最小値.
	const float SCALE_MAX		= 1.0f;		//大きさの最大値.
	const float ALPHA_MAX		= 1.0f;		//透過値の最大値.
	const float ALPHA_MIN		= 0.0f;		//透過値の最小値.
	const float INTEFER_CHANGE	= 10.0f;	//整数に変換する用の数値.
	const float SCALING_SPEED	= 0.005f;	//拡大速度.
	const float ALPHA_SPEED		= 0.01f;	//透過値速度.
	const float ROTATION_SPEED	= 0.1f;		//回転速度.

	//================関数===================//.
	void UpDate();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.
private:
	//================関数===================//.
	void Init();							//初期化処理関数.
	void Release();							//解放処理関数.
	void Disp();							//表示処理関数.
	void Move();							//移動処理関数.
	void Scaling_Transparent(int smoke);	//拡大と透過処理関数.

	//================変数===================//.
	float*		m_pfAlpha;				//透過値.
	bool*		m_pbPerson_DispFlag;	//個人の表示フラグ.
	D3DXVECTOR3	m_vOldCenterPos;		//前回の中央の位置.
	int			m_PopCnt;				//出現カウント.
	float		m_fRotation_Distance;	//回転方向.
};

#endif	//#ifndef CHORIZON_MOVE_EFFECT_H.