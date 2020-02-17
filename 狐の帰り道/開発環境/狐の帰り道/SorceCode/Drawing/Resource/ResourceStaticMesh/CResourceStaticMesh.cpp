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
//		初期設定処理関数.
//=======================================.
HRESULT CResourceStaticMesh::Init()
{
	//メッシュの最大値.
	const int MaxStaticMesh = static_cast<int>(enStaticMesh::Max);

	//CDX9Meshのクラスの配列動的確保.
	m_ppStaticMesh = new CDX9Mesh*[MaxStaticMesh];

	//初期化.
	for (int Mesh_No = 0; Mesh_No < MaxStaticMesh; Mesh_No++) {
		m_ppStaticMesh[Mesh_No] = nullptr;
	}
	
	return S_OK;
}

//=======================================.
//		読み込み処理関数.
//=======================================.
HRESULT CResourceStaticMesh::Load()
{
	//ファイルパス.
	const char fileName[][256]=
	{
		"Data\\Model\\Ground\\stage.X",					//地面.
		"Data\\Model\\Enemy\\Cow_Ghost\\ghost.X",		//牛お化け.
		"Data\\Model\\HitSphere\\Sphere.x",				//当たり判定用球体.
		"Data\\Model\\Gate\\gate.X",					//鳥居.
		"Data\\Model\\BackGround\\background.X",		//背景.
		"Data\\Model\\Grass\\grass.X",					//草.
		"Data\\Model\\Ground\\stage2.X",				//周りの地面.
		"Data\\Model\\Ground\\Ground2\\stage3.X",		//地面2つ目.
	};

	//読み込み処理.
	for (int Mesh_No = 0; Mesh_No < static_cast<int>(enStaticMesh::Max); Mesh_No++) {
		Create(static_cast<enStaticMesh>(Mesh_No), fileName[Mesh_No]);
	}
	//スフィアの作成.
	if (FAILED(InitSphere())) {
		return E_FAIL;
	}

	return S_OK;
}

//=======================================.
//		解放処理呼び出し関数.
//=======================================.
HRESULT CResourceStaticMesh::ReleaseCalling()
{
	for (int Mesh_No = static_cast<int>(enStaticMesh::Max)-1; Mesh_No <= 0; Mesh_No--) {
		Release(static_cast<enStaticMesh>(Mesh_No));
	}
	return S_OK;
}

//=======================================.
//		情報獲得処理関数.
//=======================================.
CDX9Mesh* CResourceStaticMesh::GetStaticMesh(CResourceStaticMesh::enStaticMesh StaticMesh)
{
	//範囲外なら終了.
	if (FAILED(Check_MeshRnge(StaticMesh))) {
		return nullptr;
	}
	//メッシュ番号設定.
	const int Mesh_No = static_cast<int>(StaticMesh);

	//モデルがなければ終了.
	if (m_ppStaticMesh[Mesh_No] == nullptr) {
		return nullptr;
	}

	return m_ppStaticMesh[Mesh_No];
}

//========================================.
//		作成処理関数.
//========================================.
HRESULT CResourceStaticMesh::Create(CResourceStaticMesh::enStaticMesh StaticMesh, const char* pfileName)
{
	const int MESH_NO = static_cast<int>(StaticMesh);

	//範囲外なら終了.
	if (FAILED(Check_MeshRnge(StaticMesh))) {
		return E_FAIL;
	}

	//モデルが既にある場合は終了.
	if (m_ppStaticMesh[MESH_NO] != nullptr) {
		return E_FAIL;
	}

	//モデルの読み込み.
	m_ppStaticMesh[MESH_NO] = new CDX9Mesh();
	if (FAILED(m_ppStaticMesh[MESH_NO]->Init(m_hWnd, m_pDevice9, m_pDevice11, m_pContext11, pfileName))) {
		return E_FAIL;
	}


	return S_OK;
}

//========================================.
//		解放処理関数.
//========================================.
HRESULT CResourceStaticMesh::Release(CResourceStaticMesh::enStaticMesh StaticMesh)
{
	//範囲外なら終了.
	if (FAILED(Check_MeshRnge(StaticMesh))) {
		return E_FAIL;
	}

	//メッシュ番号設定.
	const int Mesh_No = static_cast<int>(StaticMesh);

	//モデルがなければ終了.
	if (m_ppStaticMesh[Mesh_No] == nullptr) {
		return S_OK;
	}

	//解放.
	m_ppStaticMesh[Mesh_No]->Release();
	delete m_ppStaticMesh[Mesh_No];
	m_ppStaticMesh[Mesh_No] = nullptr;

	return S_OK;
}

//========================================.
//		メッシュの範囲を調べる関数.
//========================================.
HRESULT CResourceStaticMesh::Check_MeshRnge(CResourceStaticMesh::enStaticMesh StaticMesh)
{
	//範囲外なら終了.
	if (StaticMesh < enStaticMesh::Start || enStaticMesh::Max <= StaticMesh)
	{
		return E_FAIL;
	}
	return S_OK;
}

//========================================.
//		スフィア作成処理関数.
//========================================.
HRESULT	CResourceStaticMesh::InitSphere()
{
	//メッシュ番号設定.
	const int	MeshNo = static_cast<int>(CResourceStaticMesh::enStaticMesh::Hit_Sphere);

	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;			//頂点バッファ.
	void*					pVertices = nullptr;	//頂点.
	D3DXVECTOR3				vCenter;				//中心.
	float					fRadius;				//半径.

	//頂点バッファを取得.
	if (FAILED(
		m_ppStaticMesh[MeshNo]->GetMesh()->GetVertexBuffer(&pVB)))
	{
		return E_FAIL;
	}
	//メッシュの頂点バッファをロックする.
	if (FAILED(
		pVB->Lock(0, 0, &pVertices, 0)))
	{
		SAFE_RELEASE(pVB);
		return E_FAIL;
	}
	//メッシュの外接円の中心と半径を計算する.
	D3DXComputeBoundingSphere(
		static_cast<D3DXVECTOR3*>(pVertices),
		m_ppStaticMesh[MeshNo]->GetMesh()->GetNumVertices(),				//頂点の数.
		D3DXGetFVFVertexSize(m_ppStaticMesh[MeshNo]->GetMesh()->GetFVF()),	//頂点の情報.
		&vCenter,															//(out)中心座標.
		&fRadius);															//(out)半径.

	//アンロック.
	pVB->Unlock();
	SAFE_RELEASE(pVB);

	//中心と半径を構造体に設定.
	m_ppStaticMesh[MeshNo]->m_Sphere.vCenter = vCenter;
	m_ppStaticMesh[MeshNo]->m_Sphere.fRadius = fRadius;				

	return S_OK;
}