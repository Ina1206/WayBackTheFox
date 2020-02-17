#ifndef C_SE_PLAYMANAGER_H
#define C_SE_PLAYMANAGER_H

#include "CSoundResource.h"

/**************************************
*		サウンド再生管理クラス.
**/
class CSEPlayManager
{
public:
	CSEPlayManager();
	~CSEPlayManager();

	//==================定数==================//.
	const int ONE_SE_MAX			= static_cast<int>(CSoundResource::enSoundSE::Max);		//SEの最大数.
	const int SE_RESEVE				= 10;													//SEの補欠.
	const int ALL_ONESE_MAX			= ONE_SE_MAX * SE_RESEVE;								//補欠合わせたSEの最大数.
	const int LOOP_SE_MAX			= static_cast<int>(CSoundResource::enLoopSound::Max);	//ループ音の最大数.
	const int VOLUME_MAX			= 1000;													//サウンドの最大音量.
	const int VOLUME_STANDERD_MAX	= 500;

	//=============シングルトン化==============//.
	static CSEPlayManager* GetSEPlayManagerInstance()
	{
		static CSEPlayManager s_Instance;
		return &s_Instance;
	}

	//==================関数==================//.
	HRESULT Init(HWND hWnd);			//初期化処理関数.
	void	Play();						//再生処理関数.
	HRESULT Release();					//解放処理関数.

	//～情報置換処理関数～.
	//SE再生フラグ.
	void SetSEPlayFlag(CSoundResource::enSoundSE SoundSE,bool flag) { m_pbPlayOneSE[static_cast<int>(SoundSE)] = flag; }
	//LoopSE再生フラグ.
	void SetLoopSEPlay(CSoundResource::enLoopSound LoopSE, bool flag) { m_pbPlayLoopSE[static_cast<int>(LoopSE)] = flag;}
	//音量置換処理関数.
	void SetVolume(int volume) { m_SoundVolume = volume; }
	//SEの音量置換処理関数.
	void SetSE_Volume(CSoundResource::enSoundSE SoundSE, int Volume) { m_pSEVolume[static_cast<int>(SoundSE)] = Volume; }

	clsSound*	GetSound() { return m_ppCOneCSound[static_cast<int>(CSoundResource::enSoundSE::Hit)]; }
	int	GetPlaySound() { return m_PlaySound; }
private:
	clsSound**			m_ppCOneCSound;		//サウンドクラス.
	clsSound**			m_ppCLoopSound;		//ループSEクラス.
	CSoundResource*		m_pCSoundResource;	//サウンド読み込みクラス.

	bool*				m_pbPlayOneSE;		//音の再生フラグ.
	int*				m_pCnt;				//カウント.

	bool*				m_pbPlayLoopSE;		//ループ音再生フラグ.
	int					m_PlaySound;		//再生中のBGM.
	int					m_SoundVolume;		//音量.
	int*				m_pSEVolume;		//SEの音量.
};

#endif	//#ifndef C_SE_PLAYMANAGER_H.