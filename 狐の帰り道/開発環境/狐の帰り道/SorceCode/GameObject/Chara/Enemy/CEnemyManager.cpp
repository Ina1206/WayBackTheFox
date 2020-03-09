#include <algorithm>
#include "CEnemyManager.h"

/***************************************************
*	�G�̊Ǘ��p�N���X.
**/
CEnemyManager::CEnemyManager()
	: m_pstNormalEnemyInfo		(nullptr)
	, m_ppCNormalEnemy			(nullptr)
	, m_pCBigRaccoon_Dog		(nullptr)
	, m_pEnemyMax				(nullptr)
	, m_AllNormalEnemyMax		(0)
	, m_AllEnemyMax				(0)
	, m_EnemyHit				(0)
	, m_pCommandMax				(nullptr)
	, m_ppenInputDecision		(nullptr)
	, m_penInputDecision		(nullptr)
	, m_pbDecisionPossible		(nullptr)
	, m_eninputInformation		(enCommandType::Max)
	, m_enOldInputInformation	(enCommandType::Max)
	, m_LongPushCnt				(0)
	, m_pButtonNum				(nullptr)
	, m_fMoveSpeed				(0.0f)
	, m_fMovingDistance			(0.0f)
	, m_fUpDistance				(0.0f)
	, m_bDecelerationStart		(false)
	, m_bMoveFlag				(false)
	, m_vPlayerPos				(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_pCFileManager			(nullptr)
	, m_pCInput					(nullptr)
	, m_bMoveUpCamera			(false)
	, m_Point_WholeSum(0)
	, m_VegetablesSum(0)
	, m_VegetablesPoint(0)
	, m_MeatSum(0)
	, m_MeatPoint(0)
	, m_FishSum(0)
	, m_FishPoint(0)
	, m_RiceSum(0)
	, m_RicePoint(0)
	, m_bCheckItem_Point(false)
	, m_bCheckItem_Number(false)

	, m_OldenJudge(nullptr)
{
}

CEnemyManager::~CEnemyManager()
{
	//�������.
	Release();
}

//========================================.
//		�����������֐�.
//========================================.
void CEnemyManager::InitProcess()
{
	//�t�@�C��.
	m_pCFileManager = CFileLoadManager::GetCFileLoadManagerInstance();

	//====================�G�̗񋓑�====================//.
	const enEnemy m_enRaccoonDog	= enEnemy::RaccoonDog;		
	const enEnemy m_enKappa			= enEnemy::Kappa;			
	const enEnemy m_enCowGhost		= enEnemy::Cow_Ghost;		

	//=====================�G�̔ԍ�======================//.
	const int RaccoonDogNum = static_cast<int>(m_enRaccoonDog);	
	const int KappaNum		= static_cast<int>(m_enKappa);		
	const int COW_GHOST		= static_cast<int>(m_enCowGhost);	

	//�z�񓮓I�m��.
	m_pstNormalEnemyInfo	= new stNormalEnemyInfo[static_cast<int>(enEnemy::NormalEnemyMax)]();	//�G���Ƃ̏��.
	m_pEnemyMax				= new int[ENEMY_MAX]();													//�G�̍ő吔.
	m_pCommandMax			= new int[ENEMY_MAX]();													//�R�}���h�̍ő吔.

	//�t�@�C������̏��擾.
	for (int enemyType = 0; enemyType < ENEMY_MAX; enemyType++) {
		//�G�̍ő�l.
		m_pEnemyMax[enemyType] = m_pCFileManager->GetEnemyMax(enemyType);
		
		//�R�}���h�̍ő�l.
		m_pCommandMax[enemyType] = m_pCFileManager->GetEnemyMax(enemyType);
	}

	//�f�J�^�k�L�͐��1�C�ɌŒ�.
	m_pEnemyMax[static_cast<int>(enEnemy::Big_RaccoonDog)] = 1;

	//�ʏ�G�̑����v�v�Z.
	for (int enemyType = 0; enemyType < NORMAL_ENEMY_MAX; enemyType++) {
		m_AllNormalEnemyMax += m_pEnemyMax[enemyType];
	}
	//�S�Ă̓G�̑����v�v�Z.
	m_AllEnemyMax = m_AllNormalEnemyMax + m_pEnemyMax[static_cast<int>(enEnemy::Big_RaccoonDog)];

	//�ʏ�G�̃N���X�̔z�񓮓I�m��.
	m_ppCNormalEnemy = new CNormalEnemyBase*[m_AllNormalEnemyMax]();

	//�R�}���h�n�̓��I�m��.
	m_penInputDecision		= new enInput_Decision[m_AllEnemyMax]();		
	m_pbDecisionPossible	= new bool[m_AllEnemyMax]();					
	m_ppenInputDecision		= new enInput_Decision*[m_AllEnemyMax]();
	m_pButtonNum			= new int[m_pCFileManager->GetAllEnemyMax()]();

	//�{�^���ԍ��擾.
	for (int button = 0; button < m_pCFileManager->GetAllEnemyMax(); button++) {
		m_pButtonNum[button] = m_pCFileManager->GetButtonNum(button) - 1;
	}

	//�R�}���h�n�̏�����.
	for (int enemy = 0; enemy < m_AllEnemyMax; enemy++) {

		//�{�X�̃R�}���h���茋��.
		m_penInputDecision[enemy] = enInput_Decision::Max;
		//�R�}���h����\�t���O.
		if (enemy < m_AllNormalEnemyMax) {
			m_pbDecisionPossible[enemy] = false;
		}

		m_ppenInputDecision[enemy] = new enInput_Decision[COMMAND_DECISION_MAX]();
		
		//�ʏ�G�̃R�}���h���茋��.
		for (int command = 0; command < COMMAND_DECISION_MAX; command++) {
			m_ppenInputDecision[enemy][command] = enInput_Decision::Max;
		}
	}
	
	//�A�C�e���̓��I�m��.
	m_pCItemManager = new CItemManager[m_AllEnemyMax];
	m_OldenJudge = new enItemJudge[m_AllEnemyMax];
	//�A�C�e���̏�����.
	for (int enemy = 0; enemy < m_AllEnemyMax; enemy++) {
		m_pCItemManager[enemy].Init_Process();
		m_OldenJudge[enemy] = enItemJudge::Max;
	}

	//�G���Ƃ̃N���X�쐬.
	int EnemyMax = 0;
	//=============================�^�k�L==================================//.
	for (int enemy = 0; enemy < m_pEnemyMax[RaccoonDogNum]; enemy++) {
		m_ppCNormalEnemy[enemy] = new CRaccoon_Dog();
		//�A�C�e���̐ݒ�.
		m_pCItemManager[enemy].SetEnemyType(enEnemy::RaccoonDog);

	}
	//���̓G�̊J�n�ԍ�.
	EnemyMax += m_pEnemyMax[RaccoonDogNum];

	//============================��������==================================//.
	for (int enemy = EnemyMax; enemy < m_pEnemyMax[COW_GHOST] + EnemyMax; enemy++) {
		m_ppCNormalEnemy[enemy] = new CCow_Ghost();
		//�A�C�e���̐ݒ�.
		m_pCItemManager[enemy].SetEnemyType(enEnemy::Cow_Ghost);
	}
	//���̓G�̊J�n�ԍ�.
	EnemyMax += m_pEnemyMax[COW_GHOST];

	//============================�オ��K==================================//.
	for (int enemy = EnemyMax; enemy < m_pEnemyMax[KappaNum] + EnemyMax; enemy++) {
		m_ppCNormalEnemy[enemy] = new CUpRaccoonDog();
		//�A�C�e���̐ݒ�.
		m_pCItemManager[enemy].SetEnemyType(enEnemy::Kappa);
	}
	//���̓G�̊J�n�ԍ�.
	EnemyMax += m_pEnemyMax[KappaNum];
	
	for (int enemy = 0; enemy < m_AllNormalEnemyMax; enemy++) {
		//�����ʒu�ݒ�.
		m_ppCNormalEnemy[enemy]->SetInitPosition(m_pCFileManager->GetEnemyPos(enemy));
		//�{�^���ԍ�.
		m_ppCNormalEnemy[enemy]->SetButtonNum(m_pButtonNum[enemy]);
		//�G�̏�����.
		m_ppCNormalEnemy[enemy]->InitProcess();
	}

	//==============================�f�J�^�k�L================================//
	m_pCBigRaccoon_Dog = new CBig_Raccoon_Dog();

	//�{�X�̏����ʒu�ݒ�.
	m_pCBigRaccoon_Dog->SetInitPosition(m_pCFileManager->GetEnemyPos(EnemyMax + 1));
	//�R�}���h�{�^���ݒ�.
	for (int button = 0; button < 3; button++) {
		m_pCBigRaccoon_Dog->SetButtonNum(m_pButtonNum[EnemyMax + button], button);
	}

	//�{�X�̏����������֐�.
	m_pCBigRaccoon_Dog->InitProcess();

	//�A�C�e���̐ݒ�.
	int Boss_Num = m_AllEnemyMax - 1;
	m_pCItemManager[Boss_Num].SetEnemyType(enEnemy::Big_RaccoonDog);


	//�G�̓��������񐔓��I�m��.
	m_EnemyHit = 0;

	//�R���g���[���N���X.
	m_pCInput = new clsXInput();

}

//========================================.
//		�X�V�����֐�.
//========================================.
void CEnemyManager::Update()
{
	//�R�}���h���͏����֐�.
	CheckCommandLongPush();

	//�ʏ�G�̍X�V�����֐�.
	NormalEnemyUpDate();

	//�A�C�e���̍X�V�����֐�.
	ItemUpDate();

	//�{�X�̍X�V�����֐�.
	BossUpDate();
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CEnemyManager::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos)
{
	//=========================�G================================//.
	//�\�����邩�ǂ���.
	if (m_pCBigRaccoon_Dog->GetDispFlag() == true) {
		//�`��.
		m_pCBigRaccoon_Dog->Value_Set(mView, mProj, vLight, vCameraPos);
		m_pCBigRaccoon_Dog->Render();
	}

	for (int enemy = m_AllNormalEnemyMax - 1; enemy >= 0; enemy--) {
		if (m_ppCNormalEnemy[enemy]->GetDispFlag() == true && 
			m_pCBigRaccoon_Dog->GetInputDecision() == enInput_Decision::Max) {
			//�`��̂��߂̒l���擾.
			m_ppCNormalEnemy[enemy]->Value_Set(mView, mProj, vLight, vCameraPos);
			//�`��.
			m_ppCNormalEnemy[enemy]->Render();
		}
	}

	//=========================�A�C�e��================================//.
	for (int item = 0; item < m_AllEnemyMax; item++)
	{
		m_pCItemManager[item].Render(mView, mProj, vCameraPos);
	}

}

//========================================.
//		��������֐�.
//========================================.
void CEnemyManager::Release()
{
	//�G�̎�ނ̍ő吔.
	const int m_EnemyMax = ENEMY_MAX - 1;
	
	//�`�N���X����`.
	SAFE_DELETE_ARRAY(m_pCItemManager);
	SAFE_DELETE(m_pCInput);
	m_pCBigRaccoon_Dog->Release();
	SAFE_DELETE(m_pCBigRaccoon_Dog);
	for (int enemy = m_AllNormalEnemyMax - 1; enemy >= 0; enemy--) {
		m_ppCNormalEnemy[enemy]->Release();
		SAFE_DELETE(m_ppCNormalEnemy[enemy]);
	}

	//�`�z�����`.
	SAFE_DELETE_ARRAY(m_OldenJudge);
	SAFE_DELETE_ARRAY(m_pButtonNum);
	SAFE_DELETE_ARRAY(m_ppCNormalEnemy);
	SAFE_DELETE_ARRAY(m_pbDecisionPossible);
	for (int enemy = m_AllEnemyMax - 1; enemy >= 0; enemy--) {
		SAFE_DELETE_ARRAY(m_ppenInputDecision[enemy]);
	}
	SAFE_DELETE_ARRAY(m_ppenInputDecision);
	SAFE_DELETE_ARRAY(m_penInputDecision);	
	SAFE_DELETE_ARRAY(m_pCommandMax);		
	SAFE_DELETE_ARRAY(m_pEnemyMax);			
	SAFE_DELETE_ARRAY(m_pstNormalEnemyInfo);
}

//======================================.
//		�G�̍��W�擾�����֐�.
//======================================.
D3DXVECTOR3 CEnemyManager::GetEnemyPos(int enemyType, int enemy)
{
	if (enemyType == static_cast<int>(enEnemy::Big_RaccoonDog)) {
		return m_pCBigRaccoon_Dog->GetPostion();
	}

	//�ړI�̓G�܂ł̑��̓G�̍��v�v�Z.
	int enemyMax = 0;
	if (enemyType >= 1) {
		for (int typeNum = 0; typeNum < enemyType; typeNum++) {
			enemyMax += m_pEnemyMax[typeNum];
		}
	}
	return m_ppCNormalEnemy[enemyMax + enemy]->GetPostion();

}

//=========================================.
//		�ʏ�G�̍X�V�����֐�.
//=========================================.
void CEnemyManager::NormalEnemyUpDate()
{
	//�R�}���h����\�����֐�.
	Command_Possible();


	for (int enemy = 0; enemy < m_AllNormalEnemyMax; enemy++) {

		//�\�����菈��.
		m_ppCNormalEnemy[enemy]->DecisionDisp();

		//�n�ʂ̃X�N���[�����x�ɍ��킹��.
		m_ppCNormalEnemy[enemy]->SetSpeed(m_fMoveSpeed);
		m_ppCNormalEnemy[enemy]->FitMoveGround();

		//�v���C���[�ʒu���擾.
		m_ppCNormalEnemy[enemy]->SetPlayerPos(m_vPlayerPos);

		//�\�����Ă���ꍇ�̂ݏ���.
		if (m_ppCNormalEnemy[enemy]->GetDispFlag() == true) {
			//����\�t���O�̎擾�����֐�.
			m_ppCNormalEnemy[enemy]->SetJudgePossible(m_pbDecisionPossible[enemy]);

			//�������J�E���g�擾�����֐�.
			m_ppCNormalEnemy[enemy]->SetLongPushCnt(m_LongPushCnt);

			//���̓{�^�����擾�����֐�.
			m_ppCNormalEnemy[enemy]->SetCommandType(m_eninputInformation);
			
			//�G�̓��������񐔂̒l�ݒ�.
			m_ppCNormalEnemy[enemy]->SetHitNum(m_EnemyHit);

			//�X�V�����֐�.
			m_ppCNormalEnemy[enemy]->Update();

			//�R�}���h���茋�ʎ擾.
			for (int command = 0; command < COMMAND_DECISION_MAX; command++) {
				m_ppenInputDecision[enemy][command] = m_ppCNormalEnemy[enemy]->GetInputDecision(command);
			}

			//�G�̓��������񐔂̒l���Ƃ�.
			m_EnemyHit = m_ppCNormalEnemy[enemy]->GetHitNum();
		}
	}

}

//============================================.
//		�{�X�X�V�����֐�.
//============================================.
void CEnemyManager::BossUpDate()
{
	//�\�����菈��.
	m_pCBigRaccoon_Dog->DecisionDisp();

	//�n�ʂ̃X�N���[�����x�ɍ��킹��.
	m_pCBigRaccoon_Dog->SetSpeed(m_fMoveSpeed);
	m_pCBigRaccoon_Dog->FitMoveGround();

	//�v���C���[�ʒu���擾.
	m_pCBigRaccoon_Dog->SetPlayerPos(m_vPlayerPos);

	//�\�����Ă���ꍇ�̂ݏ���.
	if (m_pCBigRaccoon_Dog->GetDispFlag() == true) {
		//�������J�E���g�擾�����֐�.
		m_pCBigRaccoon_Dog->SetLongPushCnt(m_LongPushCnt);

		//���̓{�^�����擾�����֐�.
		m_pCBigRaccoon_Dog->SetCommandType(m_eninputInformation);
		
		//�R�}���h���茋�ʎ擾.
		int BossNum = m_AllEnemyMax - 1;
		m_pCBigRaccoon_Dog->SetInputDecision(m_penInputDecision[BossNum]);
		m_penInputDecision[BossNum] = m_pCBigRaccoon_Dog->GetInputDecision();

		//�h��Ă���Ƃ��̏㉺�̋������擾.
		m_pCBigRaccoon_Dog->SetUpDistance(m_fUpDistance);

		//�X�V�����֐�.
		m_pCBigRaccoon_Dog->Update();
	}


	//�{�X��O�̌�������.
	D3DXVECTOR3 m_vBossPos = m_pCBigRaccoon_Dog->GetPostion();
	if (m_vPlayerPos.z + DECELERATION_DISTANCE >= m_vBossPos.z) {
		m_bDecelerationStart = true;
		//�A�C�e���̃{�X�t���O�𗧂Ă�.
		const int BossNum = m_AllEnemyMax - 1;
		m_pCItemManager[BossNum].SetBossFlag(true);
	}
	//�s���t���O.
	m_pCBigRaccoon_Dog->SetMove(m_bMoveFlag);
}

//==========================================.
//		�R�}���h����\�����֐�.
//==========================================.
void CEnemyManager::Command_Possible()
{
	//���肷��G�̍��W.
	D3DXVECTOR3 m_vDecisionEnemyPos;
	D3DXVECTOR3 m_vDecisionTargetPos;
	int			tmp = -1;


	//��ŕҏW.
	for (int enemy = 0; enemy < m_AllNormalEnemyMax; enemy++) {
		m_pbDecisionPossible[enemy] = false;
		
		//���W�擾.
		m_vDecisionEnemyPos = m_ppCNormalEnemy[enemy]->GetPostion();

		//Player�ɓ����邮�炢�߂������画�肩��O��.
		if (m_vDecisionEnemyPos.z <= m_vPlayerPos.z + DECISION_END_BACK) {
			continue;
		}

		//�͈͓�.
		if (m_vDecisionEnemyPos.x >= m_vPlayerPos.x - DECISION_START_WIDTH &&
			m_vDecisionEnemyPos.x <= m_vPlayerPos.x + DECISION_START_WIDTH) {

			//tmp�̉��擾.
			if (tmp < 0) {
				tmp = enemy;
			}
			//��ׂ鑊��.
			m_vDecisionTargetPos = m_ppCNormalEnemy[tmp]->GetPostion();
			
			//��ׂ鑊����Player�Ƃ̋��������������������ւ�.
			if (fabsf(m_vDecisionEnemyPos.z - m_vPlayerPos.z) < fabsf(m_vDecisionTargetPos.z - m_vPlayerPos.z)) {
				tmp = enemy;
			}			

		}
	}

	//tmp == -1�̗\�h.
	if (tmp >= 0) {
		//��ԋ߂������L�����̔���\�t���O.
		m_pbDecisionPossible[tmp] = true;
	}
}

//=====================================.
//		�R�}���h���͏����֐�.
//=====================================.
HRESULT CEnemyManager::Command_Entry()
{
	m_pCInput->UpdateStatus();//�������Ȃ��Ɠ����Ȃ�.

	enCommandType m_enTmpCommandType = enCommandType::Max;

	//A�{�^��.
	if (m_pCInput->IsPress(XINPUT_GAMEPAD_A)) {
		m_enTmpCommandType = enCommandType::A;
	}

	//B�{�^��.
	if (m_pCInput->IsPress(XINPUT_GAMEPAD_B)) {
		m_enTmpCommandType = enCommandType::B;
	}

	//X�{�^��.
	if (m_pCInput->IsPress(XINPUT_GAMEPAD_X)) {
		m_enTmpCommandType = enCommandType::X;
	}

	//Y�{�^��.
	if (m_pCInput->IsPress(XINPUT_GAMEPAD_Y)) {
		m_enTmpCommandType = enCommandType::Y;
	}

#ifdef _DEBUG

	//A�{�^��.
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_enTmpCommandType = enCommandType::A;
	}

	//B�{�^��.
	if (GetAsyncKeyState('W') & 0x8000) {
		m_enTmpCommandType = enCommandType::B;
	}

	//X�{�^��.
	if (GetAsyncKeyState('E') & 0x8000) {
		m_enTmpCommandType = enCommandType::X;
	}

	//Y�{�^��.
	if (GetAsyncKeyState('R') & 0x8000) {
		m_enTmpCommandType = enCommandType::Y;
	}
#endif	//#ifdef _DEBUG.

	//�{�^�����������΍�.
	if (m_eninputInformation == enCommandType::Max || 
		m_enTmpCommandType == enCommandType::Max ||
		m_enTmpCommandType == m_eninputInformation) {
		m_eninputInformation = m_enTmpCommandType;
	}

	return S_OK;
}

