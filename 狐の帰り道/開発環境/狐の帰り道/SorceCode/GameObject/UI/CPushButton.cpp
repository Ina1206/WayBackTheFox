#include "CPushButton.h"

CPushButton::CPushButton()
	: m_pCPushButton(nullptr)
	, m_enButtonFade(enFade::Fade_In)
	, m_fPushButtonAlpha(0.0f)
	, m_FadeTime(0)
{
	Init_Process();
}

CPushButton::~CPushButton()
{
}

//------------------------------------------.
//	初期設定処理関数.
//------------------------------------------.
void CPushButton::Init_Process()
{
	m_vPos = BUTTON_POS;
}

//------------------------------------------.
//	更新処理関数.
//------------------------------------------.
void CPushButton::UpDate()
{
	ButtonFade();
}

//------------------------------------------.
//	描画処理関数.
//------------------------------------------.
void CPushButton::Render()
{
	//ボタン指示.
	m_pCPushButton = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::PushButton);
	_ASSERT_EXPR(m_pCPushButton != nullptr, L"m_pCPushButton == nullptr");
	m_pCPushButton->SetPosition(m_vPos);
	m_pCPushButton->SetAlpha(m_fPushButtonAlpha);
	m_pCDepth_Stencil->SetDepth(false);
	m_pCPushButton->Render();
	m_pCDepth_Stencil->SetDepth(true);
}

//------------------------------------------.
//	解放処理関数.
//------------------------------------------.
void CPushButton::Release()
{
	if (m_pCPushButton != nullptr) {
		m_pCPushButton = nullptr;
	}

}

//------------------------------------------.
//	ボタンフェード処理関数.
//------------------------------------------.
void CPushButton::ButtonFade()
{
	if (m_fPushButtonAlpha > BUTTON_ALPHA_MAX)
	{
		m_FadeTime++;
		//50秒待つ.
		if (m_FadeTime % BUTTON_WAITTIME == 0)
		{
			m_enButtonFade = enFade::Fade_Out;
		}
	}
	if (m_fPushButtonAlpha < 0.0f)
	{
		m_enButtonFade = enFade::Fade_In;
		m_FadeTime = 0;
	}

	//フェード処理.
	switch (m_enButtonFade)
	{
	case CUI_Base::enFade::Fade_In:
		m_fPushButtonAlpha += BUTTON_ALPHA_SPEED;
		break;
	case CUI_Base::enFade::Fade_Out:
		m_fPushButtonAlpha -= BUTTON_ALPHA_SPEED;
		break;
	default:
		break;
	}
}
