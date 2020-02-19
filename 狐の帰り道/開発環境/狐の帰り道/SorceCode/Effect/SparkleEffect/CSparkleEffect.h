#ifndef CSPARKLE_EFFECT_H
#define CSPARKLE_EFFECT_H

#include "..\CEffectBase.h"

/***********************************************
*		キラキラエフェクト関連クラス.
***/
class CSparkleEffect
	: public CEffectBase
{
public:
	CSparkleEffect();
	virtual ~CSparkleEffect();

	//==================定数=====================//.
	const float SCALE_MIN				= 0.2f;	//スケール最小値.
	const float SCALE_MAX				= 1.0f;	//スケール最大値.
	const float SCALING_SPEED			= 0.08f;//拡縮する速度.
	const int	STANDERD_SPARKLE_NUM	= 0;	//基準となるキラキラの番号.
	const int	SCALING_MAX				= 2;	//拡縮最大.
	const int	STAR_HORIZON_MAX		= 3;	//横に並ぶ星の最大数.

	//==================関数======================//.
	void Update();								//更新処理関数.

protected:
	//=================列挙体=====================//.
	enum class enScalingType {
		Large = 0,	//大きくする.
		Small,		//小さくする.

		Nothing,
	};
	//==================関数=====================//.

	//==================変数=====================//.
	int				m_Sparkle_max;			//キラキラの最大数.
	enScalingType*	m_penScalingType;		//拡縮処理のタイプ.
	int				m_CheckCnt;				//カウント.
	float			m_fCenterDifferencial;	//中央からの上の高さ.
	int				m_RowMax;				//横列の最大数.
	float			m_fHeight_Width;		//高さの幅.
	float			m_fLeftInterval;		//左側の間隔.
	float			m_fRightInterval;		//右側の間隔.
	float			m_fLeftMost;			//左端.
	float			m_fRightMost;			//右端.
	float			m_fScaleMax;			//大きさ.

private:
	//==================関数=====================//.
	void ScalingCnt(int sparkle);	//拡縮のカウント処理関数.
	void Scaling(int sparkle);		//拡縮処理関数.
	void InitScaling(int sparkle);	//拡縮初期設定処理関数.
	void InitPosition(int sparkle);	//初期配置設定処理関数.

};

#endif	//#ifndef CSPARKLE_EFFECT_H.