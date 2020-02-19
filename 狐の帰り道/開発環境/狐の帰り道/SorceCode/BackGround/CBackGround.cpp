#include "CBackGround.h"

/********************************************
*		�w�i�I�u�W�F�N�g�N���X.
*****/
CBackGround::CBackGround()
	: m_pCDx9Mesh(nullptr)
{
	//�����������֐�.
	Init();
}

CBackGround::~CBackGround()
{
	//��������֐�.
	Release();
}

//==================================.
//		�`�揈���֐�.
//==================================.
void CBackGround::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos)
{
	//�ʒu�ݒ�.
	m_pCDx9Mesh->SetPosition(POSITION);
	//�傫���ݒ�.
	m_pCDx9Mesh->SetScale(SCALE);
	//��]�p�x�ݒ�.
	m_pCDx9Mesh->SetRotation(ROTATION);
	//�`��.
	m_pCDx9Mesh->Render(mView, mProj, vLight, vCameraPos);
}

//==================================.
//		�����������֐�.
//==================================.
void CBackGround::Init()
{
	//�w�i�̃I�u�W�F�N�g�A�h���X�擾.
	CResourceManager* m_pCResoueceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDx9Mesh = m_pCResoueceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::BackGround);
}

//===================================.
//		��������֐�.
//===================================.
void CBackGround::Release()
{
	m_pCDx9Mesh = nullptr;
}