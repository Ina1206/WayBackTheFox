#ifndef CCHARA_H
#define CCHARA_H

#include "..\CGameObject.h"
#include "..\Collider_Detection/CCollision_Detection.h"
#include "..\Collider_Detection/CDebugCollisionSphere.h"


/********************************************
*		�L�����N�^�N���X.
*****/
class CChara
	: public CGameObject
{
public:
	CChara();
	virtual ~CChara();

	//===================�萔========================//.
	const int	FOOT_MAX			= 2;		//���̍ő吔.
	const float	HIT_FOOT_SCALE		= 0.2f;		//���̓����蔻��傫��.
	const float	HIT_GROUND_SCALE	= 0.8f;		//�n�ʂ̓����蔻��傫��.
	const int	LEFT_FOOT_NUM		= 0;		//�����ԍ�.
	const int	RIGHT_FOOT_NUM		= 1;		//�E���ԍ�.
	const int	HIT_GROUND_NUM		= 2;		//�n�ʂ̔ԍ�.
	const int	FOOT_SPHERE_MAX		= 3;		//�f�o�b�O�p���̂̍ő吔.
	const float GROUND_HIT_H		= -0.25f;	//�n�ʂ̓����蔻��̍���.
	const float	SHADOW_HIGHT		= 0.05f;	//�e�̍���.

	//===================�֐�========================//.
	void Init();																		//�����������֐�.
	void Destroy();																		//��������֐�.
	void FootStepSE(CDX9SkinMesh* pSkinMesh, CSoundResource::enSoundSE enSoundSE);	//������SE.
	void RenderDebug();																	//�f�o�b�O�p�`��.

protected:
	void RenderShadow();									//�e�̕`�揈���֐�.

	//===================�ϐ�========================//.
	CCollision_Detection**	m_ppCCollision_Detection;		//�����蔻��̃N���X.
	CDebugCollisionSphere**	m_ppCDebug_Collision_Sphere;	//�����蔻��f�o�b�O�p����.
	D3DXVECTOR3*			m_pvFootPos;					//�����̍��W.
	bool*					m_pbGroundHit;					//�n�ʂɑ����������̃t���O.
	D3DXVECTOR3				m_vFootDownPos;					//�����̍��W.
	D3DXVECTOR3				m_vShadowPos;		//�e�̍��W.

private:
	CSprite*			m_pCSprite;			//�X�v���C�g�N���X.

};

#endif	//#ifndef CCHARA_H.