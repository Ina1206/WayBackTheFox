#include "CResourceParticle.h"

CResourceParticle::CResourceParticle()
	: m_ppParticle(nullptr)
{
}

CResourceParticle::~CResourceParticle()
{
	//解放処理.
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
//		初期設定処理関数.
//=======================================.
HRESULT CResourceParticle::Init()
{
	//パーティクルの最大値.
	const int MaxStaticMesh = static_cast<int>(enParticle::Max);

	//CPartileのクラスの配列動的確保.
	m_ppParticle = new CParticle*[MaxStaticMesh];

	//初期化.
	for (int Mesh_No = 0; Mesh_No < MaxStaticMesh; Mesh_No++) {
		m_ppParticle[Mesh_No] = nullptr;
	}

	return S_OK;
}

//=======================================.
//		読み込み処理関数.
//=======================================.
HRESULT CResourceParticle::Load()
{
	//ファイルパス.
	const char fileName[][256] =
	{
		"Data\\Texture\\SceneUI\\maple.png",
		"Data\\Texture\\SceneUI\\maple2.png",
	};

	//読み込み処理.
	for (int Mesh_No = 0; Mesh_No < static_cast<int>(enParticle::Max); Mesh_No++) {
		Create(static_cast<enParticle>(Mesh_No), fileName[Mesh_No]);
	}

	return S_OK;
}

//=======================================.
//		解放処理呼び出し関数.
//=======================================.
HRESULT CResourceParticle::ReleaseCalling()
{
	for (int Mesh_No = static_cast<int>(enParticle::Max) - 1; Mesh_No >= 0; Mesh_No--) {
		Release(static_cast<enParticle>(Mesh_No));
	}
	return S_OK;
}

//=======================================.
//		情報獲得処理関数.
//=======================================.
CParticle* CResourceParticle::GetParticle(CResourceParticle::enParticle Particle)
{
	//範囲外なら終了.
	if (FAILED(Check_ParticleRnge(Particle))) {
		return nullptr;
	}
	//メッシュ番号設定.
	const int Mesh_No = static_cast<int>(Particle);

	//テクスチャがなければ終了.
	if (m_ppParticle[Mesh_No] == nullptr) {
		return nullptr;
	}

	return m_ppParticle[Mesh_No];
}

//========================================.
//		作成処理関数.
//========================================.
HRESULT CResourceParticle::Create(CResourceParticle::enParticle Particle, const char* pfileName)
{
	const int MESH_NO = static_cast<int>(Particle);

	//範囲外なら終了.
	if (FAILED(Check_ParticleRnge(Particle))) {
		return E_FAIL;
	}

	//テクスチャが既にある場合は終了.
	if (m_ppParticle[MESH_NO] != nullptr) {
		return E_FAIL;
	}
	_ASSERT_EXPR(pfileName != nullptr, L"エラー");

	//テクスチャの読み込み.
	m_ppParticle[MESH_NO] = new CParticle();
	if (FAILED(m_ppParticle[MESH_NO]->Init(m_pDevice11, m_pContext11, pfileName))) {
		return E_FAIL;
	}

	return S_OK;
}

//========================================.
//		解放処理関数.
//========================================.
HRESULT CResourceParticle::Release(CResourceParticle::enParticle Particle)
{
	//範囲外なら終了.
	if (FAILED(Check_ParticleRnge(Particle))) {
		return E_FAIL;
	}

	//テクスチャ番号設定.
	const int Tex_No = static_cast<int>(Particle);

	//テクスチャがなければ終了.
	if (m_ppParticle[Tex_No] == nullptr) {
		return S_OK;
	}

	//解放.
	m_ppParticle[Tex_No]->Release();
	delete m_ppParticle[Tex_No];
	m_ppParticle[Tex_No] = nullptr;

	return S_OK;
}

//========================================.
//		パーティクルの範囲を調べる関数.
//========================================.
HRESULT CResourceParticle::Check_ParticleRnge(CResourceParticle::enParticle Particle)
{
	//範囲外なら終了.
	if (Particle < enParticle::Start || enParticle::Max <= Particle)
	{
		return E_FAIL;
	}
	return S_OK;
}