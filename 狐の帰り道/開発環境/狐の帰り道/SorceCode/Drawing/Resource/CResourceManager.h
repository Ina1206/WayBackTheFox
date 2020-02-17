#ifndef CRESOURCE_MANAGER_H
#define CRESOURCE_MANAGER_H

//�ǂݍ��݃N���X.
#include "ResourceBordPolygon/ResourceParticle/CResourceParticle.h"
#include "ResourceBordPolygon/ResourcePolygon/CResourceSprite.h"
#include "ResourceBordPolygon/ResourceSpriteUI/CResourceSpriteUI.h"
#include "ResourceSkinMesh/CResourceSkinMesh.h"
#include "ResourceStaticMesh/CResourceStaticMesh.h"
#include "..\Bord_Polygon\DebugText\CDebugText.h"

/*********************************************
*	�ǂݍ��݊Ǘ��N���X.
**/
class CResourceManager
{
public:
	CResourceManager();
	~CResourceManager();

	//==================�񋓑�=====================//.
	enum class enResourceType {
		StaticMesh,		//���b�V��.
		SkinMesh,		//�X�L�����b�V��.
		Particle,		//�p�[�e�B�N��.
		Sprite,			//�X�v���C�g.
		SpriteUI,		//�X�v���C�gUI.

		Max,
	};

	//===================�萔======================//.
	const int RESOURCE_TYPE_MAX = static_cast<int>(enResourceType::Max);

	//===================�֐�======================//.
	void Load(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);			//�ǂݍ��ݏ����֐�.
	void Release();																			//��������֐�.
	void FontRender(const char* cha, int x, int y);																		//�t�H���g�����_�����O.

	//�`���l�������֐��`.
	CDX9Mesh*			GetStaticMesh(CResourceStaticMesh::enStaticMesh enStaticMehs)	{ return m_pCResourceStaticMesh->GetStaticMesh(enStaticMehs); }	//CDX9Mesh�̏��l�������֐�.
	CDX9SkinMesh*		GetSkinMesh(CResourceSkinMesh::enSkincMesh enSkinMesh)			{ return m_pCResourceSkinMesh->GetSkinMesh(enSkinMesh); }		//SkinMehs�̏��l�������֐�.
	CParticle*			GetParticle(CResourceParticle::enParticle enParticle)			{ return m_pCResourceParticle->GetParticle(enParticle); }		//Particle�̏��l�������֐�.
	CSprite*			GetSprite(CResourceSprite::enSprite enSprite)					{ return m_pCResourceSprite->GetSprite(enSprite); }				//Sprite�̏��l�������֐�.
	CSpriteUI*			GetSpriteUI(CResourceSpriteUI::enSpriteUI enSpriteUI)			{ return m_pCResourceSpriteUI->GetSpriteUI(enSpriteUI); }		//SpriteUI�̏��l�������֐�.
	//================�V���O���g��=================//.
	static CResourceManager* GetResourceManagerInstance()
	{
		static CResourceManager s_Instance;
		return &s_Instance;
	}

private:
	//===================�֐�======================//.
	void Create();			//�쐬�����֐�.

	//==================�N���X=====================//.
	CResourceStaticMesh*	m_pCResourceStaticMesh;			//StaticMesh�N���X.
	CResourceSkinMesh*		m_pCResourceSkinMesh;			//SkinMesh�N���X.
	CResourceParticle*		m_pCResourceParticle;			//�p�[�e�B�N���N���X.
	CResourceSprite*		m_pCResourceSprite;				//Sprite�N���X.
	CResourceSpriteUI*		m_pCResourceSpriteUI;			//SpriteUI�N���X.

	CDebugText*				m_pCDebugText;					//�f�o�b�O�e�L�X�g.

};

#endif	//#ifndef CRESOURCE_MANAGER_H.