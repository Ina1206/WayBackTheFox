#include "CCow_Ghost.h"

CCow_Ghost::CCow_Ghost()
	: m_pStaticMesh			(nullptr)
	, m_enVerticalMoveType	(enVerticalMove_Type::Up)
	, m_enHorizonMoveType	(enHorizonMove_Type::Left_Move)
	, m_JumpCnt				(0)
	, m_fOldPos_x			(0.0f)
	, m_bCheckSE			(false)
{
}

CCow_Ghost::~CCow_Ghost()
{
}

//================================================.
//		�����������֐�.
//================================================.
void CCow_Ghost::Init_Process()
{
	//���W�ݒ�.
	m_vPos = m_vInitPos;
	m_vPos.y = STANDERD_HIGH;

	//�^�C�~���O�R�}���h�N���X�쐬.
	m_pCCommand_Base = new CTimingCommand();
	//�{�^���ԍ��ݒ�.
	m_pCCommand_Base->SetButtonNum(m_ButtonNum);
	//�^�C�~���O�R�}���h�̍����ݒ�.
	m_pCCommand_Base->SetDispHight(COMMAND_HIGH);

	//���ړ��G�t�F�N�g�N���X�쐬.
	m_pCEffectBase = new CHorizonMoveEffect();	
}

//================================================.
//		�X�V�����֐�.
//================================================.
void CCow_Ghost::UpDate()
{

	if (m_HitFlag == false || m_pCCommand_Base->GetButtonLightFinish() == false) {
		//�ړ������֐�.
		Move();

		//�R�}���h.
		//Player�̍��W.
		m_pCCommand_Base->SetPlayerPos(m_vPlayerPos);
		//�R�}���h����\�t���O.
		m_pCCommand_Base->SetJudgePossible(m_bJudgePossible);
		//�������J�E���g.
		m_pCCommand_Base->SetLongPushCnt(m_LongPushCnt);
		//�R�}���h�X�V�����֐�.
		m_pCCommand_Base->Update(m_enCommandType);
	}
	else {
		
		//���ł����ړ������֐�.
		FlyMove();
	}
	//�R�}���h�̍��W.
	m_pCCommand_Base->SetPos(m_vPos);
	//�R�}���hSE�ƃG�t�F�N�g�Đ�����.
	m_pCCommand_Base->PlayEffectAndSE();
}

//================================================.
//		�`�揈���֐�.
//================================================.
void CCow_Ghost::Render()
{
	//�e�̕`��.
	if (m_vPos.y < SHADOW_DISP_UP_LIMIT) {
		m_vShadowPos = m_vPos;
		//�e�̕`�揈���֐�.
		ShadowRender();
	}

	//=======================.
	//	�G�t�F�N�g�`��.
	if (m_pCEffectBase->GetEffectStartFlag() == true) {
		m_pCEffectBase->Render(m_mView, m_mProj, m_vCameraPos);
	}

	if (m_HitFlag == true) {
		m_pCEnemyFlyEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}

	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();

	m_pStaticMesh = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Cow_Gohst);
	_ASSERT_EXPR(m_pStaticMesh != nullptr, L"m_pStaticMesh == nullptr");
	m_pStaticMesh->SetScale(SCALE_SIZE);
	m_pStaticMesh->SetPosition(m_vPos);
	m_pStaticMesh->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);

	//�R�}���h�̕`��.
	m_pCCommand_Base->SetValue(m_mView, m_mProj, m_vCameraPos);
	m_pCCommand_Base->Render();
	m_pCCommand_Base->RenderEffect();

}

//================================================.
//		��������֐�.
//================================================.
void CCow_Ghost::Release()
{
	//�N���X���.
	SAFE_DELETE(m_pCEffectBase);
	SAFE_DELETE(m_pCCommand_Base);
	m_pStaticMesh = nullptr;
}

//================================================.
//		�ړ������֐�.
//================================================.
void CCow_Ghost::Move()
{
	//���̈ʒu�܂��́A���ړ�����̎��͈ړ��\.
	if (m_vPos.z >= m_vPlayerPos.z + STOP_DISTANCE || m_enVerticalMoveType == enVerticalMove_Type::Waiting) {
		FarMove();
	}
	else {
		//���������킹��.
		if (m_vPos.y >= STANDERD_HIGH) {
			m_vPos.y -= VERTICAL_SPEED;
		}
	}

	if (m_HitFlag == false) {
		//���ł����ړ������֐�.
		FlyJudge();
	}
	//================================.
	//	�G�t�F�N�g.
	m_pCEffectBase->UpDate();

}

