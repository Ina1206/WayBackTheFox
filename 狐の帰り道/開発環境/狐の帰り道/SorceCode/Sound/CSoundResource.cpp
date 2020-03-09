#include "CSoundResource.h"
#include <stdio.h>

/**********************************************
*	サウンド読み込みクラス.
******/
CSoundResource::CSoundResource()
	: m_hWnd		(nullptr)
	, m_ppCOneSound	(nullptr)
	, m_ppOneSoundSE(nullptr)
	, m_ppCLoopSound	(nullptr)
	, m_ppLoopSoundSE(nullptr)
{
}

CSoundResource::~CSoundResource()
{
}

//==================================.
//		初期化処理関数.
//==================================.
HRESULT CSoundResource::Init(HWND hWnd)
{
	//ウィンドウハンドル取得.
	m_hWnd = hWnd;

	//動的確保.
	//サウンドクラス.
	m_ppCOneSound = new clsSound*[ALL_SE_MAX]();
	//SEのエイリアス名.
	m_ppOneSoundSE = new char*[ALL_SE_MAX]();
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		m_ppOneSoundSE[sound] = new char[LENGTH_MAX]();
	}

	//初期化.
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		m_ppCOneSound[sound] = nullptr;
	}

	//サウンドクラス.
	m_ppCLoopSound = new clsSound*[LOOP_SE_MAX]();
	//SEのエイリアス名.
	m_ppLoopSoundSE = new char*[LOOP_SE_MAX]();
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_ppLoopSoundSE[sound] = new char[LENGTH_MAX]();
		m_ppCLoopSound[sound] = nullptr;
	}

	return S_OK;
}

//==================================.
//		読み込み処理関数.
//==================================.
HRESULT CSoundResource::Load()
{
	if (FAILED(OneceLoadSE())) {
		_ASSERT_EXPR(false, L"単発SEの読み込み失敗.");
		return E_FAIL;
	}

	if (FAILED(LoopLoadSound())) {
		_ASSERT_EXPR(false, L"ループSEの読み込み失敗");
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		解放処理関数.
//==================================.
HRESULT CSoundResource::Release()
{
	//ループSE.
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		//それぞれのエイリアス名配列解放.
		SAFE_DELETE_ARRAY(m_ppLoopSoundSE[sound]);
		//それぞれのサウンドクラス解放.
		SAFE_DELETE(m_ppCLoopSound[sound]);
	}
	//エイリアス名配列解放.
	SAFE_DELETE_ARRAY(m_ppLoopSoundSE);
	//サウンドクラス解放.
	SAFE_DELETE_ARRAY(m_ppCLoopSound);

	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		//それぞれのエイリアス名配列解放.
		SAFE_DELETE_ARRAY(m_ppOneSoundSE[sound]);
		//それぞれのサウンドクラス解放.
		SAFE_DELETE(m_ppCOneSound[sound]);
	}
	//エイリアス名配列解放.
	SAFE_DELETE_ARRAY(m_ppOneSoundSE);
	//サウンドクラス配列解放.
	SAFE_DELETE_ARRAY(m_ppCOneSound);

	return S_OK;
}

//==================================.
//		作成処理関数.
//==================================.
HRESULT CSoundResource::Create(int sound, const char* pfilename,
							   clsSound* pCSound, char* paliasname)
{
	//音の読み込み.
	if (FAILED(pCSound->Open(pfilename, paliasname, m_hWnd))) {
		return E_FAIL;
	}
	return S_OK;
}

