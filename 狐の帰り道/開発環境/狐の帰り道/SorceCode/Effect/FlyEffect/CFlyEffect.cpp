#include "CFlyEffect.h"

/**********************************************
*		飛ぶエフェクトクラス.
*****/
CFlyEffect::CFlyEffect()
	: m_pfAlpha				(nullptr)
	, m_fStartPos_x			(0.0f)
	, m_Row_Max				(0)
	, m_fInterval_Width		(0.0f)
	, m_fFoot_Differencial	(0.0f)
	, m_fMax_Scale			(0.0f)
	, m_DispCnt				(0)
	, m_pbSmokeDispFlag		(nullptr)
	, m_FinishCnt			(0)
{
}

CFlyEffect::~CFlyEffect()
{
}

//=========================================.
//		煙の表示処理関数.
//=========================================.
void CFlyEffect::DispSmoke()
{
	//出現時間になるまでカウント.
	m_DispCnt++;
	if (m_DispCnt >= DISP_TIME) {
		for (int smoke = 0; smoke < m_SmokeMax; smoke++) {
			if (m_pbSmokeDispFlag[smoke] == false) {
				//位置設定処理関数.
				SetPosition(smoke);
				//フラグ.
				m_pbSmokeDispFlag[smoke] = true;
				//戻す.
				m_DispCnt = 0;
				break;
			}
		}
	}

	//出現しているときは動きの処理.
	for (int smoke = 0; smoke < m_SmokeMax; smoke++) {
		if (m_pbSmokeDispFlag[smoke] == true) {
			//煙の動きの処理.
			MoveSmoke(smoke);
		}
	}

	if (m_FinishCnt > m_SmokeMax) {
		m_bDispFlag = false;
	}
}

//=========================================.
//		位置設定処理関数.
//=========================================.
void CFlyEffect::SetPosition(int smoke)
{
	//位置設定.
	m_pvPos[smoke].x = (m_vCenterPos.x + m_fStartPos_x) + ((smoke%m_Row_Max)*m_fInterval_Width);
	m_pvPos[smoke].y = m_vCenterPos.y - m_fFoot_Differencial;
	m_pvPos[smoke].z = m_vCenterPos.z;
}

//=========================================.
//		煙の動き処理関数.
//=========================================.
void CFlyEffect::MoveSmoke(int smoke)
{
	//拡大と透過.
	if (m_pfScale[smoke] < m_fMax_Scale) {
		m_pfScale[smoke] += SCALING_SPEED ;
	}
	else {
		//透過.
		if (m_pfAlpha[smoke] > MIN_ALPHA) {
			m_pfAlpha[smoke] -= ALPHA_SPEED;
		}
		else {
			//非表示.
			m_pbSmokeDispFlag[smoke] = false;
			m_FinishCnt++;
		}
	}

}

//========================================.
//		煙の回転処理関数.
//========================================.
void CFlyEffect::Ratation(int smoke, bool CameraRot)
{
	//方向計算.
	int Direction = LEFT_DIRECTION + ((smoke % m_Row_Max) * m_Row_Max);
	//カメラが回転していなければz軸を回転する.
	if (CameraRot == false) {
		m_pvRot[smoke].z += RATATION_SPEED * Direction;
		if (fabsf(m_pvRot[smoke].z) > RATATION_MAX) {
			m_pvRot[smoke].z = 0.0f;
		}
	}
	else {
		//回転していればｘ軸を回転する.
		m_pvRot[smoke].x += RATATION_SPEED * Direction;
		if (fabsf(m_pvRot[smoke].x) > RATATION_MAX) {
			m_pvRot[smoke].x = 0.0f;
		}
	}
}