#include "CPlayer.h"


//===================================.
//	コンストラクタ.
//===================================.
CPlayer::CPlayer()
	: m_PlayerParam			()
	, m_pCPlayerAnim		(nullptr)
	, m_pCInput				(nullptr)
	, m_pCResourceManager	(nullptr)
	, m_pCSEPlayManager		(nullptr)
	, m_enOperation			(enOperation::Max)
	, m_pChangeTexture		(nullptr)
	, m_vEnemyPosition		(D3DXVECTOR3(0.0f,0.0f,0.0f))
	, m_bEndFlag			(false)
	, m_frame				(0)
	, m_WaitTime			(0)
	, m_bFixedPosFlag		(false)
	, m_bLongCommandFlag	(false)
	, m_OperationFlag		(false)
	, m_bJumpEndFlag		(false)
	, m_bStartCountFlag		(false)
	, m_StartCount			(0)
	, m_FlashTime			(0)
	//=================.
	//		追加.
	, m_pCShadow(nullptr)
{
}

//===================================.
//	デストラクタ.
//===================================.
CPlayer::~CPlayer()
{
	Release();
}

//初期設定関数.
void CPlayer::InitProcess()
{
	m_PlayerParam.m_vPos	= D3DXVECTOR3(0.0f, 0.0f, POISITION_Z);
	m_PlayerParam.m_vOldPos = m_PlayerParam.m_vPos;
	m_PlayerParam.m_AnimSpeed = ANIM_SPEED;
	m_pCInput				= new clsXInput();
	m_pCResourceManager		= CResourceManager::GetResourceManagerInstance();
	m_pCSEPlayManager		= CSEPlayManager::GetSEPlayManagerInstance();

	//初期化処理関数.
	Init();

	//アニメーション.
	SetAnim(enPlyAct::Run);

	//エフェクト.
	//配列動的確保.
	m_ppCEffectBase = new CEffectBase*[EFFECT_MAX]();
	//クラス.
	m_ppCEffectBase[STEP_EFFECT_NUM] = new CStepEffect();	
	m_ppCEffectBase[LAND_EFFECT_NUM] = new CLandingEffect();

}

//===================================.
//更新処理関数.
//===================================.
void CPlayer::Update()
{
	m_pCInput->UpdateStatus();//これ入れないと動かない.

	//カウントダウン中は動かないようにする.
	if (m_bStartCountFlag == true) {
		m_StartCount++;
		if (m_StartCount >= MOVE_START) {
			m_OperationFlag = true;
		}
	}

	//---操作可能であるとき---.
	if (m_OperationFlag == true && m_bFixedPosFlag == false) {
		//---自機移動(コントローラ対応)---//.
		//右移動.
		if (m_PlayerParam.m_vPos.x != MOVING_RANGE) {
			if (m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_RIGHT)|| m_pCInput->GetLThumbX() >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				m_PlayerParam.m_MoveCount_R++;
				Move(MOVING_RANGE, m_PlayerParam.m_MoveCount_R);
				SetAnim(enPlyAct::Run);
			}
			else
			{
				m_PlayerParam.m_MoveCount_R = 0;
			}
		}
		//左移動.
		if (m_PlayerParam.m_vPos.x != -MOVING_RANGE) {
			if (m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_LEFT) || m_pCInput->GetLThumbX() <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				m_PlayerParam.m_MoveCount_L++;
				Move(-MOVING_RANGE, m_PlayerParam.m_MoveCount_L);
				SetAnim(enPlyAct::Run);
			}
			else
			{
				m_PlayerParam.m_MoveCount_L = 0;
			}
		}

		//---自機移動制御---//.
		//x座標.
		if (m_PlayerParam.m_vPos.x > MOVING_RANGE) { m_PlayerParam.m_vPos.x = MOVING_RANGE; }
		if (m_PlayerParam.m_vPos.x < -MOVING_RANGE) { m_PlayerParam.m_vPos.x = -MOVING_RANGE; }
	}

	//長押しコマンドを押しているとき.
	if (m_bLongCommandFlag == true) {
		m_OperationFlag = false;
		m_bJumpEndFlag = false;
	}

	//減速前にボタンが押されている場合もプレイヤーを真ん中にする.
	if (m_OperationFlag == true) {
		if (m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_RIGHT)
			|| m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			if (m_bFixedPosFlag == true)
			{
				m_OperationFlag = false;							//操作不可能にする.
				if (m_PlayerParam.m_Count == 0)
				{
					m_PlayerParam.m_vPos = m_PlayerParam.m_vOldPos;		//プレイヤーを真ん中にする.
				}
			}
		}
	}

	//減速したらプレイヤーが真ん中になるようにする.
	if (m_bFixedPosFlag == true)
	{
		m_OperationFlag = false;							//操作不可能にする.

		if (m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_RIGHT)
			|| m_pCInput->IsPress(XINPUT_GAMEPAD_DPAD_LEFT))
		{
			m_OperationFlag = false;						//操作不可能にする.
		}
		m_PlayerParam.m_vPos.x = m_PlayerParam.m_vOldPos.x;
		if (m_PlayerParam.m_Count == 0)
		{
			//Playerが真ん中にいるときはSEを鳴らさない.
			if (m_PlayerParam.m_vPos != m_PlayerParam.m_vOldPos) {
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Player_Move, true);
			}
		}
		m_PlayerParam.m_Count++;
	}
	
	//-------------------------------.
	//	ジャンプ.
	//-------------------------------.
	Jump();

