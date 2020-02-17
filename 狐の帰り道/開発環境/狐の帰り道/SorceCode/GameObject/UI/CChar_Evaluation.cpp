#include "CChar_Evaluation.h"

CChar_Evaluation::CChar_Evaluation()
	: m_ppCCharSprite	(nullptr)
	, m_pCSEPlayManager	(nullptr)
	, m_enClear_Status	(enClear_Status::Max)
	, m_pCInput			(nullptr)
	, m_vRot			(0.0f,0.0f,0.0f)
	, m_fScale			(nullptr)
	, m_fRot			(0.0f)
	, m_pbDispFlag		(nullptr)
	, m_frame			(0)
	, m_WaitTime		(0)
	, m_bCheckSE_Eva	(false)
	, m_bCheckSE_Char	(false)
{
	Init_Process();
}

CChar_Evaluation::~CChar_Evaluation()
{
}

//------------------------------------------.
//	初期設定処理関数.
//------------------------------------------.
void CChar_Evaluation::Init_Process()
{
	//動的確保.
	m_ppCCharSprite		= new CSprite*[SPRITE_MAX];
	m_fScale			= new float[SPRITE_MAX];
	m_pbDispFlag		= new bool[SPRITE_MAX];
	m_pCInput			= new clsXInput();


	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();

	for (int sprite = 0; sprite < CHAR_EVALUATION; sprite++)
	{
		//スケールの初期化.
		m_fScale[sprite] = SCALE_MIN;
	}
	m_fScale[CHAR_EVALUATION] = SCALE_MAX;

}

//------------------------------------------.
//	更新処理関数.
//------------------------------------------.
void CChar_Evaluation::UpDate()
{
	static int pushCnt = 0;	//再度入力を求めるためのカウント.

	m_frame++;
	//タイトル画面ですぐタイトルが表示されないようにする処理.
	if (m_frame < INPUT_OK || g_BranOpenFlag == false) {
		if (m_pCInput->IsPress(XINPUT_GAMEPAD_A)) {
			pushCnt++;
		}
	}

	m_pCInput->UpdateStatus();//これ入れないと動かない.

	if (m_pCInput->IsPress(XINPUT_GAMEPAD_A) && g_BranOpenFlag == true)
	{
		if (m_frame >= INPUT_OK && pushCnt == 0) {
			m_bMoveEndFlag = true;
		}
	}
	else {
		pushCnt = 0;
	}


	if (m_bMoveEndFlag == false)
	{
		if (m_frame > EVALUATION_DISP_TIME)
		{
			m_pbDispFlag[CHAR_EVALUATION] = true;
			SetScale_Dowm(CHAR_EVALUATION);
			if (m_bCheckSE_Eva == false) {
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Evaluation_Disp, true);
				m_bCheckSE_Eva = true;
			}
		}

		//「評価」が標準サイズになったら.
		if (m_fScale[CHAR_EVALUATION] == SCALE_STANDARD && m_frame > CHAR_DISP_TIME)
		{
			switch (m_enClear_Status)
			{
			case CUI_Base::enClear_Status::High:
				m_pbDispFlag[CHAR_HIGH] = true;
				SetRotation(CHAR_HIGH);
				break;
			case CUI_Base::enClear_Status::Middle:
				m_pbDispFlag[CHAR_MIDDLE] = true;
				SetRotation(CHAR_MIDDLE);
				break;
			case CUI_Base::enClear_Status::Low:
				m_pbDispFlag[CHAR_LOW] = true;
				SetRotation(CHAR_LOW);
				break;
			default:
				break;
			}
		}
	}
	else 
	{
		m_pbDispFlag[CHAR_EVALUATION] = true;
		m_fScale[CHAR_EVALUATION] = SCALE_STANDARD;
		m_fRot = ROTAITON_MAX;
		switch (m_enClear_Status)
		{
		case CUI_Base::enClear_Status::High:
			m_pbDispFlag[CHAR_HIGH]		= true;
			m_fScale[CHAR_HIGH]			= SCALE_STANDARD;
			break;
		case CUI_Base::enClear_Status::Middle:
			m_pbDispFlag[CHAR_MIDDLE]	= true;
			m_fScale[CHAR_MIDDLE]		= SCALE_STANDARD;
			break;
		case CUI_Base::enClear_Status::Low:
			m_pbDispFlag[CHAR_LOW]		= true;
			m_fScale[CHAR_LOW]			= SCALE_STANDARD;
			break;
		default:
			break;
		}
		if (m_bCheckSE_Char == false) {
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Char_Disp, true);
			m_bCheckSE_Char = true;
		}
	}
}

