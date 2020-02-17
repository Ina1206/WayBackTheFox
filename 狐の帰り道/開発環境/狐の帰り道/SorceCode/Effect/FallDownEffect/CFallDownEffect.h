#ifndef CFALL_DOWN_EFFECT_H
#define CFALL_DOWN_EFFECT_H

#include "..\CEffectBase.h"

/**********************************
*		倒れる時のエフェクト.
********/
class CFallDownEffect
	: public CEffectBase
{
public:
	CFallDownEffect();
	~CFallDownEffect();

	//======================定数============================//.
	const int	SMOKE_MAX			= 20;		//煙の最大数.

	const int	APPEARANCE_MAX		= 20;		//出現タイム.
	const int	APPEARANCE_SMOKE	= 2;		//一回の煙の出現数.
	
	const float	START_POSITION		= 1.8f;		//開始位置.

	const float SMOKE_HIGHT			= 1.0f;		//煙の高さ.	
	const float SMOKE_HIGHT_ADJUST	= 0.3f;		//煙の高さ微調整.
	const float SMOKE_WIDTH_ADJUST	= 0.2f;		//煙の幅の微調整.

	const int	ODD_EVEN_JUDGE		= 2;		//奇数・偶数判断数値.
	const float SCALE_MAX			= 1.5f;		//煙の最大の大きさ.
	const float SCALE_MIN			= 0.8f;		//煙の最小の大きさ.
	const float SCALE_SPEED			= 0.005f;	//煙の大きくなる速度.
	const float ALPHA_MAX			= 1.0f;		//煙の透過値の最大数.
	const float ALPHA_MIN			= 0.0f;		//煙の透過値の最小数.
	const float ALPHA_SPEED			= 0.01f;	//煙の透過値の速度.
	const float ROTATION_MAX		= 6.5f;		//煙の角度最大値.
	const float ROTATION_MIN		= 0.0f;		//煙の角度最小値.
	const float ROTATION_SPEED		= 0.01f;	//煙の傾く速度.
	const int	FADE_WAIT_TIME		= 60;		//煙のフェードを待つ時間.

	const float MOVE_SPEED_MAX		= 0.03f;	//移動速度の最大数.
	const float MOVE_SPEED_MIN		= 0.002f;	//移動速度の最小数.
	const float SPEED_DECREMENT		= 0.0015f;	//移動速度の減少数値.

	const float MOVE_TARGET_HEIGHT	= 0.5f;		//移動の最終地点の高さ.
	const float	CONTROL_POINT_WIDTH = 0.4f;		//制御点の幅.
	const float CONTROL_WIDTH_ADJUST= 0.09f;	//制御点の幅の微調整.
	const float CONTROL_POINT_START = -0.7f;	//制御点の最初.
	const float CONTROL_POINT_END	= -2.0f;	//制御点の最後.
	const float CONTROL_ADJUST_HEI	= 0.02f;	//制御点の微調整.

	//======================関数============================//.
	void UpDate();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.
private:
	//======================関数============================//.
	void Init();															//初期化処理関数.
	void Release();															//解放処理関数.
	void Disp();															//表示処理関数.
	void Move();															//行動処理関数.
	void Scaling(int smoke);												//大きさ変更処理関数.
	void AlphaChange(int smoke);											//透過値の変更処理関数.
	void Rotation(int smoe);												//煙の回転処理関数.

	//======================変数============================//.
	float*			m_pfAlpha;			//透過値.
	int*			m_pFadeStartCnt;	//フェード開始カウント.
	D3DXVECTOR3*	m_pvInitPos;		//初期位置.
	float*			m_pfMoveSpeed;		//移動速度.
	float			m_fSpeed;			//速度.
};


#endif	//#ifndef CFALL_DOWN_EFFECT_H.