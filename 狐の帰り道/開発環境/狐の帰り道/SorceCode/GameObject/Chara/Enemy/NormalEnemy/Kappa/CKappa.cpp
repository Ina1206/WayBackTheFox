#include "CKappa.h"

CKappa::CKappa()
	: m_pKappa			(nullptr)
	, m_pAnimController	(nullptr)
	, m_bCheckSound		(false)
	, m_pGrassMesh		(nullptr)
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();

	//�J�b�p.
	m_pKappa = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Raccoon_Dog);
	//�A�j���[�V�����R���g���[���[�R�s�[.
	m_pKappa->GetAnimationController()->CloneAnimationController(
		m_pKappa->GetAnimationController()->GetMaxNumAnimationOutputs(),
		m_pKappa->GetAnimationController()->GetMaxNumAnimationSets(),
		m_pKappa->GetAnimationController()->GetMaxNumTracks(),
		m_pKappa->GetAnimationController()->GetMaxNumEvents(),
		&m_pAnimController
	);

	
	m_pKappa->ChangeAnimSet(ANIMATION_NUM,  m_pAnimController);
}

CKappa::~CKappa()
{
}

//==================================.
//		�����ݒ菈���֐�.
//==================================.
void CKappa::Init_Process()
{
	//�������R�}���h�N���X�쐬.
	m_pCCommand_Base = new CLongPushCommand();
	//�R�}���h�{�^���ԍ�.
	m_pCCommand_Base->SetButtonNum(m_ButtonNum);

	m_vPos = m_vInitPos;
	m_vPos.y = START_HIGH;
}

//==================================.
//		�X�V�����֐�.
//==================================.
void CKappa::UpDate()
{
	//�ړ������֐�.
	Move();

	//�R�}���h�ʒu���.
	m_pCCommand_Base->SetPos(m_vPos);
	//�v���C���[���W.
	m_pCCommand_Base->SetPlayerPos(m_vPlayerPos);
	//�R�}���h����t���O.
	m_pCCommand_Base->SetJudgePossible(m_bJudgePossible);
	//�������J�E���g.
	m_pCCommand_Base->SetLongPushCnt(m_LongPushCnt);
	//�R�}���h�X�V�����֐�.
	m_pCCommand_Base->UpDate(m_enCommandType);
	//SE�Đ������֐�.
	m_pCCommand_Base->EffectAndSE_Play();
	//���茋�ʂ̎擾.
	for (int command = 0; command < DECISION_MAX; command++) {
		m_enInputDecision[command] = m_pCCommand_Base->GetInput_Deision(command);
	}
}

//==================================.
//		�`�揈���֐�.
//==================================.
void CKappa::Render()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();

	//�J�b�p.
	m_pKappa = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Raccoon_Dog);
	_ASSERT_EXPR(m_pKappa != nullptr, L"m_pKappa == nullptr");
	//�ʒu�ݒ�.
	m_pKappa->SetPosition(m_vPos);
	//�p�x�ݒ�.
	m_pKappa->SetRotation(m_vRot);
	//�傫���ݒ�.
	m_pKappa->SetScale(SCALE_SIZE);
	//�`�揈���֐�.
	m_pKappa->Render(m_mView, m_mProj, m_vLight, m_vCameraPos, m_pAnimController);

	//�^�k�L���B��Ă��鑐�̕`��.
	m_pGrassMesh = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Grass);
	_ASSERT_EXPR(m_pGrassMesh != nullptr, L"m_pGrassMesh == nullptr");
	//�ʒu�ݒ�.
	m_pGrassMesh->SetPosition(D3DXVECTOR3(m_vPos.x, 0.0f, m_vPos.z));
	//�傫���ݒ�.
	m_pGrassMesh->SetScale(SCALE_SIZE);
	//�`��ݒ�.
	m_pGrassMesh->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);

	//�R�}���h�̕`��.
	m_pCCommand_Base->Value_Set(m_mView, m_mProj, m_vCameraPos);
	m_pCCommand_Base->Render();
	//�G�t�F�N�g�̕`��.
	m_pCCommand_Base->EffectRender();
}

//==================================.
//		��������֐�.
//==================================.
void CKappa::Release()
{
	//�������R�}���h�N���X���.
	SAFE_DELETE(m_pCCommand_Base);

	m_pGrassMesh	= nullptr;
	m_pKappa		= nullptr;
}

//==================================.
//		�ړ������֐�.
//==================================.
void CKappa::Move()
{
	//�v���C���[���^�k�L�ɋ߂Â��Ă��珈��.
	if (m_vPos.z <= m_vPlayerPos.z + UP_MOVE_DISTANCE) {
		//�^�k�L����ɏオ�鏈��.
		if (m_vPos.y < HIGH_MAX) {
			m_vPos.y += UP_MOVE_SPEED;
		}

		//�オ��SE�̏���.
		if (m_bCheckSound == false && m_vPos.z != 0.0f) {
			//SE�Đ�.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::App, true);
			//�Đ��t���O.
			m_bCheckSound = true;
		}	
	}
}