#ifdef _DEBUG
	if (m_OperationFlag == true)
	{
		if (GetAsyncKeyState('A') & 0x0001)
		{
			m_PlayerParam.m_vPos.x -= MOVING_RANGE;
			SetAnim(enPlyAct::Run);
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Player_Move, true);
		}
		if (GetAsyncKeyState('D') & 0x0001)
		{
			m_PlayerParam.m_vPos.x += MOVING_RANGE;
			SetAnim(enPlyAct::Run);
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Player_Move, true);
		}
	}

	//---ジャンプ---//.
	if (GetAsyncKeyState(VK_SPACE) & 0x0001)
	{
		if (m_PlayerParam.m_bJumpFlag == false) {
			//ジャンプ中でないとき.
			m_PlayerParam.m_bJumpFlag = true;		//ジャンプ開始.
			m_PlayerParam.m_fAcc = 0.0f;			//加速初期化.
		}
	}

	//--------------------------------
	//	アニメーション切り替え.
	//--------------------------------
	static int anim_no = 0;
	if (GetAsyncKeyState('C') & 0x0001)
	{
		anim_no++;
		if (anim_no >= m_pCPlayerAnim->GetAnimMax()) {
			anim_no = 0;
		}
		m_pCPlayerAnim->ChangeAnimSet(anim_no);
	}

#endif

	if (m_pCPlayerAnim != nullptr) {
		//プレイヤーの足元の座標.
		m_vFootDownPos = D3DXVECTOR3(m_PlayerParam.m_vPos.x, GROUND_HIT_H, m_PlayerParam.m_vPos.z);
		//足音のSEの処理関数.
		FootStepSE(m_pCPlayerAnim, CSoundResource::enSoundSE::Player_Step);
	}

}

//===================================.
//描画処理関数.
//===================================.
void CPlayer::Render()
{
	//=========================.
	//		影追加.
	//影描画.
	m_pCShadow = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Shadow);
	_ASSERT_EXPR(m_pCShadow != nullptr, L"m_pCShadow == nullptr");
	//座標.
	D3DXVECTOR3 m_vShadowPos = m_PlayerParam.m_vPos;
	m_vShadowPos.y = SHADOW_HIGHT;
	m_pCShadow->SetPosition(m_vShadowPos);
	m_pCShadow->SetCancelRotationFlag(false);
	m_pCShadow->Render(m_mView, m_mProj, m_vCameraPos);

	//プレイヤーのアニメーション.
	m_pCPlayerAnim = m_pCResourceManager->GetSkinMesh(CResourceSkinMesh::enSkincMesh::Player);
	_ASSERT_EXPR(m_pCPlayerAnim != nullptr, L"m_pPlayerAnim == nullptr");
	m_pCPlayerAnim->SetPosition(m_PlayerParam.m_vPos);
	m_pCPlayerAnim->SetRotation(D3DXVECTOR3(0.0f, ROTATION, 0.0f));
	m_pCPlayerAnim->SetAnimSpeed(m_PlayerParam.m_AnimSpeed);
	m_pCPlayerAnim->SetScale(SCALE_SIZE);
	m_pCPlayerAnim->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);

	//--------------------------------
	//	アニメーション切り替え.
	//--------------------------------
	switch (m_PlayerParam.m_Action)
	{
	case enPlyAct::Run:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_RUN);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	case enPlyAct::Jump:
	case enPlyAct::TwoRowJump:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_JUMP);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	case enPlyAct::Wait:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_WAIT);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	case enPlyAct::Attack:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_ATTACK);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	case enPlyAct::Panic:
		if (m_PlayerParam.m_SetAnimFlag == true)
		{
			m_pCPlayerAnim->ChangeAnimSet(ANIM_PANIC);
			m_PlayerParam.m_SetAnimFlag = false;
		}
		break;
	default:
		break;
	}

	//エフェクトの描画処理関数.
	for (int effect = 0; effect < EFFECT_MAX; effect++) {
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->Render(m_mView, m_mProj, m_vCameraPos);
		}
	}

}

