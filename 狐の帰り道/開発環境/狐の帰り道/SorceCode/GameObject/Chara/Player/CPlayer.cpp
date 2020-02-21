#include "CPlayer.h"


//===================================.
//	�R���X�g���N�^.
//===================================.
CPlayer::CPlayer()
	: m_PlayerParam			()
	, m_pCPlayerAnim		(nullptr)
	, m_pCInput				(nullptr)
	, m_pCResourceManager	(nullptr)
	, m_pCSEPlayManager		(nullptr)
	, m_enOperation			(enOperation::Max)
	, m_pChangeTexture		(nullptr)
	, m_vEnemyPosition		(D3DXVECTOR3(0.0f,0.0f,0.0f))
	, m_bEndFlag			(false)
	, m_frame				(0)
	, m_WaitTime			(0)
	, m_bFixedPosFlag		(false)
	, m_bLongCommandFlag	(false)
	, m_OperationFlag		(false)
	, m_bJumpEndFlag		(false)
	, m_bStartCountFlag		(false)
	, m_StartCount			(0)
	, m_FlashTime			(0)
	//=================.
	//		�ǉ�.
	, m_pCShadow(nullptr)
{
}

//===================================.
//	�f�X�g���N�^.
//===================================.
CPlayer::~CPlayer()
{
	Release();
}

//�����ݒ�֐�.
void CPlayer::InitProcess()
{
	m_PlayerParam.m_vPos	= D3DXVECTOR3(0.0f, 0.0f, POISITION_Z);
	m_PlayerParam.m_vOldPos = m_PlayerParam.m_vPos;
	m_PlayerParam.m_AnimSpeed = ANIM_SPEED;
	m_pCInput				= new clsXInput();
	m_pCResourceManager		= CResourceManager::GetResourceManagerInstance();
	m_pCSEPlayManager		= CSEPlayManager::GetSEPlayManagerInstance();

	//�����������֐�.
	Init();

	//�A�j���[�V����.
	SetAnim(enPlyAct::Run);

	//�G�t�F�N�g.
	//�z�񓮓I�m��.
	m_ppCEffectBase = new CEffectBase*[EFFECT_MAX]();
	//�N���X.
	m_ppCEffectBase[STEP_EFFECT_NUM] = new CStepEffect();	
	m_ppCEffectBase[LAND_EFFECT_NUM] = new CLandingEffect();

}

//===================================.
//�X�V�����֐�.
//===================================.
void CPlayer::Update()
{
	m_pCInput->UpdateStatus();//�������Ȃ��Ɠ����Ȃ�.

	//�J�E���g�_�E�����͓����Ȃ��悤�ɂ���.
	if (m_bStartCountFlag == true) {
		m_StartCount++;
		if (m_StartCount >= MOVE_START) {
			m_OperationFlag = true;
		}
	}

	//---����\�ł���Ƃ�---.
	if (m_OperationFlag == true && m_bFixedPosFlag == false) {
		//---���@�ړ�(�R���g���[���Ή�)---//.
		//�E�ړ�.
		if (m_PlayerParam.m_vPos.x != MOVING_RANGE) {
			if (m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_RIGHT)|| m_pCInput->GetLThumbX() >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				m_PlayerParam.m_MoveCount_R++;
				Move(MOVING_RANGE, m_PlayerParam.m_MoveCount_R);
				SetAnim(enPlyAct::Run);
			}
			else
			{
				m_PlayerParam.m_MoveCount_R = 0;
			}
		}
		//���ړ�.
		if (m_PlayerParam.m_vPos.x != -MOVING_RANGE) {
			if (m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_LEFT) || m_pCInput->GetLThumbX() <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				m_PlayerParam.m_MoveCount_L++;
				Move(-MOVING_RANGE, m_PlayerParam.m_MoveCount_L);
				SetAnim(enPlyAct::Run);
			}
			else
			{
				m_PlayerParam.m_MoveCount_L = 0;
			}
		}

		//---���@�ړ�����---//.
		//x���W.
		if (m_PlayerParam.m_vPos.x > MOVING_RANGE) { m_PlayerParam.m_vPos.x = MOVING_RANGE; }
		if (m_PlayerParam.m_vPos.x < -MOVING_RANGE) { m_PlayerParam.m_vPos.x = -MOVING_RANGE; }
	}

	//�������R�}���h�������Ă���Ƃ�.
	if (m_bLongCommandFlag == true) {
		m_OperationFlag = false;
		m_bJumpEndFlag = false;
	}

	//�����O�Ƀ{�^����������Ă���ꍇ���v���C���[��^�񒆂ɂ���.
	if (m_OperationFlag == true) {
		if (m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_RIGHT)
			|| m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			if (m_bFixedPosFlag == true)
			{
				m_OperationFlag = false;							//����s�\�ɂ���.
				if (m_PlayerParam.m_Count == 0)
				{
					m_PlayerParam.m_vPos = m_PlayerParam.m_vOldPos;		//�v���C���[��^�񒆂ɂ���.
				}
			}
		}
	}

	//����������v���C���[���^�񒆂ɂȂ�悤�ɂ���.
	if (m_bFixedPosFlag == true)
	{
		m_OperationFlag = false;							//����s�\�ɂ���.

		if (m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_RIGHT)
			|| m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			m_OperationFlag = false;						//����s�\�ɂ���.
		}
		m_PlayerParam.m_vPos.x = m_PlayerParam.m_vOldPos.x;
		if (m_PlayerParam.m_Count == 0)
		{
			//Player���^�񒆂ɂ���Ƃ���SE��炳�Ȃ�.
			if (m_PlayerParam.m_vPos != m_PlayerParam.m_vOldPos) {
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Player_Move, true);
			}
		}
		m_PlayerParam.m_Count++;
	}
	
	//-------------------------------.
	//	�W�����v.
	//-------------------------------.
	Jump();

