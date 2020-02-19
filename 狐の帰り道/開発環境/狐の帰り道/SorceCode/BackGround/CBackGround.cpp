#include "CBackGround.h"

/********************************************
*		背景オブジェクトクラス.
*****/
CBackGround::CBackGround()
	: m_pCDx9Mesh(nullptr)
{
	//初期化処理関数.
	Init();
}

CBackGround::~CBackGround()
{
	//解放処理関数.
	Release();
}

//==================================.
//		描画処理関数.
//==================================.
void CBackGround::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos)
{
	//位置設定.
	m_pCDx9Mesh->SetPosition(POSITION);
	//大きさ設定.
	m_pCDx9Mesh->SetScale(SCALE);
	//回転角度設定.
	m_pCDx9Mesh->SetRotation(ROTATION);
	//描画.
	m_pCDx9Mesh->Render(mView, mProj, vLight, vCameraPos);
}

//==================================.
//		初期化処理関数.
//==================================.
void CBackGround::Init()
{
	//背景のオブジェクトアドレス取得.
	CResourceManager* m_pCResoueceManager = CResourceManager::GetResourceManagerInstance();
	m_pCDx9Mesh = m_pCResoueceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::BackGround);
}

//===================================.
//		解放処理関数.
//===================================.
void CBackGround::Release()
{
	m_pCDx9Mesh = nullptr;
}