#ifndef CGAME_MAIN_H
#define CGAME_MAIN_H

#include "..\CSceneBase.h"

#include "..\..\BackGround\CBackGround.h"

//キャラクタ関係.
#include "..\..\GameObject\Chara\Player\CPlayer.h"
#include "..\..\GameObject\Chara\Enemy\CEnemyManager.h"
#include "..\..\GameObject\Chara\Enemy\Boss\Big_Raccoon_Dog\CBig_Raccoon_Dog.h"
#include "..\..\GameObject\Ground\CGround.h"

#include "..\..\Camera\StamderdCamera\CStanderdCamera.h"
#include "..\..\Camera\CCameraManager.h"
//アイテム.
#include "..\..\GameObject\Item\CItemManager.h"
//当たり判定.
#include "..\..\GameObject/Collider_Detection/CCollision_Detection.h"
#include "..\..\GameObject\Collider_Detection\CDebugCollisionSphere.h"


//UI.
#include "..\..\GameObject\UI\CMainUIManager.h"


//サウンド.
#include "..\..\Sound\CSEPlayManager.h"

/*************************************
*	ゲームメインクラス.
**/
class CGameMain
	: public CSceneBase
{
public:
	CGameMain();
	~CGameMain();

	//=============定数===============//.
	const D3DXVECTOR3	BOSS_COMMANDDISP_POS = D3DXVECTOR3(0.0f, 6.0f, 3.5f);	//ボスの時のカメラ位置.


	//=============関数==============//.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//=============定数===============//.
	const float			HIT_SCALE = 0.5f;
	const float			HIT_SCALE_COW = 1.5f;
	const int           INVINCIBLETIME = 2500;
	const int			ITEM_BOUNCE_TIME = 60;
	const int			GAME_END_TIME = 300;


	//=============関数==============//.
	void Release();			//解放処理関数.

	void SetCommndDecision(int enemyType, int enemy);	//コマンド判定とアイテムの動き処理関数.
	void SetHit_Test(int enemyType, int enemy);			//当たり判定処理関数.
	void SetHit_Test_Jump(int enemyType, int enemy);	//ジャンプのための当たり判定処理関数.
	void SetItemPosition(int enemyType, int enemy);		//アイテムの位置設定関数.

	//============クラス=============//.
	CPlayer*				m_pCPlayer;				//プレイヤークラス.
	CEnemyManager*			m_pCEnemyManager;		//敵の管理クラス.
	CBackGround*			m_pCBackGround;			//背景.
	CGround*				m_pCGround;				//地面.
	CCameraManager*			m_pCCameraManager;		//カメラ.

	CCollision_Detection*	m_CHit;					//当たり判定.
	bool**					m_ppbCheckSound;		//当たった時のSE.


	CMainUIManager*			m_pCUIManager;			//UI管理クラス.

	///======================.
	//	試し.
	CEffectBase*		m_pCEffectBase;				//エフェクトベース.
	//=======================.

	int				m_frame;
	int				m_waittime;

	int				m_Count;
	int            m_HitCount;


	int				m_EndCount;

};

#endif //#ifndef CGAME_MAIN_H.