//==================================.
//	�R�}���h�������m�F�����֐�.
//==================================.
void CEnemyManager::CheckCommandLongPush()
{
	Command_Entry();


	const int Max = 10000;	//�������̗ʍő吔.

	if (m_eninputInformation == m_enOldInputInformation) {
		m_LongPushCnt++;
		if (m_LongPushCnt >= Max) {
			m_LongPushCnt = 1;
		}
	}
	else {
		m_LongPushCnt = 0;
	}

	m_enOldInputInformation = m_eninputInformation;

}

//==================================.
//	�R�}���h����.
//==================================.
enInput_Decision CEnemyManager::GetEnemyInputDecision(int enemy, int num) 
{
	if (enemy >= m_AllEnemyMax - 1) {
		return m_penInputDecision[enemy];
	}

	return m_ppenInputDecision[enemy][num]; 
}

//==================================.
//	�J�����̏オ�邩�̔��菈���֐�.
//==================================.
bool CEnemyManager::JudgeCameraUp()
{
	const int StartEnemyNum = m_pEnemyMax[static_cast<int>(enEnemy::RaccoonDog)] + m_pEnemyMax[static_cast<int>(enEnemy::Cow_Ghost)];
	D3DXVECTOR3 m_vPos;

	for (int enemy = StartEnemyNum; enemy < m_AllNormalEnemyMax; enemy++) {
		m_vPos = m_ppCNormalEnemy[enemy]->GetPostion();
		//�G�L���������̈ʒu�܂ŗ���.
		if (m_vPlayerPos.z + 10.0f > m_vPos.z) {
			//���߂̂Ƃ���ł̔��肪�s��ꂽ��J�����ړ�.
			if (m_ppCNormalEnemy[enemy]->GetInputDecision(0) != enInput_Decision::Max) {
				m_bMoveUpCamera = true;
			}
			//�Ō�̔��肪�s��ꂽ��J�����߂�ړ�.
			if (m_ppCNormalEnemy[enemy]->GetInputDecision(1) != enInput_Decision::Max) {
				m_bMoveUpCamera = false;
			}
		}

	}
	return false;
}

