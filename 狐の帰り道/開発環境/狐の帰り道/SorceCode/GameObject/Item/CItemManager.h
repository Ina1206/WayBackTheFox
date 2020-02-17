#ifndef CITEMMANAGER_H
#define CITEMMANAGER_H

#include "CItem_Meat.h"
#include "CItem_Fish.h"
#include "CItem_Vegetables.h"
#include "CItem_Rice.h"
#include "..\Collider_Detection\CCollision_Detection.h"

#include "..\Chara\Enemy\EnemyType.h"

/***************************************************
*	アイテム管理用クラス.
**/
class CItemManager
{
public:
	CItemManager();
	~CItemManager();

	//=====================関数=======================//.
	void Init_Process();													//初期化処理関数.
	void UpDate();															//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.

	//～情報置換処理関数～.
	void SetEnemyType(enEnemy enemyType) { m_enEnemy = enemyType; }						//敵のタイプ.
	void SetInput_Decision(enInput_Decision enInput) { m_enInput_Decision = enInput; }	//コマンド判定結果.
	void SetInitPosition(D3DXVECTOR3 vPos) { m_vInitPos = vPos; }						//初期位置. 
	void SetPlayerPosition(D3DXVECTOR3 vPos) { m_vPlayerPos = vPos; }					//プレイヤー位置.
	void SetItemJudge(enItemJudge enJudge) { m_ItemJudge = enJudge; }					//アイテムの判定.
	void SetDispFlag(bool flag) { m_bDispFlag = flag; }									//描画フラグ.
	void SetBossFlag(bool flag) { m_bBossFlag = flag; }									//ボスフラグ.
	void SetItemSum(int itemType, int num);												//アイテムの合計.


	//～情報取得処理関数～.
	enEnemy		GetEnemyType()   { return m_enEnemy; }			//敵のタイプ.
	enItemJudge	GetItemJudge() { return m_ItemJudge; }
	int			GetPointSum(int itemType) { return m_ppCItemBase[itemType]->GetPointSum(); };
	int			GetCollitionNum(int itemType) { return m_ppCItemBase[itemType]->GetCollitionNum(); }
	int			GetDropNum(int itemType) { return m_ppCItemBase[itemType]->GetDropNum(); }
	bool		GetBossFlag() { return m_bBossFlag; }
	bool		GetDispFlag(int itemType) { return m_ppCItemBase[itemType]->GetDispFlag(); }

	D3DXVECTOR3 GetPosition(int itemType) { return m_ppCItemBase[itemType]->GetPosition(); }
	D3DXVECTOR3 GetIconPos (int itemType);

private:
	//=====================関数=======================//.
	void Release();		//解放処理関数.

	//==================定数==================.
	const D3DXVECTOR3 ICONPOS_VEG  = D3DXVECTOR3(-2.5f, 1.4f, 0.0f);
	const D3DXVECTOR3 ICONPOS_MEAT = D3DXVECTOR3(-2.5f, 2.8f, 0.0f);
	const D3DXVECTOR3 ICONPOS_FISH = D3DXVECTOR3(-2.5f, 2.3f, 0.0f);
	const D3DXVECTOR3 ICONPOS_RICE = D3DXVECTOR3(-2.5f, 1.4f, 0.0f);
	const D3DXVECTOR3 ITEMNUM_POS  = D3DXVECTOR3(125.0f, 25.0f, 0.0f);
	const D3DXVECTOR2 ITEMNUM_POS_ADJ = D3DXVECTOR2(75.0f, 95.0f);

	const int ENEMYTYPE_MAX		= static_cast<int>(enEnemy::Max);				//敵の最大数.
	const int VEGETABlE			= 0;
	const int MEAT				= 1;
	const int FISH				= 2;
	const int RICE				= 3;
	const int ITEM_TYPE_MAX		= static_cast<int>(enItemType::MAX);		//アイテムの最大数.
	const int NUM_SPRITE_MAX	= 2;
	const int TEN_PLACE			= 0;
	const int ONE_RANK			= 1;
	const int IMAGE_WIDTH_MAX	= 5;
	const int IMAGE_HIGH_MAX	= 5;
	const int TEN				= 10;

	//==================変数=======================//.
	enEnemy					m_enEnemy;			//敵の種類.
	CItem_Base**			m_ppCItemBase;		//CItem_Baseクラス.
	CCollision_Detection*	m_pCCollision;		//当たり判定クラス.
	enInput_Decision		m_enInput_Decision;	//コマンド判定.
	enItemJudge				m_ItemJudge;		//アイテムの判定.

	D3DXVECTOR3				m_vInitPos;			//初期位置.
	D3DXVECTOR3				m_vPlayerPos;		//プレイヤー位置.
	D3DXVECTOR3				m_vIconPos;			//アイコン位置.

	bool					m_bDispFlag;		//描画フラグ.
	bool					m_bBossFlag;		//ボスフラグ.

	int*					m_pSum;				//野菜合計.

};


#endif//#ifndef CITEMMANAGER_H
