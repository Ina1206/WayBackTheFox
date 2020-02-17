#ifndef CRESOURCE_MANAGER_H
#define CRESOURCE_MANAGER_H

//読み込みクラス.
#include "ResourceBordPolygon/ResourceParticle/CResourceParticle.h"
#include "ResourceBordPolygon/ResourcePolygon/CResourceSprite.h"
#include "ResourceBordPolygon/ResourceSpriteUI/CResourceSpriteUI.h"
#include "ResourceSkinMesh/CResourceSkinMesh.h"
#include "ResourceStaticMesh/CResourceStaticMesh.h"
#include "..\Bord_Polygon\DebugText\CDebugText.h"

/*********************************************
*	読み込み管理クラス.
**/
class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	//==================列挙体=====================//.
	enum class enResourceType {
		StaticMesh,		//メッシュ.
		SkinMesh,		//スキンメッシュ.
		Particle,		//パーティクル.
		Sprite,			//スプライト.
		SpriteUI,		//スプライトUI.

		Max,
	};

	//===================定数======================//.
	const int RESOURCE_TYPE_MAX = static_cast<int>(enResourceType::Max);

	//===================関数======================//.
	void Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);			//読み込み処理関数.
	void Release();																			//解放処理関数.
	void FontRender(const char* cha, int x, int y);																		//フォントレンダリング.

	//～情報獲得処理関数～.
	CDX9Mesh*			GetStaticMesh(CResourceStaticMesh::enStaticMesh enStaticMehs)	{ return m_pCResourceStaticMesh->GetStaticMesh(enStaticMehs); }	//CDX9Meshの情報獲得処理関数.
	CDX9SkinMesh*		GetSkinMesh(CResourceSkinMesh::enSkincMesh enSkinMesh)			{ return m_pCResourceSkinMesh->GetSkinMesh(enSkinMesh); }		//SkinMehsの情報獲得処理関数.
	CParticle*			GetParticle(CResourceParticle::enParticle enParticle)			{ return m_pCResourceParticle->GetParticle(enParticle); }		//Particleの情報獲得処理関数.
	CSprite*			GetSprite(CResourceSprite::enSprite enSprite)					{ return m_pCResourceSprite->GetSprite(enSprite); }				//Spriteの情報獲得処理関数.
	CSpriteUI*			GetSpriteUI(CResourceSpriteUI::enSpriteUI enSpriteUI)			{ return m_pCResourceSpriteUI->GetSpriteUI(enSpriteUI); }		//SpriteUIの情報獲得処理関数.
	//================シングルトン=================//.
	static CResourceManager* GetResourceManagerInstance()
	{
		static CResourceManager s_Instance;
		return &s_Instance;
	}

private:
	//===================関数======================//.
	void Create();			//作成処理関数.

	//==================クラス=====================//.
	CResourceStaticMesh*	m_pCResourceStaticMesh;			//StaticMeshクラス.
	CResourceSkinMesh*		m_pCResourceSkinMesh;			//SkinMeshクラス.
	CResourceParticle*		m_pCResourceParticle;			//パーティクルクラス.
	CResourceSprite*		m_pCResourceSprite;				//Spriteクラス.
	CResourceSpriteUI*		m_pCResourceSpriteUI;			//SpriteUIクラス.

	CDebugText*				m_pCDebugText;					//デバッグテキスト.

};

#endif	//#ifndef CRESOURCE_MANAGER_H.