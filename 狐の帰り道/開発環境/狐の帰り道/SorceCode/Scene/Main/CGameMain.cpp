#include "CGameMain.h"

CGameMain::CGameMain()
	: m_pCPlayer			(nullptr)
	, m_pCEnemyManager		(nullptr)
	, m_pCBackGround		(nullptr)
	, m_pCGround			(nullptr)
	, m_pCCameraManager		(nullptr)
	, m_CHit				(nullptr)
	, m_ppbCheckSound		(nullptr)
	, m_pCUIManager			(nullptr)
	, m_frame				(0)
	, m_waittime			(0)
	, m_pCEffectBase		(nullptr)
	, m_Count				(0)
	, m_HitCount			(0)
	, m_EndCount			(0)
{
}

CGameMain::~CGameMain()
{
	//��������֐�.
	Release();
}

//=====================================.
//		�����ݒ菈���֐�.
//=====================================.
void CGameMain::Init_Process()
{
	//---------�v���C���[-------//.
	m_pCPlayer = new CPlayer();
	m_pCPlayer->Init_Process();

	//-------------�G-------------//.
	m_pCEnemyManager = new CEnemyManager();
	m_pCEnemyManager->Init_Process();

	//------------�w�i------------//.
	m_pCBackGround = new CBackGround();

	//------------�n��------------//.
	m_pCGround = new CGround();
	m_pCGround->Init_Process();
	//�Q�[�g�̐ݒ�.
	m_pCGround->SetGatePosition(m_pCEnemyManager->GetEnemyPos(static_cast<int>(enEnemy::Big_RaccoonDog)));

	//-----------�����蔻��---------//.
	m_CHit = new CCollision_Detection;
	m_CHit->Init();

	//------------UI----------//.
	m_pCUIManager = new CMainUIManager();
	m_pCUIManager->Init_Process();

	//------------�J����----------//.
	m_pCCameraManager = new CCameraManager();


	//������������SE�t���O.
	m_ppbCheckSound = new bool*[static_cast<int>(enEnemy::Max)]();
	for (int enemyType = 0; enemyType < static_cast<int>(enEnemy::Max); enemyType++) {
		m_ppbCheckSound[enemyType] = new bool[m_pCEnemyManager->GetEnemyMax(enemyType)]();
		for (int enemy = 0; enemy < m_pCEnemyManager->GetEnemyMax(enemyType); enemy++) {
			m_ppbCheckSound[enemyType][enemy] = false;
		}
	}

	//================================.
	//����.
	m_pCEffectBase = new CHitEffect();
	//================================.
}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CGameMain::UpDate()
{
	//-----------�J����-----------//.
	//�����������������ǂ����̃t���O.
	m_pCEnemyManager->CameraUpJudge();
	m_pCCameraManager->SetChangeCamera(m_pCEnemyManager->GetMoveUpCamera());
	m_pCCameraManager->SetLongPush(m_pCEnemyManager->GetMoveUpCamera());
	//�R�}���h����.
	m_pCCameraManager->SetInputDecision(m_pCEnemyManager->GetEnemyInputDecision(m_pCEnemyManager->GetAllEnemySumMax() - 1));
	m_pCCameraManager->ChangeCamera();
	if (m_pCEnemyManager->GetBossDispFlag() == true) {
		m_pCCameraManager->SetTargetPos(m_pCEnemyManager->GetEnemyPos(static_cast<int>(enEnemy::Big_RaccoonDog)));
	}
	else {
		m_pCCameraManager->SetTargetPos(m_pCPlayer->GetPosition());
	}
	m_pCCameraManager->UpDate();


	//----------�v���C���[---------//.
	m_pCPlayer->UpDate();
	m_pCPlayer->SetFixedPosFlag(m_pCEnemyManager->GetDeceleration());
	m_pCPlayer->SetStartCountFlag(m_pCUIManager->GetStartCountDispFlag());
	if (m_pCGround->GetMoveSpeed() == 0.0f
		&& m_pCEnemyManager->GetBossCommandDisp() == false
		&& m_pCEnemyManager->GetEnemyInputDecision(m_pCEnemyManager->GetAllEnemySumMax() - 1) == enInput_Decision::Max) {
		m_pCPlayer->SetAnim(CPlayer::enPlyAct::Wait);
	}
	if (m_pCEnemyManager->GetBossCommandDisp() == true) {
		m_pCPlayer->SetAnim(CPlayer::enPlyAct::Attack);

	}

	//------------�n��------------//.
	m_pCGround->UpDate();
	//�����������������ǂ����̃t���O.
	m_pCGround->SetUpCamera(m_pCEnemyManager->GetMoveUpCamera());
	//�������邩�̃t���O.
	m_pCGround->SetDeceleration_StartFlag(m_pCEnemyManager->GetDeceleration());
	//�p�x�̎��.
	m_pCGround->SetBossRotation(m_pCEnemyManager->GetEnemyRot(static_cast<int>(enEnemy::Big_RaccoonDog)));
	//�{�X�̔���.
	m_pCGround->SetBossCommand(m_pCEnemyManager->GetEnemyInputDecision(m_pCEnemyManager->GetAllEnemySumMax() - 1, 0));
	
	//-------------�G-------------//.
	//�n�ʂ̃X�N���[�����x�ɍ��킹��.
	m_pCEnemyManager->SetSpeed(m_pCGround->GetMoveSpeed());
	
	//�v���C���[�ʒu���擾.
	m_pCEnemyManager->SetPlayerPos(m_pCPlayer->GetPosition());

	//�オ�鋗���擾.
	m_pCEnemyManager->SetUpDistance(m_pCGround->GetUpDistance());

	//�ړ������ƃL�����̈ʒu�����킹��.
	m_pCEnemyManager->SetMovingDistance(m_pCGround->GetMovingDistance());

	//�X�V�����֐�.
	m_pCEnemyManager->UpDate();

	//------------�R�}���h--------------//.
	for (int enemyType = 0; enemyType < static_cast<int>(enEnemy::Max); enemyType++) {
		for (int enemy = 0; enemy < m_pCEnemyManager->GetEnemyMax(enemyType); enemy++) {
			SetCommndDecision(enemyType, enemy);
		}
	}

	//----------------UI------------------//.
	m_pCUIManager->UpDate();
	for (int item = 0; item < static_cast<int>(enItemType::MAX); item++)
	{
		m_pCUIManager->SetItemCount(item, m_pCEnemyManager->GetItem_Sum(item));
	}
	m_pCUIManager->SetItemPointSum(m_pCEnemyManager->GetPoint_WholeSum());
	m_PointSum = m_pCEnemyManager->GetPoint_WholeSum();

	//------------ �G�t�F�N�g���� ------------//.
	m_pCEffectBase->UpDate();
}

