#include "CMainUIManager.h"

CMainUIManager::CMainUIManager()
	: m_pCItemIcon	(nullptr)
	, m_pCFaceIcon	(nullptr)
	, m_pCStartCount(nullptr)
	, m_pCItemCount	(nullptr)
	, m_pCtemPoint_Bar(nullptr)
{
}

CMainUIManager::~CMainUIManager()
{
	Release();
}

//=======================================.
//		‰Šú‰»ŠÖ”.
//=======================================.
void CMainUIManager::Init_Process()
{
	m_pCItemIcon	= new CItemIcon();
	m_pCFaceIcon	= new CFaceIcon();
	m_pCStartCount	= new CStartCount();
	m_pCItemCount	= new CItemCount();
	m_pCStartCount->SetDispFlag(true);
	m_pCtemPoint_Bar = new CItemPoint_Bar();
}

//=======================================.
//		XVˆ—ŠÖ”.
//=======================================.
void CMainUIManager::UpDate()
{
	m_pCFaceIcon->SetItemPointSum(m_PointSum);
	m_pCFaceIcon->UpDate();
	m_pCStartCount->UpDate();
	m_pCtemPoint_Bar->SetItemPointSum(m_PointSum);
	m_pCtemPoint_Bar->UpDate();

	for (int item = 0; item < ITEM_TYPE_MAX; item++)
	{
		m_pCItemCount->SetIconPos(item, m_pCItemIcon->GetIconPosition(item));
	}

}

//=======================================.
//		•`‰æˆ—ŠÖ”.
//=======================================.
void CMainUIManager::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	m_pCItemIcon->Value_Set(mView, mProj, vCamePos);
	m_pCItemIcon->Render();
	m_pCFaceIcon->Value_Set(mView, mProj, vCamePos);
	m_pCFaceIcon->Render();
	m_pCStartCount->Value_Set(mView, mProj, vCamePos);
	m_pCStartCount->Render();
	m_pCItemCount->Value_Set(mView, mProj, vCamePos);
	m_pCItemCount->Render();
	m_pCtemPoint_Bar->Value_Set(mView, mProj, vCamePos);
	m_pCtemPoint_Bar->Render();
}

//=======================================.
//		‰ğ•úˆ—ŠÖ”.
//=======================================.
void CMainUIManager::Release()
{
	SAFE_DELETE(m_pCtemPoint_Bar);
	SAFE_DELETE(m_pCItemCount);
	SAFE_DELETE(m_pCStartCount);
	SAFE_DELETE(m_pCFaceIcon);
	SAFE_DELETE(m_pCItemIcon);
}
