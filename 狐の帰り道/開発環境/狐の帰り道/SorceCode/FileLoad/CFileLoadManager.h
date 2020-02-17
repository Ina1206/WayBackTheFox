#ifndef CFILE_LOAD_MANAGER_H
#define CFILE_LOAD_MANAGER_H

#include "CFileInitPos.h"
#include "CFileCommandSetting.h"

class CFileLoadManager
{
public:
	CFileLoadManager();
	~CFileLoadManager();

	//===================定数======================//.
	const float WIDTH			= 1.5f;				//横幅.
	const float DEPTH_INTERVAL	= 2.0f;				//縦幅.
	const float STANDERD_Y		= 0.0f;				//基準Y軸.
	const float START_WIDTH		= 1.5f;				//スタートの間隔.
	const float START_DEPTH		= 6.0f;				//スタートの奥行.
	const int	FILE_MAX		= 3;				//ファイルの最大数.


	//===================関数======================//.
	void ALL_Setting();			//すべての設定処理関数.

	//～情報獲得処理関数～.
	//敵の座標.
	D3DXVECTOR3 GetEnemyPos(int enemy)		{ return m_pstAllEnemyInfo[m_FileNum].m_pvInitPos[enemy]; }
	//各敵の最大数.
	int			GetEnemyMax(int enemyType)	{ return m_pstAllEnemyInfo[m_FileNum].m_pEnemyMax[enemyType]; }
	//ボタン番号.
	int			GetButtonNum(int enemy)		{ return m_pstAllEnemyInfo[m_FileNum].m_pButtonNum[enemy]; }
	//敵総合の最大数.
	int			GetAllEnemyMax()			{ return m_pstAllEnemyInfo[m_FileNum].m_AllEnemyMax; }
	//ファイルの総数.
	int			GetFileMax()				{ return m_FileMax; }

	//～情報置換処理関数～.
	//ファイル番号設定.
	void		SetFileNum(int fileNum)		{ m_FileNum = fileNum; }

	//=================シングルトン=================//
	static CFileLoadManager* GetCFileLoadManagerInstance()
	{
		static CFileLoadManager Instance;
		return &Instance;
	}

private:
	//===================関数======================//.
	void EnemySetting(int fileNum);							//敵の設定処理関数.
	void NumCheck(int fileNum);								//番号チェック処理関数.
	void EnemyMaxCnt(int fileNum);							//敵の最大値をカウント処理関数.
	void EnemyPosSetting(int fileNum,int column, int line);	//敵の位置設定処理関数.
	void ButtonSetting(int fileNum, int column, int line);	//ボタンの種類設定処理関数.
	void Release();											//解放処理関数.

	//==================構造体======================//.
	//ステージごとの全部の敵の情報.
	struct stAllEnemyInfo {
		D3DXVECTOR3*	m_pvInitPos;	//初期位置.
		int*			m_pButtonNum;	//ボタン番号.
		int*			m_pEnemyMax;	//敵の最大数.
		int				m_AllEnemyMax;	//全ての敵の総合最大数.

		stAllEnemyInfo()
			: m_pvInitPos	(nullptr)
			, m_pButtonNum	(nullptr)
			, m_pEnemyMax	(nullptr)
			, m_AllEnemyMax	(0)
		{}
	};

	//===================変数========================//.
	CFileInitPos*			m_pCFileInitPos;	//敵の位置設定クラス.
	CFileCommandSetting*	m_pCFileCommandSet;	//コマンド読み込み処理クラス.
	
	stAllEnemyInfo*			m_pstAllEnemyInfo;	//ステージごとの全敵の情報.
	int						m_FileMax;			//ファイル最大数.
	int						m_FileNum;			//ファイル番号指定.
	int*					m_pEnemyCnt;		//敵のカウント.

};

#endif	//#ifndef CFILE_LOAD_MANAGER_H.