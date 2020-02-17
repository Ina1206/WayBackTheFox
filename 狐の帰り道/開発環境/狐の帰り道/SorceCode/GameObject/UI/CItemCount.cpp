#include "CItemCount.h"

CItemCount::CItemCount()
	: m_pstItemInfo		(nullptr)
	, m_Vegetable_Count	(0)
	, m_Meat_Count		(0)
	, m_Fish_Count		(0)
	, m_Rice_Count		(0)
{
	m_pstItemInfo = new stItemInfo[ITEM_TYPE_MAX];
	
	for (int item = 0; item < ITEM_TYPE_MAX; item++)
	{
		m_pstItemInfo[item].m_ppCNumSprite	= new CSpriteUI*[NUM_SPRITE_MAX];
		m_pstItemInfo[item].m_pvPattern		= new D3DXVECTOR2[NUM_SPRITE_MAX];
	}
}

CItemCount::~CItemCount()
{
	Release();
}

//===================================.
//	更新処理関数.
//===================================.
void CItemCount::UpDate()
{
}

//===================================.
//	描画処理関数.
//===================================.
void CItemCount::Render()
{
	for (int item = 0; item < ITEM_TYPE_MAX; item++)
	{
		//画像パターンの設定.
		switch (item)
		{
		case 0:
			m_pstItemInfo[item].m_pvPattern[0]
				= D3DXVECTOR2(static_cast<float>((m_Vegetable_Count / TEN) % IMAGE_WIDTH_MAX), static_cast<float>((m_Vegetable_Count / TEN) / IMAGE_HIGH_MAX));
			m_pstItemInfo[item].m_pvPattern[1] 
				= D3DXVECTOR2(static_cast<float>(m_Vegetable_Count % IMAGE_WIDTH_MAX), static_cast<float>(m_Vegetable_Count / IMAGE_HIGH_MAX));
			break;
		case 1:
			m_pstItemInfo[item].m_pvPattern[0]
				= D3DXVECTOR2(static_cast<float>((m_Meat_Count / TEN) % IMAGE_WIDTH_MAX), static_cast<float>((m_Meat_Count / TEN) / IMAGE_HIGH_MAX));
			m_pstItemInfo[item].m_pvPattern[1]
				= D3DXVECTOR2(static_cast<float>(m_Meat_Count % IMAGE_WIDTH_MAX), static_cast<float>(m_Meat_Count / IMAGE_HIGH_MAX));
			break;
		case 2:
			m_pstItemInfo[item].m_pvPattern[0]
				= D3DXVECTOR2(static_cast<float>((m_Fish_Count / TEN) % IMAGE_WIDTH_MAX), static_cast<float>((m_Fish_Count / TEN) / IMAGE_HIGH_MAX));
			m_pstItemInfo[item].m_pvPattern[1]
				= D3DXVECTOR2(static_cast<float>(m_Fish_Count % IMAGE_WIDTH_MAX), static_cast<float>(m_Fish_Count / IMAGE_HIGH_MAX));
			break;
		case 3:
			m_pstItemInfo[item].m_pvPattern[0]
				= D3DXVECTOR2(static_cast<float>((m_Rice_Count / TEN) % IMAGE_WIDTH_MAX), static_cast<float>((m_Rice_Count / TEN) / IMAGE_HIGH_MAX));
			m_pstItemInfo[item].m_pvPattern[1]
				= D3DXVECTOR2(static_cast<float>(m_Rice_Count % IMAGE_WIDTH_MAX), static_cast<float>(m_Rice_Count / IMAGE_HIGH_MAX));
			break;
		default:
			break;
		}

		for (int sprite = 0; sprite < NUM_SPRITE_MAX; sprite++)
		{
			//スプライトUIのアドレス取得.
			m_pstItemInfo[item].m_ppCNumSprite[sprite] = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::TimerNum);		
	
			//位置.
			m_vPos = D3DXVECTOR3(m_pstItemInfo[item].m_vIconPos.x + 130.0f + (75.0f*sprite), m_pstItemInfo[item].m_vIconPos.y + 35.0f, m_pstItemInfo[item].m_vIconPos.z);
			if (item == 1) {
				m_vPos = D3DXVECTOR3(m_pstItemInfo[item].m_vIconPos.x + 130.0f + (75.0f*sprite), m_pstItemInfo[item].m_vIconPos.y + 20.0f, m_pstItemInfo[item].m_vIconPos.z);
			}
			m_pstItemInfo[item].m_ppCNumSprite[sprite]->SetPosition(m_vPos);

			//パターン.
			m_pstItemInfo[item].m_ppCNumSprite[sprite]->SetPattern(m_pstItemInfo[item].m_pvPattern[sprite]);
			//描画.
			m_pstItemInfo[item].m_ppCNumSprite[sprite]->Render();
		}
	}

}

//===================================.
//	アイテムの個数取得.
//===================================.
void CItemCount::SetItemCount(int ItemNum, int Count)
{
	switch (ItemNum)
	{
	case 0:
		m_Vegetable_Count = Count;
		break;
	case 1:
		m_Meat_Count = Count;
		break;
	case 2:
		m_Fish_Count = Count;
		break;
	case 3:
		m_Rice_Count = Count;
		break;
	default:
		break;
	}
}

//===================================.
//	解放処理関数.
//===================================.
void CItemCount::Release()
{
	for (int item = ITEM_TYPE_MAX - 1; item >= 0; item--)
	{
		SAFE_DELETE_ARRAY(m_pstItemInfo[item].m_pvPattern);
		SAFE_DELETE_ARRAY(m_pstItemInfo[item].m_ppCNumSprite);
	}
	SAFE_DELETE_ARRAY(m_pstItemInfo);
}
