#include "CLongPushCommand.h"

/***************************************
*		長押しコマンドクラス.
***********/
CLongPushCommand::CLongPushCommand()
	: m_ppCCommandSprite	(nullptr)
	, m_pvCommandPos		(nullptr)
	, m_PushCount			(0)
	, m_bSoundCheck			(false)
	, m_pCEffectBase		(nullptr)
	, m_fButtonHigh			(0)
	, m_vOldPos				(0.0f, 0.0f, 0.0f)
{
	//コマンド用スプライトクラスの配列動的確保.
	m_ppCCommandSprite = new CSprite*[static_cast<int>(enCommandSpriteType::Max)]();
	//コマンド位置の配列動的確保.
	m_pvCommandPos = new D3DXVECTOR3[static_cast<int>(enCommandSpriteType::Max)]();
	//表示フラグ初期化.
	m_bDispFlag = false;

	//エフェクトクラス作成.
	m_pCEffectBase = new CLongPushEffect();

	//ボタン高さ.
	m_fButtonHigh = BUTTON_DISP_POS_MAX;
}

CLongPushCommand::~CLongPushCommand()
{
	//エフェクトクラス解放.
	SAFE_DELETE(m_pCEffectBase);

	for (int command = static_cast<int>(enCommandSpriteType::Max) - 1; command >= 0; command--) {
		m_ppCCommandSprite[command] = nullptr;
	}
	//解放.
	SAFE_DELETE_ARRAY(m_pvCommandPos);
	SAFE_DELETE_ARRAY(m_ppCCommandSprite);

}

//=====================================.
//		更新処理関数.
//=====================================.
void CLongPushCommand::Update(enCommandType CommandType)
{
	//長押しコマンドのコマンド画像表示.
	for (int command = 0; command < static_cast<int>(enCommandSpriteType::Max); command++) {
		m_pvCommandPos[command].x = m_vPos.x;
		m_pvCommandPos[command].y = START_DISP_HEIGH - ((command % 2) * DISP_HEIGH_ADJUST);
		m_pvCommandPos[command].z = (m_vPos.z - (COMMAND_LENGHT * (DEPTH_ADJUST * command))) - COMMAND_POS_Z;
	}

	//表示判定処理関数.
	DecisionDisp();

	if (m_bDispFlag == true) {
		if (m_vPos.x == m_vPlayerPos.x && m_bJudgePossible == true) {
			//コマンド判定処理関数.
			DecisionCommand(CommandType);
		}
		//最初に判定した後押しながら横に行くとBad判定.
		if (m_vPos.x != m_vPlayerPos.x && m_PushCount > 0) {
			if (m_penInput_Decision[StartDecisionNum] != enInput_Decision::Max) {
				m_PushCount = DECISION_TERMIN;
				m_penInput_Decision[EndDecisionNum] = enInput_Decision::Bad;
			}
		}
		//コマンド押さずに通り抜ける.
		const int COMMAND_START_NUM = static_cast<int>(enCommandSpriteType::CommandStart);
		if (m_pvCommandPos[COMMAND_START_NUM].z + GOOD_RANGE < m_vPlayerPos.z && 
			m_penInput_Decision[StartDecisionNum] == enInput_Decision::Max) {
			//判定終了.
			m_PushCount = DECISION_TERMIN;
		}
	}
	else if (m_PushCount > 0) {
		//押したまま非表示になるとBad判定.
		m_penInput_Decision[EndDecisionNum] = enInput_Decision::Bad;
		m_PushCount = DECISION_TERMIN;
	}

	//SE.
	if (m_PushCount > 0 && m_penInput_Decision[StartDecisionNum] != enInput_Decision::Max) {
		//再生.
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::LongPush, true);
		m_bSoundCheck = true;
		//エフェクト.
		if (m_pCEffectBase->GetEffectStartFlag() == false) {
			//中央座標の取得.
			m_pCEffectBase->SetCenterPos(m_vPlayerPos);
			//エフェクト表示開始フラグ.
			m_pCEffectBase->SetEffectStart(true);
		}
		//エフェクト更新処理関数.
		m_pCEffectBase->Update();
	}
	//鳴らしている場合.
	else if(m_bSoundCheck == true){
		//停止.
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::LongPush, false);
		m_bSoundCheck = false;
	}
}

//=====================================.
//		描画処理関数.
//=====================================.
void CLongPushCommand::Render()
{
	int Standerd_CommandAlpha = 0;	//コマンド内での透過値の基準.

	m_vPos.y += m_fButtonHigh;

	if (m_bDispFlag == true) {
		//ボタンの高さ変更.
		if (m_vPos.y > m_vOldPos.y) {
			if (m_fButtonHigh >= BUTTON_DISP_POS_MIN) {
				m_fButtonHigh -= BUTTON_DOWN_SPEED;
			}
		}

		//長押しコマンド描画.
		RenderCommand();
		//ボタンコマンド描画.
		RenderButton();
		//エフェクト描画.
		m_pCEffectBase->Render(m_mView, m_mProj, m_vCameraPos);
	}

	//前回のボタン座標設定.
	m_vOldPos = m_vPos;
}

