#ifndef _CHIT_EFFECT_H
#define _CHIT_EFFECT_H

#include "..\CEffectBase.h"

/**********************************************
*		当たった時のエフェクト.
**/
class CHitEffect 
	: public CEffectBase
{
public:
	CHitEffect();
	~CHitEffect();

	//================定数======================//.
	const int	DISP_EFFECT_MAX		= 2;		//表示エフェクト最大数.
	const float BASIC_DIFFERENCIAL	= 0.5f;		//表示基本x軸差分.
	const float BASIC_BLANK_WIDTH	= 1.0f;		//基本空白幅.
	const float ADD_HIGHT			= 0.8f;		//加算される高さ.
	const float START_ROTAITON		= 3.5f;		//初めの角度.
	const float MOVING_DISTANCE_MAX = 0.1f;		//移動距離最大数.
	const float MOVING_SPEED		= 0.02f;	//移動速度.
	const float BASE_SCALE			= 0.65f;	//基本の大きさ.

	//===============列挙体=====================//.
	enum class enMoveType {
		Right = 0,	//右. 
		Left,		//左.

		Nothing,	//無し.
	};

	//================関数======================//.
	void Update();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.

	//～情報取得処理関数～.
	//大きさ変更処理関数.
	void SetEffectScale(float Scale); 
private:
	//================関数======================//.
	void Init();			//初期化処理関数.
	void Release();			//解放処理関数.
	void Move(int sprite);	//移動処理関数.

	//================変数=====================//.
	float		m_fMoving_Distance;	//移動距離.
	enMoveType	m_enMoveType;		//移動種類.
	D3DXVECTOR3 m_vInitPos;			//はじめの座標.

};

#endif	//#ifndef _CHIT_EFFECT_H.