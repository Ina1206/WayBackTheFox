#include "CSceneManager.h"

#include <crtdbg.h>

CSceneManager::CSceneManager()
	: m_hWnd				(nullptr)
	, m_pDevice11			(nullptr)
	, m_pContext11			(nullptr)
	, m_pCScene				(nullptr)
	, m_pCInput				(nullptr)
	, m_pCBran				(nullptr)
	, m_enScene				(enScene::Title)
	, m_enOperation			(enOperation::Possible)
	, m_Frame				(0)
	, m_BGMnum				()
	, m_BGM_Volume			(BGM_VOLUME_MAX)
	, m_bLoadFinish			(false)
	, m_pStageTypeNum		(nullptr)
	, m_OldStageTypeNum		(-1)
	, m_StageCnt			(0)
	, m_PushButtonCnt		(0)
	, m_SceneChangeCnt		(0)
	, m_bSpecialStageFlag	(false)
{
	m_pCInput	= new clsXInput();
	m_pCBran	= new CBran();
}

CSceneManager::~CSceneManager()
{
	Destroy();
}

//=======================================.
//		シーン設定処理関数.
//=======================================.
void CSceneManager::SceneChange()
{
	m_pCInput->UpdateStatus();//これ入れないと動かない.

	//開いて一番初めのシーン.
	if (m_pCScene == nullptr) {
		//クラス作成.
		m_pCScene = new CTitle();
		m_pCScene->Init_Process();

		//再生.
		CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::TestTilte_Part2, true);
	}

	//Aボタンが押され続けたときに進むのを防ぐ処理.
	if ((m_pCInput->IsPress(XINPUT_GAMEPAD_A)) || 
		(GetAsyncKeyState(VK_RETURN) & 0x8000) ||
		(GetAsyncKeyState(VK_SPACE) & 0x8000)) {
		m_SceneChangeCnt++;
	}
	else {
		m_SceneChangeCnt = 0;
	}

	//操作可能の時.
	if (m_enOperation == enOperation::Possible) {
		if (m_enScene != enScene::GameMain)
		{
			//タイトルのフェードが終わったか.
			if (m_pCScene->GetUIDrawEndFlag() == true)
			{
				if (((m_pCInput->IsPress(XINPUT_GAMEPAD_A)) 
					|| (GetAsyncKeyState(VK_RETURN) & 0x8000)
					|| (GetAsyncKeyState(VK_SPACE) & 0x8000))
					&& m_SceneChangeCnt == 1)
				{
					//再度入力.
					if (m_PushButtonCnt == 0) {
						if (m_enOperation == enOperation::Possible)
						{
							m_enOperation = enOperation::Impossible;
						}
						//次のシーンへ.
						m_pCBran->SetBran_Open();

						if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
							m_bSpecialStageFlag = true;
						}

						CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
						m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::SceneChange, true);
					}
				}
				else {
					m_PushButtonCnt = 0;
				}
			}
			else
			{
				//フェードが終わる前にAボタンが押されたか.
				if ((m_pCInput->IsPress(XINPUT_GAMEPAD_A))
					 || (GetAsyncKeyState(VK_RETURN) & 0x8000)
					|| GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					m_PushButtonCnt++;
				}
			}
		}

		//GameMainの時.
		if (m_enScene == enScene::GameMain && m_pCScene->GetEndGameMain() == true)
		{
			if (m_enOperation == enOperation::Possible)
			{
				m_enOperation = enOperation::Impossible;
			}
			//次のシーンへ.
			if (m_Frame == 0)
			{
				m_pCBran->SetBran_Open();
			}
			m_Frame++;
		}
		else
		{
			m_Frame = 0;
		}
	}
	//シーンを切り替える.
	SceneSetting();

	//フェードアウトが終われば操作可能にする.
	if (m_pCBran->GetBran_CloseFlag() == true && m_pCBran->GetBran_OpenFlag() == true)
	{
		m_enOperation = enOperation::Possible;
	}
	else {
		m_enOperation = enOperation::Impossible;
	}

	//※ふすまの関数名Open,Close逆になっている.
	g_BranOpenFlag = m_pCBran->GetBran_CloseFlag();

#ifdef _DEBUG
	if (m_enScene != enScene::GameMain) {
		if (m_pCScene->GetUIDrawEndFlag() == true && GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//次のシーンへ.
			m_pCBran->SetBran_Open();
			CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::SceneChange, true);
		}
}
	else {
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//次のシーンへ.
			m_pCBran->SetBran_Open();
			CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::SceneChange, true);
		}
	}
#endif	//#ifdef _DEBUG.
}

