#ifndef CFLY_EFFECT_H
#define CFLY_EFFECT_H

#include "..\CEffectBase.h"

/**********************************************
*		飛ぶエフェクトクラス.
*****/
class CFlyEffect
	: public CEffectBase
{
public:
	CFlyEffect();
	~CFlyEffect();

	//==================定数=======================//.
	const float MIN_SCALE		= 0.1f;		//大きさの最小値.
	const float	SCALING_SPEED	= 0.12f;	//大きくなる速度.
	const float	MIN_ALPHA		= 0.0f;		//透過値の最小値.
	const float ALPHA_SPEED		= 0.03f;	//透過する速度.
	const int	LEFT_DIRECTION	= -1;		//左方向.
	const float	RATATION_SPEED	= 0.025f;	//回転角度.
	const float	RATATION_MAX	= 4.0f;		//最大回転角度.
	const int	DISP_TIME		= 2;		//出現する時間.

protected:
	//==================関数=======================//.
	void SmokeDisp();						//煙の表示処理関数.
	void SetPosition(int smoke);			//位置設定処理関数.
	void SmokeMove(int smoke);				//煙の動き処理関数.
	void Ratation(int smoke,bool CameraRot);//煙の回転処理関数.

	//==================変数=======================//.
	float*	m_pfAlpha;				//透過値.
	int		m_SmokeMax;				//煙の最大数.
	float	m_fStartPos_x;			//左端の位置.
	int		m_Row_Max;				//横の列の最大数.
	float	m_fInterval_Width;		//幅の間隔.
	float	m_fFoot_Differencial;	//中心から足元の差.
	float	m_fMax_Scale;			//大きさの最大.
	int		m_DispCnt;				//出現カウント.
	bool*	m_pbSmokeDispFlag;		//煙が出るフラグ.
	int		m_FinishCnt;			//終了カウント.

private:
};

#endif	//#ifndef CFLY_EFFECT_H.