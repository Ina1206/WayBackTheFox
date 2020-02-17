#include "CItem_Rice.h"

//===================================.
//	コンストラクタ.
//===================================.
CItem_Rice::CItem_Rice()
	: m_Num(0)
	, m_CItemMove(nullptr)
	, m_vOldPos(0.0f,0.0f,0.0f)
{
}

//===================================.
//	デストラクタ.
//===================================.
CItem_Rice::~CItem_Rice()
{
	Release();
}

//===================================.
//	初期化処理関数.
//===================================.
void CItem_Rice::Init_Process()
{
	m_CItemMove = new CItemMove[RICE_MAX]();
}

//===================================.
//	更新処理関数.
//===================================.
void CItem_Rice::UpDate()
{
	for (int i = 0; i < RICE_MAX; i++)
	{
		//更新処理関数.
		if (m_enItemJudge == enItemJudge::Success) {
			m_CItemMove[i].UpDate(m_bDispFlag, m_enItemJudge, m_vIconPos);
		}
		m_CItemMove[i].SetBossFlag(m_BossFlag);

		if (m_bDispFlag == true) {
			m_vPos = m_CItemMove[i].GetItemPosition();
		}
		else
		{
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
void CItem_Rice::Render()
{
	if (m_bDispFlag == true) {
		ItemRender();
	}
}

//===================================.
//	解放処理関数.
//===================================.
void CItem_Rice::Release()
{
	SAFE_DELETE_ARRAY(m_CItemMove);
}

//===================================.
//	アイテムの合計処理関数.
//===================================.
void CItem_Rice::ItemCount()
{
	//アイテム個数の設定.
	if (m_enInputDecision == enInput_Decision::Great) { m_DropNum = RICE_MAX; }
	if (m_enInputDecision == enInput_Decision::Good) { m_DropNum = RICE_MAX; }
	if (m_enItemJudge == enItemJudge::failure)
	{
		m_DropNum = ITEM_MIN;
	}

		//ポイント設定.
	m_Point = RICEPOINT * m_DropNum;
}


//===================================.
//	アイテム描画処理関数.
//===================================.
void CItem_Rice::ItemRender()
{
	m_pCSprite = new CSprite*[RICE_MAX];

	//クラス.
	for (int sprite = 0; sprite < m_DropNum; sprite++)
	{
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Rice);
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
