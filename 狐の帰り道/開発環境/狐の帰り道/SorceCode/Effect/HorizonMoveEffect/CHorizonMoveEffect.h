#ifndef CHORIZON_MOVE_EFFECT_H
#define CHORIZON_MOVE_EFFECT_H

#include "..\CEffectBase.h"

/****************************************
*		���ړ����̃G�t�F�N�g�N���X.
******/
class CHorizonMoveEffect
	: public CEffectBase
{
public:
	CHorizonMoveEffect();
	~CHorizonMoveEffect();

	//================�萔===================//.
	const int	SMOKE_MAX		= 3;		//���̍ő吔.
	const float	DISP_HEIGHT		= 0.1f;		//���̕\������.
	const int	POP_TIME		= 5;		//�\������Ԋu.
	const float SCALE_MIN		= 0.2f;		//�傫���̍ŏ��l.
	const float SCALE_MAX		= 1.0f;		//�傫���̍ő�l.
	const float ALPHA_MAX		= 1.0f;		//���ߒl�̍ő�l.
	const float ALPHA_MIN		= 0.0f;		//���ߒl�̍ŏ��l.
	const float INTEFER_CHANGE	= 10.0f;	//�����ɕϊ�����p�̐��l.
	const float SCALING_SPEED	= 0.005f;	//�g�呬�x.
	const float ALPHA_SPEED		= 0.01f;	//���ߒl���x.
	const float ROTATION_SPEED	= 0.1f;		//��]���x.

	//================�֐�===================//.
	void UpDate();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.
private:
	//================�֐�===================//.
	void Init();							//�����������֐�.
	void Release();							//��������֐�.
	void Disp();							//�\�������֐�.
	void Move();							//�ړ������֐�.
	void Scaling_Transparent(int smoke);	//�g��Ɠ��ߏ����֐�.

	//================�ϐ�===================//.
	float*		m_pfAlpha;				//���ߒl.
	bool*		m_pbPerson_DispFlag;	//�l�̕\���t���O.
	D3DXVECTOR3	m_vOldCenterPos;		//�O��̒����̈ʒu.
	int			m_PopCnt;				//�o���J�E���g.
	float		m_fRotation_Distance;	//��]����.
};

#endif	//#ifndef CHORIZON_MOVE_EFFECT_H.