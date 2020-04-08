#include "CBarrageCommand.h"

/****************************************
*		連打コマンドクラス.
***************/
CBarrageCommand::CBarrageCommand()
	: m_fAlpha				(MAX_ALPHA)
	, m_ppCGageSprite		(nullptr)
	, m_pvGagePos			(nullptr)
	, m_fPushCnt			(0)
	, m_BarrageButtonNum	(0)
	, m_OldBarrageButtonNum	(0)
	, m_ChangeButtonCnt		(0)
	, m_ChangeAfterCnt		(0)
	, m_pCPushButtonSprite	(nullptr)
	, m_fPushButtonAlpha	(PUSH_ALPHA_MIN)
	, m_fPushButtonSize		(PUSH_SCALE_MIN)
	, m_bButtonChangeSE		(false)
	, m_BarrageCheckCnt		(0)
	, m_fButtonScale		(BUTTONSCALE_MIN)
	, m_Timer				(MAX_TIME)
	, m_Timer_num			(0)
	, m_ppCTimeSprite		(nullptr)
	, m_pCHitEffect			(nullptr)
	, m_bBGMChange			(false)
{
	//配列動的確保.
	m_ppCGageSprite = new CSpriteUI*[GAGE_SPRITE_MAX]();	//ゲージスプライトUIクラス.
	m_pvGagePos		= new D3DXVECTOR3[GAGE_SPRITE_MAX]();	//ゲージの表示位置.
	m_ppCTimeSprite = new CSpriteUI*[TIME_SPRITE_MAX]();	//タイムUIクラス.
	m_pButtonNum	= new int[USE_BUTTON_MAX]();			//ボタン番号.

	//エフェクトクラスのインスタンス.
	m_pCHitEffect	= new CHitEffect();						//ボタン押したときのエフェクトクラス.
	m_pCHitEffect->SetEffectScale(HIT_EFFECT_SCALE);		//エフェクトの大きさ.
}

CBarrageCommand::~CBarrageCommand()
{
	//解放処理関数.
	Release();
}

//============================================.
//		更新処理関数.
//============================================.
void CBarrageCommand::Update(enCommandType CommandType)
{
	if (m_bDispFlag == true && m_penInput_Decision[STANDERD_COMMAND_USE] == enInput_Decision::Max) {
		//コマンド判定処理関数.
		DecisionCommand(CommandType);
		//時間処理関数.
		Time();
		//エフェクト更新処理関数.
		m_pCHitEffect->Update();
	}

	if (m_bBGMChange == false && m_bDispFlag == true) {
		//BGM変更.
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::GameMain_BGM, false);
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::Boss_BGM, true);
		//音量.
		m_pCSEPlayManager->SetVolume(m_pCSEPlayManager->VOLUME_STANDERD_MAX);
		m_bBGMChange = true;
	}

}

