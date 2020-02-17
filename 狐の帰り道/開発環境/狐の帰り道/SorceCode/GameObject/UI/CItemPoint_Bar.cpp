#include "CItemPoint_Bar.h"

CItemPoint_Bar::CItemPoint_Bar()
	: m_ppCBarSprite(nullptr)
	, m_pfScale		(nullptr)
	, m_PointSum	(0)
{
	m_ppCBarSprite = new CSpriteUI*[BER_MAX];
	m_pfScale      = new float[BER_MAX];

	for (int bar = 0; bar < BER_MAX; bar++) {
		m_pfScale[bar] = 0.0f;
	}
}

CItemPoint_Bar::~CItemPoint_Bar()
{
	Release();
}

void CItemPoint_Bar::UpDate()
{
	const float SCALE = m_PointSum / static_cast<float>(HIGH_POINT);

	for (int bar = BER_BLUEMAX; bar < BER_MAX; bar++)
	{
		if (m_pfScale[bar] <= SCALE) {
			m_pfScale[bar] += SCALE_SPEED;
		}
		if (m_pfScale[bar] != 0 && m_pfScale[bar] >= SCALE) {
			m_pfScale[bar] -= SCALE_SPEED;
		}
		if (m_pfScale[bar] > SCALE_MAX) {
			m_pfScale[bar] = SCALE_MAX;
		}
	}

}

void CItemPoint_Bar::Render()
{
	for (int bar = 0; bar < BER_MAX; bar++)
	{
		int BarNum = static_cast<int>(CResourceSpriteUI::enSpriteUI::Point_Bar_Back) + bar;
		m_ppCBarSprite[bar] = m_pCResourceManager->GetSpriteUI(static_cast<CResourceSpriteUI::enSpriteUI>(BarNum));

		//à íuê›íË.
		m_vPos = BER_BACK_POSITION;
		D3DXVECTOR3 BarPosition = D3DXVECTOR3(BER_BACK_POSITION.x + BER_POSITION.x, BER_BACK_POSITION.y + BER_POSITION.y, 0.0f);
		if (bar == BER_BACK) {
			m_ppCBarSprite[bar]->SetPosition(m_vPos);
		}
		else
		{
			m_ppCBarSprite[bar]->SetPosition(BarPosition);
		}

		//ëÂÇ´Ç≥ê›íË.
		if (bar == BER_BACK) {
			m_pfScale[bar] = SCALE_MAX;
		}
		//else {
		//	m_pfScale[bar] = m_PointSum / static_cast<float>(HIGH_POINT);
		//	if (m_pfScale[bar] > 1.0f) {
		//		m_pfScale[bar] = 1.0f;
		//	}
		//}
		m_ppCBarSprite[bar]->SetScale(m_pfScale[bar]);
	}
	//ï`âÊ.
	m_pCDepth_Stencil->SetDepth(false);
	m_ppCBarSprite[0]->Render();
	if (m_PointSum < MIDDLE_POINT)
	{
		m_ppCBarSprite[BER_BLUEMAX]->Render();
	}
	else if (m_PointSum >= MIDDLE_POINT && m_PointSum < HIGH_POINT)
	{
		m_ppCBarSprite[BER_REDMAX]->Render();
	}
	else
	{
		m_ppCBarSprite[BER_RAINBOWMAX]->Render();
	}
	m_pCDepth_Stencil->SetDepth(true);

}

void CItemPoint_Bar::Release()
{
	SAFE_DELETE_ARRAY(m_pfScale);
	SAFE_DELETE_ARRAY(m_ppCBarSprite);
}
