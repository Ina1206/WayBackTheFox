#include "CLoad.h"

CLoad::CLoad()
	: m_pLoadScreen	(nullptr)
{
}

CLoad::~CLoad()
{
	SAFE_DELETE(m_pLoadScreen);
}

//=======================================.
//		‰Šú‰»ˆ—ŠÖ”.
//=======================================.
void CLoad::Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_pLoadScreen = new CSpriteUI();
	CSpriteUI::SPRITE_STATE ss;
	ss.Base.w = WND_W;
	ss.Base.h = WND_H;
	ss.Stride.w = ss.Base.w;
	ss.Stride.h = ss.Base.h;
	ss.Disp.w = WND_W;
	ss.Disp.h = WND_H;


	m_pLoadScreen->Init(pDevice11, pContext11, "Data\\Texture\\Load\\Load.png", &ss);
}

//=======================================.
//		•`‰æˆ—ŠÖ”.
//=======================================.
void CLoad::Render()
{
	m_pLoadScreen->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	m_pLoadScreen->Render();
	
}

//=======================================.
//		“Ç‚İ‚İˆ—ŠÖ”.
//=======================================.
HRESULT	CLoad::Load()
{
	return S_OK;
}