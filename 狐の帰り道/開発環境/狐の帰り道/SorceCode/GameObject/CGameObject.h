#ifndef CGAMEOBJECT_H
#define CGAMEOBJECT_H


//---�`��---//.
#include "..\Drawing\3D_Object\CDX9Mesh.h"
#include "..\Drawing\Resource\CResourceManager.h"

#include "..\Sound\CSEPlayManager.h"

#include "..\Effect\HitEffect\CHitEffect.h"
#include "..\Effect\SparkleEffect\GreatEffect\CGreatEffect.h"
#include "..\Effect\FlyEffect\EnemyFlyEffect\CEnemyFlyEffect.h"
#include "..\Effect\FlyEffect\BossFlyEffect\CBossFlyEffect.h"
#include "..\Effect\FallDownEffect\CFallDownEffect.h"
#include "..\Effect\SparkleEffect\PunchEffect\CPunchEffect.h"
#include "..\Effect\SparkleEffect\StepEffect\CStepEffect.h"
#include "..\Effect\\LndingEffect\CLandingEffect.h"
#include "..\Effect\HorizonMoveEffect\CHorizonMoveEffect.h"

/***************************************
*		�Q�[���I�u�W�F�N�g�N���X.
**/
class CGameObject
{
public:
	//=============�萔==================//.
	const float SCALE_SIZE = 0.02f;		//�X�P�[���T�C�Y.

	CGameObject();
	virtual ~CGameObject();
	//=============�֐�==================//.
	void Value_Set(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos);		//�l�Z�b�g�����֐�.
	virtual void Init_Process() = 0;																		//�����������֐�.
	virtual void UpDate() = 0;																				//�X�V�����֐�.
	virtual void Render() = 0;																				//�`�揈���֐�.
	virtual void Release() = 0;																				//��������֐�.
	
protected:

	D3DXVECTOR3				m_vLight;						//���C�g�̕���.
	D3DXVECTOR3				m_vCameraPos;					//�J�����ʒu.
	D3DXMATRIX				m_mView;						//�r���[�s��.
	D3DXMATRIX				m_mProj;						//�v���W�F�N�V�����s��.

	CSEPlayManager*			m_pCSEPlayManager;				//�T�E���h�Đ��Ǘ��N���X.
	CEffectBase*			m_pCEffectBase;					//�G�t�F�N�g�N���X.	(���Ƃō폜)
	CEffectBase**			m_ppCEffectBase;				//�G�t�F�N�g�N���X.

private:

};

#endif //#ifndef CGAMEOBJECT_H.