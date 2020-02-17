#ifndef CENEMY_FLY_EFFECT_H
#define CENEMY_FLY_EFFECT_H

#include "..\CFlyEffect.h"

/*************************************
*		�G����Ԏ��̃G�t�F�N�g.
*******/
class CEnemyFlyEffect
	: public CFlyEffect
{
public:
	CEnemyFlyEffect();
	~CEnemyFlyEffect();

	//====================�萔======================//.
	const int	SMOKE_MAX			= 30;		//���̍ő吔.
	const int	ROW_MAX				= 2;		//���̉��̗�̍ő吔.
	const float	START_POSITION_X	= -0.8f;	//���[�̈ʒu.
	const float	FOOT_DIFFERENCIAL	= 0.1f;		//���S���瑫���܂ł̍���.
	const float	INTERVAL_WIDTH		= 0.8f;		//���ǂ����̕��̊Ԋu.
	const float MAX_SCALE			= 1.0f;		//�傫���̍ő�l.
	const float ALPHA_MAX			= 1.0f;		//���ߒl�̍ő�l.

	//====================�֐�======================//.
	void UpDate();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.

private:
	//====================�֐�======================//.
	void Init();					//�����������֐�.
	void Release();					//��������֐�.


};


#endif	//#ifndef CENEMY_FLY_EFFECT_H.