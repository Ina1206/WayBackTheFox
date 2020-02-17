#include "CItemMove.h"

CItemMove::CItemMove()
	: m_vPos			(0.0f,0.0f,0.0f)
	, m_vIconPos		(0.0f,0.0f,0.0f)
	, m_bDispFlag		(false)
	, m_enItemJudge		(enItemJudge::Max)

	, m_bBounceFlag		(false)
	, m_BounceCount		(0)
	, m_fAcc			(0.0f)
	, m_fSpeed			(0.0f)
	, m_fDirect			(0.0f)
	, m_fSpdSpin		(0.0f)
	, m_enAction		(enItemAct::MAX)
	, m_Num				(0)
	, m_CollectionFlag	(false)
	, m_CollectionItem	(0)
	, m_Sum				(0)
	, m_BossFlag		(false)
	, m_pCSEPlayManager	(nullptr)
	, m_bCheckSE		(false)

{
	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
}

CItemMove::~CItemMove()
{
	Release();
}

//===================================.
//	�����������֐�.
//===================================.
void CItemMove::Init_Process(D3DXVECTOR3 vPos)
{
	m_vPos			= vPos;
	m_fSpeed		= SPEED;
	m_fDirect		= 0.0f;
	m_fSpdSpin		= ROTATION;
	m_BounceCount	= 0;
	m_bDispFlag		= false;
	m_enAction		= enItemAct::Bounce;
}

//===================================.
//	�X�V�����֐�.
//===================================.
void CItemMove::UpDate(bool disp, enItemJudge judge,  D3DXVECTOR3 IconPos)
{
	m_bDispFlag		= disp;
	m_enItemJudge	= judge;
	m_vIconPos		= IconPos;

	if (m_bDispFlag == true) {
		if (m_BossFlag == false)
		{
			Collection();
			Drop();
		}
		else
		{
			Collection_Boss();
			Drop_Boss();
		}
	}
}

//===================================.
//	�A�C�e�����.
//===================================.
void CItemMove::Collection()
{
	if (m_enItemJudge == enItemJudge::Success)
	{
		Bounce();
		Absorption();
		m_BounceCount++;
		if (m_BounceCount > BOUNCE_COUNR_MAX)
		{
			m_enAction = enItemAct::Absorption;
		}
		//�A�C�R���̈ʒu�𒴂�����\���t���O�����낷.
		if (m_vPos.y >= m_vIconPos.y)
		{
			m_vPos.y = m_vIconPos.y + m_vPos.y*2;
			m_bDispFlag = false;

			if (m_CollectionFlag == false) {
				m_CollectionItem = COLLITION_NUMBER;
				m_CollectionFlag = true;
			}
			else
			{
				m_CollectionItem = 0;
			}

			if (m_bCheckSE == false) {
				CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::ItemGet, true);
				m_bCheckSE = true;
			}
		}
	}
}

//===================================.
//	�{�X�A�C�e�����.
//===================================.
void CItemMove::Collection_Boss()
{
	if (m_enItemJudge == enItemJudge::Success)
	{
		Bounce();
		Absorption();
		m_BounceCount++;
		if (m_BounceCount > BOUNCE_COUNR_MAX)
		{
			m_enAction = enItemAct::Wait;
		}
		if (m_BounceCount > WAIT_TIME)
		{
			m_enAction = enItemAct::Absorption;
		}
		//�A�C�R���̈ʒu�𒴂�����\���t���O�����낷.
		if (m_vPos.y >= m_vIconPos.y)
		{
			m_vPos.y = m_vIconPos.y + m_vPos.y * 2;
			m_bDispFlag = false;

			if (m_CollectionFlag == false) {
				m_CollectionItem = COLLITION_NUMBER;
				m_CollectionFlag = true;
			}
			else
			{
				m_CollectionItem = 0;
			}

			if (m_bCheckSE == false) {
				CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::ItemGet, true);
				m_bCheckSE = true;
			}
		}
	}
}

//===================================.
//	�A�C�e�����Ƃ�.
//===================================.
void CItemMove::Drop()
{
	if (m_enItemJudge == enItemJudge::failure)
	{
		m_BounceCount++;
		Bounce();
		Absorption();
		if (m_BounceCount > BOUNCE_COUNR_MAX) {
			m_enAction = enItemAct::Flow;
		}
		if (m_enAction == enItemAct::Flow) {
			m_vPos.y = DROP_ITEMPOS.y;
			m_vPos.z -= DROP_ITEMPOS.z;
		}
		//�ʒu�𒴂�����\���t���O�����낷.
		if (m_vPos.z < DISP_POS) {
			m_bDispFlag = false;
		}
	}
}

