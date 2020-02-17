#include "CBig_Raccoon_Dog.h"

CBig_Raccoon_Dog::CBig_Raccoon_Dog()
	: m_pCStaticMesh		(nullptr)
	, m_pCMesh				(nullptr)
	, m_pCSkinMesh			(nullptr)
	, m_pCStar				(nullptr)
	, m_pButtonNum			(nullptr)
	, m_enInputDecision		(enInput_Decision::Max)
	, m_enOldInDecision		(enInput_Decision::Max)
	, m_bCommandDispStart	(false)
	, m_enRotation_Move		(enRotation_Move::Start)
	, m_enRotationType		(enRotation_Move::Behind)
	, m_fFall_Down_Speed	(0.0f)
	, m_vSwingBefore_Pos	(0.0f, 0.0f, 0.0f)
	, m_fScale				(SCALE_SIZE)
	, m_bInputSE_Check		(false)
	, m_bMoveStart			(false)
	, m_fUpDistance			(0.0f)
	, m_fAnimSpeed			(ANIM_SPEED_MIN)
	, m_enAnimType			(enAnimType::Noting)
	, m_bAnimChange			(false)
	, m_pvPlayerHandlePos	(nullptr)
	, m_pbHitHandleFlag		(nullptr)
	, m_Cnt					(0)
	, m_WaitCnt				(0)
	, m_fHitRotation		(HIT_ROTATION_SPEED)
	, m_vStarPos			(0.0f, 0.0f, 0.0f)
	, m_fStarScale			(0.0f)
	, m_enStarScaling		(enStarScaling::Scale)
	, m_vPrePos				(0.0f, 0.0f, 0.0f)
{
	m_pButtonNum = new int[COMMAND_BUTTON_MAX]();
}

CBig_Raccoon_Dog::~CBig_Raccoon_Dog()
{
}

//===================================.
//		�����������֐�.
//===================================.
void CBig_Raccoon_Dog::Init_Process()
{
	//�����ʒu.
	m_vPos = m_vInitPos;
	m_vPos.y = STANDERD_POS_H;
	m_vRot.x = START_ROTATION;

	//�z�񓮓I�m��.
	m_pvPlayerHandlePos			= new D3DXVECTOR3[HANDLE_MAX]();
	m_ppCCollision_Detection	= new CCollision_Detection*[HANDLE_MAX]();
	m_ppCDebug_Collision_Sphere = new CDebugCollisionSphere*[HANDLE_MAX + HIT_TARGET_MAX]();
	m_pbHitHandleFlag			= new bool[HANDLE_MAX]();
	m_ppCEffectBase				= new CEffectBase*[EFFECT_MAX]();

	//�A�j���[�V�����̎�ނ�h��Ă�����̂ɐݒ�.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::BigRaccoon_Dog);
	m_pCSkinMesh->ChangeAnimSet(static_cast<int>(enAnimType::Swing));

	//�����蔻��Ɋւ���N���X�̍쐬.
	for (int collision = 0; collision < HANDLE_MAX; collision++) {
		m_ppCCollision_Detection[collision]		= new CCollision_Detection();
		m_ppCDebug_Collision_Sphere[collision]	= new CDebugCollisionSphere();
	}
	m_ppCDebug_Collision_Sphere[HIT_TARGET_NUM] = new CDebugCollisionSphere();

	//�����蔻��̏����ݒ�.
	for (int collision = 0; collision < HANDLE_MAX; collision++) {
		m_ppCCollision_Detection[collision]->Init();
		m_ppCCollision_Detection[collision]->SetScale(PLAYER_HIT_SCALE, CCollision_Detection::enObject::Playre);
		m_ppCCollision_Detection[collision]->SetScale(BOSS_HIT_SCALE, CCollision_Detection::enObject::BigRccoon_Dog);
		m_pbHitHandleFlag[collision] = false;
	}

	m_vPrePos.y = CENTER_AXIS_DIFF;

	//���ꂼ��̃G�t�F�N�g�N���X�̍쐬.
	m_ppCEffectBase[HIT_FLY_EFFECT_NUM]		= new CBossFlyEffect();	//���ł����Ƃ��̉��G�t�F�N�g.
	m_ppCEffectBase[FALLDOWN_EFFECT_NUM]	= new CFallDownEffect();//�|�ꂽ�Ƃ��̉��G�t�F�N�g.
	m_ppCEffectBase[PUNCH_EFFECT_NUM]		= new CPunchEffect();	//�p���`���ꂽ���̃G�t�F�N�g.

	m_pCCommand_Base = new CBarrageCommand();
	//�{�^���ԍ��ݒ�.
	for (int button = 0; button < COMMAND_BUTTON_MAX; button++) {
		m_pCCommand_Base->SetMultipleButtonNum(m_pButtonNum[button], button);
	}
}

