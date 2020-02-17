#ifndef CRESOURCE_CDX9MESH_H
#define CRESOURCE_CDX9MESH_H

#include "..\..\3D_Object\CDX9Mesh.h"
#include "..\CResourceBase.h"

/**********************************************
*	StaticMesh�p�ǂݍ��݃N���X.
**/
class CResourceStaticMesh
	: public CResourceBase
{
public:
	CResourceStaticMesh();
	~CResourceStaticMesh();

	//===================�񋓑�======================//.
	//StaticMesh�̎��.
	enum class enStaticMesh {
		Ground = 0,		//�n��.
		Cow_Gohst,		//��������
		Hit_Sphere,		//�����蔻��p����.
		Gate,			//����.
		BackGround,		//�w�i.
		Grass,			//��.
		AroundGround,	//����̒n��.
		Ground2,		//�n��2��.

		Max,			//�ő吔.
		Start = Ground,	//�ŏ�.
	};

	//====================�֐�======================//.
	HRESULT Init();						//�����ݒ菈���֐�.
	HRESULT Load();													//�ǂݍ��ݏ����֐�.
	HRESULT ReleaseCalling();										//��������Ăяo���֐�.

	//===============���l�������֐�================//.
	CDX9Mesh*	GetStaticMesh(enStaticMesh StaticMesh);
private: 
	//====================�֐�======================//.
	HRESULT Create(enStaticMesh StaticMesh, const char* pfileName);	//�쐬�����֐�.
	HRESULT Release(enStaticMesh StaticMesh);						//��������֐�.
	HRESULT Check_MeshRnge(enStaticMesh StaticMesh);				//���b�V���͈̔͂𒲂ׂ�֐�.
	HRESULT	InitSphere();											//�X�t�B�A�̍쐬�����֐�.

	//===================�N���X=====================//.
	CDX9Mesh**	m_ppStaticMesh;	//���b�V���N���X.


};

#endif	//#ifndef CRESOURCE_CDX9MESH_H.