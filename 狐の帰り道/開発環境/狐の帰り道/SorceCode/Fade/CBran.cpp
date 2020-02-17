#include "CBran.h"

CBran::CBran()
	: m_ppCSpriteUI			(nullptr)
	, m_pCResourceManager	(nullptr)
	, m_pDepth_Srencil		(nullptr)
	, m_vPos				(nullptr)
	, m_vRot				(nullptr)
	, m_enBran_State		(enBran_Status::MAX)
	, m_bBran_OpenFlag		(true)
	, m_bBran_OpenEndFlag	(false)
	, m_bBran_CloseFlag		(true)
	, m_WaitTime			(0)
	//===================================.
	//		追加.
	, m_pCSEPlayManager		(nullptr)
	//===================================.
{
	m_ppCSpriteUI	= new CSpriteUI*[BRAN_MAX];
	m_vPos			= new D3DXVECTOR3[BRAN_MAX];
	m_vRot			= new D3DXVECTOR3[BRAN_MAX];

	m_vPos[LEFT]  = LEFT_INIT_POSITION;
	m_vPos[RIGHT] = RIGHT_INIT_POSITION;

	m_vRot[LEFT]  = LEFT_ROTATION;
	m_vRot[RIGHT] = RIGHT_ROTATION;

	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
}

CBran::~CBran()
{
	//解放処理関数.
	Release();
}


//------------------------------------.
//	更新処理関数.
//------------------------------------.
void CBran::UpDate()
{
	if (m_enBran_State == enBran_Status::Open)
	{
		Bran_Open();
		m_WaitTime = 0;
	}
	if (m_enBran_State == enBran_Status::Close)
	{
		m_WaitTime++;
		Bran_Close();
	}

	//================================================.
	//		追加.
	//ふすまの位置によって音量変更.
	int Volume = static_cast<int>(((m_vPos[RIGHT].x - CLOSE_POSITION.x) / (RIGHT_INIT_POSITION.x / 2)) * m_pCSEPlayManager->VOLUME_STANDERD_MAX);
	//BGM.
	m_pCSEPlayManager->SetVolume(Volume);
	//SE(足音は通常音量の半分小さい).
	Volume /= 3;
	m_pCSEPlayManager->SetSE_Volume(CSoundResource::enSoundSE::Player_Step,Volume);
	//================================================.
}

//------------------------------------.
//	描画処理関数.
//------------------------------------.
void CBran::Render()
{
	//スプライトクラスUIのアドレス取得.
	for (int bran = 0; bran < BRAN_MAX; bran++)
	{
		m_ppCSpriteUI[bran] = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::Bran);
		_ASSERT_EXPR(m_ppCSpriteUI != nullptr, L"m_ppCSpriteUI == nullptr");
		m_ppCSpriteUI[bran]->SetPosition(m_vPos[bran]);
		m_ppCSpriteUI[bran]->SetRotation(m_vRot[bran]);
		//描画.
		m_pDepth_Srencil->SetDepth(false);
		m_ppCSpriteUI[bran]->Render();
		m_pDepth_Srencil->SetDepth(true);
	}
}

//------------------------------------.
//～情報置換関数～.
//------------------------------------.
void CBran::SetBran_Open()
{
	m_vPos[LEFT] = LEFT_INIT_POSITION;
	m_vPos[RIGHT] = RIGHT_INIT_POSITION;
	m_bBran_OpenFlag = false;

	//開く動作開始.
	m_enBran_State = enBran_Status::Open;

	//=====================================.
	//		追加.
	//ふすまを開ける音.
	m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Fusuma_Open, true);
	//=====================================.
}


void CBran::SetBran_Close()
{
	for (int bran = 0; bran < BRAN_MAX; bran++) {
		m_vPos[bran] = CLOSE_POSITION;
	}
	m_bBran_OpenEndFlag = false;
	m_bBran_CloseFlag = false;

	//閉める動作開始.
	m_enBran_State = enBran_Status::Close;

	//======================================.
	//		追加.
	//ふすまを閉める音.
	m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Fusuma_Close, true);
	//======================================.
}

//------------------------------------.
//	初期化処理関数.
//------------------------------------.
void CBran::Init()
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pDepth_Srencil	= CDepth_Stencil::GetDepthStencilInstance();
}

//------------------------------------.
//	開く.
//------------------------------------.
void CBran::Bran_Open()
{
	if (m_bBran_OpenFlag == false)
	{
		if (m_vPos[LEFT].x <= CLOSE_POSITION.x) {
			m_vPos[LEFT].x += SPEED;
		}
		if (m_vPos[RIGHT].x >= CLOSE_POSITION.x) {
			m_vPos[RIGHT].x -= SPEED;
		}

		//x座標がClosePositionを超えたらフラグを立てる.
		if (m_vPos[0].x >= CLOSE_POSITION.x && m_vPos[1].x <= CLOSE_POSITION.x)
		{
			for (int bran = 0; bran < BRAN_MAX; bran++)
			{
				m_vPos[bran].x = CLOSE_POSITION.x;
			}
			m_bBran_OpenFlag = true;
			m_bBran_OpenEndFlag = true;
		}
	}
}

//------------------------------------.
//	閉める.
//------------------------------------.
void CBran::Bran_Close()
{
	if (m_bBran_CloseFlag == false)
	{
		if (m_WaitTime > CLOSE_TIME) {
			if (m_vPos[LEFT].x >= LEFT_INIT_POSITION.x) {
				m_vPos[LEFT].x -= SPEED;
			}
			if (m_vPos[RIGHT].x <= RIGHT_INIT_POSITION.x) {
				m_vPos[RIGHT].x += SPEED;
			}

			if (m_vPos[LEFT].x <= LEFT_INIT_POSITION.x && m_vPos[RIGHT].x >= RIGHT_INIT_POSITION.x)
			{
				m_bBran_CloseFlag = true;
			}
		}
	}
}

//------------------------------------.
//	解放処理関数.
//------------------------------------.
void CBran::Release()
{
	SAFE_DELETE_ARRAY(m_vRot);
	SAFE_DELETE_ARRAY(m_vPos);
	SAFE_DELETE_ARRAY(m_ppCSpriteUI);
}
