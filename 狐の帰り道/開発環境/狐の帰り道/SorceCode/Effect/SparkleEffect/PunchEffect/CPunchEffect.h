#ifndef CPUNCH_EFFECT_H
#define CPUNCH_EFFECT_H

#include "..\CSparkleEffect.h"

/**********************************************
*		パンチエフェクトクラス.
*****/
class CPunchEffect
	: public CEffectBase
{
public:
	CPunchEffect();
	~CPunchEffect();

	//======================定数==========================//.
	const int			SPARKLE_MAX			= 2;						//星の最大数.
	const int			USE_SPARKLE_MAX		= 2;						//使用する星の種類最大数.
	const int			VERTICAL_STAR_MAX	= 2;						//縦の列の星の最大数.
	const D3DXVECTOR2	START_POS			= D3DXVECTOR2(0.1f, 0.5f);	//中心から始まる位置の距離.
	const float			INTERVAL_WIDTH		= 0.35f;					//星同士の横の間隔.
	const float			INTERVAL_HEIGHT		= 0.35f;					//星同士の縦の間隔.
	const int			DISP_STAR			= 2;						//表示する星.	
	const float			SCALE_MAX			= 0.7f;						//大きさの最大値.
	const float			SCALING_SPEED		= 0.05f;					//拡縮の速度.
	const float			CENTER_ADJUST_X		= 0.1f;						//中心x軸の調整.

	//======================関数==========================//.
	void Update();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.
private:
	void Init();					//初期化処理関数.
	void Release();					//解放処理関数.
	void InitPos(int sparkle);		//初期位置設定.

	//=======================変数==========================//.
	int		m_StartNum;				//始める番号.
	bool*	m_pbDispFlag;			//表示フラグ.
	int		m_EndStarNum;			//終わりの番号.

};

#endif	//#ifndef CPUNCH_EFFECT_H.