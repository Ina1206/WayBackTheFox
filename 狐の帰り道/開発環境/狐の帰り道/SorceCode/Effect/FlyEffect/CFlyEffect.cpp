#include "CFlyEffect.h"

/**********************************************
*		��ԃG�t�F�N�g�N���X.
*****/
CFlyEffect::CFlyEffect()
	: m_pfAlpha				(nullptr)
	, m_fStartPos_x			(0.0f)
	, m_Row_Max				(0)
	, m_fInterval_Width		(0.0f)
	, m_fFoot_Differencial	(0.0f)
	, m_fMax_Scale			(0.0f)
	, m_DispCnt				(0)
	, m_pbSmokeDispFlag		(nullptr)
	, m_FinishCnt			(0)
{
}

CFlyEffect::~CFlyEffect()
{
}

//=========================================.
//		���̕\�������֐�.
//=========================================.
void CFlyEffect::DispSmoke()
{
	//�o�����ԂɂȂ�܂ŃJ�E���g.
	m_DispCnt++;
	if (m_DispCnt >= DISP_TIME) {
		for (int smoke = 0; smoke < m_SmokeMax; smoke++) {
			if (m_pbSmokeDispFlag[smoke] == false) {
				//�ʒu�ݒ菈���֐�.
				SetPosition(smoke);
				//�t���O.
				m_pbSmokeDispFlag[smoke] = true;
				//�߂�.
				m_DispCnt = 0;
				break;
			}
		}
	}

	//�o�����Ă���Ƃ��͓����̏���.
	for (int smoke = 0; smoke < m_SmokeMax; smoke++) {
		if (m_pbSmokeDispFlag[smoke] == true) {
			//���̓����̏���.
			MoveSmoke(smoke);
		}
	}

	if (m_FinishCnt > m_SmokeMax) {
		m_bDispFlag = false;
	}
}

//=========================================.
//		�ʒu�ݒ菈���֐�.
//=========================================.
void CFlyEffect::SetPosition(int smoke)
{
	//�ʒu�ݒ�.
	m_pvPos[smoke].x = (m_vCenterPos.x + m_fStartPos_x) + ((smoke%m_Row_Max)*m_fInterval_Width);
	m_pvPos[smoke].y = m_vCenterPos.y - m_fFoot_Differencial;
	m_pvPos[smoke].z = m_vCenterPos.z;
}

//=========================================.
//		���̓��������֐�.
//=========================================.
void CFlyEffect::MoveSmoke(int smoke)
{
	//�g��Ɠ���.
	if (m_pfScale[smoke] < m_fMax_Scale) {
		m_pfScale[smoke] += SCALING_SPEED ;
	}
	else {
		//����.
		if (m_pfAlpha[smoke] > MIN_ALPHA) {
			m_pfAlpha[smoke] -= ALPHA_SPEED;
		}
		else {
			//��\��.
			m_pbSmokeDispFlag[smoke] = false;
			m_FinishCnt++;
		}
	}

}

//========================================.
//		���̉�]�����֐�.
//========================================.
void CFlyEffect::Ratation(int smoke, bool CameraRot)
{
	//�����v�Z.
	int Direction = LEFT_DIRECTION + ((smoke % m_Row_Max) * m_Row_Max);
	//�J��������]���Ă��Ȃ����z������]����.
	if (CameraRot == false) {
		m_pvRot[smoke].z += RATATION_SPEED * Direction;
		if (fabsf(m_pvRot[smoke].z) > RATATION_MAX) {
			m_pvRot[smoke].z = 0.0f;
		}
	}
	else {
		//��]���Ă���΂�������]����.
		m_pvRot[smoke].x += RATATION_SPEED * Direction;
		if (fabsf(m_pvRot[smoke].x) > RATATION_MAX) {
			m_pvRot[smoke].x = 0.0f;
		}
	}
}