//================================================.
//		�������̈ړ������֐�.
//================================================.
void CCow_Ghost::FarMove()
{
	//�ړ����@.
	switch (m_enVerticalMoveType) {
	//��Ɉړ�.
	case enVerticalMove_Type::Up:

		m_vPos.y += VERTICAL_SPEED;

		//����ɒB�����牺�Ɉړ�.
		if (m_vPos.y > HIGH_MAX) {
			//���̃X�e�[�W��.
			m_enVerticalMoveType = enVerticalMove_Type::Down;
		}
		break;
	//���Ɉړ�.
	case enVerticalMove_Type::Down:

		m_vPos.y -= VERTICAL_SPEED;

		//���ɒB�������Ɉړ�.
		if (m_vPos.y <= STANDERD_HIGH) {
			m_enVerticalMoveType = enVerticalMove_Type::Up;
			//�W�����v�J�E���g�ǉ�.
			m_JumpCnt++;

			//�W�����v�J�E���g�ő�Ȃ獶�E�Ɉړ�.
			if (m_JumpCnt >= JUMP_MAX) {
				m_JumpCnt = 0;
				//�E�̃��[���Ȃ獶�Ɉړ�.
				if (m_vPos.x > CENTER_POS_X) {
					m_enVerticalMoveType = enVerticalMove_Type::Waiting;
				}
				//�^�񒆂ƍ��̃��[���Ȃ�E�Ɉړ�.
				else {
					m_enVerticalMoveType = enVerticalMove_Type::Waiting;
				}
				//�O��̈ʒu�ɋL��.
				m_fOldPos_x = m_vPos.x;

				//�t���O�������ɖ߂�.
				m_bCheckSE = false;
			}
		}
		break;
	//�ҋ@.
	case enVerticalMove_Type::Waiting:
		//���ړ������֐�.
		HorizonMove();

		//���ړ�����SE�Đ�.
		if (m_bCheckSE == false) {
			//�Đ�.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Ghost_Move, true);
			//�Đ������`�F�b�N.
			m_bCheckSE = true;
		}
		break;
	}

}

//===========================================.
//		���ړ������֐�.
//===========================================.
void CCow_Ghost::HorizonMove()
{
	//���ړ�����.
	switch (m_enHorizonMoveType) {
	//�E�Ɉړ�.
	case enHorizonMove_Type::Right_Move:
		//�E�ړ�.
		m_vPos.x += HORIZON_SPEED;

		//���̃��[���ɍs���΂܂��c�ړ�.
		if (m_vPos.x >= m_fOldPos_x + MOVE_WIDTH) {
			m_vPos.x = m_fOldPos_x + MOVE_WIDTH;
			m_enVerticalMoveType = enVerticalMove_Type::Up;
		}

		//���[���̍ő�l�ɍs���΍��ړ���.
		if (m_vPos.x >= LANE_MAX) {
			m_enHorizonMoveType = enHorizonMove_Type::Left_Move;
			//�ʒu�Ȃ����Ă���.
			m_vPos.x = LANE_MAX;
		}
		if (m_vPlayerPos.z + EFFECT_DISP_POS > m_vPos.z) {
			//�G�t�F�N�g�\������.
			m_pCEffectBase->SetEffectStart(true);
		}
		break;
	//���Ɉړ�.
	case enHorizonMove_Type::Left_Move:
		//���ړ�.
		m_vPos.x -= HORIZON_SPEED;

		//���̃��[���ɍs���΂܂��c�ړ�.
		if (m_vPos.x <= m_fOldPos_x - MOVE_WIDTH) {
			m_vPos.x = m_fOldPos_x - MOVE_WIDTH;
			m_enVerticalMoveType = enVerticalMove_Type::Up;
		}

		//���[���̍��[�ɍs���ΉE�ړ���.
		if (m_vPos.x <= LANE_MIN) {
			m_enHorizonMoveType = enHorizonMove_Type::Right_Move;
			//�ʒu�������.
			m_vPos.x = LANE_MIN;
		}
	
		if (m_vPlayerPos.z + EFFECT_DISP_POS> m_vPos.z) {
			//�G�t�F�N�g�\������.
			m_pCEffectBase->SetEffectStart(true);
		}
		break;
	}

	//�G�t�F�N�g�̒��S�ʒu�ݒ�.
	m_pCEffectBase->SetCenterPos(m_vPos);
}

