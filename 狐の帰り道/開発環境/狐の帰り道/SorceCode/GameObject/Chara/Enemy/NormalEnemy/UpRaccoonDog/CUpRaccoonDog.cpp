#include "CUpRaccoonDog.h"

/********************************************
*		上がる狸クラス.
**/
CUpRaccoonDog::CUpRaccoonDog()
	: m_pRaccoonDog		(nullptr)
	, m_pAnimController	(nullptr)
	, m_bCheckSound		(false)
	, m_pGrassMesh		(nullptr)
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();

	//カッパ.
	m_pRaccoonDog = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Raccoon_Dog);
	//アニメーションコントローラーコピー.
	m_pRaccoonDog->GetAnimationController()->CloneAnimationController(
		m_pRaccoonDog->GetAnimationController()->GetMaxNumAnimationOutputs(),
		m_pRaccoonDog->GetAnimationController()->GetMaxNumAnimationSets(),
		m_pRaccoonDog->GetAnimationController()->GetMaxNumTracks(),
		m_pRaccoonDog->GetAnimationController()->GetMaxNumEvents(),
		&m_pAnimController
	);

	
	m_pRaccoonDog->ChangeAnimSet(ANIMATION_NUM,  m_pAnimController);
}

CUpRaccoonDog::~CUpRaccoonDog()
{
}

//==================================.
//		初期設定処理関数.
//==================================.
void CUpRaccoonDog::InitProcess()
{
	//長押しコマンドクラス作成.
	m_pCCommand_Base = new CLongPushCommand();
	//コマンドボタン番号.
	m_pCCommand_Base->SetButtonNum(m_ButtonNum);

	m_vPos = m_vInitPos;
	m_vPos.y = START_HIGH;
}

//==================================.
//		更新処理関数.
//==================================.
void CUpRaccoonDog::Update()
{
	//移動処理関数.
	Move();

	//コマンド位置情報.
	m_pCCommand_Base->SetPos(m_vPos);
	//プレイヤー座標.
	m_pCCommand_Base->SetPlayerPos(m_vPlayerPos);
	//コマンド判定フラグ.
	m_pCCommand_Base->SetJudgePossible(m_bJudgePossible);
	//長押しカウント.
	m_pCCommand_Base->SetLongPushCnt(m_LongPushCnt);
	//コマンド更新処理関数.
	m_pCCommand_Base->Update(m_enCommandType);
	//SE再生処理関数.
	m_pCCommand_Base->PlayEffectAndSE();
	//判定結果の取得.
	for (int command = 0; command < DECISION_MAX; command++) {
		m_enInputDecision[command] = m_pCCommand_Base->GetInputDeision(command);
	}
}

//==================================.
//		描画処理関数.
//==================================.
void CUpRaccoonDog::Render()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();

	//カッパ.
	m_pRaccoonDog = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Raccoon_Dog);
	_ASSERT_EXPR(m_pRaccoonDog != nullptr, L"m_pRaccoonDog == nullptr");
	//位置設定.
	m_pRaccoonDog->SetPosition(m_vPos);
	//角度設定.
	m_pRaccoonDog->SetRotation(m_vRot);
	//大きさ設定.
	m_pRaccoonDog->SetScale(SCALE_SIZE);
	//描画処理関数.
	m_pRaccoonDog->Render(m_mView, m_mProj, m_vLight, m_vCameraPos, m_pAnimController);

	//タヌキが隠れている草の描画.
	m_pGrassMesh = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Grass);
	_ASSERT_EXPR(m_pGrassMesh != nullptr, L"m_pGrassMesh == nullptr");
	//位置設定.
	m_pGrassMesh->SetPosition(D3DXVECTOR3(m_vPos.x, 0.0f, m_vPos.z));
	//大きさ設定.
	m_pGrassMesh->SetScale(SCALE_SIZE);
	//描画設定.
	m_pGrassMesh->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);

	//コマンドの描画.
	m_pCCommand_Base->SetValue(m_mView, m_mProj, m_vCameraPos);
	m_pCCommand_Base->Render();
	//エフェクトの描画.
	m_pCCommand_Base->RenderEffect();
}

//==================================.
//		解放処理関数.
//==================================.
void CUpRaccoonDog::Release()
{
	//長押しコマンドクラス解放.
	SAFE_DELETE(m_pCCommand_Base);

	m_pGrassMesh	= nullptr;
	m_pRaccoonDog = nullptr;
}

//==================================.
//		移動処理関数.
//==================================.
void CUpRaccoonDog::Move()
{
	//プレイヤーがタヌキに近づいてから処理.
	if (m_vPos.z <= m_vPlayerPos.z + UP_MOVE_DISTANCE) {
		//タヌキが上に上がる処理.
		if (m_vPos.y < HIGH_MAX) {
			m_vPos.y += UP_MOVE_SPEED;
		}

		//上がるSEの処理.
		if (m_bCheckSound == false && m_vPos.z != 0.0f) {
			//SE再生.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::App, true);
			//再生フラグ.
			m_bCheckSound = true;
		}	
	}
}