//======================================.
//		�A�C�e���̐ݒ菈���֐�.
//======================================.
void CEnemyManager::SetItem(int enemyType, int num, enItemJudge enJudge)
{
	int enemyMax = 0;
	if (enemyType >= 1) {
		for (int typeNum = 0; typeNum < enemyType; typeNum++) {
			enemyMax += m_pEnemyMax[typeNum];
		}
	}

	m_pCItemManager[enemyMax + num].SetItemJudge(enJudge);
	m_pCItemManager[enemyMax + num].SetDispFlag(true);
}


//============================================.
//		�A�C�e���̍X�V�����֐�.
//============================================.
void CEnemyManager::ItemUpDate()
{
	int BossNum = m_AllEnemyMax - 1;
	const int ITEM_MAX = static_cast<int>(enItemType::MAX);

	for (int item = 0; item < m_AllNormalEnemyMax; item++)
	{
		//�e�G�̈ʒu���擾.
		m_pCItemManager[item].SetInitPosition(m_ppCNormalEnemy[item]->GetPostion());
	}
	//�{�X�̈ʒu���擾.
	m_pCItemManager[BossNum].SetInitPosition(m_pCBigRaccoon_Dog->GetPostion());

	const int Enemy = m_pEnemyMax[static_cast<int>(enEnemy::Cow_Ghost)] + m_pEnemyMax[static_cast<int>(enEnemy::RaccoonDog)];
	for (int item = 0; item < m_AllEnemyMax; item++)
	{
		//�A�C�e���̍��v���擾.
		for (int itemType = 0; itemType < ITEM_MAX; itemType++)
		{
			m_pCItemManager[item].SetItemSum(itemType, GetItem_Sum(itemType));
			//�R�}���h���茋�ʂ��擾.
			if (item >= Enemy && item < Enemy + m_pEnemyMax[static_cast<int>(enEnemy::Kappa)])
			{
				//�J�b�p�̂ݕʔ���.
				m_pCItemManager[item].SetInput_Decision(GetEnemyInputDecision(item, 1));
			}
			else 
			{
				m_pCItemManager[item].SetInput_Decision(GetEnemyInputDecision(item));
			}

		}


		//�v���C���[�ʒu���擾.
		m_pCItemManager[item].SetPlayerPosition(m_vPlayerPos);
		//�X�V�����֐�.
		m_pCItemManager[item].UpDate();

		if (m_OldenJudge[item] != m_pCItemManager[item].GetItemJudge())
		{
			Point_WholeSum(item);
		}
		Item_WholeSum(item);
	}
}

