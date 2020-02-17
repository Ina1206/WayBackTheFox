#include "CClearUI.h"

CClearUI::CClearUI()
	: m_ppCClearSpriteUI(nullptr)
	, m_ClearNo(-1)

{
	Init_Process();
}

CClearUI::~CClearUI()
{
}

//------------------------------------------.
//	初期設定処理関数.
//------------------------------------------.
void CClearUI::Init_Process()
{
	m_ppCClearSpriteUI = new CSpriteUI*[SPRITEUI_MAX];
}

//------------------------------------------.
//	更新処理関数.
//------------------------------------------.
void CClearUI::UpDate()
{
	//クリア番号が入ったら再生.
	if (m_ClearNo > -1) {
		CSEPlayManager* m_pCSEPlayerManager = CSEPlayManager::GetSEPlayManagerInstance();
		int BGM_No = static_cast<int>(CSoundResource::enLoopSound::EndingHight_BGM) + m_ClearNo;
		m_pCSEPlayerManager->SetLoopSEPlay(CSoundResource::enLoopSound::Boss_BGM, false);
		m_pCSEPlayerManager->SetLoopSEPlay(static_cast<CSoundResource::enLoopSound>(BGM_No), true);
	}
}

//------------------------------------------.
//	描画処理関数.
//------------------------------------------.
void CClearUI::Render()
{

	for (int clear = 0; clear < 3; clear++) {
		int spriteUI = (static_cast<int>(CResourceSpriteUI::enSpriteUI::Clear_High)) + clear;
		m_ppCClearSpriteUI[clear] = m_pCResourceManager->GetSpriteUI(static_cast<CResourceSpriteUI::enSpriteUI>(spriteUI));
		_ASSERT_EXPR(m_ppCClearSpriteUI != nullptr, L"m_ppCClearSpriteUI == nullptr");
		m_ppCClearSpriteUI[clear]->SetPosition(m_vPos);
	}

	m_pCDepth_Stencil->SetDepth(false);
	if (CClearUI::m_PointSum <= MIDDLE_POINT) {
		m_ppCClearSpriteUI[SPRITEUI_AMOUNT]->Render();
		m_ClearNo = SPRITEUI_AMOUNT;
	}
	if (CClearUI::m_PointSum >= MIDDLE_POINT && m_PointSum <= HIGH_POINT) {
		m_ppCClearSpriteUI[SPRITEUI_SMILE]->Render();
		m_ClearNo = SPRITEUI_SMILE;
	}
	if (CClearUI::m_PointSum >= HIGH_POINT) {
		m_ppCClearSpriteUI[SPRITEUI_MAX_SMILE]->Render();
		m_ClearNo = SPRITEUI_MAX_SMILE;
	}
	m_pCDepth_Stencil->SetDepth(true);

}

//------------------------------------------.
//	解放処理関数.
//------------------------------------------.
void CClearUI::Release()
{
	SAFE_DELETE_ARRAY(m_ppCClearSpriteUI);
}
