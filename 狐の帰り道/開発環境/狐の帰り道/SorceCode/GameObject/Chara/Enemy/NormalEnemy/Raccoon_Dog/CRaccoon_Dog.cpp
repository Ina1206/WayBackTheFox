#include "CRaccoon_Dog.h"

/****************************************
*	�^�k�L�N���X.
**/
CRaccoon_Dog::CRaccoon_Dog()
	:m_pRacconAnim		(nullptr)
	, m_pAnimController	(nullptr)
	, m_bOldHit			(false)
	, m_pCSEHit			(nullptr)
	, m_pCTimingCommand	(nullptr)
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	//�^�k�L�A�j���[�V����.
	m_pRacconAnim = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Raccoon_Dog);
	_ASSERT_EXPR(m_pRacconAnim != nullptr, L"m_pRaccoonAnim == nullptr");
}

CRaccoon_Dog::~CRaccoon_Dog()
{
}

//==================================.
//		�����ݒ菈���֐�.
//==================================.
void CRaccoon_Dog::InitProcess()
{
	//�����ʒu.
	m_vPos = m_vInitPos;
	//�G�t�F�N�g.
	m_pCEffectBase = new CEnemyFlyEffect();

	//�R�}���h.
	m_pCCommand_Base = new CTimingCommand();
	//�{�^���ԍ�.
	m_pCCommand_Base->SetButtonNum(m_ButtonNum);
	//�\������.
	m_pCCommand_Base->SetDispHight(COMMAND_DISP_H);

	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pRacconAnim = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Raccoon_Dog);
	//�A�j���[�V�����R���g���[���[�R�s�[.
	m_pRacconAnim->GetAnimationController()->CloneAnimationController(
		m_pRacconAnim->GetAnimationController()->GetMaxNumAnimationOutputs(),
		m_pRacconAnim->GetAnimationController()->GetMaxNumAnimationSets(),
		m_pRacconAnim->GetAnimationController()->GetMaxNumTracks(),
		m_pRacconAnim->GetAnimationController()->GetMaxNumEvents(),
		&m_pAnimController
	);
	//����̃A�j���[�V�����ɐݒ�.
	m_pRacconAnim->ChangeAnimSet(static_cast<int>(enAnimType::Run), m_pAnimController);
}

//==================================.
//		�X�V�����֐�.
//==================================.
void CRaccoon_Dog::Update()
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
	else{
		//����������̈ړ������֐�.
		MoveFly();
	}
	//�R�}���h�̍��W.
	m_pCCommand_Base->SetPos(m_vPos);
	//�R�}���hSE�ƃG�t�F�N�g�Đ�����.
	m_pCCommand_Base->PlayEffectAndSE();
}

//==================================.
//		�`�揈���֐�.
//==================================.
void CRaccoon_Dog::Render()
{
	//�e�̕`��.
	if (m_vPos.y < SHADOW_UP_LIMIT) {
		m_vShadowPos = m_vPos;
		ShadowRender();
	}
	//�ʒu.
	m_pRacconAnim->SetPosition(m_vPos);
	//�傫��.
	m_pRacconAnim->SetScale(SCALE_MAX);
	//�p�x.
	m_pRacconAnim->SetRotation(m_vRot);
	//�X�s�[�h.
	m_pRacconAnim->SetAnimSpeed(ANIM_SPEED);
	//�`��.
	m_pRacconAnim->Render(m_mView, m_mProj, m_vLight, m_vCameraPos, m_pAnimController);


	//�`�`�`�`�`�`�`�`�`�`�`.
	//�G�t�F�N�g�`��.
	//�`�`�`�`�`�`�`�`�`�`�`.
	if (m_pCEffectBase->GetEffectStartFlag() == true) {
		m_pCEnemyFlyEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}

	//�R�}���h�`�揈��.
	m_pCCommand_Base->SetValue(m_mView, m_mProj, m_vCameraPos);
	m_pCCommand_Base->Render();
	//�R�}���h�G�t�F�N�g�`�揈��.
	m_pCCommand_Base->RenderEffect();

}

//==================================.
//		��������֐�.
//==================================.
void CRaccoon_Dog::Release()
{
	//�G�t�F�N�g���.
	SAFE_DELETE(m_pCCommand_Base);
	SAFE_DELETE(m_pCEffectBase);

	//�^�k�L���b�V��.
	m_pRacconAnim = nullptr;
}

//==================================.
//		�ړ������֐�.
//==================================.
void CRaccoon_Dog::Move()
{
	//�G�@�̓���.
	m_vPos.z -= MOVE_SPEED;

	//���ł����ړ������֐�.
	if (m_HitFlag == false) {
		JudgeFly();
	}

	if (m_HitFlag != m_bOldHit) {
		//�����������̃A�j���[�V�����ɕύX.
		m_pRacconAnim->ChangeAnimSet(static_cast<int>(enAnimType::Hit), m_pAnimController);
	}
	m_bOldHit = m_HitFlag;
}
