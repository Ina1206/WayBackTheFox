#include "CRaccoon_Dog.h"

/****************************************
*	タヌキクラス.
**/
CRaccoon_Dog::CRaccoon_Dog()
	:m_pRacconAnim		(nullptr)
	, m_pAnimController	(nullptr)
	, m_bOldHit			(false)
	, m_pCSEHit			(nullptr)
	, m_pCTimingCommand	(nullptr)
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	//タヌキアニメーション.
	m_pRacconAnim = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Raccoon_Dog);
	_ASSERT_EXPR(m_pRacconAnim != nullptr, L"m_pRaccoonAnim == nullptr");
}

CRaccoon_Dog::~CRaccoon_Dog()
{
}

//==================================.
//		初期設定処理関数.
//==================================.
void CRaccoon_Dog::InitProcess()
{
	//初期位置.
	m_vPos = m_vInitPos;
	//エフェクト.
	m_pCEffectBase = new CEnemyFlyEffect();

	//コマンド.
	m_pCCommand_Base = new CTimingCommand();
	//ボタン番号.
	m_pCCommand_Base->SetButtonNum(m_ButtonNum);
	//表示高さ.
	m_pCCommand_Base->SetDispHight(COMMAND_DISP_H);

	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pRacconAnim = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Raccoon_Dog);
	//アニメーションコントローラーコピー.
	m_pRacconAnim->GetAnimationController()->CloneAnimationController(
		m_pRacconAnim->GetAnimationController()->GetMaxNumAnimationOutputs(),
		m_pRacconAnim->GetAnimationController()->GetMaxNumAnimationSets(),
		m_pRacconAnim->GetAnimationController()->GetMaxNumTracks(),
		m_pRacconAnim->GetAnimationController()->GetMaxNumEvents(),
		&m_pAnimController
	);
	//走りのアニメーションに設定.
	m_pRacconAnim->ChangeAnimSet(static_cast<int>(enAnimType::Run), m_pAnimController);
}

//==================================.
//		更新処理関数.
//==================================.
void CRaccoon_Dog::Update()
{

	if (m_HitFlag == false || m_pCCommand_Base->GetButtonLightFinish() == false) {
		//移動処理関数.
		Move();		

		//コマンド.
		//Playerの座標.
		m_pCCommand_Base->SetPlayerPos(m_vPlayerPos);
		//コマンド判定可能フラグ.
		m_pCCommand_Base->SetJudgePossible(m_bJudgePossible);
		//長押しカウント.
		m_pCCommand_Base->SetLongPushCnt(m_LongPushCnt);
		//コマンド更新処理関数.
		m_pCCommand_Base->Update(m_enCommandType);

	}
	else{
		//当たった後の移動処理関数.
		MoveFly();
	}
	//コマンドの座標.
	m_pCCommand_Base->SetPos(m_vPos);
	//コマンドSEとエフェクト再生処理.
	m_pCCommand_Base->PlayEffectAndSE();
}

//==================================.
//		描画処理関数.
//==================================.
void CRaccoon_Dog::Render()
{
	//影の描画.
	if (m_vPos.y < SHADOW_UP_LIMIT) {
		m_vShadowPos = m_vPos;
		ShadowRender();
	}
	//位置.
	m_pRacconAnim->SetPosition(m_vPos);
	//大きさ.
	m_pRacconAnim->SetScale(SCALE_MAX);
	//角度.
	m_pRacconAnim->SetRotation(m_vRot);
	//スピード.
	m_pRacconAnim->SetAnimSpeed(ANIM_SPEED);
	//描画.
	m_pRacconAnim->Render(m_mView, m_mProj, m_vLight, m_vCameraPos, m_pAnimController);


	//～～～～～～～～～～～.
	//エフェクト描画.
	//～～～～～～～～～～～.
	if (m_pCEffectBase->GetEffectStartFlag() == true) {
		m_pCEnemyFlyEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}

	//コマンド描画処理.
	m_pCCommand_Base->SetValue(m_mView, m_mProj, m_vCameraPos);
	m_pCCommand_Base->Render();
	//コマンドエフェクト描画処理.
	m_pCCommand_Base->RenderEffect();

}

//==================================.
//		解放処理関数.
//==================================.
void CRaccoon_Dog::Release()
{
	//エフェクト解放.
	SAFE_DELETE(m_pCCommand_Base);
	SAFE_DELETE(m_pCEffectBase);

	//タヌキメッシュ.
	m_pRacconAnim = nullptr;
}

//==================================.
//		移動処理関数.
//==================================.
void CRaccoon_Dog::Move()
{
	//敵機の動作.
	m_vPos.z -= MOVE_SPEED;

	//飛んでいく移動処理関数.
	if (m_HitFlag == false) {
		JudgeFly();
	}

	if (m_HitFlag != m_bOldHit) {
		//当たった時のアニメーションに変更.
		m_pRacconAnim->ChangeAnimSet(static_cast<int>(enAnimType::Hit), m_pAnimController);
	}
	m_bOldHit = m_HitFlag;
}
