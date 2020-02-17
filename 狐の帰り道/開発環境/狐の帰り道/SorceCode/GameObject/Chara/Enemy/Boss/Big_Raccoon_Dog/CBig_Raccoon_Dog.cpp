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
//		初期化処理関数.
//===================================.
void CBig_Raccoon_Dog::Init_Process()
{
	//初期位置.
	m_vPos = m_vInitPos;
	m_vPos.y = STANDERD_POS_H;
	m_vRot.x = START_ROTATION;

	//配列動的確保.
	m_pvPlayerHandlePos			= new D3DXVECTOR3[HANDLE_MAX]();
	m_ppCCollision_Detection	= new CCollision_Detection*[HANDLE_MAX]();
	m_ppCDebug_Collision_Sphere = new CDebugCollisionSphere*[HANDLE_MAX + HIT_TARGET_MAX]();
	m_pbHitHandleFlag			= new bool[HANDLE_MAX]();
	m_ppCEffectBase				= new CEffectBase*[EFFECT_MAX]();

	//アニメーションの種類を揺れているものに設定.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::BigRaccoon_Dog);
	m_pCSkinMesh->ChangeAnimSet(static_cast<int>(enAnimType::Swing));

	//当たり判定に関するクラスの作成.
	for (int collision = 0; collision < HANDLE_MAX; collision++) {
		m_ppCCollision_Detection[collision]		= new CCollision_Detection();
		m_ppCDebug_Collision_Sphere[collision]	= new CDebugCollisionSphere();
	}
	m_ppCDebug_Collision_Sphere[HIT_TARGET_NUM] = new CDebugCollisionSphere();

	//当たり判定の初期設定.
	for (int collision = 0; collision < HANDLE_MAX; collision++) {
		m_ppCCollision_Detection[collision]->Init();
		m_ppCCollision_Detection[collision]->SetScale(PLAYER_HIT_SCALE, CCollision_Detection::enObject::Playre);
		m_ppCCollision_Detection[collision]->SetScale(BOSS_HIT_SCALE, CCollision_Detection::enObject::BigRccoon_Dog);
		m_pbHitHandleFlag[collision] = false;
	}

	m_vPrePos.y = CENTER_AXIS_DIFF;

	//それぞれのエフェクトクラスの作成.
	m_ppCEffectBase[HIT_FLY_EFFECT_NUM]		= new CBossFlyEffect();	//飛んでいくときの煙エフェクト.
	m_ppCEffectBase[FALLDOWN_EFFECT_NUM]	= new CFallDownEffect();//倒れたときの煙エフェクト.
	m_ppCEffectBase[PUNCH_EFFECT_NUM]		= new CPunchEffect();	//パンチされた時のエフェクト.

	m_pCCommand_Base = new CBarrageCommand();
	//ボタン番号設定.
	for (int button = 0; button < COMMAND_BUTTON_MAX; button++) {
		m_pCCommand_Base->SetMultipleButtonNum(m_pButtonNum[button], button);
	}
}

//===================================.
//		更新処理関数.
//===================================.
void CBig_Raccoon_Dog::UpDate()
{
	m_enInputDecision = m_pCCommand_Base->GetInput_Deision();
	if (m_enInputDecision == enInput_Decision::Max) {
		if (m_bMoveStart == false) {
			//行動開始処理関数.
			Move_Judgement();
		}
		if (m_bMoveStart == true) {
			//殴られた時の音処理関数.
			HitSound();

			//～コマンドの設定～.
			m_pCCommand_Base->SetPos(m_vPos);				//座標.
			m_pCCommand_Base->SetPlayerPos(m_vPlayerPos);	//Player座標.
			m_pCCommand_Base->SetDispFlag(m_bMoveStart);	//行動開始フラグ.
			m_pCCommand_Base->UpDate(m_enCommandType);		//更新処理関数.
		}
	}
	else {
		//コマンド表示終了.
		m_bCommandDispStart = false;
	}

	//コマンドエフェクトとSE再生クラス.
	m_pCCommand_Base->EffectAndSE_Play();

	//パンチされた時のエフェクト更新処理関数.
	m_ppCEffectBase[PUNCH_EFFECT_NUM]->UpDate();

	//コマンド成功時.
	if (m_enInputDecision == enInput_Decision::Good || 
		m_enInputDecision == enInput_Decision::Great) {
		//当たった時の処理関数.
		HitMove();
	}

	//コマンド失敗時.
	if(m_enInputDecision == enInput_Decision::Bad){
		//待ち時間計算.
		if (m_Cnt < FALL_DOWN_WAIT_TIME) {
			m_Cnt++;
		}
		else {
			//倒れるときの処理関数.
			FALL_DOWN();
		}
	}


	//アニメーション変更.
	if (m_enInputDecision != m_enOldInDecision) {
		m_bAnimChange = true;
	}
	//回転するアニメーションに変更.
	if (m_bAnimChange == true) {
		if (m_vRot.x < ANIM_CHANGE_ROT) {
			if (m_enInputDecision == enInput_Decision::Bad) {
				//通常.
				m_pCSkinMesh->ChangeAnimSet(static_cast<int>(enAnimType::Noting));
			}
			else {
				//飛んで行くアニメーション
				m_pCSkinMesh->ChangeAnimSet(static_cast<int>(enAnimType::Finish));
			}
			//アニメーション変更終了.
			m_bAnimChange = false;
		}
	}

	//前回と今回の入力結果の差分.
	m_enOldInDecision = m_enInputDecision;

}