//============================================.
//		描画処理関数.
//============================================.
void CBarrageCommand::Render()
{
	if (m_bDispFlag == true) {
		//ボタンの描画.
		RenderButton();

		//ボタンの光の描画.
		RenderPushButton();

		//ゲージの描画.
		RenderGage();

		//時間描画処理関数.
		RenderTime();

		//エフェクトの描画.
		m_pCHitEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//============================================.
//		解放処理関数.
//============================================.
void CBarrageCommand::Release()
{
	//エフェクトクラス解放.
	SAFE_DELETE(m_pCHitEffect);

	//動的確保解放.
	SAFE_DELETE_ARRAY(m_pButtonNum);
	SAFE_DELETE_ARRAY(m_ppCTimeSprite);
	SAFE_DELETE_ARRAY(m_pvGagePos);
	SAFE_DELETE_ARRAY(m_ppCGageSprite);


	m_pCSprite = nullptr;

}

//=============================================.
//		コマンド判定処理関数.
//=============================================.
void CBarrageCommand::DecisionCommand(enCommandType CommandType)
{
	//ボタン変更処理関数.
	ChangeButton();

	//変更後のカウント.
	m_ChangeAfterCnt++;

	//敵の所持しているボタン番号と入力ボタン番号が一致しているかどうか.
	if (m_ButtonNum == static_cast<int>(CommandType)) {
		//長押し防止.
		m_BarrageCheckCnt++;
		if (m_BarrageCheckCnt == 1) {
			if (m_fPushCnt < BARRAGE_MAX) {
				
				//押されたらカウント.
				m_fPushCnt++;

				//エフェクトの表示座標設定.
				D3DXVECTOR3 m_vEffectPos = m_vPos;
				m_vEffectPos.y += EFFECT_HIGH;
				m_pCHitEffect->SetCenterPos(m_vEffectPos);
				
				//エフェクト表示開始.
				m_pCHitEffect->SetEffectStart(true);

				//ボタンを光らす.
				m_fPushButtonAlpha = PUSH_ALPHA_MAX;
			}

			//SEの再生.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Button_push, true);
		}

		//光の透過.
		m_fPushButtonAlpha -= PUSH_ALPHA_SPEED;
		if (m_fPushButtonAlpha <= PUSH_ALPHA_MIN) {
			m_fPushButtonAlpha = PUSH_ALPHA_MIN;
		}
		//光の拡縮.
		m_fPushButtonSize += PUSH_SCALE_SPEED;
		if (m_fPushButtonSize > PUSH_SCALE_MAX) {
			m_fPushButtonSize = PUSH_SCALE_MAX;
		}
	}
	else {
		//ボタンの光を消す.
		m_fPushButtonAlpha = PUSH_ALPHA_MIN;
		m_fPushButtonSize = PUSH_SCALE_MIN;
		
		if (CommandType == enCommandType::Max) {
			m_BarrageCheckCnt = 0;
			return;
		}
		m_BarrageCheckCnt++;
		if (m_BarrageCheckCnt == 1 && m_ChangeAfterCnt > CHANGE_WAIT_TIME) {
			if (m_fPushCnt > 0) {
				m_fPushCnt--;
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::GageDown, true);
			}
		}
	}


	//時間内に押し終わればGreat判定.
	if (m_fPushCnt >= BARRAGE_MAX) {
		m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Great;
		m_bDispFlag = false;
	}

}

//============================================.
//		時間処理判定処理関数.
//============================================.
void CBarrageCommand::Time()
{

	m_Timer_num++;
	//一秒たてば減らす.
	if (m_Timer_num % FRAME == 0) {
		//制限時間減らす.
		m_Timer--;

		//5秒前から再生.
		if (m_Timer <= SOUND_TIME) {
			//SE再生.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Time, true);
		}

		m_Timer_num = 0;
	}

	//制限時間が終われば非表示.
	if (m_Timer <= 0) {
		m_bDispFlag = false;
		//時間までに押せなかったらBad.
		m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Bad;
	}

}

//===========================================.
//		時間描画処理関数.
//===========================================.
void CBarrageCommand::RenderTime()
{
	//画像パターンの設定.
	D3DXVECTOR2* Pattern = nullptr;
	Pattern = new D3DXVECTOR2[TIME_SPRITE_MAX]();
	Pattern[TIME_TENS_PLACE] = D3DXVECTOR2(static_cast<float>((m_Timer / TIME_TENS) % IMAGE_WIDTH_MAX), static_cast<float>((m_Timer / TIME_TENS) / IMAGE_HIGH_MAX));
	Pattern[TIME_ONE_RANK] = D3DXVECTOR2(static_cast<float>(m_Timer % IMAGE_WIDTH_MAX), static_cast<float>(m_Timer / IMAGE_HIGH_MAX));

	//描画.
	for (int timenum = 0; timenum < 2; timenum++) {
		//スプライトUIクラスのアドレス取得.
		m_ppCTimeSprite[timenum] = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::TimerNum);
		//位置.
		D3DXVECTOR3	TimePos = TIME_DISP_POS;
		TimePos.x += timenum * TIME_WIDTH;
		m_ppCTimeSprite[timenum]->SetPosition(TimePos);
		//パターン.
		m_ppCTimeSprite[timenum]->SetPattern(Pattern[timenum]);
		//描画.
		m_ppCTimeSprite[timenum]->Render();
	}

	//Pattern配列解放処理.
	SAFE_DELETE_ARRAY(Pattern);
}

//===========================================.
//		ボタン変更処理関数.
//===========================================.
void CBarrageCommand::ChangeButton()
{
	//連打ゲージの区切り.
	int m_BurrageButton_Delimiter = BARRAGE_MAX / USE_BUTTON_MAX;
	//使われるコマンドの最大数を区切って連打回数でボタンを変える.
	m_BarrageButtonNum = m_fPushCnt / m_BurrageButton_Delimiter;
	
	if (m_BarrageButtonNum < USE_BUTTON_MAX) {
		
		m_ButtonNum = m_pButtonNum[m_BarrageButtonNum];

		//ボタン変更演出準備.
		if (m_BarrageButtonNum != m_OldBarrageButtonNum) {
			//m_ChangeButtonCnt	= m_fPushCnt;
			m_fButtonScale		= BUTTONSCALE_MAX;
			m_bButtonChangeSE	= true;
			m_ChangeAfterCnt	= 0;
		}
	}

	m_fButtonScale -= SCALE_SPEED_BUT;
	if (m_fButtonScale < BUTTONSCALE_MIN) {
		m_fButtonScale = BUTTONSCALE_MIN;
		//SE.
		if (m_bButtonChangeSE == true) {
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::ButtonChage, true);
			m_bButtonChangeSE = false;
		}
	}


	m_OldBarrageButtonNum = m_BarrageButtonNum;
}