#ifdef _DEBUG
	if (m_OperationFlag == true)
	{
		if (GetAsyncKeyState('A') & 0x0001)
		{
			m_PlayerParam.m_vPos.x -= MOVING_RANGE;
			SetAnim(enPlyAct::Run);
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Player_Move, true);
		}
		if (GetAsyncKeyState('D') & 0x0001)
		{
			m_PlayerParam.m_vPos.x += MOVING_RANGE;
			SetAnim(enPlyAct::Run);
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Player_Move, true);
		}
	}

	//---�W�����v---//.
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		if (m_PlayerParam.m_bJumpFlag == false) {
			//�W�����v���łȂ��Ƃ�.
			m_PlayerParam.m_bJumpFlag = true;		//�W�����v�J�n.
			m_PlayerParam.m_fAcc = 0.0f;			//����������.
		}
	}

	//--------------------------------
	//	�A�j���[�V�����؂�ւ�.
	//--------------------------------
	static int anim_no = 0;
	if (GetAsyncKeyState('C') & 0x0001)
	{
		anim_no++;
		if (anim_no >= m_pCPlayerAnim->GetAnimMax()) {
			anim_no = 0;
		}
		m_pCPlayerAnim->ChangeAnimSet(anim_no);
	}

#endif

	if (m_pCPlayerAnim != nullptr) {
		//�v���C���[�̑����̍��W.
		m_vFootDownPos = D3DXVECTOR3(m_PlayerParam.m_vPos.x, GROUND_HIT_H, m_PlayerParam.m_vPos.z);
		//������SE�̏����֐�.
		FootStepSE(m_pCPlayerAnim, CSoundResource::enSoundSE::Player_Step);
	}

}

//===================================.
//�`�揈���֐�.
//===================================.
void CPlayer::Render()
{
	//=========================.
	//		�e�ǉ�.
	//�e�`��.
	m_pCShadow = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Shadow);
	_ASSERT_EXPR(m_pCShadow != nullptr, L"m_pCShadow == nullptr");
	//���W.
	D3DXVECTOR3 m_vShadowPos = m_PlayerParam.m_vPos;
	m_vShadowPos.y = SHADOW_HIGHT;
	m_pCShadow->SetPosition(m_vShadowPos);
	m_pCShadow->SetCancelRotationFlag(false);
	m_pCShadow->Render(m_mView, m_mProj, m_vCameraPos);

	//�v���C���[�̃A�j���[�V����.
	m_pCPlayerAnim = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Player);
	_ASSERT_EXPR(m_pCPlayerAnim != nullptr, L"m_pPlayerAnim == nullptr");
	m_pCPlayerAnim->SetPosition(m_PlayerParam.m_vPos);
	m_pCPlayerAnim->SetRotation(D3DXVECTOR3(0.0f, ROTATION, 0.0f));
	m_pCPlayerAnim->SetAnimSpeed(m_PlayerParam.m_AnimSpeed);
	m_pCPlayerAnim->SetScale(SCALE_SIZE);
	m_pCPlayerAnim->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);

	//--------------------------------
	//	�A�j���[�V�����؂�ւ�.
	//--------------------------------
	switch (m_PlayerParam.m_Action)
	{
	case enPlyAct::Run:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_RUN);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	case enPlyAct::Jump:
	case enPlyAct::TwoRowJump:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_JUMP);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	case enPlyAct::Wait:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_WAIT);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	case enPlyAct::Attack:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_ATTACK);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	case enPlyAct::Panic:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_PANIC);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	default:
		break;
	}

	//�G�t�F�N�g�̕`�揈���֐�.
	for (int effect = 0; effect < EFFECT_MAX; effect++) {
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->Render(m_mView, m_mProj, m_vCameraPos);
		}
	}

}

