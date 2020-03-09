#include <algorithm>
#include "CEnemyManager.h"

/***************************************************
*	敵の管理用クラス.
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
	//解放処理.
	Release();
}

//========================================.
//		初期化処理関数.
//========================================.
void CEnemyManager::InitProcess()
{
	//ファイル.
	m_pCFileManager = CFileLoadManager::GetCFileLoadManagerInstance();

	//====================敵の列挙体====================//.
	const enEnemy m_enRaccoonDog	= enEnemy::RaccoonDog;		
	const enEnemy m_enKappa			= enEnemy::Kappa;			
	const enEnemy m_enCowGhost		= enEnemy::Cow_Ghost;		

	//=====================敵の番号======================//.
	const int RaccoonDogNum = static_cast<int>(m_enRaccoonDog);	
	const int KappaNum		= static_cast<int>(m_enKappa);		
	const int COW_GHOST		= static_cast<int>(m_enCowGhost);	

	//配列動的確保.
	m_pstNormalEnemyInfo	= new stNormalEnemyInfo[static_cast<int>(enEnemy::NormalEnemyMax)]();	//敵ごとの情報.
	m_pEnemyMax				= new int[ENEMY_MAX]();													//敵の最大数.
	m_pCommandMax			= new int[ENEMY_MAX]();													//コマンドの最大数.

	//ファイルからの情報取得.
	for (int enemyType = 0; enemyType < ENEMY_MAX; enemyType++) {
		//敵の最大値.
		m_pEnemyMax[enemyType] = m_pCFileManager->GetEnemyMax(enemyType);
		
		//コマンドの最大値.
		m_pCommandMax[enemyType] = m_pCFileManager->GetEnemyMax(enemyType);
	}

	//デカタヌキは絶対1匹に固定.
	m_pEnemyMax[static_cast<int>(enEnemy::Big_RaccoonDog)] = 1;

	//通常敵の総合計計算.
	for (int enemyType = 0; enemyType < NORMAL_ENEMY_MAX; enemyType++) {
		m_AllNormalEnemyMax += m_pEnemyMax[enemyType];
	}
	//全ての敵の総合計計算.
	m_AllEnemyMax = m_AllNormalEnemyMax + m_pEnemyMax[static_cast<int>(enEnemy::Big_RaccoonDog)];

	//通常敵のクラスの配列動的確保.
	m_ppCNormalEnemy = new CNormalEnemyBase*[m_AllNormalEnemyMax]();

	//コマンド系の動的確保.
	m_penInputDecision		= new enInput_Decision[m_AllEnemyMax]();		
	m_pbDecisionPossible	= new bool[m_AllEnemyMax]();					
	m_ppenInputDecision		= new enInput_Decision*[m_AllEnemyMax]();
	m_pButtonNum			= new int[m_pCFileManager->GetAllEnemyMax()]();

	//ボタン番号取得.
	for (int button = 0; button < m_pCFileManager->GetAllEnemyMax(); button++) {
		m_pButtonNum[button] = m_pCFileManager->GetButtonNum(button) - 1;
	}

	//コマンド系の初期化.
	for (int enemy = 0; enemy < m_AllEnemyMax; enemy++) {

		//ボスのコマンド判定結果.
		m_penInputDecision[enemy] = enInput_Decision::Max;
		//コマンド判定可能フラグ.
		if (enemy < m_AllNormalEnemyMax) {
			m_pbDecisionPossible[enemy] = false;
		}

		m_ppenInputDecision[enemy] = new enInput_Decision[COMMAND_DECISION_MAX]();
		
		//通常敵のコマンド判定結果.
		for (int command = 0; command < COMMAND_DECISION_MAX; command++) {
			m_ppenInputDecision[enemy][command] = enInput_Decision::Max;
		}
	}
	
	//アイテムの動的確保.
	m_pCItemManager = new CItemManager[m_AllEnemyMax];
	m_OldenJudge = new enItemJudge[m_AllEnemyMax];
	//アイテムの初期化.
	for (int enemy = 0; enemy < m_AllEnemyMax; enemy++) {
		m_pCItemManager[enemy].Init_Process();
		m_OldenJudge[enemy] = enItemJudge::Max;
	}

	//敵ごとのクラス作成.
	int EnemyMax = 0;
	//=============================タヌキ==================================//.
	for (int enemy = 0; enemy < m_pEnemyMax[RaccoonDogNum]; enemy++) {
		m_ppCNormalEnemy[enemy] = new CRaccoon_Dog();
		//アイテムの設定.
		m_pCItemManager[enemy].SetEnemyType(enEnemy::RaccoonDog);

	}
	//次の敵の開始番号.
	EnemyMax += m_pEnemyMax[RaccoonDogNum];

	//============================牛お化け==================================//.
	for (int enemy = EnemyMax; enemy < m_pEnemyMax[COW_GHOST] + EnemyMax; enemy++) {
		m_ppCNormalEnemy[enemy] = new CCow_Ghost();
		//アイテムの設定.
		m_pCItemManager[enemy].SetEnemyType(enEnemy::Cow_Ghost);
	}
	//次の敵の開始番号.
	EnemyMax += m_pEnemyMax[COW_GHOST];

	//============================上がる狸==================================//.
	for (int enemy = EnemyMax; enemy < m_pEnemyMax[KappaNum] + EnemyMax; enemy++) {
		m_ppCNormalEnemy[enemy] = new CUpRaccoonDog();
		//アイテムの設定.
		m_pCItemManager[enemy].SetEnemyType(enEnemy::Kappa);
	}
	//次の敵の開始番号.
	EnemyMax += m_pEnemyMax[KappaNum];
	
	for (int enemy = 0; enemy < m_AllNormalEnemyMax; enemy++) {
		//初期位置設定.
		m_ppCNormalEnemy[enemy]->SetInitPosition(m_pCFileManager->GetEnemyPos(enemy));
		//ボタン番号.
		m_ppCNormalEnemy[enemy]->SetButtonNum(m_pButtonNum[enemy]);
		//敵の初期化.
		m_ppCNormalEnemy[enemy]->InitProcess();
	}

	//==============================デカタヌキ================================//
	m_pCBigRaccoon_Dog = new CBig_Raccoon_Dog();

	//ボスの初期位置設定.
	m_pCBigRaccoon_Dog->SetInitPosition(m_pCFileManager->GetEnemyPos(EnemyMax + 1));
	//コマンドボタン設定.
	for (int button = 0; button < 3; button++) {
		m_pCBigRaccoon_Dog->SetButtonNum(m_pButtonNum[EnemyMax + button], button);
	}

	//ボスの初期化処理関数.
	m_pCBigRaccoon_Dog->InitProcess();

	//アイテムの設定.
	int Boss_Num = m_AllEnemyMax - 1;
	m_pCItemManager[Boss_Num].SetEnemyType(enEnemy::Big_RaccoonDog);


	//敵の当たった回数動的確保.
	m_EnemyHit = 0;

	//コントローラクラス.
	m_pCInput = new clsXInput();

}

//========================================.
//		更新処理関数.
//========================================.
void CEnemyManager::Update()
{
	//コマンド入力処理関数.
	CheckCommandLongPush();

	//通常敵の更新処理関数.
	NormalEnemyUpDate();

	//アイテムの更新処理関数.
	ItemUpDate();

	//ボスの更新処理関数.
	BossUpDate();
}

//========================================.
//		描画処理関数.
//========================================.
void CEnemyManager::Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos)
{
	//=========================敵================================//.
	//表示するかどうか.
	if (m_pCBigRaccoon_Dog->GetDispFlag() == true) {
		//描画.
		m_pCBigRaccoon_Dog->Value_Set(mView, mProj, vLight, vCameraPos);
		m_pCBigRaccoon_Dog->Render();
	}

	for (int enemy = m_AllNormalEnemyMax - 1; enemy >= 0; enemy--) {
		if (m_ppCNormalEnemy[enemy]->GetDispFlag() == true && 
			m_pCBigRaccoon_Dog->GetInputDecision() == enInput_Decision::Max) {
			//描画のための値を取得.
			m_ppCNormalEnemy[enemy]->Value_Set(mView, mProj, vLight, vCameraPos);
			//描画.
			m_ppCNormalEnemy[enemy]->Render();
		}
	}

	//=========================アイテム================================//.
	for (int item = 0; item < m_AllEnemyMax; item++)
	{
		m_pCItemManager[item].Render(mView, mProj, vCameraPos);
	}

}

//========================================.
//		解放処理関数.
//========================================.
void CEnemyManager::Release()
{
	//敵の種類の最大数.
	const int m_EnemyMax = ENEMY_MAX - 1;
	
	//～クラス解放～.
	SAFE_DELETE_ARRAY(m_pCItemManager);
	SAFE_DELETE(m_pCInput);
	m_pCBigRaccoon_Dog->Release();
	SAFE_DELETE(m_pCBigRaccoon_Dog);
	for (int enemy = m_AllNormalEnemyMax - 1; enemy >= 0; enemy--) {
		m_ppCNormalEnemy[enemy]->Release();
		SAFE_DELETE(m_ppCNormalEnemy[enemy]);
	}

	//～配列解放～.
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
//		敵の座標取得処理関数.
//======================================.
D3DXVECTOR3 CEnemyManager::GetEnemyPos(int enemyType, int enemy)
{
	if (enemyType == static_cast<int>(enEnemy::Big_RaccoonDog)) {
		return m_pCBigRaccoon_Dog->GetPostion();
	}

	//目的の敵までの他の敵の合計計算.
	int enemyMax = 0;
	if (enemyType >= 1) {
		for (int typeNum = 0; typeNum < enemyType; typeNum++) {
			enemyMax += m_pEnemyMax[typeNum];
		}
	}
	return m_ppCNormalEnemy[enemyMax + enemy]->GetPostion();

}

//=========================================.
//		通常敵の更新処理関数.
//=========================================.
void CEnemyManager::NormalEnemyUpDate()
{
	//コマンド判定可能処理関数.
	Command_Possible();


	for (int enemy = 0; enemy < m_AllNormalEnemyMax; enemy++) {

		//表示判定処理.
		m_ppCNormalEnemy[enemy]->DecisionDisp();

		//地面のスクロール速度に合わせる.
		m_ppCNormalEnemy[enemy]->SetSpeed(m_fMoveSpeed);
		m_ppCNormalEnemy[enemy]->FitMoveGround();

		//プレイヤー位置情報取得.
		m_ppCNormalEnemy[enemy]->SetPlayerPos(m_vPlayerPos);

		//表示している場合のみ処理.
		if (m_ppCNormalEnemy[enemy]->GetDispFlag() == true) {
			//判定可能フラグの取得処理関数.
			m_ppCNormalEnemy[enemy]->SetJudgePossible(m_pbDecisionPossible[enemy]);

			//長押しカウント取得処理関数.
			m_ppCNormalEnemy[enemy]->SetLongPushCnt(m_LongPushCnt);

			//入力ボタン情報取得処理関数.
			m_ppCNormalEnemy[enemy]->SetCommandType(m_eninputInformation);
			
			//敵の当たった回数の値設定.
			m_ppCNormalEnemy[enemy]->SetHitNum(m_EnemyHit);

			//更新処理関数.
			m_ppCNormalEnemy[enemy]->Update();

			//コマンド判定結果取得.
			for (int command = 0; command < COMMAND_DECISION_MAX; command++) {
				m_ppenInputDecision[enemy][command] = m_ppCNormalEnemy[enemy]->GetInputDecision(command);
			}

			//敵の当たった回数の値をとる.
			m_EnemyHit = m_ppCNormalEnemy[enemy]->GetHitNum();
		}
	}

}

//============================================.
//		ボス更新処理関数.
//============================================.
void CEnemyManager::BossUpDate()
{
	//表示判定処理.
	m_pCBigRaccoon_Dog->DecisionDisp();

	//地面のスクロール速度に合わせる.
	m_pCBigRaccoon_Dog->SetSpeed(m_fMoveSpeed);
	m_pCBigRaccoon_Dog->FitMoveGround();

	//プレイヤー位置情報取得.
	m_pCBigRaccoon_Dog->SetPlayerPos(m_vPlayerPos);

	//表示している場合のみ処理.
	if (m_pCBigRaccoon_Dog->GetDispFlag() == true) {
		//長押しカウント取得処理関数.
		m_pCBigRaccoon_Dog->SetLongPushCnt(m_LongPushCnt);

		//入力ボタン情報取得処理関数.
		m_pCBigRaccoon_Dog->SetCommandType(m_eninputInformation);
		
		//コマンド判定結果取得.
		int BossNum = m_AllEnemyMax - 1;
		m_pCBigRaccoon_Dog->SetInputDecision(m_penInputDecision[BossNum]);
		m_penInputDecision[BossNum] = m_pCBigRaccoon_Dog->GetInputDecision();

		//揺れているときの上下の距離を取得.
		m_pCBigRaccoon_Dog->SetUpDistance(m_fUpDistance);

		//更新処理関数.
		m_pCBigRaccoon_Dog->Update();
	}


	//ボス戦前の減速判定.
	D3DXVECTOR3 m_vBossPos = m_pCBigRaccoon_Dog->GetPostion();
	if (m_vPlayerPos.z + DECELERATION_DISTANCE >= m_vBossPos.z) {
		m_bDecelerationStart = true;
		//アイテムのボスフラグを立てる.
		const int BossNum = m_AllEnemyMax - 1;
		m_pCItemManager[BossNum].SetBossFlag(true);
	}
	//行動フラグ.
	m_pCBigRaccoon_Dog->SetMove(m_bMoveFlag);
}

//==========================================.
//		コマンド判定可能処理関数.
//==========================================.
void CEnemyManager::Command_Possible()
{
	//判定する敵の座標.
	D3DXVECTOR3 m_vDecisionEnemyPos;
	D3DXVECTOR3 m_vDecisionTargetPos;
	int			tmp = -1;


	//後で編集.
	for (int enemy = 0; enemy < m_AllNormalEnemyMax; enemy++) {
		m_pbDecisionPossible[enemy] = false;
		
		//座標取得.
		m_vDecisionEnemyPos = m_ppCNormalEnemy[enemy]->GetPostion();

		//Playerに当たるぐらい近かったら判定から外す.
		if (m_vDecisionEnemyPos.z <= m_vPlayerPos.z + DECISION_END_BACK) {
			continue;
		}

		//範囲内.
		if (m_vDecisionEnemyPos.x >= m_vPlayerPos.x - DECISION_START_WIDTH &&
			m_vDecisionEnemyPos.x <= m_vPlayerPos.x + DECISION_START_WIDTH) {

			//tmpの仮取得.
			if (tmp < 0) {
				tmp = enemy;
			}
			//比べる相手.
			m_vDecisionTargetPos = m_ppCNormalEnemy[tmp]->GetPostion();
			
			//比べる相手よりPlayerとの距離が小さかったら入れ替え.
			if (fabsf(m_vDecisionEnemyPos.z - m_vPlayerPos.z) < fabsf(m_vDecisionTargetPos.z - m_vPlayerPos.z)) {
				tmp = enemy;
			}			

		}
	}

	//tmp == -1の予防.
	if (tmp >= 0) {
		//一番近かったキャラの判定可能フラグ.
		m_pbDecisionPossible[tmp] = true;
	}
}

//=====================================.
//		コマンド入力処理関数.
//=====================================.
HRESULT CEnemyManager::Command_Entry()
{
	m_pCInput->UpdateStatus();//これ入れないと動かない.

	enCommandType m_enTmpCommandType = enCommandType::Max;

	//Aボタン.
	if (m_pCInput->IsPress(XINPUT_GAMEPAD_A)) {
		m_enTmpCommandType = enCommandType::A;
	}

	//Bボタン.
	if (m_pCInput->IsPress(XINPUT_GAMEPAD_B)) {
		m_enTmpCommandType = enCommandType::B;
	}

	//Xボタン.
	if (m_pCInput->IsPress(XINPUT_GAMEPAD_X)) {
		m_enTmpCommandType = enCommandType::X;
	}

	//Yボタン.
	if (m_pCInput->IsPress(XINPUT_GAMEPAD_Y)) {
		m_enTmpCommandType = enCommandType::Y;
	}

#ifdef _DEBUG

	//Aボタン.
	if (GetAsyncKeyState('Q') & 0x8000) {
		m_enTmpCommandType = enCommandType::A;
	}

	//Bボタン.
	if (GetAsyncKeyState('W') & 0x8000) {
		m_enTmpCommandType = enCommandType::B;
	}

	//Xボタン.
	if (GetAsyncKeyState('E') & 0x8000) {
		m_enTmpCommandType = enCommandType::X;
	}

	//Yボタン.
	if (GetAsyncKeyState('R') & 0x8000) {
		m_enTmpCommandType = enCommandType::Y;
	}
#endif	//#ifdef _DEBUG.

	//ボタン同時押し対策.
	if (m_eninputInformation == enCommandType::Max || 
		m_enTmpCommandType == enCommandType::Max ||
		m_enTmpCommandType == m_eninputInformation) {
		m_eninputInformation = m_enTmpCommandType;
	}

	return S_OK;
}

//==================================.
//	コマンド長押し確認処理関数.
//==================================.
void CEnemyManager::CheckCommandLongPush()
{
	Command_Entry();


	const int Max = 10000;	//長押しの量最大数.

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
//	コマンド結果.
//==================================.
enInput_Decision CEnemyManager::GetEnemyInputDecision(int enemy, int num) 
{
	if (enemy >= m_AllEnemyMax - 1) {
		return m_penInputDecision[enemy];
	}

	return m_ppenInputDecision[enemy][num]; 
}

//==================================.
//	カメラの上がるかの判定処理関数.
//==================================.
bool CEnemyManager::JudgeCameraUp()
{
	const int StartEnemyNum = m_pEnemyMax[static_cast<int>(enEnemy::RaccoonDog)] + m_pEnemyMax[static_cast<int>(enEnemy::Cow_Ghost)];
	D3DXVECTOR3 m_vPos;

	for (int enemy = StartEnemyNum; enemy < m_AllNormalEnemyMax; enemy++) {
		m_vPos = m_ppCNormalEnemy[enemy]->GetPostion();
		//敵キャラが一定の位置まで来る.
		if (m_vPlayerPos.z + 10.0f > m_vPos.z) {
			//初めのところでの判定が行われたらカメラ移動.
			if (m_ppCNormalEnemy[enemy]->GetInputDecision(0) != enInput_Decision::Max) {
				m_bMoveUpCamera = true;
			}
			//最後の判定が行われたらカメラ戻る移動.
			if (m_ppCNormalEnemy[enemy]->GetInputDecision(1) != enInput_Decision::Max) {
				m_bMoveUpCamera = false;
			}
		}

	}
	return false;
}

//======================================.
//		アイテムの設定処理関数.
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
//		アイテムの更新処理関数.
//============================================.
void CEnemyManager::ItemUpDate()
{
	int BossNum = m_AllEnemyMax - 1;
	const int ITEM_MAX = static_cast<int>(enItemType::MAX);

	for (int item = 0; item < m_AllNormalEnemyMax; item++)
	{
		//各敵の位置を取得.
		m_pCItemManager[item].SetInitPosition(m_ppCNormalEnemy[item]->GetPostion());
	}
	//ボスの位置を取得.
	m_pCItemManager[BossNum].SetInitPosition(m_pCBigRaccoon_Dog->GetPostion());

	const int Enemy = m_pEnemyMax[static_cast<int>(enEnemy::Cow_Ghost)] + m_pEnemyMax[static_cast<int>(enEnemy::RaccoonDog)];
	for (int item = 0; item < m_AllEnemyMax; item++)
	{
		//アイテムの合計を取得.
		for (int itemType = 0; itemType < ITEM_MAX; itemType++)
		{
			m_pCItemManager[item].SetItemSum(itemType, GetItem_Sum(itemType));
			//コマンド判定結果を取得.
			if (item >= Enemy && item < Enemy + m_pEnemyMax[static_cast<int>(enEnemy::Kappa)])
			{
				//カッパのみ別判定.
				m_pCItemManager[item].SetInput_Decision(GetEnemyInputDecision(item, 1));
			}
			else 
			{
				m_pCItemManager[item].SetInput_Decision(GetEnemyInputDecision(item));
			}

		}


		//プレイヤー位置を取得.
		m_pCItemManager[item].SetPlayerPosition(m_vPlayerPos);
		//更新処理関数.
		m_pCItemManager[item].UpDate();

		if (m_OldenJudge[item] != m_pCItemManager[item].GetItemJudge())
		{
			Point_WholeSum(item);
		}
		Item_WholeSum(item);
	}
}

//========================================.
//		ポイント合計の計算処理関数.
//========================================.
void CEnemyManager::Point_WholeSum(int item)
{
	m_bCheckItem_Point = false;

	if (m_pCItemManager[item].GetItemJudge() == enItemJudge::Success)
	{
		switch (m_pCItemManager[item].GetEnemyType())
		{
		case enEnemy::RaccoonDog:
			//タヌキ用アイテム.
			m_VegetablesPoint += m_pCItemManager[item].GetPointSum(0);
			break;
		case enEnemy::Cow_Ghost:
			//牛お化けアイテム.
			m_MeatPoint += m_pCItemManager[item].GetPointSum(1);
			break;
		case enEnemy::Kappa:
			//カッパ用アイテムクラス.
			m_FishPoint += m_pCItemManager[item].GetPointSum(2);
			break;
		case enEnemy::Big_RaccoonDog:
			//デカタヌキ用アイテムクラス.
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
			//タヌキ用アイテム.
			m_VegetablesPoint -= m_pCItemManager[item].GetPointSum(0);
			if (m_VegetablesPoint < 0) { m_VegetablesPoint = 0; }
			break;
		case enEnemy::Cow_Ghost:
			//牛お化けアイテム.
			m_MeatPoint -= m_pCItemManager[item].GetPointSum(1);
			if (m_MeatPoint < 0) { m_MeatPoint = 0; }
			break;
		case enEnemy::Kappa:
			//カッパ用アイテムクラス.
			m_FishPoint -= m_pCItemManager[item].GetPointSum(2);
			if (m_FishPoint < 0) { m_FishPoint = 0; }
			break;
		case enEnemy::Big_RaccoonDog:
			//デカタヌキ用アイテムクラス.
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

	//ポイント合計.
	m_Point_WholeSum = m_MeatPoint + m_FishPoint + m_VegetablesPoint + m_RicePoint;
	m_OldenJudge[item] = m_pCItemManager[item].GetItemJudge();

}

//===================================.
//	アイテムの数描画処理関数.
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
				//タヌキ用アイテム.
				m_OldVegetablesSum += m_pCItemManager[num].GetCollitionNum(0);
				break;

			case enEnemy::Cow_Ghost:
				//牛お化けアイテム.
				m_OldMeatSum += m_pCItemManager[num].GetCollitionNum(1);
				break;
			case enEnemy::Kappa:
				//カッパ用アイテムクラス.
				m_OldFishSum += m_pCItemManager[num].GetCollitionNum(2);
				break;
			case enEnemy::Big_RaccoonDog:
				//デカタヌキ用アイテムクラス.
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
				//タヌキ用アイテム.
				m_OldVegetablesSum -= m_pCItemManager[num].GetDropNum(0);
				break;
			case enEnemy::Cow_Ghost:
				//牛お化けアイテム.
				m_OldMeatSum -= m_pCItemManager[num].GetDropNum(1);
				break;
			case enEnemy::Kappa:
				//カッパ用アイテムクラス.
				m_OldFishSum -= m_pCItemManager[num].GetDropNum(2);
				break;
			case enEnemy::Big_RaccoonDog:
				//デカタヌキ用アイテムクラス.
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
//		アイテムの合計処理関数.
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
