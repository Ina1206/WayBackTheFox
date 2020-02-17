#ifndef CLANDING_EFFECT_H
#define CLANDING_EFFECT_H

#include "..\CEffectBase.h"

/*************************************
*		���n�G�t�F�N�g�N���X.
***************/
class CLandingEffect
	: public CEffectBase
{
public:
	CLandingEffect();
	~CLandingEffect();

	//=================�萔====================//.
	const int			SMOKE_MAX		= 2;							//���̍ő吔.
	//�傫��.
	const float			SCALE_MAX		= 1.0f;							//���̑傫���ő�l.
	const float			SCALE_MIN		= 0.2f;							//���̑傫���ŏ��l.
	const float			SCALE_SPEED		= 0.008f;						//�g�呬�x.
	//����.
	const float			ALPHA_MAX		= 1.0f;							//���ߒl�̍ő吔.
	const float			ALPHA_MIN		= 0.0f;							//���ߒl�̍ŏ���.
	const float			TRANS_SPEED		= 0.01f;						//���ߑ��x.
	//�ʒu.
	const float			START_POS		= 0.05f;						//�^�񒆂���̎n�߂�ʒu.
	const float			INTERVAL_WIDTH	= 0.08f;						//�����m�̊Ԋu�̕�.
	const D3DXVECTOR2	MOVE_SPEED		= D3DXVECTOR2(0.005f, 0.001f);	//�ړ����x.
	//�p�x.
	const float			ROTATION_MAX	= 6.5f;							//��]�l�ő吔.
	const float			ROTATION_SPEED	= 0.05f;						//��]���x.
	

	//=================�֐�====================//.
	void UpDate();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.
private:
	//=================�֐�====================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void Position_Setting(int smoke);		//�ʒu�ݒ菈���֐�.
	void Move();							//�ړ������֐�.
	void Alpha_Scaling(int smoke);			//���߂Ɗg�又���֐�.

	//=================�ϐ�====================//.
	float*		m_pfAlpha;					//���ߒl.
};

#endif	//#ifndef CLANDING_EFFECT_H.