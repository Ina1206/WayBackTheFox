#include "CResourceManager.h"

CResourceManager::CResourceManager()
	: m_pCResourceStaticMesh(nullptr)
	, m_pCResourceSkinMesh	(nullptr)
	, m_pCResourceParticle	(nullptr)
	, m_pCResourceSprite	(nullptr)
	, m_pCResourceSpriteUI	(nullptr)
	, m_pCDebugText			(nullptr)
{
}

CResourceManager::~CResourceManager()
{
}

//=============================================.
//		読み込み処理関数.
//=============================================.
void CResourceManager::Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	//--------------StaticMesh---------------//.
	m_pCResourceStaticMesh = new CResourceStaticMesh();
	m_pCResourceStaticMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	m_pCResourceStaticMesh->Init();
	m_pCResourceStaticMesh->Load();

	//---------------SkinMehs----------------//.
	m_pCResourceSkinMesh = new CResourceSkinMesh();
	m_pCResourceSkinMesh->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	m_pCResourceSkinMesh->Init();
	m_pCResourceSkinMesh->Load();

	//----------------Particle----------------//.
	m_pCResourceParticle = new CResourceParticle();
	m_pCResourceParticle->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	m_pCResourceParticle->Init();
	m_pCResourceParticle->Load();

	//-----------------Sprite----------------//.
	m_pCResourceSprite = new CResourceSprite();
	m_pCResourceSprite->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	m_pCResourceSprite->Init();
	m_pCResourceSprite->Load();

	//----------------SpriteUI----------------//.
	m_pCResourceSpriteUI = new CResourceSpriteUI();
	m_pCResourceSpriteUI->Init_Replacement(hWnd, pDevice9, pDevice11, pContext11);
	m_pCResourceSpriteUI->Init();
	m_pCResourceSpriteUI->Load();

#ifdef _DEBUG
	m_pCDebugText = new CDebugText();
	//m_pCDebugText->Init(pContext11, WND_W, WND_H, 50.0f, D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
#endif	//#ifdef _DEBUG.

}

//=============================================.
//		解放処理関数.
//=============================================.
void CResourceManager::Release()
{
	//クラスごとの解放処理.
	m_pCResourceSpriteUI->ReleaseCalling();		//SpriteUIクラス.
	m_pCResourceSprite->ReleaseCalling();		//Spriteクラス.
	m_pCResourceParticle->ReleaseCalling();		//Particleクラス.
	m_pCResourceSkinMesh->ReleaseCalling();		//SkinMeshクラス.
	m_pCResourceStaticMesh->ReleaseCalling();	//StaticMeshクラス.

	//クラスの解放処理.
#ifdef _DEBUG
	SAFE_DELETE(m_pCDebugText);					//デバッグテキスト.
#endif	//#ifdef _DEBUG.
	SAFE_DELETE(m_pCResourceSpriteUI);			//SpriteUIクラス.
	SAFE_DELETE(m_pCResourceSprite);			//Spriteクラス.
	SAFE_DELETE(m_pCResourceParticle);			//Particleクラス.
	SAFE_DELETE(m_pCResourceSkinMesh);			//SkinMeshクラス.
	SAFE_DELETE(m_pCResourceStaticMesh);		//StaticMeshクラス.
}

void CResourceManager::FontRender(const char* cha, int x, int y) {
	m_pCDebugText->Render(cha, x, y);
}

//=============================================.
//		作成処理関数.
//=============================================.
void CResourceManager::Create()
{

}
