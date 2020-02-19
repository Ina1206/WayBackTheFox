#ifndef CFILECOMMANDSETTING_H
#define CFILECOMMANDSETTING_H

#include "CFileLoad.h"
#include "..\GameObject\Chara\Enemy\EnemyType.h"
#include "..\Global.h"
#include "..\Command\enumCommand_Global.h"

/**************************************
*		コマンド設定ファイルクラス.
*****/
class CFileCommandSetting
{
public:
	CFileCommandSetting();
	~CFileCommandSetting();


	//================関数=====================//.
	void Setting();			//設定処理関数.
	void Close();			//閉じる処理関数.

	//～情報獲得処理関数～.
	int GetCommandDate(int fileNum, int column, int line) { return m_ppCFile[fileNum]->GetData(column, line); }

	int GetFileMax() { return m_FileMax; }

	//～情報置換処理関数～.
	void SetEnemyMax(enEnemy enemyType, int enemyMax) { m_pstCommandInfo[static_cast<int>(enemyType)].m_pCommandMax = enemyMax; }
	void SetEnemyPos(enEnemy enemyType, int enemy, D3DXVECTOR3 vPos) { m_pstCommandInfo[static_cast<int>(enemyType)].m_pvPos[enemy] = vPos; }
	void SetFileNum(int filenum) { m_FileNum = filenum; }
private:
	//================関数=====================//.
	void	Init();						//初期化処理関数.
	void	Load();						//読み込み処理関数.
	void	Release();					//解放処理関数.

	//================構造体====================//.
	//各種コマンドの種類ごとの情報.位置.
	struct stCommandInfo {
		int				m_pCommandMax;	//コマンドの最大値.
		D3DXVECTOR3*	m_pvPos;		//コマンド表示

		stCommandInfo()
			: m_pCommandMax	(0)
			, m_pvPos		(nullptr)
		{}
	};

	//=================変数=====================//.
	CFile*			m_pCFile;			//ファイルの読み込みクラス.
	int				m_FileNum;			//ファイル番号.
	stCommandInfo*	m_pstCommandInfo;	//コマンド毎の情報.

	int*			m_pEnemyMax;		//各種敵の最大数.

	CFile**			m_ppCFile;			//ファイルの読み込みクラス.
	int				m_FileMax;			//ファイルの最大数.
};

#endif	//#ifndef CFILECOMMANDSETTING_H.