#include "CBackGround.h"

CBackGround::CBackGround()
	: m_pCDx9Mesh(nullptr)
{
	//‰Šú‰»ˆ—ŠÖ”.
	Init();
}

CBackGround::~CBackGround()
{
	//‰ğ•úˆ—ŠÖ”.
	Release();
}

//==================================.
//		•`‰æˆ—ŠÖ”.
//==================================.
void CBackGround::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos)
{
	//ˆÊ’uİ’è.
	m_pCDx9Mesh->SetPosition(POSITION);
	//‘å‚«‚³İ’è.
	m_pCDx9Mesh->SetScale(SCALE);
	//‰ñ“]Šp“xİ’è.
	m_pCDx9Mesh->SetRotation(ROTATION);
	//•`‰æ.
	m_pCDx9Mesh->Render(mView, mProj, vLight, vCameraPos);
}

//==================================.
//		‰Šú‰»ˆ—ŠÖ”.
//==================================.
void CBackGround::Init()
{
	CResourceManager* m_pCResoueceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDx9Mesh = m_pCResoueceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::BackGround);
}

//===================================.
//		‰ğ•úˆ—ŠÖ”.
//===================================.
void CBackGround::Release()
{
	m_pCDx9Mesh = nullptr;
}