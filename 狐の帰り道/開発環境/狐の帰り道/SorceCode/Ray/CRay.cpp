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
//	���C�ƃ��b�V���̓����蔻��.
//==========================================.
bool CRay::Intersect( CDX9Mesh* pAttack,CDX9Mesh* pTarget,
					  float* pfDistance, D3DXVECTOR3*	pvIntersect)	
{
	D3DXMATRIXA16 mRot;	//��]�s��.

	//��]�s����v�Z.
	D3DXMatrixRotationY(&mRot, m_vRot.y);

	//���x�N�g����p��.
	D3DXVECTOR3 vecAxisZ;
	//Z�x�N�g�����̂��̂����݂̉�]��Ԃɂ��ϊ�����.
	D3DXVec3TransformCoord(&vecAxisZ, &m_vAxis, &mRot);

	//���C�̈ʒu�p.
	D3DXVECTOR3 vecStart, vecEnd;
	vecStart = vecEnd = m_vRayPos;

	//���L�����̍��W�ɉ�]���W����������.
	vecEnd += vecAxisZ * 1.0f;


	//�Ώۂ������Ă��镨�̂ł��A�Ώۂ̃��[���h�s���.
	//�t�s���p����ΐ��������C��������.
	D3DXMATRIX mWorld;
	D3DXMatrixTranslation(
		&mWorld,
		m_vTargetPos.x, m_vTargetPos.y, m_vTargetPos.z);

	//�t�s������߂�.
	//�ړ��Ɋւ��Ă݂̂�������Ă��Ȃ�.
	//��]�Ƃ��̓����蔻��̎��͂��������R�[�h�𑫂��Ȃ��Ƃ����Ȃ�.
	D3DXMatrixInverse(&mWorld, nullptr, &mWorld);
	D3DXVec3TransformCoord(&vecStart, &vecStart, &mWorld);
	D3DXVec3TransformCoord(&vecEnd, &vecEnd, &mWorld);

	//����.
	D3DXVECTOR3 vecDistance;
	vecDistance = vecEnd - vecStart;	//���������߂�.

	BOOL bHit = FALSE;	//�����t���O.

	DWORD dwIndex = 0;	//�C���f�b�N�X�ԍ�.
	D3DXVECTOR3 vVertex[3];	//���_���W.
	FLOAT U = 0.0F, V = 0.0F;	//(out)�d�S�q�b�g���W.

	//���C�ƃ��b�V���̌����𒲂ׂ�.
	D3DXIntersect(
		pTarget->m_pMeshForRay,	//�Ώۃ��b�V��.
		&vecStart,				//�J�n�ʒu.
		&vecDistance,			//���C�̋���.
		&bHit,					//(out)���茋��.
		&dwIndex,				//(out)bHit��TRUE����.
								//���C�̎n�_�ɍł��߂��̖ʂ̃C���f�b�N�X�l�ւ̃|�C���^.
		&U, &V,					//(out)�d�S�q�b�g���W.
		pfDistance,				//(out)�^�[�Q�b�g�Ƃ̋���.
		nullptr, nullptr);
	if (bHit == TRUE) {
		//���������Ƃ�.
		FindVerticesOnPoly(
			pTarget->m_pMeshForRay, dwIndex, vVertex);
		//�d�S���W�����_���Z�o.
		//���[�J����_�́Av0 + U �~ (v1-v0) + V �~ (v2-v0) �ŋ��܂�.
		*pvIntersect =
			vVertex[0]
			+ U * (vVertex[1] - vVertex[0])
			+ V * (vVertex[2] - vVertex[0]);

		return true;
	}
	return false;

}

//==========================================.
//	�����ʒu�̃|���S���̒��_��������.
//==========================================.
HRESULT CRay::FindVerticesOnPoly(
	LPD3DXMESH pMeshForRay, DWORD dwPolyIndex,
	D3DXVECTOR3* pVecVertices)	//(out)���_���W�i���[�J�����W�j.
{
	//���_���Ƃ̃o�C�g�����擾.
	//lock�cDirectX9����11�Ɉړ�����Ƃ��Ɏg��.
	DWORD dwStride = pMeshForRay->GetNumBytesPerVertex();
	//���_�����擾.
	DWORD dwVertexAmt = pMeshForRay->GetNumVertices();
	//�ʐ����擾.
	DWORD dwPolyAmt = pMeshForRay->GetNumFaces();

	WORD* pwPoly = nullptr;

	//�C���f�b�N�X�o�b�t�@�����b�N�i�ǂݍ��݃��[�h�j.
	pMeshForRay->LockIndexBuffer(
		D3DLOCK_READONLY, (VOID**)&pwPoly);
	BYTE* pbVertices = nullptr;				//���_(�o�C�g�^).
	FLOAT* pfVertices = nullptr;			//���_(FLOAT�^).
	LPDIRECT3DVERTEXBUFFER9 VB = nullptr;	//���_�o�b�t�@.
	pMeshForRay->GetVertexBuffer(&VB);		//���_���̎擾.

	//���_�o�b�t�@�̃��b�N.
	if (SUCCEEDED(
		VB->Lock(0, 0, (VOID**)&pbVertices, 0)))
	{
		//for���łł��Ȃ��́H.
		//�|���S���̒��_��1�ڂ��擾.
		pfVertices
			= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3]];
		pVecVertices[0].x = pfVertices[0];
		pVecVertices[0].y = pfVertices[1];
		pVecVertices[0].z = pfVertices[2];

		//�|���S���̒��_��2�ڂ��擾.
		pfVertices
			= (FLOAT*)&pbVertices[dwStride*pwPoly[dwPolyIndex * 3 + 1]];
		pVecVertices[1].x = pfVertices[0];
		pVecVertices[1].y = pfVertices[1];
		pVecVertices[1].z = pfVertices[2];

		//�|���S���̒��_��3�ڂ��擾.
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
