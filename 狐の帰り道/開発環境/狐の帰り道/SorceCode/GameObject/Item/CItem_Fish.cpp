#include "CItem_Fish.h"

//===================================.
//	コンストラクタ.
//===================================.
CItem_Fish::CItem_Fish()
	: m_Num(0)
	, m_CItemMove(nullptr)
{
}

//===================================.
//	デストラクタ.
//===================================.
CItem_Fish::~CItem_Fish()
{
	Release();
}

//===================================.
//	初期化処理関数.
//===================================.
void CItem_Fish::Init_Process()
{
	m_CItemMove = new CItemMove[ITEM_MAX]();
}

//===================================.
//	更新処理関数.
//===================================.
void CItem_Fish::UpDate()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		//更新処理関数.
		m_CItemMove[i].UpDate(m_bDispFlag, m_enItemJudge, m_vIconPos);
		m_CItemMove[i].SetBossFlag(m_BossFlag);

		if (m_bDispFlag == true) {
			m_vPos = m_CItemMove[i].GetItemPosition();
		}
		else
		{
			if (m_enItemJudge == enItemJudge::failure) {
					m_vPos = m_vPlayerPos;
			}
			if (m_BossFlag == true)
			{
				m_vPos.x = m_vPlayerPos.x - BOSS_ITEM_POSITION_X;
				m_vPos.z = m_vPlayerPos.z + BOSS_ITEM_POSITION_Z;
			}
			m_CItemMove[i].Init_Process(m_vPos);
		}

		if (m_CollitionNum != m_DropNum)
		{
			m_CollitionNum += m_CItemMove[i].GetCollectionItem();
		}
	}
	ItemCount();
}

//===================================.
//	描画処理関数.
//===================================.
void CItem_Fish::Render()
{
	if (m_bDispFlag == true) {
		ItemRender();
	}
}

//===================================.
//	解放処理関数.
//===================================.
void CItem_Fish::Release()
{
	SAFE_DELETE_ARRAY(m_CItemMove);
}

//===================================.
//	アイテムの合計処理関数.
//===================================.
void CItem_Fish::ItemCount()
{
	//アイテム個数の設定.
	if (m_enInputDecision == enInput_Decision::Great) { m_DropNum = ITEM_MAX; }
	if (m_enInputDecision == enInput_Decision::Good) { m_DropNum = ITEM_MIN; }
	if (m_enItemJudge == enItemJudge::failure)
	{
		if (m_bCheckBossFlag == false) {

			if (m_BossFlag == false) {
				if (m_Sum != 0) {
					m_DropNum = ITEM_MIN;
				}
			}
			else
			{
				if (m_Sum == 0) {
					m_DropNum = 0;
				}
				else if (m_Sum == ITEM_MIN) {
					m_DropNum = ITEM_MIN;
				}
				else {
					m_DropNum = ITEM_MAX;
				}
			}
			m_bCheckBossFlag = true;
		}
	}

	//ポイント設定.
	m_Point = FISHPOINT * m_DropNum;
}


//===================================.
//	アイテム描画処理関数.
//===================================.
void CItem_Fish::ItemRender()
{
	m_pCSprite = new CSprite*[ITEM_MAX];

	//クラス.
	for (int sprite = 0; sprite < m_DropNum; sprite++)
	{
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Fish);
		//アイテムの表示数設定.
		m_CItemMove[sprite].SetNumber(sprite);

		//位置.
		m_pCSprite[sprite]->SetPosition(m_CItemMove[sprite].GetItemPosition());

		//描画.
		m_pCDepth_Stencil->SetDepth(false);
		m_pCSprite[sprite]->Render(m_mView, m_mProj, m_vCameraPos);
		m_pCDepth_Stencil->SetDepth(true);
	}

	SAFE_DELETE_ARRAY(m_pCSprite);
}
