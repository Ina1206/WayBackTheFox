#ifndef CRAY_H
#define CRAY_H

//#include "RayStruct.h"
#include "..\Drawing\Resource\CResourceManager.h"
#include "CRayDraw.h"

/************************************
*		Rayクラス.
***/
class CRay
{
public:
	CRay();
	~CRay();

	//レイとメッシュの当たり判定.
	bool Intersect(	CDX9Mesh* pAttack, CDX9Mesh* pTarget, 
					float* pfDistance, D3DXVECTOR3*	pvIntersect);
	//交差位置のポリゴンの頂点を見つける.
	HRESULT FindVerticesOnPoly( LPD3DXMESH pMeshForRay, DWORD dwPolyIndex, D3DXVECTOR3* pVecVertices);

	//===情報置換処理関数===.
	void SetRayPos(D3DXVECTOR3 Pos) { m_vRayPos = Pos; }	//レイの位置を設定.
	void SetRayRot(D3DXVECTOR3 Rot) { m_vRot = Rot; }		//レイの角度設定.
	void SetTargetPos(D3DXVECTOR3 Pos) { m_vTargetPos = Pos; }

private:
	D3DXVECTOR3 m_vRayPos;		//レイの位置.
	D3DXVECTOR3 m_vRot;			//傾き.
	D3DXVECTOR3 m_vAxis;		//回転軸.
	D3DXVECTOR3 m_vTargetPos;	//相手側の座標.
};


#endif	//#ifndef CRAY_H.