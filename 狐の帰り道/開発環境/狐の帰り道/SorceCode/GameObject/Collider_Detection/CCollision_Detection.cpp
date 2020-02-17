#include "CCollision_Detection.h"

CCollision_Detection::CCollision_Detection()
	: m_ppSphereMesh(nullptr)
	, m_pvPos		(nullptr)
	, m_pfScale		(nullptr)
{
}

CCollision_Detection::~CCollision_Detection()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		初期化処理.
//==========================================.
void CCollision_Detection::Init()
{
	//オブジェクトの最大値設定.
	const int Mesh_Max = static_cast<int>(enObject::Max);

	//要素数確保.
	m_ppSphereMesh	= new CDX9Mesh*[Mesh_Max];
	m_pvPos			= new D3DXVECTOR3[Mesh_Max];
	m_pfScale		= new float[Mesh_Max];
	//初期化.
	for (int MeshNo = 0; MeshNo < Mesh_Max; MeshNo++) {
		m_ppSphereMesh[MeshNo] = nullptr;
		m_pvPos[MeshNo] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pfScale[MeshNo] = 0.0f;
	}

	Attach();

}


//==========================================.
//		衝突処理関数
//==========================================.
bool CCollision_Detection::JugeHit(stObjectInfo* AttackInfo, stObjectInfo* TargetInfo)
{
	//この関数の引数に座標と大きさ入れて処理すると
	//２つの関数が消すことできる.
	CCollision_Detection::stObjectInfo m_stAttackInfo = *AttackInfo;
	CCollision_Detection::stObjectInfo m_stTargetInfo = *TargetInfo;

	int AttackNo = static_cast<int>(m_stAttackInfo.Object);
	int TargetNo = static_cast<int>(m_stTargetInfo.Object);

	//２つの物体の中心間(２点間)の距離を求める.
	D3DXVECTOR3 vLength = m_stAttackInfo.vPos - m_stTargetInfo.vPos;
	//長さに変換する.
	float Length = D3DXVec3Length(&vLength);

	//２点間の距離が、それぞれの物体の半径を足したものより.
	//小さいということは、スフィア同士が重なっている（衝突している）ということ.
	if (Length <= m_ppSphereMesh[AttackNo]->m_Sphere.fRadius * m_pfScale[AttackNo] + m_ppSphereMesh[TargetNo]->m_Sphere.fRadius * m_pfScale[TargetNo])
	{
		return true;	//衝突.
	}
	return false;		//衝突していない.
}

//==========================================.
//		受け取り処理関数.
//==========================================.
void CCollision_Detection::Attach()
{
	//CDX9Meshのアドレス受け取り.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	for (int MeshNo = 0; MeshNo < static_cast<int>(enObject::Max); MeshNo++) {
		m_ppSphereMesh[MeshNo] = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Hit_Sphere);
	}
	
	//確認.
	for (int meshno = 0; meshno < static_cast<int>(enObject::Max); meshno++) {
		_ASSERT_EXPR(m_ppSphereMesh[meshno] != nullptr, L"m_ppSphereMesh == nullptr");
	}
}

//==========================================.
//		解放処理関数.
//==========================================.
void CCollision_Detection::Release()
{
	//メッシュの解放.
	//for (int MeshNo = static_cast<int>(enObject::Max) - 1; MeshNo >= 0; MeshNo--) {
	//	m_ppSphereMesh[MeshNo] = nullptr;
	//}

	//大きさ配列の解放.
	if (m_pfScale != nullptr) {
		delete[] m_pfScale;
		m_pfScale = nullptr;
	}

	//座標配列の解放.
	if (m_pvPos != nullptr) {
		delete[] m_pvPos;
		m_pvPos = nullptr;
	}

	//メッシュ配列解放.
	if (m_ppSphereMesh != nullptr) {
		delete[] m_ppSphereMesh;
		m_ppSphereMesh = nullptr;
	}
}