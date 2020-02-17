#ifndef CRAY_H
#define CRAY_H

//#include "RayStruct.h"
#include "..\Drawing\Resource\CResourceManager.h"
#include "CRayDraw.h"

/************************************
*		Ray�N���X.
***/
class CRay
{
public:
	CRay();
	~CRay();

	//���C�ƃ��b�V���̓����蔻��.
	bool Intersect(	CDX9Mesh* pAttack, CDX9Mesh* pTarget, 
					float* pfDistance, D3DXVECTOR3*	pvIntersect);
	//�����ʒu�̃|���S���̒��_��������.
	HRESULT FindVerticesOnPoly( LPD3DXMESH pMeshForRay, DWORD dwPolyIndex, D3DXVECTOR3* pVecVertices);

	//===���u�������֐�===.
	void SetRayPos(D3DXVECTOR3 Pos) { m_vRayPos = Pos; }	//���C�̈ʒu��ݒ�.
	void SetRayRot(D3DXVECTOR3 Rot) { m_vRot = Rot; }		//���C�̊p�x�ݒ�.
	void SetTargetPos(D3DXVECTOR3 Pos) { m_vTargetPos = Pos; }

private:
	D3DXVECTOR3 m_vRayPos;		//���C�̈ʒu.
	D3DXVECTOR3 m_vRot;			//�X��.
	D3DXVECTOR3 m_vAxis;		//��]��.
	D3DXVECTOR3 m_vTargetPos;	//���葤�̍��W.
};


#endif	//#ifndef CRAY_H.