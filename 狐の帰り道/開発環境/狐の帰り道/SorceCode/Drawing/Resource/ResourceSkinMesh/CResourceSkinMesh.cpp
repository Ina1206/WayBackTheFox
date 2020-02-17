#include "CResourceSkinMesh.h"

CResourceSkinMesh::CResourceSkinMesh()
	: m_ppSkincMesh(nullptr)
	//--------------------------------
	//	�ǉ�.
	, m_pChangeTexture(nullptr)
	//-----------------------------------
{
}

CResourceSkinMesh::~CResourceSkinMesh()
{
	if (m_ppSkincMesh != nullptr) {

		for (int i = static_cast<int>(enSkincMesh::Max) - 1; i >= 0; i--) {
			if (m_ppSkincMesh[i] != nullptr) {
				Release(static_cast<enSkincMesh>(i));
			}
		}
		delete[] m_ppSkincMesh;
		m_ppSkincMesh = nullptr;
	}
}

//=======================================.
//		�����ݒ菈���֐�.
//=======================================.
HRESULT CResourceSkinMesh::Init()
{
	//���b�V���̍ő�l.
	const int MaxStaticMesh = static_cast<int>(enSkincMesh::Max);

	//CDX9Mesh�̃N���X�̔z�񓮓I�m��.
	m_ppSkincMesh = new CDX9SkinMesh*[MaxStaticMesh];

	//������.
	for (int Mesh_No = 0; Mesh_No < MaxStaticMesh; Mesh_No++) {
		m_ppSkincMesh[Mesh_No] = nullptr;
	}

	return S_OK;
}

//=======================================.
//		�ǂݍ��ݏ����֐�.
//=======================================.
HRESULT CResourceSkinMesh::Load()
{
	//�t�@�C���p�X.
	const char fileName[][256] =
	{
		"Data\\ModelSkin\\Enemy\\Raccoon_Dog\\raccoon.X",		//�^�k�L.
		"Data\\ModelSkin\\Player\\fox.X",
		"Data\\ModelSkin\\Enemy\\BigRaccoon_Dog\\bigraccoon.X"	//�f�J�^�k�L.
	};

	//�ǂݍ��ݏ���.
	for (int Mesh_No = 0; Mesh_No < static_cast<int>(enSkincMesh::Max); Mesh_No++) {
		Create(static_cast<enSkincMesh>(Mesh_No), fileName[Mesh_No]);
	}
	//---------------------------------------------
	//	�ǉ�.
	ChangeTexture();
	//	�����܂�.
	//-------------------------------------------------

	return S_OK;
}

//=======================================.
//		��������Ăяo���֐�.
//=======================================.
HRESULT CResourceSkinMesh::ReleaseCalling()
{
	for (int Mesh_No = static_cast<int>(enSkincMesh::Max) - 1; Mesh_No >= 0; Mesh_No--) {
		Release(static_cast<enSkincMesh>(Mesh_No));
	}
	return S_OK;
}

//=======================================.
//		���l�������֐�.
//=======================================.
CDX9SkinMesh* CResourceSkinMesh::GetSkinMesh(CResourceSkinMesh::enSkincMesh StaticMesh)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SkinMeshRnge(StaticMesh))) {
		return nullptr;
	}
	//���b�V���ԍ��ݒ�.
	const int Mesh_No = static_cast<int>(StaticMesh);

	//���f�����Ȃ���ΏI��.
	if (m_ppSkincMesh[Mesh_No] == nullptr) {
		return nullptr;
	}

	return m_ppSkincMesh[Mesh_No];
}

//========================================.
//		�쐬�����֐�.
//========================================.
HRESULT CResourceSkinMesh::Create(CResourceSkinMesh::enSkincMesh StaticMesh, const char* pfileName)
{
	const int MESH_NO = static_cast<int>(StaticMesh);

	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SkinMeshRnge(StaticMesh))) {
		return E_FAIL;
	}

	//���f�������ɂ���ꍇ�͏I��.
	if (m_ppSkincMesh[MESH_NO] != nullptr) {
		return E_FAIL;
	}

	//�K�v�ȏ���n���ď�����.
	//CD3DXSKINMESH_INIT si;
	//si.hWnd				= m_hWnd;
	//si.pDevice			= m_pDevice11;
	//si.pDeviceContext	= m_pContext11;

	//���f���̓ǂݍ���.
	m_ppSkincMesh[MESH_NO] = new CDX9SkinMesh();
	
	if (FAILED(m_ppSkincMesh[MESH_NO]->Init(m_hWnd, m_pDevice9, m_pDevice11, m_pContext11, pfileName))) {
		return E_FAIL;
	}
	//m_ppSkincMesh[MESH_NO]->CreateFromX(pfileName);

	return S_OK;
}

//========================================.
//		��������֐�.
//========================================.
HRESULT CResourceSkinMesh::Release(CResourceSkinMesh::enSkincMesh StaticMesh)
{
	SAFE_DELETE(m_pChangeTexture);

	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_SkinMeshRnge(StaticMesh))) {
		return E_FAIL;
	}

	//���b�V���ԍ��ݒ�.
	const int Mesh_No = static_cast<int>(StaticMesh);

	//���f�����Ȃ���ΏI��.
	if (m_ppSkincMesh[Mesh_No] == nullptr) {
		return S_OK;
	}

	//���.
	m_ppSkincMesh[Mesh_No]->Release();
	delete m_ppSkincMesh[Mesh_No];
	m_ppSkincMesh[Mesh_No] = nullptr;

	return S_OK;
}

//========================================.
//		�X�L�����b�V���͈̔͂𒲂ׂ�֐�.
//========================================.
HRESULT CResourceSkinMesh::Check_SkinMeshRnge(CResourceSkinMesh::enSkincMesh StaticMesh)
{
	//�͈͊O�Ȃ�I��.
	if (StaticMesh < enSkincMesh::Start || enSkincMesh::Max <= StaticMesh)
	{
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------
//	�ǉ�.
//========================================.
//		�e�N�X�`���؂�ւ�.
//========================================.
HRESULT CResourceSkinMesh::ChangeTexture()
{
	m_pChangeTexture = new CDX9SkinMesh::CHANGE_TEXTURE();
	strcpy_s(m_pChangeTexture->szTextureName, "Data\\ModelSkin\\Player\\fox_UV2.png");
	strcpy_s(m_pChangeTexture->szTargetTextureName, "Fox_UV.png");

	//�e�N�X�`���쐬.
	if (m_pChangeTexture->szTargetTextureName != 0 &&
		FAILED(
			D3DX11CreateShaderResourceViewFromFileA(
				m_pDevice11, m_pChangeTexture->szTextureName,
				nullptr, nullptr, &m_pChangeTexture->pTexture, nullptr)))
	{
		MessageBox(NULL, "�e�N�X�`���ǂݍ��ݎ��s",
			"Error", MB_OK);
		return E_FAIL;
	}

	int player = static_cast<int>(enSkincMesh::Player);
	m_ppSkincMesh[player]->SetChangeTexture(m_pChangeTexture);

	return S_OK;
}
//	�����܂�.
//--------------------------------------------------