//===================================.
//��������֐�.
//===================================.
void CPlayer::Release()
{
	//��������֐�.
	Destroy();

	SAFE_DELETE(m_pChangeTexture);

	//�G�t�F�N�g���Ƃ̃N���X���.
	SAFE_DELETE(m_ppCEffectBase[LAND_EFFECT_NUM]);
	SAFE_DELETE(m_ppCEffectBase[STEP_EFFECT_NUM]);

	//�G�t�F�N�g�̔z����.
	SAFE_DELETE_ARRAY(m_ppCEffectBase);

	m_pCSEPlayManager = nullptr;
	//�ǂݍ��݊Ǘ��N���X.
	m_pCResourceManager = nullptr;
	SAFE_DELETE(m_pCInput);
	m_pCPlayerAnim  = nullptr;
}

//===================================.
//�O�i�����֐�.
//===================================.
void CPlayer::Progress()
{
	m_frame++;

	if (m_frame % SECONDS_COUNT == 0)
	{
		m_WaitTime++;
	}
	if (m_WaitTime < WAIT_END)
	{
		SetAnim(enPlyAct::Wait);
	}
	if (m_WaitTime >= WAIT_END)
	{
		SetAnim(enPlyAct::Run);
		m_PlayerParam.m_vPos.z += MOVE_SPEED;
	}
	if (m_WaitTime > GAME_END)
	{
		m_bEndFlag = true;
	}
}

//===================================.
//�_�ŏ���.
//===================================.
void CPlayer::Flashing(int count)
{

	if (m_bFixedPosFlag == false)
	{
		if (count % FLASH_DIVIDE == 0) {
			m_FlashTime++;
		}
		if (m_FlashTime % TWO_DIVIDE == 0) {
			m_pCPlayerAnim->SetEnabelChangeTextureSystem(false);
		}
		else
		{
			m_pCPlayerAnim->SetEnabelChangeTextureSystem(true);
		}

		if (count == 0)
		{
			m_FlashTime = 0;
		}
	}
	else {
		m_pCPlayerAnim->SetEnabelChangeTextureSystem(false);
	}

}

//===================================.
//�A�j���[�V�����Đ��ݒ�;
//===================================.
void CPlayer::SetAnim(enPlyAct Act)
{
	m_PlayerParam.m_Action = Act;

	if (m_PlayerParam.m_Action != m_PlayerParam.m_Old_Action)
	{
		m_PlayerParam.m_SetAnimFlag = true;
		m_PlayerParam.m_Old_Action = m_PlayerParam.m_Action;
	}
}

//===================================.
//�ړ�����.
//===================================.
void CPlayer::Move(float range, int count)
{
	//��C�Ɉړ�����̂�h������.
	if (count == FIRST_MOVETIME)
	{
		m_PlayerParam.m_vPos.x += range;
		m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Player_Move, true);
	}
}

//===================================.
//�W�����v����.
//===================================.
void CPlayer::Jump()
{

	if (m_PlayerParam.m_bJumpFlag == false) {
		m_PlayerParam.m_fAcc = 0.0f;	//����������.	
	}

	if (m_PlayerParam.m_bJumpFlag == true) {
		m_PlayerParam.m_vPos.y += JUMP_POWER + m_PlayerParam.m_fAcc;
		m_PlayerParam.m_fAcc -= GRAVITY;								//�d�͉���.
		m_OperationFlag = false;
		SetAnim(enPlyAct::Jump);

		//�n�ʂ�艺�ɂȂ���.
		if (m_PlayerParam.m_vPos.y <= 0) {
			m_PlayerParam.m_vPos.y = 0;
			m_bJumpEndFlag = true;
			m_PlayerParam.m_bJumpFlag = false;
			SetAnim(enPlyAct::Run);
			m_OperationFlag = true;

			//�n�ʂɒ��n�����Ƃ��̃G�t�F�N�g.
			m_ppCEffectBase[LAND_EFFECT_NUM]->SetCenterPos(m_PlayerParam.m_vPos);
			m_ppCEffectBase[LAND_EFFECT_NUM]->SetEffectStart(true);

		}

		//���~����.
		if (m_PlayerParam.m_vPos.y > m_PlayerParam.m_vOldPos.y)
		{
			//�G�����ɂ��邩.
			if (m_PlayerParam.m_vPos.y < m_vEnemyPosition.y + POSITION_ADJ
				&& m_PlayerParam.m_vPos.z < m_vEnemyPosition.z + ENEMY_DEPTH)
			{
				//�ēx�W�����v.
				m_PlayerParam.m_fAcc = GRAVITY;
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Jump, true);
				SetAnim(enPlyAct::TwoRowJump);

				//�^�k�L�𓥂ނƂ��̃G�t�F�N�g.
				m_ppCEffectBase[STEP_EFFECT_NUM]->SetCenterPos(m_PlayerParam.m_vPos);
				m_ppCEffectBase[STEP_EFFECT_NUM]->SetEffectStart(true);

			}
		}
	}

	for (int effect = 0; effect < EFFECT_MAX; effect++) {
		//�G�t�F�N�g�X�V�����֐�.
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->Update();
		}
	}
}