//========================================.
//		�|�C���g���v�̌v�Z�����֐�.
//========================================.
void CEnemyManager::Point_WholeSum(int item)
{
	m_bCheckItem_Point = false;

	if (m_pCItemManager[item].GetItemJudge() == enItemJudge::Success)
	{
		switch (m_pCItemManager[item].GetEnemyType())
		{
		case enEnemy::RaccoonDog:
			//�^�k�L�p�A�C�e��.
			m_VegetablesPoint += m_pCItemManager[item].GetPointSum(0);
			break;
		case enEnemy::Cow_Ghost:
			//���������A�C�e��.
			m_MeatPoint += m_pCItemManager[item].GetPointSum(1);
			break;
		case enEnemy::Kappa:
			//�J�b�p�p�A�C�e���N���X.
			m_FishPoint += m_pCItemManager[item].GetPointSum(2);
			break;
		case enEnemy::Big_RaccoonDog:
			//�f�J�^�k�L�p�A�C�e���N���X.
			m_RicePoint += m_pCItemManager[item].GetPointSum(3);
			break;
		default:
			break;
		}
	}
	else if (m_pCItemManager[item].GetItemJudge() == enItemJudge::failure) {
		switch (m_pCItemManager[item].GetEnemyType())
		{
		case enEnemy::RaccoonDog:
			//�^�k�L�p�A�C�e��.
			m_VegetablesPoint -= m_pCItemManager[item].GetPointSum(0);
			if (m_VegetablesPoint < 0) { m_VegetablesPoint = 0; }
			break;
		case enEnemy::Cow_Ghost:
			//���������A�C�e��.
			m_MeatPoint -= m_pCItemManager[item].GetPointSum(1);
			if (m_MeatPoint < 0) { m_MeatPoint = 0; }
			break;
		case enEnemy::Kappa:
			//�J�b�p�p�A�C�e���N���X.
			m_FishPoint -= m_pCItemManager[item].GetPointSum(2);
			if (m_FishPoint < 0) { m_FishPoint = 0; }
			break;
		case enEnemy::Big_RaccoonDog:
			//�f�J�^�k�L�p�A�C�e���N���X.
			if (m_bCheckItem_Point == false) {
				m_VegetablesPoint -= m_pCItemManager[item].GetPointSum(0);
				m_MeatPoint -= m_pCItemManager[item].GetPointSum(1);
				m_FishPoint -= m_pCItemManager[item].GetPointSum(2);
				if (m_VegetablesPoint < 0) { m_VegetablesPoint = 0; }
				if (m_MeatPoint < 0) { m_MeatPoint = 0; }
				if (m_FishPoint < 0) { m_FishPoint = 0; }

				m_bCheckItem_Point = true;
			}
			break;
		default:
			break;
		}
	}

	//�|�C���g���v.
	m_Point_WholeSum = m_MeatPoint + m_FishPoint + m_VegetablesPoint + m_RicePoint;
	m_OldenJudge[item] = m_pCItemManager[item].GetItemJudge();

}

