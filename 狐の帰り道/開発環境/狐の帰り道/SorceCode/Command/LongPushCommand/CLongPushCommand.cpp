#include "CLongPushCommand.h"

/***************************************
*		�������R�}���h�N���X.
***********/
CLongPushCommand::CLongPushCommand()
	: m_ppCCommandSprite	(nullptr)
	, m_pvCommandPos		(nullptr)
	, m_PushCount			(0)
	, m_bSoundCheck			(false)
	, m_pCEffectBase		(nullptr)
	, m_fButtonHigh			(0)
	, m_vOldPos				(0.0f, 0.0f, 0.0f)
{
	//�R�}���h�p�X�v���C�g�N���X�̔z�񓮓I�m��.
	m_ppCCommandSprite = new CSprite*[static_cast<int>(enCommandSpriteType::Max)]();
	//�R�}���h�ʒu�̔z�񓮓I�m��.
	m_pvCommandPos = new D3DXVECTOR3[static_cast<int>(enCommandSpriteType::Max)]();
	//�\���t���O������.
	m_bDispFlag = false;

	//�G�t�F�N�g�N���X�쐬.
	m_pCEffectBase = new CLongPushEffect();

	//�{�^������.
	m_fButtonHigh = BUTTON_DISP_POS_MAX;
}

CLongPushCommand::~CLongPushCommand()
{
	//�G�t�F�N�g�N���X���.
	SAFE_DELETE(m_pCEffectBase);

	for (int command = static_cast<int>(enCommandSpriteType::Max) - 1; command >= 0; command--) {
		m_ppCCommandSprite[command] = nullptr;
	}
	//���.
	SAFE_DELETE_ARRAY(m_pvCommandPos);
	SAFE_DELETE_ARRAY(m_ppCCommandSprite);

}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CLongPushCommand::Update(enCommandType CommandType)
{
	//�������R�}���h�̃R�}���h�摜�\��.
	for (int command = 0; command < static_cast<int>(enCommandSpriteType::Max); command++) {
		m_pvCommandPos[command].x = m_vPos.x;
		m_pvCommandPos[command].y = START_DISP_HEIGH - ((command % 2) * DISP_HEIGH_ADJUST);
		m_pvCommandPos[command].z = (m_vPos.z - (COMMAND_LENGHT * (DEPTH_ADJUST * command))) - COMMAND_POS_Z;
	}

	//�\�����菈���֐�.
	DecisionDisp();

	if (m_bDispFlag == true) {
		if (m_vPos.x == m_vPlayerPos.x && m_bJudgePossible == true) {
			//�R�}���h���菈���֐�.
			DecisionCommand(CommandType);
		}
		//�ŏ��ɔ��肵���㉟���Ȃ��牡�ɍs����Bad����.
		if (m_vPos.x != m_vPlayerPos.x && m_PushCount > 0) {
			if (m_penInput_Decision[StartDecisionNum] != enInput_Decision::Max) {
				m_PushCount = DECISION_TERMIN;
				m_penInput_Decision[EndDecisionNum] = enInput_Decision::Bad;
			}
		}
		//�R�}���h�������ɒʂ蔲����.
		const int COMMAND_START_NUM = static_cast<int>(enCommandSpriteType::CommandStart);
		if (m_pvCommandPos[COMMAND_START_NUM].z + GOOD_RANGE < m_vPlayerPos.z && 
			m_penInput_Decision[StartDecisionNum] == enInput_Decision::Max) {
			//����I��.
			m_PushCount = DECISION_TERMIN;
		}
	}
	else if (m_PushCount > 0) {
		//�������܂ܔ�\���ɂȂ��Bad����.
		m_penInput_Decision[EndDecisionNum] = enInput_Decision::Bad;
		m_PushCount = DECISION_TERMIN;
	}

	//SE.
	if (m_PushCount > 0 && m_penInput_Decision[StartDecisionNum] != enInput_Decision::Max) {
		//�Đ�.
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::LongPush, true);
		m_bSoundCheck = true;
		//�G�t�F�N�g.
		if (m_pCEffectBase->GetEffectStartFlag() == false) {
			//�������W�̎擾.
			m_pCEffectBase->SetCenterPos(m_vPlayerPos);
			//�G�t�F�N�g�\���J�n�t���O.
			m_pCEffectBase->SetEffectStart(true);
		}
		//�G�t�F�N�g�X�V�����֐�.
		m_pCEffectBase->Update();
	}
	//�炵�Ă���ꍇ.
	else if(m_bSoundCheck == true){
		//��~.
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::LongPush, false);
		m_bSoundCheck = false;
	}
}

//=====================================.
//		�`�揈���֐�.
//=====================================.
void CLongPushCommand::Render()
{
	int Standerd_CommandAlpha = 0;	//�R�}���h���ł̓��ߒl�̊.

	m_vPos.y += m_fButtonHigh;

	if (m_bDispFlag == true) {
		//�{�^���̍����ύX.
		if (m_vPos.y > m_vOldPos.y) {
			if (m_fButtonHigh >= BUTTON_DISP_POS_MIN) {
				m_fButtonHigh -= BUTTON_DOWN_SPEED;
			}
		}

		//�������R�}���h�`��.
		RenderCommand();
		//�{�^���R�}���h�`��.
		RenderButton();
		//�G�t�F�N�g�`��.
		m_pCEffectBase->Render(m_mView, m_mProj, m_vCameraPos);
	}

	//�O��̃{�^�����W�ݒ�.
	m_vOldPos = m_vPos;
}

