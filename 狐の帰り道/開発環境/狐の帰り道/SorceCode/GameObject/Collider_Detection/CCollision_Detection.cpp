#include "CCollision_Detection.h"

CCollision_Detection::CCollision_Detection()
	: m_ppSphereMesh(nullptr)
	, m_pvPos		(nullptr)
	, m_pfScale		(nullptr)
{
}

CCollision_Detection::~CCollision_Detection()
{
	//��������֐�.
	Release();
}

//==========================================.
//		����������.
//==========================================.
void CCollision_Detection::Init()
{
	//�I�u�W�F�N�g�̍ő�l�ݒ�.
	const int Mesh_Max = static_cast<int>(enObject::Max);

	//�v�f���m��.
	m_ppSphereMesh	= new CDX9Mesh*[Mesh_Max];
	m_pvPos			= new D3DXVECTOR3[Mesh_Max];
	m_pfScale		= new float[Mesh_Max];
	//������.
	for (int MeshNo = 0; MeshNo < Mesh_Max; MeshNo++) {
		m_ppSphereMesh[MeshNo] = nullptr;
		m_pvPos[MeshNo] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pfScale[MeshNo] = 0.0f;
	}

	Attach();

}


//==========================================.
//		�Փˏ����֐�
//==========================================.
bool CCollision_Detection::JugeHit(stObjectInfo* AttackInfo, stObjectInfo* TargetInfo)
{
	//���̊֐��̈����ɍ��W�Ƒ傫������ď��������
	//�Q�̊֐����������Ƃł���.
	CCollision_Detection::stObjectInfo m_stAttackInfo = *AttackInfo;
	CCollision_Detection::stObjectInfo m_stTargetInfo = *TargetInfo;

	int AttackNo = static_cast<int>(m_stAttackInfo.Object);
	int TargetNo = static_cast<int>(m_stTargetInfo.Object);

	//�Q�̕��̂̒��S��(�Q�_��)�̋��������߂�.
	D3DXVECTOR3 vLength = m_stAttackInfo.vPos - m_stTargetInfo.vPos;
	//�����ɕϊ�����.
	float Length = D3DXVec3Length(&vLength);

	//�Q�_�Ԃ̋������A���ꂼ��̕��̂̔��a�𑫂������̂��.
	//�������Ƃ������Ƃ́A�X�t�B�A���m���d�Ȃ��Ă���i�Փ˂��Ă���j�Ƃ�������.
	if (Length <= m_ppSphereMesh[AttackNo]->m_Sphere.fRadius * m_pfScale[AttackNo] + m_ppSphereMesh[TargetNo]->m_Sphere.fRadius * m_pfScale[TargetNo])
	{
		return true;	//�Փ�.
	}
	return false;		//�Փ˂��Ă��Ȃ�.
}

//==========================================.
//		�󂯎�菈���֐�.
//==========================================.
void CCollision_Detection::Attach()
{
	//CDX9Mesh�̃A�h���X�󂯎��.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	for (int MeshNo = 0; MeshNo < static_cast<int>(enObject::Max); MeshNo++) {
		m_ppSphereMesh[MeshNo] = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Hit_Sphere);
	}
	
	//�m�F.
	for (int meshno = 0; meshno < static_cast<int>(enObject::Max); meshno++) {
		_ASSERT_EXPR(m_ppSphereMesh[meshno] != nullptr, L"m_ppSphereMesh == nullptr");
	}
}

//==========================================.
//		��������֐�.
//==========================================.
void CCollision_Detection::Release()
{
	//���b�V���̉��.
	//for (int MeshNo = static_cast<int>(enObject::Max) - 1; MeshNo >= 0; MeshNo--) {
	//	m_ppSphereMesh[MeshNo] = nullptr;
	//}

	//�傫���z��̉��.
	if (m_pfScale != nullptr) {
		delete[] m_pfScale;
		m_pfScale = nullptr;
	}

	//���W�z��̉��.
	if (m_pvPos != nullptr) {
		delete[] m_pvPos;
		m_pvPos = nullptr;
	}

	//���b�V���z����.
	if (m_ppSphereMesh != nullptr) {
		delete[] m_ppSphereMesh;
		m_ppSphereMesh = nullptr;
	}
}