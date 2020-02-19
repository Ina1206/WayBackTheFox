#include "CCommand_Base.h"

/************************************************
*		コマンド基底クラス.
**/
CCommand_Base::CCommand_Base()
	: m_mView				()
	, m_mProj				()
	, m_vCameraPos			()
	, m_pCResourceManager	(nullptr)
	, m_pCSprite			(nullptr)
	, m_pCDepth_Stencil		(nullptr)
	, m_fAlpha				(1.0f)
	, m_vPos				(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vInitPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_ButtonNum			(0)
	, m_pButtonNum			(nullptr)
	, m_penInput_Decision	(nullptr)
	, m_penOld_Decision		(nullptr)
	, m_bDispFlag			(false)
	, m_bJudgePossible		(false)
	, m_LongPushCnt			(0)
	, m_vPlayerPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_pCSEPlayManager		(nullptr)
	, m_ppCEffectBase		(nullptr)
	, m_pCButtonLightSprite	(nullptr)
	, m_fButtonLightAlpha	(LIGHT_ALPHA_MAX)
	, m_fButtonLightScale	(LIGHT_SCALE_MIN)
	, m_bButtonLightFinish	(false)

{
	//初期化処理関数.
	Init();
}

CCommand_Base::~CCommand_Base()
{
	//エフェクト.
	for (int effect = static_cast<int>(enInput_Decision::Good); effect >= 0; effect--) {
		SAFE_DELETE(m_ppCEffectBase[effect]);
	}
	SAFE_DELETE_ARRAY(m_ppCEffectBase);

	//SE再生クラス.
	m_pCSEPlayManager = nullptr;

	//前回の判定フラグ.
	SAFE_DELETE_ARRAY(m_penOld_Decision);
	//成功判定フラグ.
	SAFE_DELETE_ARRAY(m_penInput_Decision);
	//デプスステンシルクラス.
	if (m_pCDepth_Stencil != nullptr) {
		m_pCDepth_Stencil = nullptr;
	}
	//スプライトクラス.
	if (m_pCSprite != nullptr) {
		m_pCSprite = nullptr;
	}
	//読み込み管理クラス.
	if (m_pCResourceManager != nullptr) {
		m_pCResourceManager = nullptr;
	}
}

//============================================.
//		値設定処理関数.
//============================================.
void CCommand_Base::SetValue(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	//読み込みクラス.
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	//デプスステンシルクラス.
	m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();

	m_mView			= mView;
	m_mProj			= mProj;
	m_vCameraPos	= vCamePos;

}

//===========================================.
//		初期化処理関数.
//===========================================.
void CCommand_Base::Init()
{
	//成功判定フラグ.
	m_penInput_Decision = new enInput_Decision[COMMAND_DECISION_MAX]();
	//前回の判定.
	m_penOld_Decision = new enInput_Decision[COMMAND_DECISION_MAX]();
	//成功判定フラグ初期化.
	for (int command = 0; command < COMMAND_DECISION_MAX; command++) {
		m_penInput_Decision[command] = enInput_Decision::Max;
		m_penOld_Decision[command] = enInput_Decision::Max;
	}

	//SE再生クラス.
	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();

	//エフェクト.
	int effect_Max = static_cast<int>(enInput_Decision::Bad);
	m_ppCEffectBase = new CEffectBase*[effect_Max]();
	//クラス取得.
	m_ppCEffectBase[static_cast<int>(enInput_Decision::Great)]	= new CGreatEffect();
	m_ppCEffectBase[static_cast<int>(enInput_Decision::Good)]	= new CGoodEffect();
}

//===========================================.
//		ボタン描画処理関数.
//===========================================.
void CCommand_Base::RenderButton()
{
	//半透明処理.
	if (m_vPos.x == m_vPlayerPos.x) {
		m_fAlpha = ALPHA_MAX;
	}
	else {
		m_fAlpha = ALPHA_MIN;
	}

	//画像の列挙体のコマンド開始番号.
	int m_SpriteStart = static_cast<int>(CResourceSprite::enSprite::CommandStart);


	//ボタン番号と画像開始番号を足して画像列挙体と同一にする.
	int m_CommandSprite = m_ButtonNum + m_SpriteStart;

	//現在作られていないボタンでエラーが起こらないように.
	if (m_CommandSprite >= static_cast<int>(CResourceSprite::enSprite::YButton)) {
		m_CommandSprite = static_cast<int>(CResourceSprite::enSprite::YButton);
	}

	//クラス.
	m_pCSprite = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(m_CommandSprite));

	//位置.
	m_pCSprite->SetPosition(m_vPos);
	//透過値.
	m_pCSprite->SetAlpha(m_fAlpha);

	//描画.
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);

	//他に影響が出ないように戻しておく.
	m_pCSprite->SetAlpha(ALPHA_MAX);

}

//==================================================.
//		SE再生処理関数.
//==================================================.
void CCommand_Base::PlayEffectAndSE()
{
	//エフェクト更新処理.
	for (int effect = 0; effect < static_cast<int>(enInput_Decision::Bad); effect++) {
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->UpDate();
		}
	}

	//判定ごとの音の処理.
	for (int command = 0; command < COMMAND_DECISION_MAX; command++) {
		if (m_penInput_Decision[command] != enInput_Decision::Max) {
			
			//前回のコマンドと違っていたら鳴らす.
			if (m_penInput_Decision[command] != m_penOld_Decision[command]) {
				//判定結果.
				const int m_Decision = static_cast<int>(m_penInput_Decision[command]);					
				//流す音番号.
				const int m_SoundNum = m_Decision + static_cast<int>(CSoundResource::enSoundSE::Great);	
				
				//エフェクト再生.
				if (m_Decision < static_cast<int>(enInput_Decision::Bad)) {
					m_ppCEffectBase[m_Decision]->SetCenterPos(m_vPlayerPos);
					m_ppCEffectBase[m_Decision]->SetEffectStart(true);
				}

				//SE再生.
				m_pCSEPlayManager->SetSEPlayFlag(static_cast<CSoundResource::enSoundSE>(m_SoundNum), true);

				m_penOld_Decision[command] = m_penInput_Decision[command];
			}
		}
	}

}

//==================================================.
//		エフェクト描画処理関数.
//==================================================.
void CCommand_Base::RenderEffect()
{
	for (int effect = 0; effect < static_cast<int>(enInput_Decision::Bad); effect++) {
		//描画処理関数.
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->Render(m_mView, m_mProj, m_vCameraPos);
		}
	}
}