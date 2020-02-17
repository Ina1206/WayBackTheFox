#include "CResourceStaticMesh.h"

CResourceStaticMesh::CResourceStaticMesh()
	: m_ppStaticMesh(nullptr)
{
}

CResourceStaticMesh::~CResourceStaticMesh()
{
	if (m_ppStaticMesh != nullptr) {

		for (int i = static_cast<int>(enStaticMesh::Max) - 1; i >= 0; i--) {
			if (m_ppStaticMesh[i] != nullptr) {
				Release(static_cast<enStaticMesh>(i));
			}
		}
		delete[] m_ppStaticMesh;
		m_ppStaticMesh = nullptr;
	}
}

//=======================================.
//		�����ݒ菈���֐�.
//=======================================.
HRESULT CResourceStaticMesh::Init()
{
	//���b�V���̍ő�l.
	const int MaxStaticMesh = static_cast<int>(enStaticMesh::Max);

	//CDX9Mesh�̃N���X�̔z�񓮓I�m��.
	m_ppStaticMesh = new CDX9Mesh*[MaxStaticMesh];

	//������.
	for (int Mesh_No = 0; Mesh_No < MaxStaticMesh; Mesh_No++) {
		m_ppStaticMesh[Mesh_No] = nullptr;
	}
	
	return S_OK;
}

//=======================================.
//		�ǂݍ��ݏ����֐�.
//=======================================.
HRESULT CResourceStaticMesh::Load()
{
	//�t�@�C���p�X.
	const char fileName[][256]=
	{
		"Data\\Model\\Ground\\stage.X",					//�n��.
		"Data\\Model\\Enemy\\Cow_Ghost\\ghost.X",		//��������.
		"Data\\Model\\HitSphere\\Sphere.x",				//�����蔻��p����.
		"Data\\Model\\Gate\\gate.X",					//����.
		"Data\\Model\\BackGround\\background.X",		//�w�i.
		"Data\\Model\\Grass\\grass.X",					//��.
		"Data\\Model\\Ground\\stage2.X",				//����̒n��.
		"Data\\Model\\Ground\\Ground2\\stage3.X",		//�n��2��.
	};

	//�ǂݍ��ݏ���.
	for (int Mesh_No = 0; Mesh_No < static_cast<int>(enStaticMesh::Max); Mesh_No++) {
		Create(static_cast<enStaticMesh>(Mesh_No), fileName[Mesh_No]);
	}
	//�X�t�B�A�̍쐬.
	if (FAILED(InitSphere())) {
		return E_FAIL;
	}

	return S_OK;
}

//=======================================.
//		��������Ăяo���֐�.
//=======================================.
HRESULT CResourceStaticMesh::ReleaseCalling()
{
	for (int Mesh_No = static_cast<int>(enStaticMesh::Max)-1; Mesh_No <= 0; Mesh_No--) {
		Release(static_cast<enStaticMesh>(Mesh_No));
	}
	return S_OK;
}

//=======================================.
//		���l�������֐�.
//=======================================.
CDX9Mesh* CResourceStaticMesh::GetStaticMesh(CResourceStaticMesh::enStaticMesh StaticMesh)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_MeshRnge(StaticMesh))) {
		return nullptr;
	}
	//���b�V���ԍ��ݒ�.
	const int Mesh_No = static_cast<int>(StaticMesh);

	//���f�����Ȃ���ΏI��.
	if (m_ppStaticMesh[Mesh_No] == nullptr) {
		return nullptr;
	}

	return m_ppStaticMesh[Mesh_No];
}

//========================================.
//		�쐬�����֐�.
//========================================.
HRESULT CResourceStaticMesh::Create(CResourceStaticMesh::enStaticMesh StaticMesh, const char* pfileName)
{
	const int MESH_NO = static_cast<int>(StaticMesh);

	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_MeshRnge(StaticMesh))) {
		return E_FAIL;
	}

	//���f�������ɂ���ꍇ�͏I��.
	if (m_ppStaticMesh[MESH_NO] != nullptr) {
		return E_FAIL;
	}

	//���f���̓ǂݍ���.
	m_ppStaticMesh[MESH_NO] = new CDX9Mesh();
	if (FAILED(m_ppStaticMesh[MESH_NO]->Init(m_hWnd, m_pDevice9, m_pDevice11, m_pContext11, pfileName))) {
		return E_FAIL;
	}


	return S_OK;
}

//========================================.
//		��������֐�.
//========================================.
HRESULT CResourceStaticMesh::Release(CResourceStaticMesh::enStaticMesh StaticMesh)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_MeshRnge(StaticMesh))) {
		return E_FAIL;
	}

	//���b�V���ԍ��ݒ�.
	const int Mesh_No = static_cast<int>(StaticMesh);

	//���f�����Ȃ���ΏI��.
	if (m_ppStaticMesh[Mesh_No] == nullptr) {
		return S_OK;
	}

	//���.
	m_ppStaticMesh[Mesh_No]->Release();
	delete m_ppStaticMesh[Mesh_No];
	m_ppStaticMesh[Mesh_No] = nullptr;

	return S_OK;
}

//========================================.
//		���b�V���͈̔͂𒲂ׂ�֐�.
//========================================.
HRESULT CResourceStaticMesh::Check_MeshRnge(CResourceStaticMesh::enStaticMesh StaticMesh)
{
	//�͈͊O�Ȃ�I��.
	if (StaticMesh < enStaticMesh::Start || enStaticMesh::Max <= StaticMesh)
	{
		return E_FAIL;
	}
	return S_OK;
}

//========================================.
//		�X�t�B�A�쐬�����֐�.
//========================================.
HRESULT	CResourceStaticMesh::InitSphere()
{
	//���b�V���ԍ��ݒ�.
	const int	MeshNo = static_cast<int>(CResourceStaticMesh::enStaticMesh::Hit_Sphere);

	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;			//���_�o�b�t�@.
	void*					pVertices = nullptr;	//���_.
	D3DXVECTOR3				vCenter;				//���S.
	float					fRadius;				//���a.

	//���_�o�b�t�@���擾.
	if (FAILED(
		m_ppStaticMesh[MeshNo]->GetMesh()->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}
	//���b�V���̒��_�o�b�t�@�����b�N����.
	if (FAILED(
		pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}
	//���b�V���̊O�ډ~�̒��S�Ɣ��a���v�Z����.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>(pVertices),
		m_ppStaticMesh[MeshNo]->GetMesh()->GetNumVertices(),				//���_�̐�.
		D3DXGetFVFVertexSize(m_ppStaticMesh[MeshNo]->GetMesh()->GetFVF()),	//���_�̏��.
		&vCenter,															//(out)���S���W.
		&fRadius);															//(out)���a.

	//�A�����b�N.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//���S�Ɣ��a���\���̂ɐݒ�.
	m_ppStaticMesh[MeshNo]->m_Sphere.vCenter = vCenter;
	m_ppStaticMesh[MeshNo]->m_Sphere.fRadius = fRadius;				

	return S_OK;
}