//===================================.
//		�X�V�����֐�.
//===================================.
void CBig_Raccoon_Dog::UpDate()
{
	m_enInputDecision = m_pCCommand_Base->GetInput_Deision();
	if (m_enInputDecision == enInput_Decision::Max) {
		if (m_bMoveStart == false) {
			//�s���J�n�����֐�.
			Move_Judgement();
		}
		if (m_bMoveStart == true) {
			//����ꂽ���̉������֐�.
			HitSound();

			//�`�R�}���h�̐ݒ�`.
			m_pCCommand_Base->SetPos(m_vPos);				//���W.
			m_pCCommand_Base->SetPlayerPos(m_vPlayerPos);	//Player���W.
			m_pCCommand_Base->SetDispFlag(m_bMoveStart);	//�s���J�n�t���O.
			m_pCCommand_Base->UpDate(m_enCommandType);		//�X�V�����֐�.
		}
	}
	else {
		//�R�}���h�\���I��.
		m_bCommandDispStart = false;
	}

	//�R�}���h�G�t�F�N�g��SE�Đ��N���X.
	m_pCCommand_Base->EffectAndSE_Play();

	//�p���`���ꂽ���̃G�t�F�N�g�X�V�����֐�.
	m_ppCEffectBase[PUNCH_EFFECT_NUM]->UpDate();

	//�R�}���h������.
	if (m_enInputDecision == enInput_Decision::Good || 
		m_enInputDecision == enInput_Decision::Great) {
		//�����������̏����֐�.
		HitMove();
	}

	//�R�}���h���s��.
	if(m_enInputDecision == enInput_Decision::Bad){
		//�҂����Ԍv�Z.
		if (m_Cnt < FALL_DOWN_WAIT_TIME) {
			m_Cnt++;
		}
		else {
			//�|���Ƃ��̏����֐�.
			FALL_DOWN();
		}
	}


	//�A�j���[�V�����ύX.
	if (m_enInputDecision != m_enOldInDecision) {
		m_bAnimChange = true;
	}
	//��]����A�j���[�V�����ɕύX.
	if (m_bAnimChange == true) {
		if (m_vRot.x < ANIM_CHANGE_ROT) {
			if (m_enInputDecision == enInput_Decision::Bad) {
				//�ʏ�.
				m_pCSkinMesh->ChangeAnimSet(static_cast<int>(enAnimType::Noting));
			}
			else {
				//���ōs���A�j���[�V����
				m_pCSkinMesh->ChangeAnimSet(static_cast<int>(enAnimType::Finish));
			}
			//�A�j���[�V�����ύX�I��.
			m_bAnimChange = false;
		}
	}

	//�O��ƍ���̓��͌��ʂ̍���.
	m_enOldInDecision = m_enInputDecision;

}

//====================================.
//		�`�揈���֐�.
//====================================.
void CBig_Raccoon_Dog::Render()
{
	//�f�J�^�k�L�`��.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::BigRaccoon_Dog);
	//�Y���̈ʒu.
	m_pCSkinMesh->SetPrePos(m_vPrePos);
	//�傫��.
	m_pCSkinMesh->SetScale(m_fScale);
	//�X��.
	m_pCSkinMesh->SetRotation(m_vRot);
	//�ʒu.
	m_pCSkinMesh->SetPosition(m_vPos);
	//�A�j���[�V�������x.
	m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	//�`��.
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);

	//�G�t�F�N�g�̕`��.
	for (int effect = 0; effect < EFFECT_MAX; effect++) {
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->Render(m_mView, m_mProj, m_vCameraPos);
		}
	}
	
	//�Ō�̐��̕`��.
	m_pCStar = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Sparkle);
	//�ʒu.
	m_pCStar->SetPosition(m_vStarPos);
	//���ߒl.
	m_pCStar->SetAlpha(ALPHA_MAX);
	//�傫��.
	m_pCStar->SetScale(D3DXVECTOR3(m_fStarScale, m_fStarScale, m_fStarScale));
	//�`��.
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->SetDepth(false);
	m_pCStar->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepthStencil->SetDepth(true);

	//�R�}���h�N���X�̕`��.
	m_pCCommand_Base->Value_Set(m_mView, m_mProj, m_vCameraPos);
	m_pCCommand_Base->Render();
	m_pCCommand_Base->EffectRender();
}

