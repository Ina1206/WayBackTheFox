#ifndef CBACK_GROUND_H
#define CBACK_GROUND_H

#include "..\Global.h"
#include "..\Drawing\Resource\CResourceManager.h"

/********************************************
*		�w�i�I�u�W�F�N�g�N���X.
*****/
class CBackGround
{
public:
	CBackGround();
	~CBackGround();
	//====================�萔=======================//.
	const D3DXVECTOR3	POSITION	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�ݒ�.
	const float			SCALE		= 0.01f;							//�傫��.
	const D3DXVECTOR3	ROTATION	= D3DXVECTOR3(0.0f, 3.2f, 0.0f);	//��]�p�x.

	//====================�֐�=======================//.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos);	//�`�揈���֐�.

private:
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

	//====================�ϐ�=========================//.
	CDX9Mesh*		m_pCDx9Mesh;	//���b�V���N���X.
};

#endif	//#ifndef CBACK_GROUND_H.