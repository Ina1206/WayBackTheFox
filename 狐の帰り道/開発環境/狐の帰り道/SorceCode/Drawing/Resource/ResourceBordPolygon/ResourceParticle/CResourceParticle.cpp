#include "CResourceParticle.h"

CResourceParticle::CResourceParticle()
	: m_ppParticle(nullptr)
{
}

CResourceParticle::~CResourceParticle()
{
	//�������.
	if (m_ppParticle != nullptr) {

		for (int i = static_cast<int>(enParticle::Max) - 1; i >= 0; i--) {
			if (m_ppParticle[i] != nullptr) {
				Release(static_cast<enParticle>(i));
			}
		}
		delete[] m_ppParticle;
		m_ppParticle = nullptr;
	}
}

//=======================================.
//		�����ݒ菈���֐�.
//=======================================.
HRESULT CResourceParticle::Init()
{
	//�p�[�e�B�N���̍ő�l.
	const int MaxStaticMesh = static_cast<int>(enParticle::Max);

	//CPartile�̃N���X�̔z�񓮓I�m��.
	m_ppParticle = new CParticle*[MaxStaticMesh];

	//������.
	for (int Mesh_No = 0; Mesh_No < MaxStaticMesh; Mesh_No++) {
		m_ppParticle[Mesh_No] = nullptr;
	}

	return S_OK;
}

//=======================================.
//		�ǂݍ��ݏ����֐�.
//=======================================.
HRESULT CResourceParticle::Load()
{
	//�t�@�C���p�X.
	const char fileName[][256] =
	{
		"Data\\Texture\\SceneUI\\maple.png",
		"Data\\Texture\\SceneUI\\maple2.png",
	};

	//�ǂݍ��ݏ���.
	for (int Mesh_No = 0; Mesh_No < static_cast<int>(enParticle::Max); Mesh_No++) {
		Create(static_cast<enParticle>(Mesh_No), fileName[Mesh_No]);
	}

	return S_OK;
}

//=======================================.
//		��������Ăяo���֐�.
//=======================================.
HRESULT CResourceParticle::ReleaseCalling()
{
	for (int Mesh_No = static_cast<int>(enParticle::Max) - 1; Mesh_No >= 0; Mesh_No--) {
		Release(static_cast<enParticle>(Mesh_No));
	}
	return S_OK;
}

//=======================================.
//		���l�������֐�.
//=======================================.
CParticle* CResourceParticle::GetParticle(CResourceParticle::enParticle Particle)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_ParticleRnge(Particle))) {
		return nullptr;
	}
	//���b�V���ԍ��ݒ�.
	const int Mesh_No = static_cast<int>(Particle);

	//�e�N�X�`�����Ȃ���ΏI��.
	if (m_ppParticle[Mesh_No] == nullptr) {
		return nullptr;
	}

	return m_ppParticle[Mesh_No];
}

//========================================.
//		�쐬�����֐�.
//========================================.
HRESULT CResourceParticle::Create(CResourceParticle::enParticle Particle, const char* pfileName)
{
	const int MESH_NO = static_cast<int>(Particle);

	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_ParticleRnge(Particle))) {
		return E_FAIL;
	}

	//�e�N�X�`�������ɂ���ꍇ�͏I��.
	if (m_ppParticle[MESH_NO] != nullptr) {
		return E_FAIL;
	}
	_ASSERT_EXPR(pfileName != nullptr, L"�G���[");

	//�e�N�X�`���̓ǂݍ���.
	m_ppParticle[MESH_NO] = new CParticle();
	if (FAILED(m_ppParticle[MESH_NO]->Init(m_pDevice11, m_pContext11, pfileName))) {
		return E_FAIL;
	}

	return S_OK;
}

//========================================.
//		��������֐�.
//========================================.
HRESULT CResourceParticle::Release(CResourceParticle::enParticle Particle)
{
	//�͈͊O�Ȃ�I��.
	if (FAILED(Check_ParticleRnge(Particle))) {
		return E_FAIL;
	}

	//�e�N�X�`���ԍ��ݒ�.
	const int Tex_No = static_cast<int>(Particle);

	//�e�N�X�`�����Ȃ���ΏI��.
	if (m_ppParticle[Tex_No] == nullptr) {
		return S_OK;
	}

	//���.
	m_ppParticle[Tex_No]->Release();
	delete m_ppParticle[Tex_No];
	m_ppParticle[Tex_No] = nullptr;

	return S_OK;
}

//========================================.
//		�p�[�e�B�N���͈̔͂𒲂ׂ�֐�.
//========================================.
HRESULT CResourceParticle::Check_ParticleRnge(CResourceParticle::enParticle Particle)
{
	//�͈͊O�Ȃ�I��.
	if (Particle < enParticle::Start || enParticle::Max <= Particle)
	{
		return E_FAIL;
	}
	return S_OK;
}