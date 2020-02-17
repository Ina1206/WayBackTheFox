#include "CDebugCollisionSphere.h"

CDebugCollisionSphere::CDebugCollisionSphere()
	: m_pSphere	(nullptr)
	, m_vPos	(0.0f, 0.0f, 0.0f)
	, m_fScale	(1.0f)
{
}

CDebugCollisionSphere::~CDebugCollisionSphere()
{
	Release();
}

//=========================================.
//		•`‰æˆ—ŠÖ”.
//=========================================.
void CDebugCollisionSphere::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos)
{
	Attach();
	m_pSphere->SetScale(m_fScale);
	m_pSphere->SetPosition(m_vPos);
	m_pSphere->Render(mView, mProj, vLight, vCameraPos);
}

//=========================================.
//		æ“¾ŠÖ”.
//=========================================.
void CDebugCollisionSphere::Attach()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pSphere = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Hit_Sphere);
	_ASSERT_EXPR(m_pSphere != nullptr, L"m_pSphere == nullptr");
}

//=========================================.
//		‰ğ•úˆ—ŠÖ”.
//=========================================.
void CDebugCollisionSphere::Release()
{
	m_pSphere = nullptr;
}