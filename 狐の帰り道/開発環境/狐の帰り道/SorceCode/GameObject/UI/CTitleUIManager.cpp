#include "CTitleUIManager.h"

CTitleUIManager::CTitleUIManager()
	: m_pCTitle_Particle	(nullptr)
	, m_pCPushButton		(nullptr)
	, m_pCTitle_Character	(nullptr)
{
}

CTitleUIManager::~CTitleUIManager()
{
	Release();
}

//------------------------------------------.
//	‰Šúİ’èˆ—ŠÖ”.
//------------------------------------------.
void CTitleUIManager::Init_Process()
{
	m_pCTitle_Particle = new CTitle_Particle();
	m_pCTitle_Particle->Init_Process();
	m_pCPushButton = new CPushButton();
	m_pCPushButton->Init_Process();
	m_pCTitle_Character = new CTitle_Character();
	m_pCTitle_Character->Init_Process();
}

//------------------------------------------.
//	XVˆ—ŠÖ”.
//------------------------------------------.
void CTitleUIManager::UpDate()
{
	m_pCTitle_Particle->UpDate();
	if (m_pCTitle_Character->GetMoveEndFlag() == true)
	{
		m_pCPushButton->UpDate();
	}
	m_pCTitle_Character->UpDate();
}

//------------------------------------------.
//	•`‰æˆ—ŠÖ”.
//------------------------------------------.
void CTitleUIManager::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vCameraPos)
{
	m_pCTitle_Particle->Value_Set(mView, mProj, vCameraPos);
	m_pCTitle_Particle->Render();

	m_pCPushButton->Value_Set(mView, mProj, vCameraPos);
	m_pCPushButton->Render();

	m_pCTitle_Character->Value_Set(mView, mProj, vCameraPos);
	m_pCTitle_Character->Render();
}

//------------------------------------------.
//	‰ğ•úˆ—ŠÖ”.
//------------------------------------------.
void CTitleUIManager::Release()
{
	SAFE_DELETE(m_pCTitle_Character);
	SAFE_DELETE(m_pCPushButton);
	SAFE_DELETE(m_pCTitle_Particle);
}
