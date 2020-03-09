#include "CSparkleEffect.h"

/***********************************************
*		キラキラエフェクトクラス.
***/
CSparkleEffect::CSparkleEffect()
	: m_Sparkle_max			(0)
	, m_penScalingType		(nullptr)
	, m_CheckCnt			(0)
	, m_fCenterDifferencial	(0.0f)
	, m_RowMax				(0)
	, m_fHeight_Width		(0.0f)
	, m_fLeftInterval		(0.0f)
	, m_fRightInterval		(0.0f)
	, m_fLeftMost			(0.0f)
	, m_fRightMost			(0.0f)
	, m_fScaleMax			(SCALE_MAX)
{
}

CSparkleEffect::~CSparkleEffect()
{
}

//===========================================.
//		更新処理関数.
//===========================================.
void CSparkleEffect::Update()
{
	//フラグが変わってすぐ.
	if (m_bDispFlag != m_bOldDispFlag) {
		for (int sparkle = 0; sparkle < m_Sparkle_max; sparkle++) {
			//初期配置設定処理関数.
			InitPosition(sparkle);
			//拡縮初期設定処理関数.
			InitScaling(sparkle);
			//チェックカウント初期化.
			m_CheckCnt = 0;
		}
	}

	//拡縮処理関数.
	for (int sparkle = 0; sparkle < m_Sparkle_max; sparkle++) {
		Scaling(sparkle);
	}

	//現在のフラグ取得.
	m_bOldDispFlag = m_bDispFlag;
}

//==============================================.
//		拡縮初期設定処理関数.
//==============================================.
void CSparkleEffect::InitScaling(int sparkle)
{
	if (sparkle % STAR_HORIZON_MAX == 0) {
		//大きさを最大に設定.
		m_pfScale[sparkle] = m_fScaleMax;
		//小さくする処理へ.
		m_penScalingType[sparkle] = enScalingType::Small;
	}
	else {
		//大きさを最小に設定.
		m_pfScale[sparkle] = SCALE_MIN;
		//小さくする処理へ.
		m_penScalingType[sparkle] = enScalingType::Large;
	}
}

//==============================================.
//		拡縮処理関数.
//==============================================.
void CSparkleEffect::Scaling(int sparkle)
{
	switch (m_penScalingType[sparkle]) {
	//大きくする.
	case enScalingType::Large:
		m_pfScale[sparkle] += SCALING_SPEED;
		//最大で小さくなる処理へ.
		if (m_pfScale[sparkle] > m_fScaleMax) {
			m_penScalingType[sparkle] = enScalingType::Small;
		}
		break;
	//小さくする.
	case enScalingType::Small:
		m_pfScale[sparkle] -= SCALING_SPEED;

		//最小で大きくなる処理へ.
		if (m_pfScale[sparkle] < SCALE_MIN) {
		
			m_penScalingType[sparkle] = enScalingType::Large;

			//拡縮のカウント処理関数.
			ScalingCnt(sparkle);
		}
		break;
	}
}

//===================================================.
//		拡縮のカウント処理関数.
//===================================================.
void CSparkleEffect::ScalingCnt(int sparkle)
{
	//カウント.
	if (sparkle == STANDERD_SPARKLE_NUM) {

		m_CheckCnt++;

		//数回やれば終了
		if (m_CheckCnt > SCALING_MAX) {
			m_bDispFlag = false;
		}
	}
}


//==========================================.
//		初期配置設定処理関数.
//==========================================.
void CSparkleEffect::InitPosition(int sparkle)
{
	//高さ.
	m_pvPos[sparkle].y = (m_vCenterPos.y + m_fCenterDifferencial) - ((sparkle / m_RowMax) * m_fHeight_Width);
	//奥行はプレイヤーに合わせる.
	m_pvPos[sparkle].z = m_vCenterPos.z;

	//引く値(奇数になれば引く).
	float Start_Distance = ((sparkle / m_RowMax) % 2) * m_fLeftInterval;		//左側.
	float Interval_Distance = ((sparkle / m_RowMax) % 2) * m_fRightInterval;	//右側.
	//基準のx座標計算.
	float Criteria_PosX = (m_fLeftMost + Start_Distance) + ((sparkle % m_RowMax) * (m_fRightMost - Interval_Distance));
	//プレイヤーの中心に合わせる.
	m_pvPos[sparkle].x = m_vCenterPos.x + Criteria_PosX;


}