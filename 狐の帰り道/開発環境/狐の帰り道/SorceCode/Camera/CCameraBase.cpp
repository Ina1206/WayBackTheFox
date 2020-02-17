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
//		ビュー変換処理関数.
//=====================================.
void CCameraBase::Change_mView()
{
	//ビュー(カメラ)変換.
	D3DXVECTOR3 vUpVec(UP_VECTOR);	//上方(ベクトル).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)ビュー計算結果.
		&m_Camera.vPos, &m_Camera.vLook, &vUpVec);

}