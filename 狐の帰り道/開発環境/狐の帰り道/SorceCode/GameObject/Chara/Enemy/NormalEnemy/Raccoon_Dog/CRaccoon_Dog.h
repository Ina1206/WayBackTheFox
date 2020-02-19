#ifndef CRACCOON_DOG_H
#define CRACCOON_DOG_H

#include "..\CNormalEnemyBase.h"
#include "..\..\..\..\..\Command\TimingCommand\CTimingCommand.h"


/****************************************
*	タヌキクラス.
**/
class CRaccoon_Dog
	: public CNormalEnemyBase
{
public:
	//================定数==================//.
	const float			SCALE_MAX		= 0.02f;					//大きさ.
	const float			MOVE_SPEED		= 0.05f;					//移動速度.
	const D3DXVECTOR2	FLY_SPEED		= D3DXVECTOR2(0.1f, 0.09f);	//飛ぶ速度.
	const float			COMMAND_DISP_H	= 1.5f;						//コマンド表示高さ.
	const float			SHADOW_UP_LIMIT = 2.5f;						//影の表示上限値.

	CRaccoon_Dog();
	~CRaccoon_Dog();

	//================関数==================//.
	void InitProcess();	//初期設定処理関数.
	void Update();			//更新処理関数.
	void Render();			//描画処理関数.
	void Release();			//解放処理関数.

private:
	//================関数==================//.
	void Move();			//移動処理関数.

	//===============列挙体=================//.
	//アニメーションの種類.
	enum class enAnimType {
		Hit = 0,		//攻撃受けたとき.
		Run,			//走り.
		Nothing,		//なし.

		Max,			//最大値.
		Start = Hit,	//最小値.
	};

	//================変数==================//.
	CDX9SkinMesh*				m_pRacconAnim;			//タヌキ.
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;		//アニメーションコントローラ.
	bool						m_bOldHit;				//前回のヒットフラグ.
	CSEPlayManager*				m_pCSEHit;				//当たったSE.
	CTimingCommand*				m_pCTimingCommand;		//タイミング
};

#endif	//#ifndef CRACCOON_DOG_H.