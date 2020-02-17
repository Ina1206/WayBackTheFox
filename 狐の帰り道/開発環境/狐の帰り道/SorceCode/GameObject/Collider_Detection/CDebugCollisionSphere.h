#ifndef CDEBUG_COLLISION_SPHERE_H
#define CDEBUG_COLLISION_SPHERE_H

#include "..\..\Drawing\Resource\CResourceManager.h"

/**************************************************
*	�f�o�b�O�p�̓����蔻�苅�̃N���X.
**/
class CDebugCollisionSphere
{
public:
	CDebugCollisionSphere();
	~CDebugCollisionSphere();

	//=====================�֐�=========================//.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos);		//�`�揈���֐�.

	//====���u�������֐�====//.
	void SetPos(D3DXVECTOR3 vPos) { m_vPos = vPos; }
	void SetScale(float fScale) { m_fScale = fScale; }
private:
	//=====================�֐�=========================//.
	void Attach();				//�擾�֐�.
	void Release();				//��������֐�.


	//=====================�ϐ�==========================//.
	CDX9Mesh*		m_pSphere;	//���̂̃��b�V��.

	D3DXVECTOR3		m_vPos;		//���W.
	float			m_fScale;	//�傫��.
};

#endif	//#ifndef CDEBUG_COLLISION_SPHERE_H.