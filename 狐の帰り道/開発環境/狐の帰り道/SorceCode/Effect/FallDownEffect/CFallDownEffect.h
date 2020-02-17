#ifndef CFALL_DOWN_EFFECT_H
#define CFALL_DOWN_EFFECT_H

#include "..\CEffectBase.h"

/**********************************
*		�|��鎞�̃G�t�F�N�g.
********/
class CFallDownEffect
	: public CEffectBase
{
public:
	CFallDownEffect();
	~CFallDownEffect();

	//======================�萔============================//.
	const int	SMOKE_MAX			= 20;		//���̍ő吔.

	const int	APPEARANCE_MAX		= 20;		//�o���^�C��.
	const int	APPEARANCE_SMOKE	= 2;		//���̉��̏o����.
	
	const float	START_POSITION		= 1.8f;		//�J�n�ʒu.

	const float SMOKE_HIGHT			= 1.0f;		//���̍���.	
	const float SMOKE_HIGHT_ADJUST	= 0.3f;		//���̍���������.
	const float SMOKE_WIDTH_ADJUST	= 0.2f;		//���̕��̔�����.

	const int	ODD_EVEN_JUDGE		= 2;		//��E�������f���l.
	const float SCALE_MAX			= 1.5f;		//���̍ő�̑傫��.
	const float SCALE_MIN			= 0.8f;		//���̍ŏ��̑傫��.
	const float SCALE_SPEED			= 0.005f;	//���̑傫���Ȃ鑬�x.
	const float ALPHA_MAX			= 1.0f;		//���̓��ߒl�̍ő吔.
	const float ALPHA_MIN			= 0.0f;		//���̓��ߒl�̍ŏ���.
	const float ALPHA_SPEED			= 0.01f;	//���̓��ߒl�̑��x.
	const float ROTATION_MAX		= 6.5f;		//���̊p�x�ő�l.
	const float ROTATION_MIN		= 0.0f;		//���̊p�x�ŏ��l.
	const float ROTATION_SPEED		= 0.01f;	//���̌X�����x.
	const int	FADE_WAIT_TIME		= 60;		//���̃t�F�[�h��҂���.

	const float MOVE_SPEED_MAX		= 0.03f;	//�ړ����x�̍ő吔.
	const float MOVE_SPEED_MIN		= 0.002f;	//�ړ����x�̍ŏ���.
	const float SPEED_DECREMENT		= 0.0015f;	//�ړ����x�̌������l.

	const float MOVE_TARGET_HEIGHT	= 0.5f;		//�ړ��̍ŏI�n�_�̍���.
	const float	CONTROL_POINT_WIDTH = 0.4f;		//����_�̕�.
	const float CONTROL_WIDTH_ADJUST= 0.09f;	//����_�̕��̔�����.
	const float CONTROL_POINT_START = -0.7f;	//����_�̍ŏ�.
	const float CONTROL_POINT_END	= -2.0f;	//����_�̍Ō�.
	const float CONTROL_ADJUST_HEI	= 0.02f;	//����_�̔�����.

	//======================�֐�============================//.
	void UpDate();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.
private:
	//======================�֐�============================//.
	void Init();															//�����������֐�.
	void Release();															//��������֐�.
	void Disp();															//�\�������֐�.
	void Move();															//�s�������֐�.
	void Scaling(int smoke);												//�傫���ύX�����֐�.
	void AlphaChange(int smoke);											//���ߒl�̕ύX�����֐�.
	void Rotation(int smoe);												//���̉�]�����֐�.

	//======================�ϐ�============================//.
	float*			m_pfAlpha;			//���ߒl.
	int*			m_pFadeStartCnt;	//�t�F�[�h�J�n�J�E���g.
	D3DXVECTOR3*	m_pvInitPos;		//�����ʒu.
	float*			m_pfMoveSpeed;		//�ړ����x.
	float			m_fSpeed;			//���x.
};


#endif	//#ifndef CFALL_DOWN_EFFECT_H.