//=====================================.
//		�`�揈���֐�.
//=====================================.
void CGameMain::Render()
{
	//�u������.
	m_mView = m_pCCameraManager->GetmView();	//�r���[�s��.
	m_vCamPos = m_pCCameraManager->GetvPos();	//�J�����ʒu.
	
	//------------�w�i------------//.
	m_pCBackGround->Render(m_mView, m_mProj, m_vLight, m_vCamPos);

	//------------�n��------------//.
	//�`��.
	m_pCGround->Value_Set(m_mView, m_mProj, m_vLight, m_vCamPos);
	m_pCGround->Render();

	//===============================.
	//	�G�t�F�N�g����.
	m_pCEffectBase->Render(m_mView, m_mProj, m_vCamPos);
	//===============================.

	//-------------�G-------------//.
	m_pCEnemyManager->Render(m_mView, m_mProj, m_vLight, m_vCamPos);

	//------------�v���C���[------------//.
	m_pCPlayer->Value_Set(m_mView, m_mProj, m_vLight, m_vCamPos);
	m_pCPlayer->Render();
	
	//----------UI------------//.
	m_pCUIManager->Render(m_mView, m_mProj, m_vCamPos);
	
}

//======================================.
//		��������֐�.
//======================================.
void CGameMain::Release()
{
	for (int enemyType = static_cast<int>(enEnemy::Max) - 1; enemyType >= 0; enemyType--) {
		SAFE_DELETE_ARRAY(m_ppbCheckSound[enemyType]);
	}
	SAFE_DELETE_ARRAY(m_ppbCheckSound);

	//����.
	SAFE_DELETE(m_pCEffectBase);

	//�N���X���.
	SAFE_DELETE(m_pCUIManager);			//CUIManager�N���X.
	SAFE_DELETE(m_CHit);				//CCollision�N���X.
	SAFE_DELETE(m_pCCameraManager);		//CCameraManager�N���X.
	SAFE_DELETE(m_pCGround);			//CGround�N���X.
	SAFE_DELETE(m_pCBackGround);		//BackGround�N���X.
	SAFE_DELETE(m_pCEnemyManager);		//CEnemyManager�N���X.
	SAFE_DELETE(m_pCPlayer);			//CPlayer�N���X.

}