//=====================================.
//		解放処理関数.
//=====================================.
void CLongPushCommand::Release()
{
	m_pvCommandPos = nullptr;
	m_ppCCommandSprite = nullptr;
}

//=====================================.
//		描画判定処理関数.
//=====================================.
void CLongPushCommand::DecisionDisp()
{
	//距離によって表示するかどうか.
	if (m_vPos.z < DISP_ALPHA) {
		m_bDispFlag = true;
		//プレイヤーより手前に行くと非表示.
		if (m_vPos.z < m_vPlayerPos.z) {
			m_bDispFlag = false;
		}
	}

	//判定とった後消す.
	if (m_bDispFlag == true && m_PushCount == DECISION_TERMIN) {
		m_bDispFlag = false;
	}
}

//=====================================.
//		コマンド判定処理関数.
//=====================================.
void CLongPushCommand::DecisionCommand(enCommandType CommandType)
{
	//敵の所持しているボタン番号と入力ボタン番号が一致しているかどうか.
	if (m_ButtonNum == static_cast<int>(CommandType)) {
		m_PushCount++;
	}
	else if(m_PushCount > 0) {
		if (m_penInput_Decision[StartDecisionNum] != enInput_Decision::Max) {
			//途中で離したら終了.
			m_PushCount = DECISION_TERMIN;
		}
		else {
			m_PushCount = 0;
		}
	}

	//コマンドスタート地点判定処理関数.
	if (m_PushCount == 1 && m_LongPushCnt == 0) {
		DecisionCommandStart();
	}

	//コマンド終了地点の判定処理関数.
	if (m_PushCount == DECISION_TERMIN) {
		DecisionCommandEnd();
	}

}

//=====================================.
//	コマンドスタート地点判定処理関数.
//=====================================.
void CLongPushCommand::DecisionCommandStart()
{
	const int COMMAND_START_NUM = static_cast<int>(enCommandSpriteType::CommandStart);

	//Great判定.
	if ((m_pvCommandPos[COMMAND_START_NUM].z - GREAT_RANGE) <= m_vPlayerPos.z &&
		(m_pvCommandPos[COMMAND_START_NUM].z + GREAT_RANGE) >= m_vPlayerPos.z) {
		m_penInput_Decision[StartDecisionNum] = enInput_Decision::Great;
	}
	//Good判定.
	else if((m_pvCommandPos[COMMAND_START_NUM].z - GOOD_RANGE) <= m_vPlayerPos.z &&
			(m_pvCommandPos[COMMAND_START_NUM].z + GOOD_RANGE) >= m_vPlayerPos.z) {
			m_penInput_Decision[StartDecisionNum] = enInput_Decision::Good;
	}
}

//======================================.
//	コマンド終了地点の判定処理関数.
//======================================.
void CLongPushCommand::DecisionCommandEnd()
{
	const int COMMAND_END_NUM = static_cast<int>(enCommandSpriteType::CommandEnd);

	//Great判定.
	if (m_pvCommandPos[COMMAND_END_NUM].z - GREAT_RANGE <= m_vPlayerPos.z &&
		m_pvCommandPos[COMMAND_END_NUM].z + GREAT_RANGE >= m_vPlayerPos.z) {
		m_penInput_Decision[EndDecisionNum] = enInput_Decision::Great;
	}
	//Good判定.
	else if (m_pvCommandPos[COMMAND_END_NUM].z - GOOD_RANGE <= m_vPlayerPos.z &&
			 m_pvCommandPos[COMMAND_END_NUM].z + GOOD_RANGE >= m_vPlayerPos.z) {
			 m_penInput_Decision[EndDecisionNum] = enInput_Decision::Good;
	}
	//Bad判定.
	else {
		m_penInput_Decision[EndDecisionNum] = enInput_Decision::Bad;
	}
}

//=====================================.
//		コマンド画像の描画.
//=====================================.
void CLongPushCommand::RenderCommand()
{
	int m_Intermediate	= static_cast<int>(enCommandSpriteType::Intermediate);	//間の四角.

	//クラスのアドレス.
	for (int circlecommand = 0; circlecommand < static_cast<int>(enCommandSpriteType::Max); circlecommand += 2) {
		//円のスプライトを取得.
		m_ppCCommandSprite[circlecommand] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::LongPushCircle);
	}
	//中間の四角のスプライトを取得.
	m_ppCCommandSprite[m_Intermediate] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Long_Square);

	//透過値と位置の設定.
	for (int command = 0; command < static_cast<int>(enCommandSpriteType::Max); command++) {
		//カメラの向きにあわさない.
		m_ppCCommandSprite[command]->SetCancelRotationFlag(false);
		//位置設定.
		m_ppCCommandSprite[command]->SetPosition(m_pvCommandPos[command]);
		//透過値設定.
		m_ppCCommandSprite[command]->SetAlpha(m_fAlpha);
		//描画.
		m_ppCCommandSprite[command]->Render(m_mView, m_mProj, m_vCameraPos);
	}
}