//===================================.
//解放処理関数.
//===================================.
void CPlayer::Release()
{
	//解放処理関数.
	Destroy();

	SAFE_DELETE(m_pChangeTexture);

	//エフェクトごとのクラス解放.
	SAFE_DELETE(m_ppCEffectBase[LAND_EFFECT_NUM]);
	SAFE_DELETE(m_ppCEffectBase[STEP_EFFECT_NUM]);

	//エフェクトの配列解放.
	SAFE_DELETE_ARRAY(m_ppCEffectBase);

	m_pCSEPlayManager = nullptr;
	//読み込み管理クラス.
	m_pCResourceManager = nullptr;
	SAFE_DELETE(m_pCInput);
	m_pCPlayerAnim  = nullptr;
}

//===================================.
//前進処理関数.
//===================================.
void CPlayer::Progress()
{
	m_frame++;

	if (m_frame % SECONDS_COUNT == 0)
	{
		m_WaitTime++;
	}
	if (m_WaitTime < WAIT_END)
	{
		SetAnim(enPlyAct::Wait);
	}
	if (m_WaitTime >= WAIT_END)
	{
		SetAnim(enPlyAct::Run);
		m_PlayerParam.m_vPos.z += MOVE_SPEED;
	}
	if (m_WaitTime > GAME_END)
	{
		m_bEndFlag = true;
	}
}

//===================================.
//点滅処理.
//===================================.
void CPlayer::Flashing(int count)
{

	if (m_bFixedPosFlag == false)
	{
		if (count % FLASH_DIVIDE == 0) {
			m_FlashTime++;
		}
		if (m_FlashTime % TWO_DIVIDE == 0) {
			m_pCPlayerAnim->SetEnabelChangeTextureSystem(false);
		}
		else
		{
			m_pCPlayerAnim->SetEnabelChangeTextureSystem(true);
		}

		if (count == 0)
		{
			m_FlashTime = 0;
		}
	}
	else {
		m_pCPlayerAnim->SetEnabelChangeTextureSystem(false);
	}

}

//===================================.
//アニメーション再生設定;
//===================================.
void CPlayer::SetAnim(enPlyAct Act)
{
	m_PlayerParam.m_Action = Act;

	if (m_PlayerParam.m_Action != m_PlayerParam.m_Old_Action)
	{
		m_PlayerParam.m_SetAnimFlag = true;
		m_PlayerParam.m_Old_Action = m_PlayerParam.m_Action;
	}
}

//===================================.
//移動処理.
//===================================.
void CPlayer::Move(float range, int count)
{
	//一気に移動するのを防ぐ処理.
	if (count == FIRST_MOVETIME)
	{
		m_PlayerParam.m_vPos.x += range;
		m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Player_Move, true);
	}
}

//===================================.
//ジャンプ処理.
//===================================.
void CPlayer::Jump()
{

	if (m_PlayerParam.m_bJumpFlag == false) {
		m_PlayerParam.m_fAcc = 0.0f;	//加速初期化.	
	}

	if (m_PlayerParam.m_bJumpFlag == true) {
		m_PlayerParam.m_vPos.y += JUMP_POWER + m_PlayerParam.m_fAcc;
		m_PlayerParam.m_fAcc -= GRAVITY;								//重力加速.
		m_OperationFlag = false;
		SetAnim(enPlyAct::Jump);

		//地面より下になった.
		if (m_PlayerParam.m_vPos.y <= 0) {
			m_PlayerParam.m_vPos.y = 0;
			m_bJumpEndFlag = true;
			m_PlayerParam.m_bJumpFlag = false;
			SetAnim(enPlyAct::Run);
			m_OperationFlag = true;

			//地面に着地したときのエフェクト.
			m_ppCEffectBase[LAND_EFFECT_NUM]->SetCenterPos(m_PlayerParam.m_vPos);
			m_ppCEffectBase[LAND_EFFECT_NUM]->SetEffectStart(true);

		}

		//下降中か.
		if (m_PlayerParam.m_vPos.y > m_PlayerParam.m_vOldPos.y)
		{
			//敵が下にいるか.
			if (m_PlayerParam.m_vPos.y < m_vEnemyPosition.y + POSITION_ADJ
				&& m_PlayerParam.m_vPos.z < m_vEnemyPosition.z + ENEMY_DEPTH)
			{
				//再度ジャンプ.
				m_PlayerParam.m_fAcc = GRAVITY;
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Jump, true);
				SetAnim(enPlyAct::TwoRowJump);

				//タヌキを踏むときのエフェクト.
				m_ppCEffectBase[STEP_EFFECT_NUM]->SetCenterPos(m_PlayerParam.m_vPos);
				m_ppCEffectBase[STEP_EFFECT_NUM]->SetEffectStart(true);

			}
		}
	}

	for (int effect = 0; effect < EFFECT_MAX; effect++) {
		//エフェクト更新処理関数.
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->Update();
		}
	}
}
