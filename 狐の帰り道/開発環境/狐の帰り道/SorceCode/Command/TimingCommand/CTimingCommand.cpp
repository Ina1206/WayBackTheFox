#include "CTimingCommand.h"

/**************************************
*		タイミングコマンド.
**/
CTimingCommand::CTimingCommand()
	: m_pCSpriteMaru		(nullptr)
	, m_vMaruPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_fScale				(2.0f)
	, m_bCircleDispry		(false)
	, m_bButtonPushFlag		(false)
{
	
}

CTimingCommand::~CTimingCommand()
{
}

//=========================================.
//		更新処理関数.
//=========================================.
void CTimingCommand::Update(enCommandType CommandType) 
{

	//表示判定処理関数.
	if (m_penInput_Decision[STANDERD_COMMAND_USE] == enInput_Decision::Max) {
		DecisionDisp();
	}

	if (m_bDispFlag == true) {
		//丸の大きさの縮小.
		ScaleDownCircle();
		//同じレーンにいればコマンド判定.
		if (m_bCircleDispry == true && m_bJudgePossible == true) {
			if (m_LongPushCnt == 0) {
				//コマンド判定処理関数.
				DecisionCommand(CommandType);
			}
		}

		if (m_bButtonPushFlag == true && m_bButtonLightFinish == false) {
			//ボタン押したときの円の処理関数.
			ButtonPushCircle();
		}
	}
}

//==========================================.
//		描画処理関数.
//==========================================.
void CTimingCommand::Render()
{
	if (m_bCircleDispry == true) {
		//丸の描画処理関数.
		RenderCircle();
	}

	if (m_bDispFlag == true) {
		//ボタンの描画処理関数.
		m_vPos.y += m_fDispHight;
		RenderButton();
	}

	if (m_bButtonPushFlag == true && m_bButtonLightFinish == false) {
		//ボタンを押した時の丸の描画処理関数.
		RenderButtonPush();
	}
}

//==========================================.
//		解放処理関数.
//==========================================.
void CTimingCommand::Release()
{
	m_pCSprite = nullptr;
	m_pCSpriteMaru = nullptr;
}

//==========================================.
//		表示判定処理関数.
//==========================================.
void CTimingCommand::DecisionDisp()
{
	if (m_vPlayerPos.z + DISPRY_DISTANCE > m_vPos.z) {
		//ボタン画像表示.
		m_bDispFlag = true;

		//丸の表示非表示.
		if (m_vPlayerPos.x == m_vPos.x) {
			m_bCircleDispry = true;
		}
		else {
			m_bCircleDispry = false;
		}

		//キャラより手前に来たら消す.
		if (m_vPlayerPos.z > m_vPos.z) {
			m_bDispFlag = false;
			m_bCircleDispry = false;
			m_fScale = CIRCLE_SIZE_MAX;
		}
	}
}

//==========================================.
//		コマンド判定処理関数.
//==========================================.
void CTimingCommand::DecisionCommand(enCommandType CommandType)
{
	//敵のボタンと同じものを押したのか.
	if (m_ButtonNum == static_cast<int>(CommandType)) {
	
		//Good判定.
		if (m_fScale >= CIRCLE_GREAT_SIZE) {
			m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Good;
		}
		else {
			//Greatの判定.
			m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Great;
			
			//Bad判定.
			if (m_fScale < CIRCLE_BAD_SIZE) {
				m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Bad;
			}
		}

		//ボタン押したフラグ.
		m_bButtonPushFlag = true;
		m_fButtonLightAlpha = ALPHA_MAX;
		m_fButtonLightScale = LIGHT_SCALE_MIN;
	}
}

//==========================================.
//		円の大きさを小さくする処理関数.
//==========================================.
void CTimingCommand::ScaleDownCircle()
{
	//Playerとの距離で拡縮.
	m_fScale = (((m_vPos.z - START_DIFFERENCE )- m_vPlayerPos.z) / DISPRY_DISTANCE) + CIRCLE_SIZE_MIN;
}

//==========================================.
//		丸の描画処理.
//==========================================.
void CTimingCommand::RenderCircle()
{
	//円画像.
	m_pCSpriteMaru = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::TimingCommand);

	//位置.
	m_vMaruPos = m_vPos;
	m_vMaruPos.y = m_vPos.y + m_fDispHight;
	m_pCSpriteMaru->SetPosition(m_vMaruPos);
	//大きさ.
	m_pCSpriteMaru->SetScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));
	
	//描画.
	CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepth_Stencil->SetDepth(false);
	m_pCSpriteMaru->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepth_Stencil->SetDepth(true);
}

//================================================.
//		ボタン押したときの円の処理関数.
//================================================.
void CTimingCommand::ButtonPushCircle()
{
	//光の大きさ処理.
	m_fButtonLightScale += LIGHT_SCALE_SPEED;
	if (m_fButtonLightScale > LIGHT_SCALE_MAX) {
		m_fButtonLightScale = LIGHT_SCALE_MAX;
	}

	//光の透過値処理.
	m_fButtonLightAlpha -= LIGHT_ALPHA_SPEED;
	if (m_fButtonLightAlpha <= LIGHT_ALPHA_MIN) {
		m_fButtonLightAlpha = LIGHT_ALPHA_MIN;
		//ボタンと丸の板ポリの非表示.
		m_bCircleDispry = false;
		m_bDispFlag		= false;
		m_bButtonLightFinish = true;
		m_fScale = CIRCLE_SIZE_MAX;

	}
}

//================================================.
//		ボタンを押したときの丸の描画処理関数.
//================================================.
void CTimingCommand::RenderButtonPush()
{
	//画像アドレス取得.
	m_pCButtonLightSprite = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::HitButton);

	//位置.
	m_pCButtonLightSprite->SetPosition(m_vPos);

	//大きさ.
	m_pCButtonLightSprite->SetScale(D3DXVECTOR3(m_fButtonLightScale, m_fButtonLightScale, m_fButtonLightScale));

	//透過値.
	m_pCButtonLightSprite->SetAlpha(m_fButtonLightAlpha);

	//描画.
	CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepth_Stencil->SetDepth(false);
	m_pCButtonLightSprite->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepth_Stencil->SetDepth(true);
}