#ifndef CKAPPA_H
#define CKAPPA_H

#include "..\CNormalEnemyBase.h"
#include "..\..\..\..\..\Command\LongPushCommand\CLongPushCommand.h"

/********************************************
*		上がる狸クラス.
**/
class CUpRaccoonDog
	: public CNormalEnemyBase
{
public:
	CUpRaccoonDog();
	~CUpRaccoonDog();
	//=====================定数======================//.
	const int	ANIMATION_NUM		= 0;		//アニメーション番号.
	const float UP_MOVE_DISTANCE	= 10.0f;	//上に上がる距離.
	const float START_HIGH			= -1.2f;	//初期の高さ.
	const float HIGH_MAX			= 0.1f;		//高さの最大値.
	const float UP_MOVE_SPEED		= 0.1f;		//上に上がる速度.

	//=====================関数======================//.
	void InitProcess();			//初期設定処理関数.
	void Update();					//更新処理関数.
	void Render();					//描画処理関数.
	void Release();					//解放処理関数.

private:
	//=====================関数======================//.
	void Move();					//移動処理関数.

	//=====================変数======================//.
	CDX9SkinMesh*				m_pRaccoonDog;		//狸メッシュ.
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;	//アニメーションコントローラ.
	bool						m_bCheckSound;		//再生チェック.
	CDX9Mesh*					m_pGrassMesh;		//草のメッシュ.
};

#endif //#ifndef CKAPPA_H.