//====================================.
//		描画処理関数.
//====================================.
void CBig_Raccoon_Dog::Render()
{
	//デカタヌキ描画.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::BigRaccoon_Dog);
	//ズレの位置.
	m_pCSkinMesh->SetPrePos(m_vPrePos);
	//大きさ.
	m_pCSkinMesh->SetScale(m_fScale);
	//傾き.
	m_pCSkinMesh->SetRotation(m_vRot);
	//位置.
	m_pCSkinMesh->SetPosition(m_vPos);
	//アニメーション速度.
	m_pCSkinMesh->SetAnimSpeed(m_fAnimSpeed);
	//描画.
	m_pCSkinMesh->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);

	//エフェクトの描画.
	for (int effect = 0; effect < EFFECT_MAX; effect++) {
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->Render(m_mView, m_mProj, m_vCameraPos);
		}
	}
	
	//最後の星の描画.
	m_pCStar = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Sparkle);
	//位置.
	m_pCStar->SetPosition(m_vStarPos);
	//透過値.
	m_pCStar->SetAlpha(ALPHA_MAX);
	//大きさ.
	m_pCStar->SetScale(D3DXVECTOR3(m_fStarScale, m_fStarScale, m_fStarScale));
	//描画.
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->SetDepth(false);
	m_pCStar->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepthStencil->SetDepth(true);

	//コマンドクラスの描画.
	m_pCCommand_Base->Value_Set(m_mView, m_mProj, m_vCameraPos);
	m_pCCommand_Base->Render();
	m_pCCommand_Base->EffectRender();
}

//====================================.
//		解放処理関数.
//====================================.
void CBig_Raccoon_Dog::Release()
{
	//クラス解放.
	//コマンドクラス.
	SAFE_DELETE(m_pCCommand_Base);

	//それぞれのエフェクトクラス.
	for (int effect = EFFECT_MAX - 1; effect >= 0; effect--) {
		SAFE_DELETE(m_ppCEffectBase[effect]);
	}

	//当たり判定の描画.
	for (int draw = (HANDLE_MAX + HIT_TARGET_MAX) - 1; draw >= 0; draw--) {
		SAFE_DELETE(m_ppCDebug_Collision_Sphere[draw]);
	}
	//当たり判定.
	for (int handle = HANDLE_MAX - 1; handle >= 0; handle--) {
		SAFE_DELETE(m_ppCCollision_Detection[handle]);
	}
	
	//配列解放.
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
//		行動処理関数.
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
//		当たった時の処理関数.
//=======================================.
void CBig_Raccoon_Dog::HitMove()
{
	//回転.
	m_vRot.x += m_fHitRotation;
	//回転速度を徐々に増やしていく.
	m_fHitRotation += HIT_ROT_SPEED_UP;
	if (m_vRot.x > ONE_ROTATION_MIN) {
		m_vRot.x = 0.0f;
	}

	//y軸のみに飛ばす.
	if (m_vPos.y < FLY_MAX) {
		m_vPos.y += HIT_MOVE_SPEED;
		//SEの再生.
		if (m_bInputSE_Check == false) {
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Boss_Fly, true);
			m_bInputSE_Check = true;
		}
	}
	else {
		//飛んだあとの処理.
		FlyAfter();
	}
	//飛んでいく高さに合わせて大きさを小さくする.
	m_fScale = SCALE_SIZE - ((m_vPos.y /FLY_MAX) * SCALE_SIZE);

	//飛んでいくときのエフェクト.
	//中心の位置設定.
	m_ppCEffectBase[HIT_FLY_EFFECT_NUM]->SetCenterPos(m_vPos);
	//エフェクト表示.
	m_ppCEffectBase[HIT_FLY_EFFECT_NUM]->SetEffectStart(true);
	//エフェクト更新処理.
	m_ppCEffectBase[HIT_FLY_EFFECT_NUM]->UpDate();

}

