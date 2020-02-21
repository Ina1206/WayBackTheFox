#include "CTitle.h"

CTitle::CTitle()
	: m_pCResourceManager	(nullptr)
	, m_pCTitleUIManager	(nullptr)
	, m_pCGround			(nullptr)
	, m_pCBackGround		(nullptr)
	, m_pCCameraManager		(nullptr)
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
}

CTitle::~CTitle()
{
	Release();
}

//=======================================.
//		�����ݒ菈���֐�.
//=======================================.
void CTitle::Init_Process()
{
	m_pCGround = new CGround();
	m_pCGround->InitProcess();

	m_pCBackGround = new CBackGround();

	m_pCTitleUIManager = new CTitleUIManager();
	m_pCTitleUIManager->Init_Process();

	m_pCCameraManager = new CCameraManager();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CTitle::UpDate()
{
	m_pCCameraManager->UpDate();
	m_pCTitleUIManager->UpDate();
	m_bUIDrawEnd      = m_pCTitleUIManager->GetUIDrawEndFlag();
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CTitle::Render()
{
	//�u������.
	m_mView = m_pCCameraManager->GetmView();	//�r���[�s��.
	m_vCamPos = m_pCCameraManager->GetvPos();	//�J�����ʒu.

	m_pCBackGround->Render(m_mView, m_mProj, m_vLight, m_vCamPos);

	m_pCGround->Value_Set(m_mView, m_mProj, m_vLight, m_vCamPos);
	m_pCGround->Render();

	m_pCTitleUIManager->Render(m_mView, m_mProj, m_vCamPos);
}

//========================================.
//		��������֐�.
//========================================.
void CTitle::Release()
{
	SAFE_DELETE(m_pCCameraManager);
	SAFE_DELETE(m_pCBackGround);
	SAFE_DELETE(m_pCGround);
	SAFE_DELETE(m_pCTitleUIManager);
	m_pCResourceManager = nullptr;
}