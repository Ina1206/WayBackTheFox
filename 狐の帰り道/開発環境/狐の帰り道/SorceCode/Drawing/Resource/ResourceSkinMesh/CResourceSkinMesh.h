#ifndef CRESOURCE_SKINMESH_H
#define CRESOURCE_SKINMESH_H

#include "..\CResourceBase.h"

#include "..\..\3D_Object\CDX9SkinMesh.h"


/**********************************************
*	SkinMesh�p�ǂݍ��݃N���X.
**/
class CResourceSkinMesh
	: public CResourceBase
{
public:
	CResourceSkinMesh();
	~CResourceSkinMesh();

	//===================�񋓑�======================//.
	//StaticMesh�̎��.
	enum class enSkincMesh {
		Raccoon_Dog,			//�^�k�L.
		Player,
		BigRaccoon_Dog,			//�f�J�^�k�L.

		Max,					//�ő吔.
		Start = Raccoon_Dog,	//�ŏ�.
	};


	//====================�֐�======================//.
	HRESULT Init();													//�����ݒ菈���֐�.
	HRESULT Load();													//�ǂݍ��ݏ����֐�.
	HRESULT ReleaseCalling();										//��������Ăяo���֐�.

	//===============���l�������֐�================//.
	CDX9SkinMesh*	GetSkinMesh(enSkincMesh StaticMesh);
private:
	//====================�֐�======================//.
	HRESULT Create(enSkincMesh StaticMesh, const char* pfileName);	//�쐬�����֐�.
	HRESULT Release(enSkincMesh StaticMesh);						//��������֐�.
	HRESULT Check_SkinMeshRnge(enSkincMesh StaticMesh);				//�X�L�����b�V���͈̔͂𒲂ׂ�֐�.
	HRESULT ChangeTexture();										//�e�N�X�`���؂�ւ�.

	//===================�N���X=====================//.
	CDX9SkinMesh**	m_ppSkincMesh;	//���b�V���N���X.
	CDX9SkinMesh::CHANGE_TEXTURE*	m_pChangeTexture;	//�e�N�X�`���؂�ւ�.

};

#endif	//#ifndef CRESOURCE_SKINMESH_H.