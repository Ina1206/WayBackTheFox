#ifndef CPUNCH_EFFECT_H
#define CPUNCH_EFFECT_H

#include "..\CSparkleEffect.h"

/**********************************************
*		�p���`�G�t�F�N�g�N���X.
*****/
class CPunchEffect
	: public CEffectBase
{
public:
	CPunchEffect();
	~CPunchEffect();

	//======================�萔==========================//.
	const int			SPARKLE_MAX			= 2;						//���̍ő吔.
	const int			USE_SPARKLE_MAX		= 2;						//�g�p���鐯�̎�ލő吔.
	const int			VERTICAL_STAR_MAX	= 2;						//�c�̗�̐��̍ő吔.
	const D3DXVECTOR2	START_POS			= D3DXVECTOR2(0.1f, 0.5f);	//���S����n�܂�ʒu�̋���.
	const float			INTERVAL_WIDTH		= 0.35f;					//�����m�̉��̊Ԋu.
	const float			INTERVAL_HEIGHT		= 0.35f;					//�����m�̏c�̊Ԋu.
	const int			DISP_STAR			= 2;						//�\�����鐯.	
	const float			SCALE_MAX			= 0.7f;						//�傫���̍ő�l.
	const float			SCALING_SPEED		= 0.05f;					//�g�k�̑��x.
	const float			CENTER_ADJUST_X		= 0.1f;						//���Sx���̒���.

	//======================�֐�==========================//.
	void Update();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.
private:
	void Init();					//�����������֐�.
	void Release();					//��������֐�.
	void InitPos(int sparkle);		//�����ʒu�ݒ�.

	//=======================�ϐ�==========================//.
	int		m_StartNum;				//�n�߂�ԍ�.
	bool*	m_pbDispFlag;			//�\���t���O.
	int		m_EndStarNum;			//�I���̔ԍ�.

};

#endif	//#ifndef CPUNCH_EFFECT_H.