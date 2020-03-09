#include "CSEPlayManager.h"

/**************************************
*		サウンド再生管理クラス.
**/
CSEPlayManager::CSEPlayManager()
	: m_ppCOneCSound	(nullptr)
	, m_ppCLoopSound	(nullptr)
	, m_pCSoundResource	(nullptr)
	, m_pbPlayOneSE		(nullptr)
	, m_pCnt			(nullptr)
	, m_pbPlayLoopSE	(nullptr)
	, m_PlaySound		(0)
	, m_SoundVolume		(VOLUME_STANDERD_MAX)
	, m_pSEVolume		(nullptr)
{
}

CSEPlayManager::~CSEPlayManager()
{
}

//=======================================.
//		初期化処理関数.
//=======================================.
HRESULT CSEPlayManager::Init(HWND hWnd)
{
	//サウンド読み込みクラス.
	m_pCSoundResource = new CSoundResource();
	//初期化処理関数.
	m_pCSoundResource->Init(hWnd);
	//読み込み処理関数.
	m_pCSoundResource->Load();

	//サウンドクラス.
	m_ppCOneCSound = new clsSound*[ALL_ONESE_MAX]();
	m_ppCLoopSound = new clsSound*[LOOP_SE_MAX]();
	//それぞれのサウンド取得.
	for (int sound = 0; sound < ALL_ONESE_MAX; sound++) {
		m_ppCOneCSound[sound] = m_pCSoundResource->GetOneSound(sound);
	}
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_ppCLoopSound[sound] = m_pCSoundResource->GetLoopSound(sound);
	}

	//再生フラグの配列動的確保.
	m_pbPlayOneSE = new bool[ONE_SE_MAX]();
	//SEの音量の配列動的確保.
	m_pSEVolume = new int[ONE_SE_MAX]();

	//カウントの配列動的確保.
	m_pCnt = new int[ONE_SE_MAX]();
	//単発SEで使う変数の初期化.
	for (int sound = 0; sound < ONE_SE_MAX ; sound++) {
		m_pbPlayOneSE[sound] = false;
		m_pSEVolume[sound] = VOLUME_STANDERD_MAX;
		if (sound >= static_cast<int>(CSoundResource::enSoundSE::Great) &&
			sound <= static_cast<int>(CSoundResource::enSoundSE::Bad)) {
			m_pSEVolume[sound] = VOLUME_MAX;
		}
	}

	//ループ再生フラグの配列動的確保.
	m_pbPlayLoopSE = new bool[LOOP_SE_MAX]();
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_pbPlayLoopSE[sound] = false;
	}

	return S_OK;
}

//=======================================.
//		再生処理関数.
//=======================================.
void CSEPlayManager::Play()
{
	//単発SEの再生.
	for (int sound = 0; sound < ONE_SE_MAX; sound++) {
		if (m_pbPlayOneSE[sound] == true) {
			if (m_ppCOneCSound[(sound * SE_RESEVE) + m_pCnt[sound]]->IsStopped() == true) {
				//初めに戻す.
				m_ppCOneCSound[(sound * SE_RESEVE) + m_pCnt[sound]]->SeekToStart();
				//音量調整.
				m_ppCOneCSound[(sound * SE_RESEVE) + m_pCnt[sound]]->VolumeConvert(m_pSEVolume[sound]);
				//再生.
				m_ppCOneCSound[(sound * SE_RESEVE) + m_pCnt[sound]]->Play();
				//フラグを下す.
				m_pbPlayOneSE[sound] = false;
			}

			//次のSEへ.
			m_pCnt[sound]++;
			if (m_pCnt[sound] >= SE_RESEVE) {
				m_pCnt[sound] = 0;
			}
		}
	}

	//ループSEの再生.
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		if (m_pbPlayLoopSE[sound] == true) {
			if (m_ppCLoopSound[sound]->IsStopped() == true) {
				//初めに戻す.
				m_ppCLoopSound[sound]->SeekToStart();
				//再生.
				m_ppCLoopSound[sound]->Play();

				m_PlaySound = sound;
			}
			//音量調整.
			m_ppCLoopSound[sound]->VolumeConvert(m_SoundVolume);
		}
		else {
			if (m_ppCLoopSound[sound]->IsPlaying() == true) {
				m_ppCLoopSound[sound]->Stop();
			}
		}
	}

}

//========================================.
//		解放処理関数.
//========================================.
HRESULT CSEPlayManager::Release()
{
	//配列解放.
	SAFE_DELETE_ARRAY(m_pSEVolume);
	SAFE_DELETE_ARRAY(m_pbPlayLoopSE);
	SAFE_DELETE_ARRAY(m_pCnt);
	SAFE_DELETE_ARRAY(m_pbPlayOneSE);

	//解放処理関数.
	m_pCSoundResource->Release();
	//サウンド読み込みクラス解放.
	SAFE_DELETE(m_pCSoundResource);

	//ループサウンドクラス.
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_ppCLoopSound[sound] = nullptr;
	}
	//ループサウンドクラスの配列解放処理.
	SAFE_DELETE_ARRAY(m_ppCLoopSound);

	for (int sound = 0; sound < ALL_ONESE_MAX; sound++) {
		m_ppCOneCSound[sound] = nullptr;
	}
	//サウンドクラスの配列解放.
	SAFE_DELETE_ARRAY(m_ppCOneCSound);

	return S_OK;
}