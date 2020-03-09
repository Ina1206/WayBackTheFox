#include "CSparkleEffect.h"

/***********************************************
*		�L���L���G�t�F�N�g�N���X.
***/
CSparkleEffect::CSparkleEffect()
	: m_Sparkle_max			(0)
	, m_penScalingType		(nullptr)
	, m_CheckCnt			(0)
	, m_fCenterDifferencial	(0.0f)
	, m_RowMax				(0)
	, m_fHeight_Width		(0.0f)
	, m_fLeftInterval		(0.0f)
	, m_fRightInterval		(0.0f)
	, m_fLeftMost			(0.0f)
	, m_fRightMost			(0.0f)
	, m_fScaleMax			(SCALE_MAX)
{
}

CSparkleEffect::~CSparkleEffect()
{
}

//===========================================.
//		�X�V�����֐�.
//===========================================.
void CSparkleEffect::Update()
{
	//�t���O���ς���Ă���.
	if (m_bDispFlag != m_bOldDispFlag) {
		for (int sparkle = 0; sparkle < m_Sparkle_max; sparkle++) {
			//�����z�u�ݒ菈���֐�.
			InitPosition(sparkle);
			//�g�k�����ݒ菈���֐�.
			InitScaling(sparkle);
			//�`�F�b�N�J�E���g������.
			m_CheckCnt = 0;
		}
	}

	//�g�k�����֐�.
	for (int sparkle = 0; sparkle < m_Sparkle_max; sparkle++) {
		Scaling(sparkle);
	}

	//���݂̃t���O�擾.
	m_bOldDispFlag = m_bDispFlag;
}

//==============================================.
//		�g�k�����ݒ菈���֐�.
//==============================================.
void CSparkleEffect::InitScaling(int sparkle)
{
	if (sparkle % STAR_HORIZON_MAX == 0) {
		//�傫�����ő�ɐݒ�.
		m_pfScale[sparkle] = m_fScaleMax;
		//���������鏈����.
		m_penScalingType[sparkle] = enScalingType::Small;
	}
	else {
		//�傫�����ŏ��ɐݒ�.
		m_pfScale[sparkle] = SCALE_MIN;
		//���������鏈����.
		m_penScalingType[sparkle] = enScalingType::Large;
	}
}

//==============================================.
//		�g�k�����֐�.
//==============================================.
void CSparkleEffect::Scaling(int sparkle)
{
	switch (m_penScalingType[sparkle]) {
	//�傫������.
	case enScalingType::Large:
		m_pfScale[sparkle] += SCALING_SPEED;
		//�ő�ŏ������Ȃ鏈����.
		if (m_pfScale[sparkle] > m_fScaleMax) {
			m_penScalingType[sparkle] = enScalingType::Small;
		}
		break;
	//����������.
	case enScalingType::Small:
		m_pfScale[sparkle] -= SCALING_SPEED;

		//�ŏ��ő傫���Ȃ鏈����.
		if (m_pfScale[sparkle] < SCALE_MIN) {
		
			m_penScalingType[sparkle] = enScalingType::Large;

			//�g�k�̃J�E���g�����֐�.
			ScalingCnt(sparkle);
		}
		break;
	}
}

//===================================================.
//		�g�k�̃J�E���g�����֐�.
//===================================================.
void CSparkleEffect::ScalingCnt(int sparkle)
{
	//�J�E���g.
	if (sparkle == STANDERD_SPARKLE_NUM) {

		m_CheckCnt++;

		//������ΏI��
		if (m_CheckCnt > SCALING_MAX) {
			m_bDispFlag = false;
		}
	}
}


//==========================================.
//		�����z�u�ݒ菈���֐�.
//==========================================.
void CSparkleEffect::InitPosition(int sparkle)
{
	//����.
	m_pvPos[sparkle].y = (m_vCenterPos.y + m_fCenterDifferencial) - ((sparkle / m_RowMax) * m_fHeight_Width);
	//���s�̓v���C���[�ɍ��킹��.
	m_pvPos[sparkle].z = m_vCenterPos.z;

	//�����l(��ɂȂ�Έ���).
	float Start_Distance = ((sparkle / m_RowMax) % 2) * m_fLeftInterval;		//����.
	float Interval_Distance = ((sparkle / m_RowMax) % 2) * m_fRightInterval;	//�E��.
	//���x���W�v�Z.
	float Criteria_PosX = (m_fLeftMost + Start_Distance) + ((sparkle % m_RowMax) * (m_fRightMost - Interval_Distance));
	//�v���C���[�̒��S�ɍ��킹��.
	m_pvPos[sparkle].x = m_vCenterPos.x + Criteria_PosX;


}