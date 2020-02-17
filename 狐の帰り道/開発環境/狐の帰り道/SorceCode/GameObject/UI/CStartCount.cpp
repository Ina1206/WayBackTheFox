#include "CStartCount.h"

CStartCount::CStartCount()
	: m_pCStartCount(nullptr)
	, m_pCStart(nullptr)
	, m_vPattarn(0.0f, 0.0f)
	, m_Frame(0)
	, m_Second(0)
	, m_bDispFlag(false)
{
	m_vPos = START_POSITION;
	m_Second = 4;
}

CStartCount::~CStartCount()
{
	Release();
}

//=====================================
//	XVˆ—ŠÖ”.
//=====================================
void CStartCount::UpDate()
{
	m_Frame++;
	if (m_Frame % 60 == 0)
	{
		m_Second--;
	}
	if (m_Second == 0)
	{
		m_bDispFlag = false;
		m_Frame = 0;
	}
}

//=====================================
//	•`‰æˆ—ŠÖ”.
//=====================================
void CStartCount::Render()
{
	if (m_bDispFlag == true) {
		m_pCStartCount = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::TimerNum);

		m_vPattarn = D3DXVECTOR2(static_cast<float>((m_Second - 1) % IMAGE_WIDTH_MAX), static_cast<float>((m_Second - 1) / IMAGE_HIGH_MAX));
		m_pCStartCount->SetPattern(m_vPattarn);

		m_pCStartCount->SetPosition(POSITION);
		if (m_Second > 1) {
			m_pCStartCount->Render();
		}

		m_pCStart = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::Start_Char);

		m_pCStart->SetPosition(m_vPos);
		if (m_Second == 1) {
			m_pCStart->Render();
		}
	}
}

//=====================================
//	‰ğ•úˆ—ŠÖ”.
//=====================================
void CStartCount::Release()
{
}

//=====================================
//	“®‚«ˆ—ŠÖ”.
//=====================================
void CStartCount::Move()
{
}