//=======================================.
//		倒れるときの処理関数.
//=======================================.
void CBig_Raccoon_Dog::FALL_DOWN()
{

	if (m_vRot.x > FALL_DOWN_ROT_MIN) {
		//高さと倒れる奥行の調整.
		m_vPos.z -= ADJUST_MOVE_SPEED.z;
		//m_vPos.y += ADJUST_MOVE_SPEED.y;
		//倒れる角度.
		m_vRot.x -= m_fFall_Down_Speed;
		//倒れる速度を徐々に増す.
		m_fFall_Down_Speed += FALL_DOWN_SPEED_UP;
		//地震が起こる前の座標.
		m_vSwingBefore_Pos = m_vPos;
	}
	else {
		m_vRot.x = FALL_DOWN_ROT_MIN;
		m_vPos.y = m_vSwingBefore_Pos.y + m_fUpDistance;

		//SEの再生.
		if (m_bInputSE_Check == false) {
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Fall_Down, true);
			m_bInputSE_Check = true;
		}

		//エフェクト処理.
		m_ppCEffectBase[FALLDOWN_EFFECT_NUM]->SetCenterPos(m_vPos);
		m_ppCEffectBase[FALLDOWN_EFFECT_NUM]->SetEffectStart(true);
		m_ppCEffectBase[FALLDOWN_EFFECT_NUM]->UpDate();
	}

}

//==============================================.
//		殴られた時の音処理関数.
//==============================================.
void CBig_Raccoon_Dog::HitSound()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCSkinMesh = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Player);
	//ボーン座標取得.
	m_pCSkinMesh->GetPosFromBone("Left_hand", &m_pvPlayerHandlePos[LEFT_HANDLE_NUM]);	//左手.
	m_pCSkinMesh->GetPosFromBone("Right_hand", &m_pvPlayerHandlePos[RIGHT_HANDLE_NUM]);	//右手.

	//手の座標と大きさの設定.
	for (int handle = 0; handle < HANDLE_MAX; handle++) {
		m_ppCDebug_Collision_Sphere[handle]->SetPos(m_pvPlayerHandlePos[handle]);
		m_ppCDebug_Collision_Sphere[handle]->SetScale(0.2f);
	}

	//殴る時のボス側の当たり判定座標設定.
	D3DXVECTOR3 m_vHitPos = D3DXVECTOR3(m_vInitPos.x, m_vInitPos.y + 1.0f, m_vPos.z - 0.5f);
	//D3DXVECTOR3 m_vHitPos = m_vInitPos+ HIT_BOSSPOS_ADJUST;
	m_ppCDebug_Collision_Sphere[HIT_TARGET_NUM]->SetPos(m_vHitPos);
	m_ppCDebug_Collision_Sphere[HIT_TARGET_NUM]->SetScale(1.5f);

	for (int handle = 0; handle < HANDLE_MAX; handle++) {
		//攻撃側の設定.
		CCollision_Detection::stObjectInfo stAtkObj;
		stAtkObj.Object = CCollision_Detection::enObject::Playre;
		stAtkObj.vPos	= m_pvPlayerHandlePos[handle];

		//敵側の設定.
		CCollision_Detection::stObjectInfo stTargetObj;
		stTargetObj.Object	= CCollision_Detection::enObject::BigRccoon_Dog;
		stTargetObj.vPos	= m_vHitPos;
		
		if (m_ppCCollision_Detection[handle]->JugeHit(&stAtkObj, &stTargetObj)) {
			if (m_pbHitHandleFlag[handle] == false) {
				//パンチされた時のエフェクト.
				m_ppCEffectBase[PUNCH_EFFECT_NUM]->SetCenterPos(m_pvPlayerHandlePos[handle]);
				m_ppCEffectBase[PUNCH_EFFECT_NUM]->SetEffectStart(true);
				//SE流す.
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
//		飛んだあとの処理関数.
//====================================================.
void CBig_Raccoon_Dog::FlyAfter()
{
	//デカタヌキに座標を合わせる.
	m_vStarPos = m_vPos;
	
	//星の拡縮.
	switch (m_enStarScaling) {
	//拡大.
	case enStarScaling::Scale:
		
		m_fStarScale += STAR_SCALE_SPEED;
		
		//星が出ている間はカメラを動かさないよう移動.
		m_vPos.x += BACK_SPEED;

		if (m_fStarScale >= STAR_MAX) {
			m_enStarScaling = enStarScaling::Scale_Down;
			//SEの再生.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Boss_Star, true);
		}
		break;
	//縮小.
	case enStarScaling::Scale_Down:

		m_fStarScale -= STAR_SCALE_SPEED;
		
		//星が出ている間はカメラを動かさないよう移動.
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