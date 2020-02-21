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
//		初期設定処理関数.
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
//		更新処理関数.
//=======================================.
void CTitle::UpDate()
{
	m_pCCameraManager->UpDate();
	m_pCTitleUIManager->UpDate();
	m_bUIDrawEnd      = m_pCTitleUIManager->GetUIDrawEndFlag();
}

//========================================.
//		描画処理関数.
//========================================.
void CTitle::Render()
{
	//置換処理.
	m_mView = m_pCCameraManager->GetmView();	//ビュー行列.
	m_vCamPos = m_pCCameraManager->GetvPos();	//カメラ位置.

	m_pCBackGround->Render(m_mView, m_mProj, m_vLight, m_vCamPos);

	m_pCGround->Value_Set(m_mView, m_mProj, m_vLight, m_vCamPos);
	m_pCGround->Render();

	m_pCTitleUIManager->Render(m_mView, m_mProj, m_vCamPos);
}

//========================================.
//		解放処理関数.
//========================================.
void CTitle::Release()
{
	SAFE_DELETE(m_pCCameraManager);
	SAFE_DELETE(m_pCBackGround);
	SAFE_DELETE(m_pCGround);
	SAFE_DELETE(m_pCTitleUIManager);
	m_pCResourceManager = nullptr;
}