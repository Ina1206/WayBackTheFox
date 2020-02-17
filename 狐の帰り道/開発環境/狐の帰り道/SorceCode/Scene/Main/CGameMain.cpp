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
	//解放処理関数.
	Release();
}

//=====================================.
//		初期設定処理関数.
//=====================================.
void CGameMain::Init_Process()
{
	//---------プレイヤー-------//.
	m_pCPlayer = new CPlayer();
	m_pCPlayer->Init_Process();

	//-------------敵-------------//.
	m_pCEnemyManager = new CEnemyManager();
	m_pCEnemyManager->Init_Process();

	//------------背景------------//.
	m_pCBackGround = new CBackGround();

	//------------地面------------//.
	m_pCGround = new CGround();
	m_pCGround->Init_Process();
	//ゲートの設定.
	m_pCGround->SetGatePosition(m_pCEnemyManager->GetEnemyPos(static_cast<int>(enEnemy::Big_RaccoonDog)));

	//-----------当たり判定---------//.
	m_CHit = new CCollision_Detection;
	m_CHit->Init();

	//------------UI----------//.
	m_pCUIManager = new CMainUIManager();
	m_pCUIManager->Init_Process();

	//------------カメラ----------//.
	m_pCCameraManager = new CCameraManager();


	//当たった時のSEフラグ.
	m_ppbCheckSound = new bool*[static_cast<int>(enEnemy::Max)]();
	for (int enemyType = 0; enemyType < static_cast<int>(enEnemy::Max); enemyType++) {
		m_ppbCheckSound[enemyType] = new bool[m_pCEnemyManager->GetEnemyMax(enemyType)]();
		for (int enemy = 0; enemy < m_pCEnemyManager->GetEnemyMax(enemyType); enemy++) {
			m_ppbCheckSound[enemyType][enemy] = false;
		}
	}

	//================================.
	//試し.
	m_pCEffectBase = new CHitEffect();
	//================================.
}

//=====================================.
//		更新処理関数.
//=====================================.
void CGameMain::UpDate()
{
	//-----------カメラ-----------//.
	//長押しを押したかどうかのフラグ.
	m_pCEnemyManager->CameraUpJudge();
	m_pCCameraManager->SetChangeCamera(m_pCEnemyManager->GetMoveUpCamera());
	m_pCCameraManager->SetLongPush(m_pCEnemyManager->GetMoveUpCamera());
	//コマンド判定.
	m_pCCameraManager->SetInputDecision(m_pCEnemyManager->GetEnemyInputDecision(m_pCEnemyManager->GetAllEnemySumMax() - 1));
	m_pCCameraManager->ChangeCamera();
	if (m_pCEnemyManager->GetBossDispFlag() == true) {
		m_pCCameraManager->SetTargetPos(m_pCEnemyManager->GetEnemyPos(static_cast<int>(enEnemy::Big_RaccoonDog)));
	}
	else {
		m_pCCameraManager->SetTargetPos(m_pCPlayer->GetPosition());
	}
	m_pCCameraManager->UpDate();


	//----------プレイヤー---------//.
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

	//------------地面------------//.
	m_pCGround->UpDate();
	//長押しを押したかどうかのフラグ.
	m_pCGround->SetUpCamera(m_pCEnemyManager->GetMoveUpCamera());
	//減速するかのフラグ.
	m_pCGround->SetDeceleration_StartFlag(m_pCEnemyManager->GetDeceleration());
	//角度の種類.
	m_pCGround->SetBossRotation(m_pCEnemyManager->GetEnemyRot(static_cast<int>(enEnemy::Big_RaccoonDog)));
	//ボスの判定.
	m_pCGround->SetBossCommand(m_pCEnemyManager->GetEnemyInputDecision(m_pCEnemyManager->GetAllEnemySumMax() - 1, 0));
	
	//-------------敵-------------//.
	//地面のスクロール速度に合わせる.
	m_pCEnemyManager->SetSpeed(m_pCGround->GetMoveSpeed());
	
	//プレイヤー位置情報取得.
	m_pCEnemyManager->SetPlayerPos(m_pCPlayer->GetPosition());

	//上がる距離取得.
	m_pCEnemyManager->SetUpDistance(m_pCGround->GetUpDistance());

	//移動距離とキャラの位置を合わせる.
	m_pCEnemyManager->SetMovingDistance(m_pCGround->GetMovingDistance());

	//更新処理関数.
	m_pCEnemyManager->UpDate();

	//------------コマンド--------------//.
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

	//------------ エフェクト試し ------------//.
	m_pCEffectBase->UpDate();
}

