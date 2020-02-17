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
//		�ǂݍ��ݏ����֐�.
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
//		��������֐�.
//=============================================.
void CResourceManager::Release()
{
	//�N���X���Ƃ̉������.
	m_pCResourceSpriteUI->ReleaseCalling();		//SpriteUI�N���X.
	m_pCResourceSprite->ReleaseCalling();		//Sprite�N���X.
	m_pCResourceParticle->ReleaseCalling();		//Particle�N���X.
	m_pCResourceSkinMesh->ReleaseCalling();		//SkinMesh�N���X.
	m_pCResourceStaticMesh->ReleaseCalling();	//StaticMesh�N���X.

	//�N���X�̉������.
#ifdef _DEBUG
	SAFE_DELETE(m_pCDebugText);					//�f�o�b�O�e�L�X�g.
#endif	//#ifdef _DEBUG.
	SAFE_DELETE(m_pCResourceSpriteUI);			//SpriteUI�N���X.
	SAFE_DELETE(m_pCResourceSprite);			//Sprite�N���X.
	SAFE_DELETE(m_pCResourceParticle);			//Particle�N���X.
	SAFE_DELETE(m_pCResourceSkinMesh);			//SkinMesh�N���X.
	SAFE_DELETE(m_pCResourceStaticMesh);		//StaticMesh�N���X.
}

void CResourceManager::FontRender(const char* cha, int x, int y) {
	m_pCDebugText->Render(cha, x, y);
}

//=============================================.
//		�쐬�����֐�.
//=============================================.
void CResourceManager::Create()
{

}
