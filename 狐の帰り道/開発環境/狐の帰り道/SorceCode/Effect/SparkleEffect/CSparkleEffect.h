#ifndef CSPARKLE_EFFECT_H
#define CSPARKLE_EFFECT_H

#include "..\CEffectBase.h"

/***********************************************
*		�L���L���G�t�F�N�g�֘A�N���X.
***/
class CSparkleEffect
	: public CEffectBase
{
public:
	CSparkleEffect();
	virtual ~CSparkleEffect();

	//==================�萔=====================//.
	const float SCALE_MIN				= 0.2f;	//�X�P�[���ŏ��l.
	const float SCALE_MAX				= 1.0f;	//�X�P�[���ő�l.
	const float SCALING_SPEED			= 0.08f;//�g�k���鑬�x.
	const int	STANDERD_SPARKLE_NUM	= 0;	//��ƂȂ�L���L���̔ԍ�.
	const int	SCALING_MAX				= 2;	//�g�k�ő�.
	const int	STAR_HORIZON_MAX		= 3;	//���ɕ��Ԑ��̍ő吔.

	//==================�֐�======================//.
	void Update();								//�X�V�����֐�.

protected:
	//=================�񋓑�=====================//.
	enum class enScalingType {
		Large = 0,	//�傫������.
		Small,		//����������.

		Nothing,
	};
	//==================�֐�=====================//.

	//==================�ϐ�=====================//.
	int				m_Sparkle_max;			//�L���L���̍ő吔.
	enScalingType*	m_penScalingType;		//�g�k�����̃^�C�v.
	int				m_CheckCnt;				//�J�E���g.
	float			m_fCenterDifferencial;	//��������̏�̍���.
	int				m_RowMax;				//����̍ő吔.
	float			m_fHeight_Width;		//�����̕�.
	float			m_fLeftInterval;		//�����̊Ԋu.
	float			m_fRightInterval;		//�E���̊Ԋu.
	float			m_fLeftMost;			//���[.
	float			m_fRightMost;			//�E�[.
	float			m_fScaleMax;			//�傫��.

private:
	//==================�֐�=====================//.
	void ScalingCnt(int sparkle);	//�g�k�̃J�E���g�����֐�.
	void Scaling(int sparkle);		//�g�k�����֐�.
	void InitScaling(int sparkle);	//�g�k�����ݒ菈���֐�.
	void InitPosition(int sparkle);	//�����z�u�ݒ菈���֐�.

};

#endif	//#ifndef CSPARKLE_EFFECT_H.