//=======================================.
//		シーン変更処理関数.
//=======================================.
void CSceneManager::SceneSetting()
{
	if (m_pCBran->GetBran_OpenEnd() == true)
	{
		//解放処理.
		if (m_pCScene != nullptr) {
			SAFE_DELETE(m_pCScene);
		}

		//サウンド.
		CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
		//ファイル.
		CFileLoadManager* m_pCFielLoadManager = CFileLoadManager::GetCFileLoadManagerInstance();

		//次のシーン設定.
		switch (m_enScene) {
		//タイトル.
		case enScene::Title:
			m_enScene = enScene::GameMain;
			m_pCScene = new CGameMain();

			//ステージ番号の指定.
			{
				const int NormalStageMax = m_pCFielLoadManager->GetFileMax() - 1;
				if (m_StageCnt >= NormalStageMax) {
					//ステージ選択処理関数.
					StageSelect();
					m_StageCnt = 0;
				}

				//特別ステージ番号設定.
				if (m_bSpecialStageFlag == true) {
					const int SpecialStageNum = 3;	//特別ステージ番号.
					m_StageCnt = SpecialStageNum;
				}
			}

			m_pCFielLoadManager->SetFileNum(m_pStageTypeNum[m_StageCnt]);
			m_OldStageTypeNum = m_pStageTypeNum[m_StageCnt];

			m_StageCnt++;

			m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::TestTilte_Part2, false);
			m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::GameMain_BGM, true);
			break;
		//ゲーム中.
		case enScene::GameMain:
			m_enScene = enScene::Clear;
			m_pCScene = new CClear();
			m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::Boss_BGM, false);
			break;
		//クリア.
		case enScene::Clear:
			m_enScene = enScene::Title;
			m_pCScene = new CTitle();
			m_pCSEPlayManager->SetLoopSEPlay(static_cast<CSoundResource::enLoopSound>(m_pCSEPlayManager->GetPlaySound()), false);
			m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::TestTilte_Part2, true);
			break;
		}

		//初期化処理.
		if (m_pCScene != nullptr) {
			m_pCScene->Init_Process();
		}

		m_pCBran->SetBran_Close();
	}
}

//========================================.
//		読み込み処理関数.
//========================================.
void CSceneManager::InitLoad(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd		= hWnd;
	m_pDevice11	= pDevice11;
	m_pContext11 = pContext11;

	//ファイル読み込みクラス.
	CFileLoadManager* m_pCFileLoadManager = CFileLoadManager::GetCFileLoadManagerInstance();
	m_pCFileLoadManager->ALL_Setting();
	//ステージの最大数.
	m_pStageTypeNum = new int[m_pCFileLoadManager->GetFileMax()]();
	for (int stage = 0; stage < m_pCFileLoadManager->GetFileMax(); stage++) {
		m_pStageTypeNum[stage] = stage;
	}

	//読み込みクラス.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCResourceManager->Load(m_hWnd, pDevice9, m_pDevice11, m_pContext11);

	//デプスステンシルクラス.
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->Init(m_pDevice11, m_pContext11);

	//サウンドクラス.
	CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
	m_pCSEPlayManager->Init(m_hWnd);

	m_pCBran->Init();

	//読み込み終了.
	m_bLoadFinish = true;
}

//========================================.
//		更新処理関数.
//========================================.
void CSceneManager::UpDate()
{
	m_pCBran->UpDate();
	m_pCScene->UpDate();

	//サウンド系統.
	CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
	//サウンド再生.
	m_pCSEPlayManager->Play();
	//サウンド音量.
	m_pCSEPlayManager->SetVolume(m_BGM_Volume);

	//終了.
	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		PostQuitMessage(0);
	}
}

//========================================.
//		描画処理関数.
//========================================.
void CSceneManager::Render(D3DXMATRIX& mProj, D3DXVECTOR3& vLight)
{
	m_pCScene->Value(mProj, vLight);
	m_pCScene->Render();
	m_pCBran->Render();
}

//========================================.
//		解放処理関数.
//========================================.
void CSceneManager::Destroy()
{
	//サウンドクラス.
	CSEPlayManager::GetSEPlayManagerInstance()->Release();

	//読み込みクラス.
	CResourceManager::GetResourceManagerInstance()->Release();			

	SAFE_DELETE(m_pCBran);
	SAFE_DELETE(m_pCInput);
	//シーン.
	SAFE_DELETE(m_pCScene);

	//配列解放.
	SAFE_DELETE_ARRAY(m_pStageTypeNum);

	m_pContext11	= nullptr;
	m_pDevice11		= nullptr;
	m_hWnd			= nullptr;
}

//==============================================.
//		ステージ選択処理関数.
//==============================================.
void CSceneManager::StageSelect()
{
	//ステージの最大数取得.
	int stageMax = CFileLoadManager::GetCFileLoadManagerInstance()->GetFileMax();

	//ランダムのステージの重複を避けるため.
	for (;;) {
		while (stageMax > 1)
		{
			int stageNum = rand() % stageMax;
			stageMax--;

			int StageType = m_pStageTypeNum[stageMax];
			m_pStageTypeNum[stageMax] = m_pStageTypeNum[stageNum];
			m_pStageTypeNum[stageNum] = StageType;
		}
		//次のステージ番号と一致しないと出ない.
		if (m_pStageTypeNum[0] != m_OldStageTypeNum) {
			break;
		}
		//ステージ最大数の値初期化.
		stageMax = CFileLoadManager::GetCFileLoadManagerInstance()->GetFileMax();
	}
}