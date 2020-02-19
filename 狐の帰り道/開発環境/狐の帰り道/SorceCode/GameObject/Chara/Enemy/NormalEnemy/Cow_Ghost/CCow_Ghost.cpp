#include "CCow_Ghost.h"

CCow_Ghost::CCow_Ghost()
	: m_pStaticMesh			(nullptr)
	, m_enVerticalMoveType	(enVerticalMove_Type::Up)
	, m_enHorizonMoveType	(enHorizonMove_Type::Left_Move)
	, m_JumpCnt				(0)
	, m_fOldPos_x			(0.0f)
	, m_bCheckSE			(false)
{
}

CCow_Ghost::~CCow_Ghost()
{
}

//================================================.
//		初期化処理関数.
//================================================.
void CCow_Ghost::Init_Process()
{
	//座標設定.
	m_vPos = m_vInitPos;
	m_vPos.y = STANDERD_HIGH;

	//タイミングコマンドクラス作成.
	m_pCCommand_Base = new CTimingCommand();
	//ボタン番号設定.
	m_pCCommand_Base->SetButtonNum(m_ButtonNum);
	//タイミングコマンドの高さ設定.
	m_pCCommand_Base->SetDispHight(COMMAND_HIGH);

	//横移動エフェクトクラス作成.
	m_pCEffectBase = new CHorizonMoveEffect();	
}

//================================================.
//		更新処理関数.
//================================================.
void CCow_Ghost::UpDate()
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
	else {
		
		//飛んでいく移動処理関数.
		FlyMove();
	}
	//コマンドの座標.
	m_pCCommand_Base->SetPos(m_vPos);
	//コマンドSEとエフェクト再生処理.
	m_pCCommand_Base->PlayEffectAndSE();
}

//================================================.
//		描画処理関数.
//================================================.
void CCow_Ghost::Render()
{
	//影の描画.
	if (m_vPos.y < SHADOW_DISP_UP_LIMIT) {
		m_vShadowPos = m_vPos;
		//影の描画処理関数.
		ShadowRender();
	}

	//=======================.
	//	エフェクト描画.
	if (m_pCEffectBase->GetEffectStartFlag() == true) {
		m_pCEffectBase->Render(m_mView, m_mProj, m_vCameraPos);
	}

	if (m_HitFlag == true) {
		m_pCEnemyFlyEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}

	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();

	m_pStaticMesh = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Cow_Gohst);
	_ASSERT_EXPR(m_pStaticMesh != nullptr, L"m_pStaticMesh == nullptr");
	m_pStaticMesh->SetScale(SCALE_SIZE);
	m_pStaticMesh->SetPosition(m_vPos);
	m_pStaticMesh->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);

	//コマンドの描画.
	m_pCCommand_Base->SetValue(m_mView, m_mProj, m_vCameraPos);
	m_pCCommand_Base->Render();
	m_pCCommand_Base->RenderEffect();

}

//================================================.
//		解放処理関数.
//================================================.
void CCow_Ghost::Release()
{
	//クラス解放.
	SAFE_DELETE(m_pCEffectBase);
	SAFE_DELETE(m_pCCommand_Base);
	m_pStaticMesh = nullptr;
}

//================================================.
//		移動処理関数.
//================================================.
void CCow_Ghost::Move()
{
	//一定の位置または、横移動判定の時は移動可能.
	if (m_vPos.z >= m_vPlayerPos.z + STOP_DISTANCE || m_enVerticalMoveType == enVerticalMove_Type::Waiting) {
		FarMove();
	}
	else {
		//高さを合わせる.
		if (m_vPos.y >= STANDERD_HIGH) {
			m_vPos.y -= VERTICAL_SPEED;
		}
	}

	if (m_HitFlag == false) {
		//飛んでいく移動処理関数.
		FlyJudge();
	}
	//================================.
	//	エフェクト.
	m_pCEffectBase->UpDate();

}

