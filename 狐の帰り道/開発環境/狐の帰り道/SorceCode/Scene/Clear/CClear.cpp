#include "CClear.h"

CClear::CClear()
	:m_pCClearUIManager(nullptr)
	, m_pCCameraManager(nullptr)
{
}

CClear::~CClear()
{
	Release();
}

//========================================.
//		初期設定処理関数.
//========================================.
void CClear::Init_Process()
{
	m_pCClearUIManager = new CClearUIManager();
	m_pCClearUIManager->Init_Process();
	m_pCClearUIManager->SetPointSum(m_PointSum);

	m_pCCameraManager = new CCameraManager();
}

//=========================================.
//		更新処理関数.
//=========================================.
void CClear::UpDate()
{
	m_pCCameraManager->UpDate();
	m_pCClearUIManager->UpDate();
	m_bUIDrawEnd = m_pCClearUIManager->GetUIDrawEndFlag();

}

//==========================================.
//		描画処理関数.
//==========================================.
void CClear::Render()
{
	//置換処理.
	m_mView = m_pCCameraManager->GetmView();	//ビュー行列.
	m_vCamPos = m_pCCameraManager->GetvPos();	//カメラ位置.

	m_pCClearUIManager->Render(m_mView, m_mProj, m_vCamPos);
}

//==========================================.
//		解放処理関数.
//==========================================.
void CClear::Release()
{
	SAFE_DELETE(m_pCCameraManager);
	SAFE_DELETE(m_pCClearUIManager);
}