//===========================================.
//		ボタンの描画.
//===========================================.
void CBarrageCommand::RenderButton()
{
	//画像の列挙体のコマンド開始番号.
	int m_SpriteStart;
	if (m_bControllerFlag == true) {
		m_SpriteStart = static_cast<int>(CResourceSprite::enSprite::ControllerCommandStart);
	}
	else {
		m_SpriteStart = static_cast<int>(CResourceSprite::enSprite::KeybordCommandStart);
	}

	//ボタン番号と画像開始番号を足して画像列挙体と同一にする.
	int m_CommandSprite = m_ButtonNum + m_SpriteStart;

	//現在作られていないボタンでエラーが起こらないように.
	if (m_bControllerFlag == true) {
		if (m_CommandSprite >= static_cast<int>(CResourceSprite::enSprite::YButton)) {
			m_CommandSprite = static_cast<int>(CResourceSprite::enSprite::YButton);
		}
	}
	else {
		if (m_CommandSprite >= static_cast<int>(CResourceSprite::enSprite::UpButton)) {
			m_CommandSprite = static_cast<int>(CResourceSprite::enSprite::UpButton);
		}
	}

	//クラス.
	m_pCSprite = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(m_CommandSprite));


	//位置.
	m_vPos.y = BUTTON_POS_Y;
	m_vPos.z -= BUTTON_POS_Z;
	m_pCSprite->SetPosition(m_vPos);

	//大きさ.
	m_pCSprite->SetScale(D3DXVECTOR3(m_fButtonScale, m_fButtonScale, m_fButtonScale));

	//設定したい透過値.
	m_pCSprite->SetAlpha(m_fAlpha);

	//描画.
	m_pCDepth_Stencil->SetDepth(false);
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepth_Stencil->SetDepth(true);

	//他のところに影響が出ないように透過値を直しておく.
	m_pCSprite->SetAlpha(ALPHA_MAX);
	m_pCSprite->SetScale(D3DXVECTOR3(BUTTONSCALE_MIN, BUTTONSCALE_MIN, BUTTONSCALE_MIN));
}

//===========================================.
//		ゲージの描画.
//===========================================.
void CBarrageCommand::RenderGage()
{
	for (int gagenum = 0; gagenum < GAGE_SPRITE_MAX; gagenum++) {
		int sprite = static_cast<int>(CResourceSpriteUI::enSpriteUI::GageGround) + gagenum;
		m_ppCGageSprite[gagenum] = m_pCResourceManager->GetSpriteUI(static_cast<CResourceSpriteUI::enSpriteUI>(sprite));
	}

	//サイズ.
	float SizeW = m_fPushCnt / static_cast<float>(BARRAGE_MAX);
	m_ppCGageSprite[GAGE_NUM]->SetScale(SizeW);
	
	//ゲージの位置.
	m_vPos.x = GAGE_POS.x;
	m_vPos.y = GAGE_POS.y;
	m_vPos.z = GAGE_POS.z;
	D3DXVECTOR3 GagePos = D3DXVECTOR3(m_vPos.x + (((SizeW * GAGE_LENGTH_MAX) / GAGE_HALF) - GAGE_POS_START), m_vPos.y, m_vPos.z);
	//ゲージ調整.
	GagePos.x += GAGE_POS_ADJUST.x;
	GagePos.y += GAGE_POS_ADJUST.y;
	GagePos.z -= GAGE_POS_ADJUST.z;
	m_ppCGageSprite[GAGE_NUM]->SetPosition(GagePos);

	//ゲージ下地の位置.
	m_ppCGageSprite[GAGE_GROUN_NUM]->SetPosition(m_vPos);

	//描画.
	for (int gage_num = 0; gage_num < GAGE_SPRITE_MAX; gage_num++) {
		m_ppCGageSprite[gage_num]->Render();
	}
}

//================================================.
//		ボタンを押したときの描画処理関数.
//================================================.
void CBarrageCommand::RenderPushButton()
{
	m_pCPushButtonSprite = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::HitButton);
	//座標.
	m_pCPushButtonSprite->SetPosition(m_vPos);
	//透過値.
	m_pCPushButtonSprite->SetAlpha(m_fPushButtonAlpha);
	//大きさ.
	m_pCPushButtonSprite->SetScale(D3DXVECTOR3(m_fPushButtonSize, m_fPushButtonSize, m_fPushButtonSize));

	//描画.
	m_pCPushButtonSprite->Render(m_mView, m_mProj, m_vCameraPos);
}

//=================================================.
//		表示判定処理関数.
//=================================================.
void CBarrageCommand::DecisionDisp()
{

}