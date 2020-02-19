#include "CNormalEnemyBase.h"

CNormalEnemyBase::CNormalEnemyBase()
	: m_HitNum			(0)
	, m_HitMoveDirection(0)
	, m_HitFlag			(false)
	, m_ButtonNum		(0)
	, m_enInputDecision	(nullptr)
	, m_pCEnemyFlyEffect(nullptr)
{
	//”ò‚ÔƒGƒtƒFƒNƒgƒNƒ‰ƒX‚ÌƒCƒ“ƒXƒ^ƒ“ƒX.
	m_pCEnemyFlyEffect = new CEnemyFlyEffect();

	//”»’è‚Ì“®“IŠm•Û.
	m_enInputDecision = new enInput_Decision[DECISION_MAX]();
	//‰Šú‰»ˆ—.
	for (int command = 0; command < DECISION_MAX; command++) {
		m_enInputDecision[command] = enInput_Decision::Max;
	}
}

CNormalEnemyBase::~CNormalEnemyBase()
{
	//‰ğ•úˆ—.
	SAFE_DELETE_ARRAY(m_enInputDecision);
	SAFE_DELETE(m_pCEnemyFlyEffect);
}

//==================================.
//		”ò‚Ô”»’èˆ—ŠÖ”.
//==================================.
void CNormalEnemyBase::FlyJudge()
{
	m_enInputDecision[STANDERD_USE_COMMAND] = m_pCCommand_Base->GetInputDeision();

	//Great,Good‚Ì‚ª‚Â‚¢‚½‚Æ‚«.
	if (m_enInputDecision[STANDERD_USE_COMMAND] == enInput_Decision::Great || 
		m_enInputDecision[STANDERD_USE_COMMAND] == enInput_Decision::Good) {
		m_HitNum++;
		m_HitFlag = true;
		//“–‚½‚Á‚½‚ÌSE.
		m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::EnemyFly, true);
		//```````````.
		//ƒGƒtƒFƒNƒg.
		//```````````.
		//•\¦ƒtƒ‰ƒO.
		m_pCEffectBase->SetEffectStart(true);
	}
}

//==================================.
//		”ò‚ñ‚Å‚¢‚­ˆÚ“®ˆ—ŠÖ”.
//==================================.
void CNormalEnemyBase::FlyMove()
{
	//”ò‚ÔŠp“x’²®.
	m_vPos.x += FLY_SPEED.x * m_HitMoveDirection;
	m_vPos.y += FLY_SPEED.y;


	//”ò‚ñ‚Å‚¢‚é‚Æ‚«‚ÌŒX‚«.	
	switch (m_HitNum % 2) {
		//¶‚É”ò‚ÔƒLƒƒƒ‰.
	case static_cast<int>(enFlyDirection::Left):
		if (m_vRot.z < LEFT_JUMP_ROT) {
			m_HitMoveDirection = LEFT_DIRECTION;
			m_vRot.z += ROT_SPEED;
		}
		break;
		//‰E‚É”ò‚ÔƒLƒƒƒ‰.
	case static_cast<int>(enFlyDirection::Right):
		if (m_vRot.z > RIGHT_JUMP_ROT) {
			m_HitMoveDirection = RIGHT_DIRECTION;
			m_vRot.z -= ROT_SPEED;
		}
		break;
	}

	//```````````.
	//ƒGƒtƒFƒNƒg.
	//```````````.
	//ˆÊ’uİ’è.
	m_pCEnemyFlyEffect->SetCenterPos(m_vPos);
	//XVˆ—ŠÖ”.
	m_pCEnemyFlyEffect->UpDate();
}