//=====================================.
//		��������֐�.
//=====================================.
void CLongPushCommand::Release()
{
	m_pvCommandPos = nullptr;
	m_ppCCommandSprite = nullptr;
}

//=====================================.
//		�`�攻�菈���֐�.
//=====================================.
void CLongPushCommand::DecisionDisp()
{
	//�����ɂ���ĕ\�����邩�ǂ���.
	if (m_vPos.z < DISP_ALPHA) {
		m_bDispFlag = true;
		//�v���C���[����O�ɍs���Ɣ�\��.
		if (m_vPos.z < m_vPlayerPos.z) {
			m_bDispFlag = false;
		}
	}

	//����Ƃ��������.
	if (m_bDispFlag == true && m_PushCount == DECISION_TERMIN) {
		m_bDispFlag = false;
	}
}

//=====================================.
//		�R�}���h���菈���֐�.
//=====================================.
void CLongPushCommand::DecisionCommand(enCommandType CommandType)
{
	//�G�̏������Ă���{�^���ԍ��Ɠ��̓{�^���ԍ�����v���Ă��邩�ǂ���.
	if (m_ButtonNum == static_cast<int>(CommandType)) {
		m_PushCount++;
	}
	else if(m_PushCount > 0) {
		if (m_penInput_Decision[StartDecisionNum] != enInput_Decision::Max) {
			//�r���ŗ�������I��.
			m_PushCount = DECISION_TERMIN;
		}
		else {
			m_PushCount = 0;
		}
	}

	//�R�}���h�X�^�[�g�n�_���菈���֐�.
	if (m_PushCount == 1 && m_LongPushCnt == 0) {
		DecisionCommandStart();
	}

	//�R�}���h�I���n�_�̔��菈���֐�.
	if (m_PushCount == DECISION_TERMIN) {
		DecisionCommandEnd();
	}

}

//=====================================.
//	�R�}���h�X�^�[�g�n�_���菈���֐�.
//=====================================.
void CLongPushCommand::DecisionCommandStart()
{
	const int COMMAND_START_NUM = static_cast<int>(enCommandSpriteType::CommandStart);

	//Great����.
	if ((m_pvCommandPos[COMMAND_START_NUM].z - GREAT_RANGE) <= m_vPlayerPos.z &&
		(m_pvCommandPos[COMMAND_START_NUM].z + GREAT_RANGE) >= m_vPlayerPos.z) {
		m_penInput_Decision[StartDecisionNum] = enInput_Decision::Great;
	}
	//Good����.
	else if((m_pvCommandPos[COMMAND_START_NUM].z - GOOD_RANGE) <= m_vPlayerPos.z &&
			(m_pvCommandPos[COMMAND_START_NUM].z + GOOD_RANGE) >= m_vPlayerPos.z) {
			m_penInput_Decision[StartDecisionNum] = enInput_Decision::Good;
	}
}

//======================================.
//	�R�}���h�I���n�_�̔��菈���֐�.
//======================================.
void CLongPushCommand::DecisionCommandEnd()
{
	const int COMMAND_END_NUM = static_cast<int>(enCommandSpriteType::CommandEnd);

	//Great����.
	if (m_pvCommandPos[COMMAND_END_NUM].z - GREAT_RANGE <= m_vPlayerPos.z &&
		m_pvCommandPos[COMMAND_END_NUM].z + GREAT_RANGE >= m_vPlayerPos.z) {
		m_penInput_Decision[EndDecisionNum] = enInput_Decision::Great;
	}
	//Good����.
	else if (m_pvCommandPos[COMMAND_END_NUM].z - GOOD_RANGE <= m_vPlayerPos.z &&
			 m_pvCommandPos[COMMAND_END_NUM].z + GOOD_RANGE >= m_vPlayerPos.z) {
			 m_penInput_Decision[EndDecisionNum] = enInput_Decision::Good;
	}
	//Bad����.
	else {
		m_penInput_Decision[EndDecisionNum] = enInput_Decision::Bad;
	}
}

//=====================================.
//		�R�}���h�摜�̕`��.
//=====================================.
void CLongPushCommand::RenderCommand()
{
	int m_Intermediate	= static_cast<int>(enCommandSpriteType::Intermediate);	//�Ԃ̎l�p.

	//�N���X�̃A�h���X.
	for (int circlecommand = 0; circlecommand < static_cast<int>(enCommandSpriteType::Max); circlecommand += 2) {
		//�~�̃X�v���C�g���擾.
		m_ppCCommandSprite[circlecommand] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::LongPushCircle);
	}
	//���Ԃ̎l�p�̃X�v���C�g���擾.
	m_ppCCommandSprite[m_Intermediate] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Long_Square);

	//���ߒl�ƈʒu�̐ݒ�.
	for (int command = 0; command < static_cast<int>(enCommandSpriteType::Max); command++) {
		//�J�����̌����ɂ��킳�Ȃ�.
		m_ppCCommandSprite[command]->SetCancelRotationFlag(false);
		//�ʒu�ݒ�.
		m_ppCCommandSprite[command]->SetPosition(m_pvCommandPos[command]);
		//���ߒl�ݒ�.
		m_ppCCommandSprite[command]->SetAlpha(m_fAlpha);
		//�`��.
		m_ppCCommandSprite[command]->Render(m_mView, m_mProj, m_vCameraPos);
	}
}