//==================================.
//		調べる処理関数.
//==================================.
HRESULT CSoundResource::Check(int sound, clsSound* pCSound)
{
	if (sound < static_cast<int>(enSoundSE::Start) || ONE_SE_MAX < sound) {
		return E_FAIL;
	}

	if (pCSound != nullptr) {
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		エイリアス名の結合.
//==================================.
void CSoundResource::AddAliasName(char* alias_name, int name)
{
	//エイリアス名と番号の結合.
	char m_Addname[256];	//追加するもの.
	char m_SoundName[256];	//追加前のエイリアス名.

	//エイリアス名の元をコピー.
	strcpy_s(m_SoundName, LENGTH_MAX, alias_name);

	//エイリアス名の番号と元の名前追加.
	sprintf_s(m_Addname, "%d", name % SE_RESEVE);
	strcat_s(m_SoundName, m_Addname);

	//エイリアス名コピー.
	strcpy_s(m_ppOneSoundSE[name], sizeof(m_SoundName), m_SoundName);
}

//=================================================.
//			単発SEの読み込み処理関数.
//=================================================.
HRESULT CSoundResource::OneceLoadSE()
{
	//ファイルパス.
	const char m_filename[][256] =
	{
		"Data\\Sound\\SE\\Hit.mp3",				//敵とプレイヤーが当たった時.
		"Data\\Sound\\SE\\EnemyFly.mp3",		//敵が飛ぶ時の音.
		"Data\\Sound\\SE\\Jump.mp3",			//ジャンプ.
		"Data\\Sound\\SE\\Good.mp3",			//Great判定.
		"Data\\Sound\\SE\\Great.mp3",			//Good判定.
		"Data\\Sound\\SE\\Bad.mp3",				//Bad判定.
		"Data\\Sound\\SE\\UpRaccoon.mp3",		//タヌキ出てくる音.
		"Data\\Sound\\SE\\PlayerMove.mp3",		//プレイヤー横移動音.
		"Data\\Sound\\SE\\CowMove.mp3",			//タヌキ横移動.
		"Data\\Sound\\SE\\Time.mp3",			//タイム音.
		"Data\\Sound\\SE\\SceneChange.wav",		//シーン遷移.
		"Data\\Sound\\SE\\ItemGet.mp3",			//アイテムアイコンにアイテムが来た時の音.
		"Data\\Sound\\SE\\Punch.mp3",			//殴る時の当たった音.
		"Data\\Sound\\SE\\Walk.mp3",			//プレイヤーの足音.
		"Data\\Sound\\SE\\FallDown.mp3",		//倒れたときの音.
		"Data\\Sound\\SE\\BossFly.mp3",			//ボスが飛ぶ時の音.
		"Data\\Sound\\SE\\BossStar.mp3",		//ボスが星になる時.
		"Data\\Sound\\SE\\ButtonPush.mp3",		//ボタンを押したとき.
		"Data\\Sound\\SE\\FaceChange.mp3",		//表情段階が上がった時の音.
		"Data\\Sound\\SE\\FaceDown.mp3",		//表情段階が下がった時の音.
		"Data\\Sound\\SE\\ButtonChange.mp3",	//表情段階が下がった時の音.
		"Data\\Sound\\SE\\fusuma_open.mp3",		//ふすまを開ける.
		"Data\\Sound\\SE\\fusuma_close.mp3",	//ふすまを閉める.
		"Data\\Sound\\SE\\Evaluation_Disp.mp3",	//評価文字表示時.
		"Data\\Sound\\SE\\Char_Disp.mp3",		//文字表示時.
		"Data\\Sound\\SE\\GageDown.mp3",		//ゲージ減る時.
	};

	//エイリアス名の元.
	char m_Sound[][256] =
	{
		"Hit",							//敵とプレイヤーが当たった時.
		"EnemyFly",						//敵が飛ぶ時の音.
		"Jump",							//ジャンプ.
		"Great",						//Great判定.
		"Good",							//Good判定.
		"Bad",							//Bad判定.
		"App",							//出現音.
		"Player_Move",					//プレイヤー横移動音.
		"Ghost_Move",					//タヌキ横移動.
		"Time",							//タイム音.
		"SceneChange",					//シーン遷移.
		"ItemGet",						//アイテムアイコンにアイテムが来た時の音.
		"Poko_Hit",						//殴る時の当たった音.
		"Player_Step",					//プレイヤーの足音.
		"Fall_Down",					//倒れたときの音.
		"Boss_Fly",						//ボスが飛ぶ時の音.
		"Boss_Star",					//ボスが星になる時.
		"Button_push",					//ボタンを押したとき.
		"Facial_UpChange",				//表情段階が上がった時の音.
		"Facial_DownChange",			//表情段階が下がった時の音.
		"ButtonChange",					//連打ボタン変更時.
		"Fusuma_Open",					//ふすまを開ける.
		"Fusuma_Close",					//ふすまを閉める.
		"Evaluation_Disp",				//評価文字表示時.
		"Char_Disp",					//文字表示時.
		"GageDown",						//ゲージ減る時.
	};

	//エイリアス名の結合.
	for (int name = 0; name < ALL_SE_MAX; name++) {
		AddAliasName(m_Sound[name / SE_RESEVE], name);
	}


	//作成処理関数.
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {

		//範囲外かチェック.
		if (Check(sound / SE_RESEVE, m_ppCOneSound[sound])) {
			return E_FAIL;
		}

		m_ppCOneSound[sound] = new clsSound();

		if (FAILED(Create(sound, m_filename[sound / SE_RESEVE],
				   m_ppCOneSound[sound], m_ppOneSoundSE[sound]))) {
			return E_FAIL;
		}
	}

	return S_OK;
}

//===============================================.
//		ループSEの読み込み処理関数.
//===============================================.
HRESULT CSoundResource::LoopLoadSound()
{
	//ファイル名.
	const char filename[][256]=
	{
		"Data\\Sound\\SE\\LongPush.mp3",			//長押し時.
		"Data\\Sound\\BGM\\Title_Part1.mp3",		//タイトルBGM.
		"Data\\Sound\\BGM\\GameMain.mp3",			//ゲーム中BGM.
		"Data\\Sound\\BGM\\BossWar.mp3",			//ボス戦のBGM.
		"Data\\Sound\\BGM\\Clear_Hight.mp3",		//クリア優BGM.
		"Data\\Sound\\BGM\\Clear_Middle_Part1.mp3",	//クリア良BGM.
		"Data\\Sound\\BGM\\Clear_Low.mp3",			//クリア可BGM.
	};

	//エイリアス名.
	const char alias_name[][256]=
	{
		"Long_Push",		//長押し時.
		"Title_BGM",		//タイトルBGM.
		"GameMain_BGM",		//ゲーム中BGM.
		"Ending_BGM",		//エンディングBGM.
		"EndingHight_BGM",	//エンディング優BGM.
		"EndingMiddle_BGM",	//エンディング良BGM.
		"EndingLow_BGM",	//エンディング可BGM.

		"TestTilte_Part2",	//テストタイトル.
		"TestClear_Middle",	//テストクリア中.

	};

	//読み込み処理.
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		//エイリアス名.
		strcpy_s(m_ppLoopSoundSE[sound], LENGTH_MAX, alias_name[sound]);
		m_ppCLoopSound[sound] = new clsSound();
		//作成処理関数.
		if (FAILED(Create(sound, filename[sound], m_ppCLoopSound[sound], m_ppLoopSoundSE[sound]))) {
			return E_FAIL;
		}
	}

	return S_OK;
}