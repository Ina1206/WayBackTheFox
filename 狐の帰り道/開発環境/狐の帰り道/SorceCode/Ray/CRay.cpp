#include "CRay.h"

CRay::CRay()
	: m_vRayPos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vRot		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vAxis		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vTargetPos	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

CRay::~CRay()
{
}

//==========================================.
//	レイとメッシュの当たり判定.
//==========================================.
bool CRay::Intersect( CDX9Mesh* pAttack,CDX9Mesh* pTarget,
					  float* pfDistance, D3DXVECTOR3*	pvIntersect)	
{
	D3DXMATRIXA16 mRot;	//回転行列.

	//回転行列を計算.
	D3DXMatrixRotationY(&mRot, m_vRot.y);

	//軸ベクトルを用意.
	D3DXVECTOR3 vecAxisZ;
	//Zベクトルそのものを現在の回転状態により変換する.
	D3DXVec3TransformCoord(&vecAxisZ, &m_vAxis, &mRot);

	//レイの位置用.
	D3DXVECTOR3 vecStart, vecEnd;
	vecStart = vecEnd = m_vRayPos;

	//自キャラの座標に回転座標を合成する.
	vecEnd += vecAxisZ * 1.0f;


	//対象が動いている物体でも、対象のワールド行列の.
	//逆行列を用いれば正しくレイが当たる.
	D3DXMATRIX mWorld;
	D3DXMatrixTranslation(
		&mWorld,
		m_vTargetPos.x, m_vTargetPos.y, m_vTargetPos.z);

	//逆行列を求める.
	//移動に関してのみしか入れていない.
	//回転とかの当たり判定の時はもう少しコードを足さないといけない.
	D3DXMatrixInverse(&mWorld, nullptr, &mWorld);
	D3DXVec3TransformCoord(&vecStart, &vecStart, &mWorld);
	D3DXVec3TransformCoord(&vecEnd, &vecEnd, &mWorld);

	//距離.
	D3DXVECTOR3 vecDistance;
	vecDistance = vecEnd - vecStart;	//距離を求める.

	BOOL bHit = FALSE;	//命中フラグ.

	DWORD dwIndex = 0;	//インデックス番号.
	D3DXVECTOR3 vVertex[3];	//頂点座標.
	FLOAT U = 0.0F, V = 0.0F;	//(out)重心ヒット座標.

	//レイとメッシュの交差を調べる.
	D3DXIntersect(
		pTarget->m_pMeshForRay,	//対象メッシュ.
		&vecStart,				//開始位置.
		&vecDistance,			//レイの距離.
		&bHit,					//(out)判定結果.
		&dwIndex,				//(out)bHitがTRUE時に.
								//レイの始点に最も近くの面のインデックス値へのポインタ.
		&U, &V,					//(out)重心ヒット座標.
		pfDistance,				//(out)ターゲットとの距離.
		nullptr, nullptr);
	if (bHit == TRUE) {
		//命中したとき.
		FindVerticesOnPoly(
			pTarget->m_pMeshForRay, dwIndex, vVertex);
		//重心座標から交点を算出.
		//ローカル交点は、v0 + U × (v1-v0) + V × (v2-v0) で求まる.
		*pvIntersect =
			vVertex[0]
			+ U * (vVertex[1] - vVertex[0])
			+ V * (vVertex[2] - vVertex[0]);

		return true;
	}
	return false;

}

//==========================================.
//	交差位置のポリゴンの頂点を見つける.
//==========================================.
HRESULT CRay::FindVerticesOnPoly(
	LPD3DXMESH pMeshForRay, DWORD dwPolyIndex,
	D3DXVECTOR3* pVecVertices)	//(out)頂点座標（ローカル座標）.
{
	//頂点ごとのバイト数を取得.
	//lock…DirectX9から11に移動するときに使う.
	DWORD dwStride = pMeshForRay->GetNumBytesPerVertex();
	//頂点数を取得.
	DWORD dwVertexAmt = pMeshForRay->GetNumVertices();
	//面数を取得.
	DWORD dwPolyAmt = pMeshForRay->GetNumFaces();

	WORD* pwPoly = nullptr;

	//インデックスバッファをロック（読み込みモード）.
	pMeshForRay->LockIndexBuffer(
		D3DLOCK_READONLY, (VOID**)&pwPoly);
	BYTE* pbVertices = nullptr;				//頂点(バイト型).
	FLOAT* pfVertices = nullptr;			//頂点(FLOAT型).
	LPDIRECT3DVERTEXBUFFER9 VB = nullptr;	//頂点バッファ.
	pMeshForRay->GetVertexBuffer(&VB);		//頂点情報の取得.

	//頂点バッファのロック.
	if (SUCCEEDED(
		VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		//for文でできないの？.
		//ポリゴンの頂点の1つ目を取得.
		pfVertices
			= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pVecVertices[0].x = pfVertices[0];
		pVecVertices[0].y = pfVertices[1];
		pVecVertices[0].z = pfVertices[2];

		//ポリゴンの頂点の2つ目を取得.
		pfVertices
			= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pVecVertices[1].x = pfVertices[0];
		pVecVertices[1].y = pfVertices[1];
		pVecVertices[1].z = pfVertices[2];

		//ポリゴンの頂点の3つ目を取得.
		pfVertices
			= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 2]];
		pVecVertices[2].x = pfVertices[0];
		pVecVertices[2].y = pfVertices[1];
		pVecVertices[2].z = pfVertices[2];

		pMeshForRay->UnlockIndexBuffer();
		VB->Unlock();
	}
	SAFE_RELEASE(VB);

	return S_OK;
}
