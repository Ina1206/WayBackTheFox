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
//		�����ݒ菈���֐�.
//========================================.
void CClear::Init_Process()
{
	m_pCClearUIManager = new CClearUIManager();
	m_pCClearUIManager->Init_Process();
	m_pCClearUIManager->SetPointSum(m_PointSum);

	m_pCCameraManager = new CCameraManager();
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CClear::UpDate()
{
	m_pCCameraManager->UpDate();
	m_pCClearUIManager->UpDate();
	m_bUIDrawEnd = m_pCClearUIManager->GetUIDrawEndFlag();

}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CClear::Render()
{
	//�u������.
	m_mView = m_pCCameraManager->GetmView();	//�r���[�s��.
	m_vCamPos = m_pCCameraManager->GetvPos();	//�J�����ʒu.

	m_pCClearUIManager->Render(m_mView, m_mProj, m_vCamPos);
}

//==========================================.
//		��������֐�.
//==========================================.
void CClear::Release()
{
	SAFE_DELETE(m_pCCameraManager);
	SAFE_DELETE(m_pCClearUIManager);
}