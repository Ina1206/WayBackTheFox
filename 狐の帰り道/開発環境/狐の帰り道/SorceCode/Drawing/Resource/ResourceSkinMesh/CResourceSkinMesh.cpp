#include "CResourceSkinMesh.h"

CResourceSkinMesh::CResourceSkinMesh()
	: m_ppSkincMesh(nullptr)
	//--------------------------------
	//	追加.
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
//		初期設定処理関数.
//=======================================.
HRESULT CResourceSkinMesh::Init()
{
	//メッシュの最大値.
	const int MaxStaticMesh = static_cast<int>(enSkincMesh::Max);

	//CDX9Meshのクラスの配列動的確保.
	m_ppSkincMesh = new CDX9SkinMesh*[MaxStaticMesh];

	//初期化.
	for (int Mesh_No = 0; Mesh_No < MaxStaticMesh; Mesh_No++) {
		m_ppSkincMesh[Mesh_No] = nullptr;
	}

	return S_OK;
}

//=======================================.
//		読み込み処理関数.
//=======================================.
HRESULT CResourceSkinMesh::Load()
{
	//ファイルパス.
	const char fileName[][256] =
	{
		"Data\\ModelSkin\\Enemy\\Raccoon_Dog\\raccoon.X",		//タヌキ.
		"Data\\ModelSkin\\Player\\fox.X",
		"Data\\ModelSkin\\Enemy\\BigRaccoon_Dog\\bigraccoon.X"	//デカタヌキ.
	};

	//読み込み処理.
	for (int Mesh_No = 0; Mesh_No < static_cast<int>(enSkincMesh::Max); Mesh_No++) {
		Create(static_cast<enSkincMesh>(Mesh_No), fileName[Mesh_No]);
	}
	//---------------------------------------------
	//	追加.
	ChangeTexture();
	//	ここまで.
	//-------------------------------------------------

	return S_OK;
}

//=======================================.
//		解放処理呼び出し関数.
//=======================================.
HRESULT CResourceSkinMesh::ReleaseCalling()
{
	for (int Mesh_No = static_cast<int>(enSkincMesh::Max) - 1; Mesh_No >= 0; Mesh_No--) {
		Release(static_cast<enSkincMesh>(Mesh_No));
	}
	return S_OK;
}

//=======================================.
//		情報獲得処理関数.
//=======================================.
CDX9SkinMesh* CResourceSkinMesh::GetSkinMesh(CResourceSkinMesh::enSkincMesh StaticMesh)
{
	//範囲外なら終了.
	if (FAILED(Check_SkinMeshRnge(StaticMesh))) {
		return nullptr;
	}
	//メッシュ番号設定.
	const int Mesh_No = static_cast<int>(StaticMesh);

	//モデルがなければ終了.
	if (m_ppSkincMesh[Mesh_No] == nullptr) {
		return nullptr;
	}

	return m_ppSkincMesh[Mesh_No];
}

//========================================.
//		作成処理関数.
//========================================.
HRESULT CResourceSkinMesh::Create(CResourceSkinMesh::enSkincMesh StaticMesh, const char* pfileName)
{
	const int MESH_NO = static_cast<int>(StaticMesh);

	//範囲外なら終了.
	if (FAILED(Check_SkinMeshRnge(StaticMesh))) {
		return E_FAIL;
	}

	//モデルが既にある場合は終了.
	if (m_ppSkincMesh[MESH_NO] != nullptr) {
		return E_FAIL;
	}

	//必要な情報を渡して初期化.
	//CD3DXSKINMESH_INIT si;
	//si.hWnd				= m_hWnd;
	//si.pDevice			= m_pDevice11;
	//si.pDeviceContext	= m_pContext11;

	//モデルの読み込み.
	m_ppSkincMesh[MESH_NO] = new CDX9SkinMesh();
	
	if (FAILED(m_ppSkincMesh[MESH_NO]->Init(m_hWnd, m_pDevice9, m_pDevice11, m_pContext11, pfileName))) {
		return E_FAIL;
	}
	//m_ppSkincMesh[MESH_NO]->CreateFromX(pfileName);

	return S_OK;
}

//========================================.
//		解放処理関数.
//========================================.
HRESULT CResourceSkinMesh::Release(CResourceSkinMesh::enSkincMesh StaticMesh)
{
	SAFE_DELETE(m_pChangeTexture);

	//範囲外なら終了.
	if (FAILED(Check_SkinMeshRnge(StaticMesh))) {
		return E_FAIL;
	}

	//メッシュ番号設定.
	const int Mesh_No = static_cast<int>(StaticMesh);

	//モデルがなければ終了.
	if (m_ppSkincMesh[Mesh_No] == nullptr) {
		return S_OK;
	}

	//解放.
	m_ppSkincMesh[Mesh_No]->Release();
	delete m_ppSkincMesh[Mesh_No];
	m_ppSkincMesh[Mesh_No] = nullptr;

	return S_OK;
}

//========================================.
//		スキンメッシュの範囲を調べる関数.
//========================================.
HRESULT CResourceSkinMesh::Check_SkinMeshRnge(CResourceSkinMesh::enSkincMesh StaticMesh)
{
	//範囲外なら終了.
	if (StaticMesh < enSkincMesh::Start || enSkincMesh::Max <= StaticMesh)
	{
		return E_FAIL;
	}
	return S_OK;
}

//------------------------------------
//	追加.
//========================================.
//		テクスチャ切り替え.
//========================================.
HRESULT CResourceSkinMesh::ChangeTexture()
{
	m_pChangeTexture = new CDX9SkinMesh::CHANGE_TEXTURE();
	strcpy_s(m_pChangeTexture->szTextureName, "Data\\ModelSkin\\Player\\fox_UV2.png");
	strcpy_s(m_pChangeTexture->szTargetTextureName, "Fox_UV.png");

	//テクスチャ作成.
	if (m_pChangeTexture->szTargetTextureName != 0 &&
		FAILED(
			D3DX11CreateShaderResourceViewFromFileA(
				m_pDevice11, m_pChangeTexture->szTextureName,
				nullptr, nullptr, &m_pChangeTexture->pTexture, nullptr)))
	{
		MessageBox(NULL, "テクスチャ読み込み失敗",
			"Error", MB_OK);
		return E_FAIL;
	}

	int player = static_cast<int>(enSkincMesh::Player);
	m_ppSkincMesh[player]->SetChangeTexture(m_pChangeTexture);

	return S_OK;
}
//	ここまで.
//--------------------------------------------------