//=====================================.
//		描画処理関数.
//=====================================.
void CGameMain::Render()
{
	//置換処理.
	m_mView = m_pCCameraManager->GetmView();	//ビュー行列.
	m_vCamPos = m_pCCameraManager->GetvPos();	//カメラ位置.
	
	//------------背景------------//.
	m_pCBackGround->Render(m_mView, m_mProj, m_vLight, m_vCamPos);

	//------------地面------------//.
	//描画.
	m_pCGround->Value_Set(m_mView, m_mProj, m_vLight, m_vCamPos);
	m_pCGround->Render();

	//===============================.
	//	エフェクト試し.
	m_pCEffectBase->Render(m_mView, m_mProj, m_vCamPos);
	//===============================.

	//-------------敵-------------//.
	m_pCEnemyManager->Render(m_mView, m_mProj, m_vLight, m_vCamPos);

	//------------プレイヤー------------//.
	m_pCPlayer->Value_Set(m_mView, m_mProj, m_vLight, m_vCamPos);
	m_pCPlayer->Render();
	
	//----------UI------------//.
	m_pCUIManager->Render(m_mView, m_mProj, m_vCamPos);
	
}

//======================================.
//		解放処理関数.
//======================================.
void CGameMain::Release()
{
	for (int enemyType = static_cast<int>(enEnemy::Max) - 1; enemyType >= 0; enemyType--) {
		SAFE_DELETE_ARRAY(m_ppbCheckSound[enemyType]);
	}
	SAFE_DELETE_ARRAY(m_ppbCheckSound);

	//試し.
	SAFE_DELETE(m_pCEffectBase);

	//クラス解放.
	SAFE_DELETE(m_pCUIManager);			//CUIManagerクラス.
	SAFE_DELETE(m_CHit);				//CCollisionクラス.
	SAFE_DELETE(m_pCCameraManager);		//CCameraManagerクラス.
	SAFE_DELETE(m_pCGround);			//CGroundクラス.
	SAFE_DELETE(m_pCBackGround);		//BackGroundクラス.
	SAFE_DELETE(m_pCEnemyManager);		//CEnemyManagerクラス.
	SAFE_DELETE(m_pCPlayer);			//CPlayerクラス.

}

//======================================.
//コマンド判定とアイテムの動き処理関数.
//======================================.
void CGameMain::SetCommndDecision(int enemyType, int enemy)
{
	//=======================================.
	//		追加.
	//敵の種類ごとに始まる番号を計算.
	int EnemyMaxCnt = 0;
	if (enemyType - 1 >= 0) {
		for (int enemynum = 0; enemynum < enemyType; enemynum++) {
			EnemyMaxCnt += m_pCEnemyManager->GetEnemyMax(enemynum);
		}
	}

	//---コマンドの判定---.
	if (enemyType != static_cast<int>(enEnemy::Kappa))
	{
		//	Switchの文を変更.
		//switch (m_pCCommandoManager->GetCommandDecision(enemyType, enemy, 0))
		enInput_Decision Decision = m_pCEnemyManager->GetEnemyInputDecision(enemy + EnemyMaxCnt, 0);
		switch (m_pCEnemyManager->GetEnemyInputDecision(enemy + EnemyMaxCnt, 0))
		{
		case enInput_Decision::Great://Great判定.
		case enInput_Decision::Good://Good判定.
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

				//============追加============================.
				//プレイヤーのアニメーションをセット.
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
		default://Bad判定,その他.
			SetHit_Test(enemyType, enemy);
			break;
		}
	}
	else
	{
		//生えるタヌキ.
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
//当たり判定処理関数.
//======================================.
void CGameMain::SetHit_Test(int enemyType, int enemy)
{
	CCollision_Detection::stObjectInfo m_Player;
	CCollision_Detection::stObjectInfo* m_Enemy;
	m_Enemy = new CCollision_Detection::stObjectInfo[m_pCEnemyManager->GetEnemyMax(enemyType)];

	//情報設定.
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
				//エフェクト.
				m_pCEffectBase->SetCenterPos(m_pCPlayer->GetPosition());
				m_pCEffectBase->SetEffectStart(true);
			}
		}
		m_HitCount++;
	}

	//無敵処理.
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
	//当たり判定の範囲設定.
	m_CHit->SetScale(HIT_SCALE, CCollision_Detection::enObject::Playre);
	m_CHit->SetScale(HIT_SCALE, CCollision_Detection::enObject::Raccoon_Dog);
	m_CHit->SetScale(HIT_SCALE_COW, CCollision_Detection::enObject::Cow_Ghost);
	m_CHit->SetScale(HIT_SCALE, CCollision_Detection::enObject::Kappa);
	m_CHit->SetScale(HIT_SCALE, CCollision_Detection::enObject::BigRccoon_Dog);

	//解放処理.
	SAFE_DELETE(m_Enemy);
}

//======================================.
//	ジャンプ用当たり判定処理関数.
//======================================.
void CGameMain::SetHit_Test_Jump(int enemyType, int enemy)
{
	CCollision_Detection::stObjectInfo m_Player;
	CCollision_Detection::stObjectInfo* m_Kappa;
	m_Kappa = new CCollision_Detection::stObjectInfo[m_pCEnemyManager->GetEnemyMax(enemyType)];

	//情報設定.
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

	//当たり判定の範囲設定.
	m_CHit->SetScale(0.5f, CCollision_Detection::enObject::Playre);
	m_CHit->SetScale(2.0f, CCollision_Detection::enObject::Kappa);

	//解放処理.
	SAFE_DELETE(m_Kappa);
}
