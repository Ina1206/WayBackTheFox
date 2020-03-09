#ifndef CSOUND_RESOURCE_H
#define CSOUND_RESOURCE_H

#include "..\Global.h"
#include "CSound.h"

/**********************************************
*	サウンド読み込みクラス.
******/
class CSoundResource
{
public:
	CSoundResource();
	~CSoundResource();

	//============列挙体=============//.
	//ループしない音.
	enum class enSoundSE {
		Hit,				//当たった時の音.
		EnemyFly,			//敵が飛ぶ時の音.
		Jump,				//ジャンプ音.
		Great,				//Great判定時の音.
		Good,				//Good判定時の音.
		Bad,				//Bad判定時の音.
		App,				//出現音.
		Player_Move,		//プレイヤー横移動音.
		Ghost_Move,			//タヌキ横移動.
		Time,				//タイム音.
		SceneChange,		//シーン遷移.
		ItemGet,			//アイテムアイコンにアイテムが来た時の音.
		Poko_Hit,			//殴る時の当たった音.
		Player_Step,		//プレイヤーの足音.
		Fall_Down,			//倒れたときの音.
		Boss_Fly,			//ボスが飛ぶ時の音.
		Boss_Star,			//ボスが星になる時.
		Button_push,		//ボタンを押したとき.
		Facial_UpChange,	//表情段階が上がった時の音.
		Facial_DownChange,	//表情段階が下がった時の音.
		ButtonChage,		//連打ボタン変更時.
		Fusuma_Open,		//ふすまを開ける.
		Fusuma_Close,		//ふすまを閉める.
		Evaluation_Disp,	//評価文字表示時.
		Char_Disp,			//文字表示時.
		GageDown,			//ゲージ減る.

		Max,				//最大数.
		Start = Hit,		//最初.
	};
	//ループする音.
	enum class enLoopSound {
		LongPush,			//長押し時の音.
		TestTilte_Part2,	//テストタイトル.
		GameMain_BGM,		//ゲーム中BGM.
		Boss_BGM,			//ボス戦のBGM.
		EndingHight_BGM,	//エンディング優BGM.
		EndingMiddle_BGM,	//エンディング良BGM.
		EndingLow_BGM,		//エンディング可BGM.

	
		Max,				//最大数.
		Start = LongPush,	//最初.
	};

	//=============定数==============//.
	const int SE_RESEVE		= 10;											//SEの補欠.

	const int ONE_SE_MAX	= static_cast<int>(enSoundSE::Max);				//単発SEの最大数.
	const int LENGTH_MAX	= 256;											//文字数最大数.
	const int ALL_SE_MAX	= ONE_SE_MAX * SE_RESEVE;						//補欠も合わせたすべての単発SEの最大数.
	
	const int LOOP_SE_MAX	= static_cast<int>(enLoopSound::Max);			//ループSEの最大数.

	//=============関数==============//.
	HRESULT Init(HWND hWnd);												//初期化処理関数.
	HRESULT Load();															//読み込み処理関数.
	HRESULT Release();														//解放処理関数.

	//情報取得処理関数.
	clsSound* GetOneSound(int SoundSE) { return m_ppCOneSound[SoundSE]; }	//単発SEクラス獲得処理関数.
	clsSound* GetLoopSound(int SoundSE) { return m_ppCLoopSound[SoundSE]; }	//ループSEクラス獲得処理関数.
private:
	//=============関数==============//.
	HRESULT Create(int sound, const char* pfilename, 
				   clsSound* pCSound, char* paliasname);				//作成処理関数.
	HRESULT Check(int sound, clsSound* pCSound);							//調べる処理関数.
	void	AddAliasName(char* alias_name, int name);						//エイリアス名の結合処理関数.												
	HRESULT	OneceLoadSE();													//単発SEの読み込み処理関数.
	HRESULT LoopLoadSound();												//ループSEの読み込み処理関数.

	//=============変数==============//.
	HWND		m_hWnd;				//ウィンドウハンドル.

	clsSound**	m_ppCOneSound;		//サウンドクラス.
	char**		m_ppOneSoundSE;		//SEのエイリアス名.

	clsSound**	m_ppCLoopSound;		//ループサウンド.
	char**		m_ppLoopSoundSE;		
};

#endif	//#ifndef CSOUND_RESOURCE_H.