#ifndef CFLY_EFFECT_H
#define CFLY_EFFECT_H

#include "..\CEffectBase.h"

/**********************************************
*		��ԃG�t�F�N�g�N���X.
*****/
class CFlyEffect
	: public CEffectBase
{
public:
	CFlyEffect();
	~CFlyEffect();

	//==================�萔=======================//.
	const float MIN_SCALE		= 0.1f;		//�傫���̍ŏ��l.
	const float	SCALING_SPEED	= 0.12f;	//�傫���Ȃ鑬�x.
	const float	MIN_ALPHA		= 0.0f;		//���ߒl�̍ŏ��l.
	const float ALPHA_SPEED		= 0.03f;	//���߂��鑬�x.
	const int	LEFT_DIRECTION	= -1;		//������.
	const float	RATATION_SPEED	= 0.025f;	//��]�p�x.
	const float	RATATION_MAX	= 4.0f;		//�ő��]�p�x.
	const int	DISP_TIME		= 2;		//�o�����鎞��.

protected:
	//==================�֐�=======================//.
	void SmokeDisp();						//���̕\�������֐�.
	void SetPosition(int smoke);			//�ʒu�ݒ菈���֐�.
	void SmokeMove(int smoke);				//���̓��������֐�.
	void Ratation(int smoke,bool CameraRot);//���̉�]�����֐�.

	//==================�ϐ�=======================//.
	float*	m_pfAlpha;				//���ߒl.
	int		m_SmokeMax;				//���̍ő吔.
	float	m_fStartPos_x;			//���[�̈ʒu.
	int		m_Row_Max;				//���̗�̍ő吔.
	float	m_fInterval_Width;		//���̊Ԋu.
	float	m_fFoot_Differencial;	//���S���瑫���̍�.
	float	m_fMax_Scale;			//�傫���̍ő�.
	int		m_DispCnt;				//�o���J�E���g.
	bool*	m_pbSmokeDispFlag;		//�����o��t���O.
	int		m_FinishCnt;			//�I���J�E���g.

private:
};

#endif	//#ifndef CFLY_EFFECT_H.