//======================================.
//�R�}���h����ƃA�C�e���̓��������֐�.
//======================================.
void CGameMain::SetCommndDecision(int enemyType, int enemy)
{
	//=======================================.
	//		�ǉ�.
	//�G�̎�ނ��ƂɎn�܂�ԍ����v�Z.
	int EnemyMaxCnt = 0;
	if (enemyType - 1 >= 0) {
		for (int enemynum = 0; enemynum < enemyType; enemynum++) {
			EnemyMaxCnt += m_pCEnemyManager->GetEnemyMax(enemynum);
		}
	}

	//---�R�}���h�̔���---.
	if (enemyType != static_cast<int>(enEnemy::Kappa))
	{
		//	Switch�̕���ύX.
		//switch (m_pCCommandoManager->GetCommandDecision(enemyType, enemy, 0))
		enInput_Decision Decision = m_pCEnemyManager->GetEnemyInputDecision(enemy + EnemyMaxCnt, 0);
		switch (m_pCEnemyManager->GetEnemyInputDecision(enemy + EnemyMaxCnt, 0))
		{
		case enInput_Decision::Great://Great����.
		case enInput_Decision::Good://Good����.
			switch (enemyType)
			{
			case 0:
			case 1:
				m_pCEnemyManager->SetItem(enemyType, enemy, enItemJudge::Success);
				m_bEndGameMainFlag = false;
				break;
			case 3:
				m_pCEnemyManager->SetItem(enemyType, enemy, enItemJudge::Success);
				m_pCPlayer->Progress();
				m_bEndGameMainFlag = m_pCPlayer->GetEndFlag();;
				break;
			default:
				break;
			}
			break;
		case enInput_Decision::Bad:
			SetHit_Test(enemyType, enemy);
			if (enemyType == static_cast<int>(enEnemy::Big_RaccoonDog))
			{
				m_EndCount++;

				//============�ǉ�============================.
				//�v���C���[�̃A�j���[�V�������Z�b�g.
				m_pCPlayer->SetAnim(CPlayer::enPlyAct::Panic);
				//==============================================.

				if (m_EndCount > ITEM_BOUNCE_TIME) {
					for (int ItemType = 0; ItemType <= 3; ItemType++) {
						m_pCEnemyManager->SetItem(enemyType, enemy, enItemJudge::failure);
					}
				}
				if (m_EndCount > GAME_END_TIME) {
					m_bEndGameMainFlag = true;
				}
			}
			else
			{
				SetHit_Test(enemyType, enemy);
				m_bEndGameMainFlag = false;
			}
			break;
		default://Bad����,���̑�.
			SetHit_Test(enemyType, enemy);
			break;
		}
	}
	else
	{
		//������^�k�L.
		switch (m_pCEnemyManager->GetEnemyInputDecision(enemy + EnemyMaxCnt, 0))
		{
		case enInput_Decision::Great:
		case enInput_Decision::Good:
		case enInput_Decision::Bad:
			m_pCPlayer->SetLongCommand(true);
			break;
		default:
			break;
		}

		switch (m_pCEnemyManager->GetEnemyInputDecision(enemy + EnemyMaxCnt, 1))
		{
		case enInput_Decision::Great:
		case enInput_Decision::Good:
			m_pCEnemyManager->SetItem(enemyType, enemy, enItemJudge::Success);
			SetHit_Test_Jump(enemyType, enemy);
			if (m_pCPlayer->GetJunpEndFlag() == true) {
				m_pCPlayer->SetLongCommand(false);
			}
			break;
		case enInput_Decision::Bad:
			SetHit_Test(enemyType, enemy);
			m_pCPlayer->SetLongCommand(false);
			m_pCPlayer->SetOperation(true);
			break;
		default:
			SetHit_Test(enemyType, enemy);
			break;
		}
	}
}

