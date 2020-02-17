#ifndef CBOSS_FLY_EFFECT_H
#define CBOSS_FLY_EFFECT_H

#include "..\CFlyEffect.h"

/****************************************
*		�{�X����Ԏ��̃G�t�F�N�g.
****/
class CBossFlyEffect
	: public CFlyEffect
{
public:
	CBossFlyEffect();
	~CBossFlyEffect();

	//================�萔==================//.
	const int	SMOKE_MAX			= 40;				//���̍ő吔.
	const float	SMOKE_HALF			= SMOKE_MAX / 2.0f;	//���̔���.
	const float SMOKE_QUATER		= SMOKE_HALF / 2.0f;//����4���̂P.
	const float	START_POSITION_X	= -1.8f;			//���[�̈ʒu.
	const float	FOOT_DIFFERENCIAL	= 1.0f;				//���S���瑫���܂ł̍���.
	const float	INTERVAL_WIDTH		= 0.2f;				//���ǂ����̕��̊Ԋu.
	const float INTERVAL_HEIGHT		= 0.5f;				//�����m�̍����̊Ԋu.
	const float POS_UP_SPEED		= 0.00055f;			//��ɏ㏸���鑬�x.
	const float SPEED_UP			= 0.00005f;			//���x���オ�鑬�x.
	const float	SCALE_SIZE_MIN		= 0.1f;				//�傫���̍ŏ��l.
	const float	SCALE_UP_SPEED		= 0.01f;			//�傫���������鑬�x.
	const float STANDERD_TRAN_SPEED = 0.005f;			//��̓��ߑ��x.
	const float TRANS_EXTRA_SPEED	= 0.0005f;			//���ꂼ��̉��ɏ�悹���铧�ߑ��x.
	const float ALPHA_MAX			= 1.0f;				//���ߒl�ő吔.
	const float	ROTATION_SPEED		= 0.05f;			//��]���x.
	const float ROTATION_MAX		= 3.5f;				//��]���.
	const float	RIGHT_ROTATION_NUM	= -1.0f;			//����]����.
	const float MOVE_UPPER_LIMIT	= 0.7f;				//�ړ�����l.

	//================�֐�==================//.
	void UpDate();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.
private:
	//================�֐�==================//.
	void Init();				//�����������֐�.
	void Release();				//��������֐�.
	void Disp();				//�\�����菈���֐�.
	void Move();				//�ړ������֐�.
	void Scaling();				//�X�P�[���̕ύX�����֐�.
	void TransparetProcess();	//���ߏ����֐�.
	void Rotation();			//��]�����֐�.

	//================�ϐ�===================//.
	float*	m_pfMoveSpeed;		//�ړ����x.
	bool*	m_pbIndiviDispFlag;	//�ʕ\���t���O.
	bool	m_bMoveFlag;		//�ړ��t���O.
	bool	m_bCheckFlag;		//�m�F�t���O.
};

#endif	//#ifndef CBOSS_FLY_EFFECT_H.