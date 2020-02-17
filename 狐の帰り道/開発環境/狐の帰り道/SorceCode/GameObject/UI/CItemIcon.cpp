#include "CItemIcon.h"

CItemIcon::CItemIcon()
	: m_ppCItemIcon		(nullptr)
	, m_vVegetable_Pos	(0.0f,0.0f,0.0f)
	, m_vMeat_Pos		(0.0f,0.0f,0.0f)
	, m_vFish_Pos		(0.0f,0.0f,0.0f)
	, m_vRice_Pos		(0.0f,0.0f,0.0f)

{
	m_ppCItemIcon  = new CSpriteUI*[ITEM_SPRITE_MAX]();
}

CItemIcon::~CItemIcon()
{
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CItemIcon::UpDate()
{
}

//=======================================.
//		描画処理関数.
//=======================================.
void CItemIcon::Render()
{
	for (int iconNum = 0; iconNum < ITEM_SPRITE_MAX; iconNum++) {
		int spriteui = static_cast<int>(CResourceSpriteUI::enSpriteUI::MeatIcon) + iconNum;
		m_ppCItemIcon[iconNum] = m_pCResourceManager->GetSpriteUI(static_cast<CResourceSpriteUI::enSpriteUI>(spriteui));
	}

	//アイコンの位置.
	m_vPos.x = ICON_POS.x;
	m_vPos.y = ICON_POS.y;

	//肉アイコン.
	m_vMeat_Pos = m_vPos;
	m_ppCItemIcon[ITEM_MEAT]->SetPosition(m_vPos);

	m_vFish_Pos = D3DXVECTOR3(m_vPos.x, FISH_POS_Y, 0.0f);
	//魚アイコン.
	m_ppCItemIcon[ITEM_FISH]->SetPosition(m_vFish_Pos);

	m_vVegetable_Pos = D3DXVECTOR3(m_vPos.x, VEGETABLES_POS_Y, 0.0f);
	//野菜アイコン.
	m_ppCItemIcon[ITEM_VEGETABLES]->SetPosition(m_vVegetable_Pos);

	m_vRice_Pos = D3DXVECTOR3(m_vPos.x, RICE_POS_Y, 0.0f);
	//米アイコン.
	m_ppCItemIcon[ITEM_RICE]->SetPosition(m_vRice_Pos);

	//描画.
	for (int iconNum = 0; iconNum < ITEM_SPRITE_MAX; iconNum++) {
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCItemIcon[iconNum]->Render();
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//=======================================.
//		アイコン位置取得処理関数.
//=======================================.
D3DXVECTOR3 CItemIcon::GetIconPosition(int num)
{
	D3DXVECTOR3 vPos;

	switch (num)
	{
	case 0://野菜.
		vPos = m_vVegetable_Pos;
		break;
	case 1://肉.
		vPos = m_vMeat_Pos;
		break;
	case 2://魚.
		vPos = m_vFish_Pos;
		break;
	case 3://米.
		vPos = m_vRice_Pos;
		break;
	default:
		break;
	}

	return vPos;
}

//=======================================.
//		解放処理関数.
//=======================================.
void CItemIcon::Release()
{
	SAFE_DELETE_ARRAY(m_ppCItemIcon);
}