//------------------------------------------.
//	描画処理関数.
//------------------------------------------.
void CChar_Evaluation::Render()
{
	//クリア状態の設定.
	//低クリア.
	if (m_PointSum <= MIDDLE_POINT) {
		m_enClear_Status = enClear_Status::Low;
	}
	//中クリア.
	if (m_PointSum >= MIDDLE_POINT && m_PointSum <= HIGH_POINT) {
		m_enClear_Status = enClear_Status::Middle;
	}
	//高クリア.
	if (m_PointSum >= HIGH_POINT) {
		m_enClear_Status = enClear_Status::High;
	}

	//スプライトの表示.
	for (int sprite = 0; sprite < SPRITE_MAX; sprite++)
	{
		int spriteUI = (static_cast<int>(CResourceSprite::enSprite::Char_High)) + sprite;
		m_ppCCharSprite[sprite] = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(spriteUI));
		_ASSERT_EXPR(m_ppCCharSprite != nullptr, L"m_ppCCharSprite == nullptr");
		//位置設定.
		if (sprite == CHAR_EVALUATION) {
			m_vPos = EVALUATION_POS;
		}
		else {
			m_vPos = CHAR_POS;
		}
		m_ppCCharSprite[sprite]->SetPosition(m_vPos);

		//回転値の設定.
		m_vRot = D3DXVECTOR3(0.0f, 0.0f, m_fRot);
		if (sprite != CHAR_EVALUATION) {
			m_ppCCharSprite[sprite]->SetRotation(m_vRot);
		}

		//描画.
		m_pCDepth_Stencil->SetDepth(false);
		if (m_pbDispFlag[sprite] == true) {
			m_ppCCharSprite[sprite]->SetScale(D3DXVECTOR3(m_fScale[sprite], m_fScale[sprite], m_fScale[sprite]));
			m_ppCCharSprite[sprite]->Render(m_mView, m_mProj, m_vCameraPos);
		}
		m_pCDepth_Stencil->SetDepth(true);

	}
}

//------------------------------------------.
//	解放処理関数.
//------------------------------------------.
void CChar_Evaluation::Release()
{
	m_pCSEPlayManager = nullptr;

	SAFE_DELETE_ARRAY(m_fScale);
	SAFE_DELETE_ARRAY(m_pbDispFlag);

	for (int sprite = SPRITE_MAX - 1; sprite >= 0; sprite--)
	{
		if (m_ppCCharSprite[sprite] != nullptr)
		{
			m_ppCCharSprite[sprite] = nullptr;
		}

	}
	SAFE_DELETE_ARRAY(m_ppCCharSprite);
	SAFE_DELETE		 (m_pCInput);
}


//------------------------------------------.
//	縮小設定.
//------------------------------------------.
void CChar_Evaluation::SetScale_Dowm(int num)
{
	m_fScale[num] -= SCALE_SPEED;

	if (m_fScale[num] <= SCALE_STANDARD)
	{
		m_fScale[num] = SCALE_STANDARD;
	}
}

//------------------------------------------.
//	回転値設定.
//------------------------------------------.
void CChar_Evaluation::SetRotation(int num)
{
	m_fRot += ROTAITON_SPEED;
	m_fScale[num] += SCALE_SPEED_CHAR;

	if (m_fRot >= ROTAITON_MAX)
	{
		m_fRot = ROTAITON_MAX;
	}


	if (m_fScale[num] >= SCALE_STANDARD)
	{
		m_fScale[num] = SCALE_STANDARD;
		m_bMoveEndFlag = true;
		if (m_bCheckSE_Char == false) {
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Char_Disp, true);
			m_bCheckSE_Char = true;
		}
	}

}