//====================================.
//		��������֐�.
//====================================.
void CBig_Raccoon_Dog::Release()
{
	//�N���X���.
	//�R�}���h�N���X.
	SAFE_DELETE(m_pCCommand_Base);

	//���ꂼ��̃G�t�F�N�g�N���X.
	for (int effect = EFFECT_MAX - 1; effect >= 0; effect--) {
		SAFE_DELETE(m_ppCEffectBase[effect]);
	}

	//�����蔻��̕`��.
	for (int draw = (HANDLE_MAX + HIT_TARGET_MAX) - 1; draw >= 0; draw--) {
		SAFE_DELETE(m_ppCDebug_Collision_Sphere[draw]);
	}
	//�����蔻��.
	for (int handle = HANDLE_MAX - 1; handle >= 0; handle--) {
		SAFE_DELETE(m_ppCCollision_Detection[handle]);
	}
	
	//�z����.
	SAFE_DELETE_ARRAY(m_ppCEffectBase);
	SAFE_DELETE_ARRAY(m_pbHitHandleFlag);
	SAFE_DELETE_ARRAY(m_ppCDebug_Collision_Sphere);
	SAFE_DELETE_ARRAY(m_ppCCollision_Detection);
	SAFE_DELETE_ARRAY(m_pvPlayerHandlePos);
	SAFE_DELETE_ARRAY(m_pButtonNum);

	m_pCSkinMesh	= nullptr;
	m_pCStaticMesh	= nullptr;
}

//====================================.
//		�s�������֐�.
//====================================.
void CBig_Raccoon_Dog::Move_Judgement()
{
	if (m_fSpeed <= 0.0f) {
		m_WaitCnt++;
		if (m_WaitCnt >= WAIT_TIME) {
			m_bMoveStart		= true;
			m_bCommandDispStart = true;
			m_fAnimSpeed		= ANIM_SPEED_MAX;
		}
	}
}

//=======================================.
//		�����������̏����֐�.
//=======================================.
void CBig_Raccoon_Dog::HitMove()
{
	//��].
	m_vRot.x += m_fHitRotation;
	//��]���x�����X�ɑ��₵�Ă���.
	m_fHitRotation += HIT_ROT_SPEED_UP;
	if (m_vRot.x > ONE_ROTATION_MIN) {
		m_vRot.x = 0.0f;
	}

	//y���݂̂ɔ�΂�.
	if (m_vPos.y < FLY_MAX) {
		m_vPos.y += HIT_MOVE_SPEED;
		//SE�̍Đ�.
		if (m_bInputSE_Check == false) {
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Boss_Fly, true);
			m_bInputSE_Check = true;
		}
	}
	else {
		//��񂾂��Ƃ̏���.
		FlyAfter();
	}
	//���ł��������ɍ��킹�đ傫��������������.
	m_fScale = SCALE_SIZE - ((m_vPos.y /FLY_MAX) * SCALE_SIZE);

	//���ł����Ƃ��̃G�t�F�N�g.
	//���S�̈ʒu�ݒ�.
	m_ppCEffectBase[HIT_FLY_EFFECT_NUM]->SetCenterPos(m_vPos);
	//�G�t�F�N�g�\��.
	m_ppCEffectBase[HIT_FLY_EFFECT_NUM]->SetEffectStart(true);
	//�G�t�F�N�g�X�V����.
	m_ppCEffectBase[HIT_FLY_EFFECT_NUM]->UpDate();

}

//=======================================.
//		�|���Ƃ��̏����֐�.
//=======================================.
void CBig_Raccoon_Dog::FALL_DOWN()
{

	if (m_vRot.x > FALL_DOWN_ROT_MIN) {
		//�����Ɠ|��鉜�s�̒���.
		m_vPos.z -= ADJUST_MOVE_SPEED.z;
		//m_vPos.y += ADJUST_MOVE_SPEED.y;
		//�|���p�x.
		m_vRot.x -= m_fFall_Down_Speed;
		//�|��鑬�x�����X�ɑ���.
		m_fFall_Down_Speed += FALL_DOWN_SPEED_UP;
		//�n�k���N����O�̍��W.
		m_vSwingBefore_Pos = m_vPos;
	}
	else {
		m_vRot.x = FALL_DOWN_ROT_MIN;
		m_vPos.y = m_vSwingBefore_Pos.y + m_fUpDistance;

		//SE�̍Đ�.
		if (m_bInputSE_Check == false) {
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Fall_Down, true);
			m_bInputSE_Check = true;
		}

		//�G�t�F�N�g����.
		m_ppCEffectBase[FALLDOWN_EFFECT_NUM]->SetCenterPos(m_vPos);
		m_ppCEffectBase[FALLDOWN_EFFECT_NUM]->SetEffectStart(true);
		m_ppCEffectBase[FALLDOWN_EFFECT_NUM]->UpDate();
	}

}