//================================================.
//		遠い時の移動処理関数.
//================================================.
void CCow_Ghost::FarMove()
{
	//移動方法.
	switch (m_enVerticalMoveType) {
	//上に移動.
	case enVerticalMove_Type::Up:

		m_vPos.y += VERTICAL_SPEED;

		//上限に達したら下に移動.
		if (m_vPos.y > HIGH_MAX) {
			//次のステージへ.
			m_enVerticalMoveType = enVerticalMove_Type::Down;
		}
		break;
	//下に移動.
	case enVerticalMove_Type::Down:

		m_vPos.y -= VERTICAL_SPEED;

		//下に達したら上に移動.
		if (m_vPos.y <= STANDERD_HIGH) {
			m_enVerticalMoveType = enVerticalMove_Type::Up;
			//ジャンプカウント追加.
			m_JumpCnt++;

			//ジャンプカウント最大なら左右に移動.
			if (m_JumpCnt >= JUMP_MAX) {
				m_JumpCnt = 0;
				//右のレーンなら左に移動.
				if (m_vPos.x > CENTER_POS_X) {
					m_enVerticalMoveType = enVerticalMove_Type::Waiting;
				}
				//真ん中と左のレーンなら右に移動.
				else {
					m_enVerticalMoveType = enVerticalMove_Type::Waiting;
				}
				//前回の位置に記憶.
				m_fOldPos_x = m_vPos.x;

				//フラグを初期に戻す.
				m_bCheckSE = false;
			}
		}
		break;
	//待機.
	case enVerticalMove_Type::Waiting:
		//横移動処理関数.
		HorizonMove();

		//横移動時にSE再生.
		if (m_bCheckSE == false) {
			//再生.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Ghost_Move, true);
			//再生したチェック.
			m_bCheckSE = true;
		}
		break;
	}

}

//===========================================.
//		横移動処理関数.
//===========================================.
void CCow_Ghost::HorizonMove()
{
	//横移動処理.
	switch (m_enHorizonMoveType) {
	//右に移動.
	case enHorizonMove_Type::Right_Move:
		//右移動.
		m_vPos.x += HORIZON_SPEED;

		//次のレーンに行けばまた縦移動.
		if (m_vPos.x >= m_fOldPos_x + MOVE_WIDTH) {
			m_vPos.x = m_fOldPos_x + MOVE_WIDTH;
			m_enVerticalMoveType = enVerticalMove_Type::Up;
		}

		//レーンの最大値に行けば左移動へ.
		if (m_vPos.x >= LANE_MAX) {
			m_enHorizonMoveType = enHorizonMove_Type::Left_Move;
			//位置なおしておく.
			m_vPos.x = LANE_MAX;
		}
		if (m_vPlayerPos.z + EFFECT_DISP_POS > m_vPos.z) {
			//エフェクト表示処理.
			m_pCEffectBase->SetEffectStart(true);
		}
		break;
	//左に移動.
	case enHorizonMove_Type::Left_Move:
		//左移動.
		m_vPos.x -= HORIZON_SPEED;

		//次のレーンに行けばまた縦移動.
		if (m_vPos.x <= m_fOldPos_x - MOVE_WIDTH) {
			m_vPos.x = m_fOldPos_x - MOVE_WIDTH;
			m_enVerticalMoveType = enVerticalMove_Type::Up;
		}

		//レーンの左端に行けば右移動へ.
		if (m_vPos.x <= LANE_MIN) {
			m_enHorizonMoveType = enHorizonMove_Type::Right_Move;
			//位置を微調整.
			m_vPos.x = LANE_MIN;
		}
	
		if (m_vPlayerPos.z + EFFECT_DISP_POS> m_vPos.z) {
			//エフェクト表示処理.
			m_pCEffectBase->SetEffectStart(true);
		}
		break;
	}

	//エフェクトの中心位置設定.
	m_pCEffectBase->SetCenterPos(m_vPos);
}

