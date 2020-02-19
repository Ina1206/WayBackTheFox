#ifndef CLONGPUSH_EFFECT_H
#define CLONGPUSH_EFFECT_H

#include "..\..\CEffectBase.h"

/*****************************************
*		���������̃G�t�F�N�g�N���X.
***/
class CLongPushEffect
	: public CEffectBase
{
public:
	CLongPushEffect();
	~CLongPushEffect();

	//====================�萔========================//.
	const int			SPARKLE_MAX			= 40;							//�L���L���̍ő吔.
	const int			USE_SPARKLE_MAX		= 3;							//�g�p����L���L���̎�ނ̍ő吔.
	const int			SPARKLE_HORIZON_MAX = 2;							//���̉���̍ő吔.
	const int			SPARKLE_POP_TIME	= 7;							//�L���L���̏o������.
	const D3DXVECTOR2	INTERVAL			= D3DXVECTOR2(0.2f, 0.4f);		//���E�̊Ԋu(x: ����	y:�E��).
	const D3DXVECTOR2	MOST				= D3DXVECTOR2(-0.5f, 0.9f);		//���E�̒[(x:��, y�E).
	const float			STANDERD_HEIGHT		= 0.01f;						//��̍���.
	const float			FLOW_SPEED			= 0.05f;						//����鑬�x.
	const float			SCALE_MAX			= 1.0f;							//�傫���̍ő�l.
	const float			SCALE_MIN			= 0.0f;							//�傫���̍ŏ��l.
	const float			SCALING_SPEED		= 0.02f;						//�g�k�̑��x.

	//====================�֐�========================//.
	void Update();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.
private:
	//====================�֐�=======================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void Disp();							//�\�������֐�.
	void SettingPosition(int sparkle);		//�ʒu���W�ݒ�֐�.
	void Move();							//�ړ������֐�.
	void Scaling(int sparkle);				//�g�k�����֐�.

	//====================�ϐ�=======================//.
	int				m_PopTime_Cnt;			//�o���J�E���g.
	bool*			m_pbIndividual_Disp;	//�ʕ\���t���O.
	
};

#endif	//#ifndef CLONGPUSH_EFFECT_H.