//==============================================.
//		����ꂽ���̉������֐�.
//==============================================.
void CBig_Raccoon_Dog::HitSound()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Player);
	//�{�[�����W�擾.
	m_pCSkinMesh->GetPosFromBone("Left_hand", &m_pvPlayerHandlePos[LEFT_HANDLE_NUM]);	//����.
	m_pCSkinMesh->GetPosFromBone("Right_hand", &m_pvPlayerHandlePos[RIGHT_HANDLE_NUM]);	//�E��.

	//��̍��W�Ƒ傫���̐ݒ�.
	for (int handle = 0; handle < HANDLE_MAX; handle++) {
		m_ppCDebug_Collision_Sphere[handle]->SetPos(m_pvPlayerHandlePos[handle]);
		m_ppCDebug_Collision_Sphere[handle]->SetScale(0.2f);
	}

	//���鎞�̃{�X���̓����蔻����W�ݒ�.
	D3DXVECTOR3 m_vHitPos = D3DXVECTOR3(m_vInitPos.x, m_vInitPos.y + 1.0f, m_vPos.z - 0.5f);
	//D3DXVECTOR3 m_vHitPos = m_vInitPos+ HIT_BOSSPOS_ADJUST;
	m_ppCDebug_Collision_Sphere[HIT_TARGET_NUM]->SetPos(m_vHitPos);
	m_ppCDebug_Collision_Sphere[HIT_TARGET_NUM]->SetScale(1.5f);

	for (int handle = 0; handle < HANDLE_MAX; handle++) {
		//�U�����̐ݒ�.
		CCollision_Detection::stObjectInfo stAtkObj;
		stAtkObj.Object = CCollision_Detection::enObject::Playre;
		stAtkObj.vPos	= m_pvPlayerHandlePos[handle];

		//�G���̐ݒ�.
		CCollision_Detection::stObjectInfo stTargetObj;
		stTargetObj.Object	= CCollision_Detection::enObject::BigRccoon_Dog;
		stTargetObj.vPos	= m_vHitPos;
		
		if (m_ppCCollision_Detection[handle]->JugeHit(&stAtkObj, &stTargetObj)) {
			if (m_pbHitHandleFlag[handle] == false) {
				//�p���`���ꂽ���̃G�t�F�N�g.
				m_ppCEffectBase[PUNCH_EFFECT_NUM]->SetCenterPos(m_pvPlayerHandlePos[handle]);
				m_ppCEffectBase[PUNCH_EFFECT_NUM]->SetEffectStart(true);
				//SE����.
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Poko_Hit, true);
				m_pbHitHandleFlag[handle] = true;
			}
		}
		else {
			m_pbHitHandleFlag[handle] = false;
		}
	}
}

//====================================================.
//		��񂾂��Ƃ̏����֐�.
//====================================================.
void CBig_Raccoon_Dog::FlyAfter()
{
	//�f�J�^�k�L�ɍ��W�����킹��.
	m_vStarPos = m_vPos;
	
	//���̊g�k.
	switch (m_enStarScaling) {
	//�g��.
	case enStarScaling::Scale:
		
		m_fStarScale += STAR_SCALE_SPEED;
		
		//�����o�Ă���Ԃ̓J�����𓮂����Ȃ��悤�ړ�.
		m_vPos.x += BACK_SPEED;

		if (m_fStarScale >= STAR_MAX) {
			m_enStarScaling = enStarScaling::Scale_Down;
			//SE�̍Đ�.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Boss_Star, true);
		}
		break;
	//�k��.
	case enStarScaling::Scale_Down:

		m_fStarScale -= STAR_SCALE_SPEED;
		
		//�����o�Ă���Ԃ̓J�����𓮂����Ȃ��悤�ړ�.
		m_vPos.x += BACK_SPEED;
		
		if (m_fStarScale < STAR_MIN) {
			m_enStarScaling = enStarScaling::Finish;
		}
		break;
	default:
		m_bDispFlag = false;
		break;
	}
}