//===================================.
//	�A�C�e���̐��`�揈���֐�.
//===================================.
void CEnemyManager::Item_WholeSum(int item)
{
	int m_OldVegetablesSum = 0;
	int m_OldMeatSum = 0;
	int m_OldFishSum = 0;
	int m_OldRiceSum = 0;

	for (int num = 0; num <= item; num++)
	{
		if (m_pCItemManager[num].GetItemJudge() == enItemJudge::Success)
		{
			switch (m_pCItemManager[num].GetEnemyType())
			{
			case enEnemy::RaccoonDog:
				//�^�k�L�p�A�C�e��.
				m_OldVegetablesSum += m_pCItemManager[num].GetCollitionNum(0);
				break;

			case enEnemy::Cow_Ghost:
				//���������A�C�e��.
				m_OldMeatSum += m_pCItemManager[num].GetCollitionNum(1);
				break;
			case enEnemy::Kappa:
				//�J�b�p�p�A�C�e���N���X.
				m_OldFishSum += m_pCItemManager[num].GetCollitionNum(2);
				break;
			case enEnemy::Big_RaccoonDog:
				//�f�J�^�k�L�p�A�C�e���N���X.
				m_OldRiceSum += m_pCItemManager[num].GetCollitionNum(3);
				break;
			default:
				break;
			}
			if (m_VegetablesSum < m_OldVegetablesSum) {
				m_VegetablesSum = m_OldVegetablesSum;
			}
			if (m_MeatSum < m_OldMeatSum) {
				m_MeatSum = m_OldMeatSum;
			}
			if (m_FishSum < m_OldFishSum) {
				m_FishSum = m_OldFishSum;
			}
			if (m_RiceSum < m_OldRiceSum) {
				m_RiceSum = m_OldRiceSum;
			}
		}
		else if (m_pCItemManager[num].GetItemJudge() == enItemJudge::failure) {
			switch (m_pCItemManager[num].GetEnemyType())
			{
			case enEnemy::RaccoonDog:
				//�^�k�L�p�A�C�e��.
				m_OldVegetablesSum -= m_pCItemManager[num].GetDropNum(0);
				break;
			case enEnemy::Cow_Ghost:
				//���������A�C�e��.
				m_OldMeatSum -= m_pCItemManager[num].GetDropNum(1);
				break;
			case enEnemy::Kappa:
				//�J�b�p�p�A�C�e���N���X.
				m_OldFishSum -= m_pCItemManager[num].GetDropNum(2);
				break;
			case enEnemy::Big_RaccoonDog:
				//�f�J�^�k�L�p�A�C�e���N���X.
				m_OldVegetablesSum -= m_pCItemManager[num].GetDropNum(0);
				m_OldMeatSum -= m_pCItemManager[num].GetDropNum(1);
				m_OldFishSum -= m_pCItemManager[num].GetDropNum(2);
				break;
			default:
				break;
			}
			if (m_VegetablesSum > m_OldVegetablesSum) {
				m_VegetablesSum = m_OldVegetablesSum;
			}
			if (m_MeatSum > m_OldMeatSum) {
				m_MeatSum = m_OldMeatSum;
			}
			if (m_FishSum > m_OldFishSum) {
				m_FishSum = m_OldFishSum;
			}
			if (m_VegetablesSum < 0) { m_VegetablesSum = 0; }
			if (m_MeatSum < 0) { m_MeatSum = 0; }
			if (m_FishSum < 0) { m_FishSum = 0; }
		}
	}
}

//========================================.
//		�A�C�e���̍��v�����֐�.
//========================================.
int CEnemyManager::GetItem_Sum(int enItem)
{
	switch (enItem)
	{
	case 0:
		return m_VegetablesSum;
		break;
	case 1:
		return m_MeatSum;
		break;
	case 2:
		return m_FishSum;
		break;
	case 3:
		return m_RiceSum;
		break;
	default:
		break;
	}
}