//===================================.
//	�{�X�A�C�e�����Ƃ�.
//===================================.
void CItemMove::Drop_Boss()
{
	if (m_enItemJudge == enItemJudge::failure)
	{
		m_BounceCount++;
		Bounce();
		if (m_BounceCount > BOUNCE_COUNR_MAX)
		{
			m_enAction = enItemAct::Wait;
		}
	}
}

void CItemMove::Release()
{
	if (m_pCSEPlayManager != nullptr) {
		m_pCSEPlayManager = nullptr;
	}
}

//===================================.
//	�A�C�e���o�E���h.
//===================================.
void CItemMove::Bounce()
{
	if (m_enAction == enItemAct::Bounce) {
		if (m_bBounceFlag == false)
		{
			m_bBounceFlag = true;
			m_fAcc = 0.0f;
		}

		if (m_bBounceFlag == true)
		{
			if (m_BossFlag == false) {
				if (m_Num % 2 == 0) { m_vPos.x += BOUNCE_SPEED + (m_Num * SPEED_ADJ); }
				else { m_vPos.x -= BOUNCE_SPEED + (m_Num * SPEED_ADJ); }
			}
			else
			{
				if (m_enItemJudge == enItemJudge::Success) {
					if (m_Num % 2 == 0) { m_vPos.x += BOUNCESPEED_BOSS_S + (m_Num * SPEED_ADJ); }
					else { m_vPos.x -= BOUNCESPEED_BOSS_S + (m_Num * SPEED_ADJ); }
				}
				else 
				{
					if (m_Num % 2 == 0) { m_vPos.x += BOUNCESPEED_BOSS_F + (m_Num * SPEED_ADJ); }
					else { m_vPos.x -= BOUNCESPEED_BOSS_F + (m_Num * SPEED_ADJ); }
				}
			}
			m_vPos.y += FJUMP_POWER + m_fAcc;
			m_fAcc -= FGRAVITY;	//�d�͉���.

			if (m_BossFlag == false) {
				if (m_vPos.y < 0.0f)
				{
					m_vPos.y = 0.0f;
					m_bBounceFlag = false;
				}
			}
			else
			{
				if (m_vPos.y < BOUNCE_POS)
				{
					m_vPos.y = BOUNCE_POS;
					m_bBounceFlag = false;
				}
			}
		}
	}
}

//===================================.
//	�A�C�R���ɋz�������.
//===================================.
void CItemMove::Absorption()
{
	if (m_enAction == enItemAct::Absorption)
	{
		float m_fItem_vX, m_fItem_vY;	//�x�N�g����x,y����.
		float m_fItem_dX, m_fItem_dY;	//�����̒P�ʃx�N�g��.
		float m_fItem_sX, m_fItem_sY;	//���x�̒P�ʃx�N�g��.

		m_fItem_vX = m_vIconPos.x - m_vPos.x;
		m_fItem_vY = m_vIconPos.y - m_vPos.y;

		//�x�N�g���̐��K��(������).
		m_fItem_dX = m_fItem_vX / static_cast<float>(sqrt(m_fItem_vX * m_fItem_vX + m_fItem_vY * m_fItem_vY));
		//�x�N�g���̐��K��(y����).
		m_fItem_dY = m_fItem_vY / static_cast<float>(sqrt(m_fItem_vX * m_fItem_vX + m_fItem_vY * m_fItem_vY));

		//���x�x�N�g���̐��K��(x����).
		m_fItem_sX = static_cast<float>(sin(m_fDirect * M_PI / DEGREE));
		//���x�x�N�g���̐��K��(y����).
		m_fItem_sY = VECTOR_SPEED * static_cast<float>(cos(m_fDirect * M_PI / DEGREE));

		if (m_fItem_sX * m_fItem_dY - m_fItem_sY * m_fItem_dX > 0.0f) {//sin�Ƃ�0���傫�����.
			m_fDirect -= m_fSpdSpin;//�A�C�e�����E�ɉ�].
		}
		else
		{
			//�A�C�e�������ɉ�].
			m_fDirect += m_fSpdSpin;
		}

		m_vPos.x -= m_fSpeed * static_cast<float>(sin(m_fDirect * M_PI / DEGREE));
		m_vPos.y += m_fSpeed * static_cast<float>(cos(m_fDirect * M_PI / DEGREE));
	}
}
