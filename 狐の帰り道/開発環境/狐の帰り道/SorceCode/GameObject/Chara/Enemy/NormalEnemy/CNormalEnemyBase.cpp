#include "CNormalEnemyBase.h"

CNormalEnemyBase::CNormalEnemyBase()
	: m_HitNum			(0)
	, m_HitMoveDirection(0)
	, m_HitFlag			(false)
	, m_ButtonNum		(0)
	, m_enInputDecision	(nullptr)
	, m_pCEnemyFlyEffect(nullptr)
{
	//��ԃG�t�F�N�g�N���X�̃C���X�^���X.
	m_pCEnemyFlyEffect = new CEnemyFlyEffect();

	//����̓��I�m��.
	m_enInputDecision = new enInput_Decision[DECISION_MAX]();
	//����������.
	for (int command = 0; command < DECISION_MAX; command++) {
		m_enInputDecision[command] = enInput_Decision::Max;
	}
}

CNormalEnemyBase::~CNormalEnemyBase()
{
	//�������.
	SAFE_DELETE_ARRAY(m_enInputDecision);
	SAFE_DELETE(m_pCEnemyFlyEffect);
}

//==================================.
//		��Ԕ��菈���֐�.
//==================================.
void CNormalEnemyBase::FlyJudge()
{
	m_enInputDecision[STANDERD_USE_COMMAND] = m_pCCommand_Base->GetInputDeision();

	//Great,Good�̎��������Ƃ�.
	if (m_enInputDecision[STANDERD_USE_COMMAND] == enInput_Decision::Great || 
		m_enInputDecision[STANDERD_USE_COMMAND] == enInput_Decision::Good) {
		m_HitNum++;
		m_HitFlag = true;
		//������������SE.
		m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::EnemyFly, true);
		//�`�`�`�`�`�`�`�`�`�`�`.
		//�G�t�F�N�g.
		//�`�`�`�`�`�`�`�`�`�`�`.
		//�\���t���O.
		m_pCEffectBase->SetEffectStart(true);
	}
}

//==================================.
//		���ł����ړ������֐�.
//==================================.
void CNormalEnemyBase::FlyMove()
{
	//��Ԋp�x����.
	m_vPos.x += FLY_SPEED.x * m_HitMoveDirection;
	m_vPos.y += FLY_SPEED.y;


	//���ł���Ƃ��̌X��.	
	switch (m_HitNum % 2) {
		//���ɔ�ԃL����.
	case static_cast<int>(enFlyDirection::Left):
		if (m_vRot.z < LEFT_JUMP_ROT) {
			m_HitMoveDirection = LEFT_DIRECTION;
			m_vRot.z += ROT_SPEED;
		}
		break;
		//�E�ɔ�ԃL����.
	case static_cast<int>(enFlyDirection::Right):
		if (m_vRot.z > RIGHT_JUMP_ROT) {
			m_HitMoveDirection = RIGHT_DIRECTION;
			m_vRot.z -= ROT_SPEED;
		}
		break;
	}

	//�`�`�`�`�`�`�`�`�`�`�`.
	//�G�t�F�N�g.
	//�`�`�`�`�`�`�`�`�`�`�`.
	//�ʒu�ݒ�.
	m_pCEnemyFlyEffect->SetCenterPos(m_vPos);
	//�X�V�����֐�.
	m_pCEnemyFlyEffect->UpDate();
}

