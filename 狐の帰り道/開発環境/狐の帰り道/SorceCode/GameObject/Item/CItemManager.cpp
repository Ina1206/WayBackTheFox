#include "CItemManager.h"

CItemManager::CItemManager()
	: m_enEnemy			(enEnemy::Max)
	, m_ppCItemBase		(nullptr)
	, m_enInput_Decision(enInput_Decision::Max)
	, m_pCCollision		(nullptr)
	, m_ItemJudge		(enItemJudge::Max)
	, m_vInitPos		(0.0f, 0.0f, 0.0f)
	, m_vPlayerPos		(0.0f, 0.0f, 0.0f)
	, m_vIconPos		(0.0f, 0.0f, 0.0f)
	, m_bDispFlag		(false)
	, m_bBossFlag		(false)
	, m_pSum			(nullptr)
{
}

CItemManager::~CItemManager()
{
	Release();
}

//========================================.
//		初期化処理関数.
//========================================.
void CItemManager::Init_Process()
{
	m_ppCItemBase = new CItem_Base*[ITEM_TYPE_MAX];
	m_pCCollision = new CCollision_Detection();

	m_ppCItemBase[VEGETABlE] = new CItem_Vegetables();
	m_ppCItemBase[MEAT] = new CItem_Meat();
	m_ppCItemBase[FISH] = new CItem_Fish();
	m_ppCItemBase[RICE] = new CItem_Rice();

	m_pSum = new int[ITEM_TYPE_MAX];

	//初期化処理.
	for (int item = 0; item < ITEM_TYPE_MAX; item++)
	{
		m_ppCItemBase[item]->Init_Process();
	}

	m_ppCItemBase[VEGETABlE]->SetIconPos(ICONPOS_VEG);
	m_ppCItemBase[MEAT]->SetIconPos(ICONPOS_MEAT);
	m_ppCItemBase[FISH]->SetIconPos(ICONPOS_FISH);
	m_ppCItemBase[RICE]->SetIconPos(ICONPOS_RICE);
}

//========================================.
//		更新処理関数.
//========================================.
void CItemManager::UpDate()
{
	for (int item = 0; item < ITEM_TYPE_MAX; item++) {
		//初期位置設定.
		m_ppCItemBase[item]->SetPotition(m_vInitPos);
		//プレイヤー位置設定.
		m_ppCItemBase[item]->SetPlayerPos(m_vPlayerPos);
		//アイテム合計の取得.
		m_ppCItemBase[item]->SetItemSum(m_pSum[item]);
		//コマンド判定結果設定.
		m_ppCItemBase[item]->SetInputDecision(m_enInput_Decision);
		//アイテム判定結果設定.
		m_ppCItemBase[item]->SetItemJudge(m_ItemJudge);
		//描画フラグ設定.
		m_ppCItemBase[item]->SetDispFlag(m_bDispFlag);
		//ボスフラグ設定.
		m_ppCItemBase[item]->SetBossFlag(m_bBossFlag);
	}

	switch (m_enEnemy)
	{
	case enEnemy::RaccoonDog:
		m_ppCItemBase[VEGETABlE]->UpDate();
		break;
	case enEnemy::Cow_Ghost:
		m_ppCItemBase[MEAT]->UpDate();
		break;
	case enEnemy::UpRaccoonDog:
		m_ppCItemBase[FISH]->UpDate();
		break;
	case enEnemy::Big_RaccoonDog:
		if (m_enInput_Decision == enInput_Decision::Bad){
			for (int item = 0; item < ITEM_TYPE_MAX - 1; item++){
				m_ppCItemBase[item]->UpDate();
			}
		}
		else {
			m_ppCItemBase[RICE]->UpDate();
		}
		break;
	default:
		break;
	}
}

//========================================.
//		描画処理関数.
//========================================.
void CItemManager::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int item = 0; item < ITEM_TYPE_MAX; item++) {
		m_ppCItemBase[item]->Value_Set(mView, mProj, vCamePos);
		m_ppCItemBase[item]->Render();
	}
}

//========================================.
//		アイテムの合計.
//========================================.
void CItemManager::SetItemSum(int itemType, int num)
{
	{
		m_pSum[itemType] = num;;
	}
}

D3DXVECTOR3 CItemManager::GetIconPos(int itemType)
{

	switch (itemType)
	{
	case 0:
		m_vIconPos = ICONPOS_VEG;
		break;
	case 1:
		m_vIconPos = ICONPOS_MEAT;
		break;
	case 2:
		m_vIconPos = ICONPOS_FISH;
		break;
	case 3:
		m_vIconPos = ICONPOS_RICE;
		break;
	default:
		break;
	}

	return m_vIconPos;
}

//========================================.
//		解放処理関数.
//========================================.
void CItemManager::Release()
{
	SAFE_DELETE(m_pCCollision);
	SAFE_DELETE_ARRAY(m_pSum);
	for (int item = ITEM_TYPE_MAX - 1; item >= 0; item--)
	{
		SAFE_DELETE(m_ppCItemBase[item]);
	}
	SAFE_DELETE_ARRAY(m_ppCItemBase);
}