//======================================.
//�����蔻�菈���֐�.
//======================================.
void CGameMain::SetHit_Test(int enemyType, int enemy)
{
	CCollision_Detection::stObjectInfo m_Player;
	CCollision_Detection::stObjectInfo* m_Enemy;
	m_Enemy = new CCollision_Detection::stObjectInfo[m_pCEnemyManager->GetEnemyMax(enemyType)];

	//���ݒ�.
	m_Player.Object = CCollision_Detection::enObject::Playre;
	m_Player.vPos = m_pCPlayer->GetPosition();

	switch (enemyType)
	{
	case 0:
		m_Enemy[enemy].Object = CCollision_Detection::enObject::Raccoon_Dog;
		break;
	case 1:
		m_Enemy[enemy].Object = CCollision_Detection::enObject::Cow_Ghost;
		break;
	case 2:
		m_Enemy[enemy].Object = CCollision_Detection::enObject::Kappa;
		break;
	default:
		m_Enemy[enemy].Object = CCollision_Detection::enObject::BigRccoon_Dog;
		break;
	}
	m_Enemy[enemy].vPos = m_pCEnemyManager->GetEnemyPos(enemyType, enemy);

	if (m_CHit->JugeHit(&m_Player, &m_Enemy[enemy]) == true)
	{
		if (m_HitCount == 0)
		{
			m_pCEnemyManager->SetItem(enemyType, enemy, enItemJudge::failure);

			//SE.
			if (m_ppbCheckSound[enemyType][enemy] == false) {
				CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Hit, true);

				m_ppbCheckSound[enemyType][enemy] = true;
				//�G�t�F�N�g.
				m_pCEffectBase->SetCenterPos(m_pCPlayer->GetPosition());
				m_pCEffectBase->SetEffectStart(true);
			}
		}
		m_HitCount++;
	}

	//���G����.
	if (m_HitCount != 0)
	{
		m_pCPlayer->Flashing(m_Count);
		m_Count++;
		if (m_Count > INVINCIBLETIME)
		{
			m_Count = 0;
			m_HitCount = 0;
		}
	}
	//�����蔻��͈̔͐ݒ�.
	m_CHit->SetScale(HIT_SCALE, CCollision_Detection::enObject::Playre);
	m_CHit->SetScale(HIT_SCALE, CCollision_Detection::enObject::Raccoon_Dog);
	m_CHit->SetScale(HIT_SCALE_COW, CCollision_Detection::enObject::Cow_Ghost);
	m_CHit->SetScale(HIT_SCALE, CCollision_Detection::enObject::Kappa);
	m_CHit->SetScale(HIT_SCALE, CCollision_Detection::enObject::BigRccoon_Dog);

	//�������.
	SAFE_DELETE(m_Enemy);
}

//======================================.
//	�W�����v�p�����蔻�菈���֐�.
//======================================.
void CGameMain::SetHit_Test_Jump(int enemyType, int enemy)
{
	CCollision_Detection::stObjectInfo m_Player;
	CCollision_Detection::stObjectInfo* m_Kappa;
	m_Kappa = new CCollision_Detection::stObjectInfo[m_pCEnemyManager->GetEnemyMax(enemyType)];

	//���ݒ�.
	m_Player.Object = CCollision_Detection::enObject::Playre;
	m_Player.vPos = m_pCPlayer->GetPosition();

	m_Kappa[enemy].Object = CCollision_Detection::enObject::Kappa;
	m_Kappa[enemy].vPos = m_pCEnemyManager->GetEnemyPos(enemyType, enemy);

	m_pCPlayer->SetEnemyPosition(m_Kappa[enemy].vPos);

	if (m_CHit->JugeHit(&m_Player, &m_Kappa[enemy]) == true)
	{
		if (m_pCPlayer->GetJumpFlag() == false) {
			CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Jump, true);
		}
		m_pCPlayer->SetJumpFlag(true);

	}

	//�����蔻��͈̔͐ݒ�.
	m_CHit->SetScale(0.5f, CCollision_Detection::enObject::Playre);
	m_CHit->SetScale(2.0f, CCollision_Detection::enObject::Kappa);

	//�������.
	SAFE_DELETE(m_Kappa);
}
