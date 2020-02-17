#include "CCameraBase.h"

CCameraBase::CCameraBase()
	: m_Camera			()
	, m_mView			()
	, m_CameraChangeFlag(false)
	, m_vTargetPos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

CCameraBase::~CCameraBase()
{
}

//=====================================.
//		�r���[�ϊ������֐�.
//=====================================.
void CCameraBase::Change_mView()
{
	//�r���[(�J����)�ϊ�.
	D3DXVECTOR3 vUpVec(UP_VECTOR);	//���(�x�N�g��).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)�r���[�v�Z����.
		&m_Camera.vPos, &m_Camera.vLook, &vUpVec);

}