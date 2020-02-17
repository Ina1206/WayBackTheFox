#ifndef CSTEP_EFFECT_H
#define CSTEP_EFFECT_H

#include "..\CSparkleEffect.h"

/**************************************
*	�G�𓥂ނƂ��̃G�t�F�N�g�N���X.
******/
class CStepEffect
	: public CSparkleEffect
{
public:
	CStepEffect();
	~CStepEffect();	

	//=====================�萔========================//.
	const int			SPARKLE_MAX				= 6;						//�L���L���̍ő吔.
	const D3DXVECTOR2	START_POSITION			= D3DXVECTOR2(0.3f, 0.35f);	//���S����̊J�n�ʒu.
	const int			HORIZON_SPARKLE			= 2;						//���̃L���L���̐�.
	const int			USE_SPARKLE_MAX			= 3;						//�g����L���L���̎�ލő吔.
	const D3DXVECTOR2	ARRANGEMENT_INTERVAL	= D3DXVECTOR2(0.25f, 0.15f);//�z�u�Ԋu.
	const float			SCALE_MAX				= 0.5f;						//�傫���̍ő吔.
	const D3DXVECTOR2	INTERVAL				= D3DXVECTOR2(0.2f, 0.3f);	//���E�̊Ԋu(x:���̊Ԋu,	y:�E�̊Ԋu).
	const D3DXVECTOR2	MOST					= D3DXVECTOR2(-0.3f, 0.5f);	//���E�̗��[(x:���̒[,	y:�E�̒[).

	//=====================�֐�========================//.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.
private:

	//=====================�֐�========================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.

};

#endif	//#ifndef CSTEP_EFFECT_H.