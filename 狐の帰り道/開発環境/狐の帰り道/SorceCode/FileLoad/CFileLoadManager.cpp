#include"CFileLoadManager.h"
#include <time.h>

/*****************************************
*		ファイル読み込み管理クラス.
*******/
CFileLoadManager::CFileLoadManager()
	: m_pCFileInitPos	(nullptr)
	, m_pCFileCommandSet(nullptr)
	, m_pstAllEnemyInfo	(nullptr)
	, m_FileMax			(0)
	, m_FileNum			(0)
	, m_pEnemyCnt		(nullptr)
{
}

CFileLoadManager::~CFileLoadManager()
{
	//解放処理関数.
	Release();
}

//==========================================.
//		すべての設定処理関数.
//==========================================.
void CFileLoadManager::ALL_Setting()
{
	m_pCFileInitPos = new CFileInitPos();
	m_pCFileCommandSet = new CFileCommandSetting();
	
	m_pCFileInitPos->SetinngEnemyPos();
	m_pCFileCommandSet->Setting();

	//ファイルの最大数取得.
	if (m_pCFileInitPos->GetFileMax() <= m_pCFileCommandSet->GetFileMax()) {
		m_FileMax = m_pCFileInitPos->GetFileMax();
	}
	else {
		m_FileMax = m_pCFileCommandSet->GetFileMax();
	}

	//ステージごとの全敵の情報配列動的確保.
	m_pstAllEnemyInfo = new stAllEnemyInfo[m_FileMax]();
	m_pEnemyCnt = new int[static_cast<int>(enEnemy::Max)]();

	//敵の設定処理関数.
	for (int file = 0; file < m_FileMax; file++) {
		SettingEnemy(file);
	}

	//それぞれのファイル解放しておく.
	SAFE_DELETE(m_pCFileCommandSet);
	SAFE_DELETE(m_pCFileInitPos);

}

//==========================================.
//		敵の設定処理関数.
//==========================================.
void CFileLoadManager::SettingEnemy(int fileNum)
{
	//番号チェック処理関数.
	CheckNum(fileNum);

	m_pstAllEnemyInfo[fileNum].m_pEnemyMax = new int[static_cast<int>(enEnemy::Max)]();

	//敵の最大数カウント処理関数.
	EnemyMaxCnt(fileNum);
	//敵の情報配列動的確保.
	m_pstAllEnemyInfo[fileNum].m_pvInitPos = new D3DXVECTOR3[m_pstAllEnemyInfo[fileNum].m_AllEnemyMax]();
	m_pstAllEnemyInfo[fileNum].m_pButtonNum = new int[m_pstAllEnemyInfo[fileNum].m_AllEnemyMax]();

	for (int enemy = 0; enemy < static_cast<int>(enEnemy::Max); enemy++) {
		m_pEnemyCnt[enemy] = 0;
	}

	for (int column = 0; column < m_pCFileInitPos->GetFileColumnMax(fileNum); column++) {
		for (int line = 0; line < m_pCFileInitPos->GetFileLineMax(fileNum); line++) {
			if (m_pCFileInitPos->GetEnemyFile(fileNum, column, line) > 0) {
				//敵の位置設定.
				SettingEnemyPos(fileNum, column, line);
				//敵事に所持しているボタン番号設定.
				SettingButton(fileNum, column, line);

				//追加.
				m_pEnemyCnt[m_pCFileInitPos->GetEnemyFile(fileNum, column, line) - 1]++;
			}
		}
	}
}

//==========================================.
//		番号チェック処理関数.
//==========================================.
void CFileLoadManager::CheckNum(int filenum)
{
	for (int column = 0; column < m_pCFileInitPos->GetFileColumnMax(filenum); column++) {
		for (int line = 0; line < m_pCFileInitPos->GetFileLineMax(filenum); line++) {
			if( m_pCFileInitPos->GetEnemyFile(filenum,column, line) > 0 ){
				_ASSERT_EXPR(m_pCFileInitPos->GetEnemyFile(filenum,column, line) > 0, L"データなし");
				_ASSERT_EXPR(m_pCFileCommandSet->GetCommandDate(filenum, column, line) > 0, L"どちらかのデータが不足しています.");
			}
		}
	}
}

//==========================================.
//		敵の最大値をカウント処理関数.
//==========================================.
void CFileLoadManager::EnemyMaxCnt(int fileNum)
{
	for (int column = 0; column < m_pCFileInitPos->GetFileColumnMax(fileNum); column++) {
		for (int line = 0; line < m_pCFileInitPos->GetFileLineMax(fileNum); line++) {
			if (m_pCFileInitPos->GetEnemyFile(fileNum,column, line) > 0) {
				//種類別最大数.
				m_pstAllEnemyInfo[fileNum].m_pEnemyMax[m_pCFileInitPos->GetEnemyFile(fileNum, column, line) - 1]++;
				//全敵の総合の最大数.
				m_pstAllEnemyInfo[fileNum].m_AllEnemyMax++;
			}
		}
	}
}

//==========================================.
//		敵の位置設定処理関数.
//==========================================.
void CFileLoadManager::SettingEnemyPos(int fileNum, int column, int line)
{
	//敵の番号.
	int m_pEnemyNum = m_pCFileInitPos->GetEnemyFile(fileNum,column, line) - 1;
	//敵の種類の初めの番号.
	int EnemyStartNum = 0;
	for (int enemy = 0; enemy < m_pEnemyNum; enemy++) {
		EnemyStartNum += m_pstAllEnemyInfo[fileNum].m_pEnemyMax[enemy];
	}

	//敵番号.
	int enemyNum = EnemyStartNum + m_pEnemyCnt[m_pEnemyNum];
	m_pstAllEnemyInfo[fileNum].m_pvInitPos[enemyNum] = D3DXVECTOR3((line * WIDTH) - START_WIDTH, STANDERD_Y, (DEPTH_INTERVAL*column) + START_DEPTH);
}

//==========================================.
//		ボタンの種類設定処理関数.
//==========================================.
void CFileLoadManager::SettingButton(int fileNum, int column, int line)
{
	int m_pEnemyNum = m_pCFileInitPos->GetEnemyFile(fileNum, column, line) - 1;

	//敵の種類の初めの番号.
	int EnemyStartNum = 0;
	for (int enemy = 0; enemy < m_pEnemyNum; enemy++) {
		EnemyStartNum += m_pstAllEnemyInfo[fileNum].m_pEnemyMax[enemy];
	}
	//敵番号.
	int enemyNum = EnemyStartNum + m_pEnemyCnt[m_pEnemyNum];
	m_pstAllEnemyInfo[fileNum].m_pButtonNum[enemyNum] = m_pCFileCommandSet->GetCommandDate(fileNum, column, line);
}

//==========================================.
//		解放処理関数.
//==========================================.
void CFileLoadManager::Release()
{
	//それぞれの配列解放.
	for (int file = m_FileMax - 1; file >= 0; file--) {
		SAFE_DELETE_ARRAY(m_pstAllEnemyInfo[file].m_pEnemyMax);	//敵ごとの最大数.
		SAFE_DELETE_ARRAY(m_pstAllEnemyInfo[file].m_pButtonNum);//ボタン番号.
		SAFE_DELETE_ARRAY(m_pstAllEnemyInfo[file].m_pvInitPos);	//初期位置.
	}
	SAFE_DELETE_ARRAY(m_pEnemyCnt);			//敵のカウント.
	SAFE_DELETE_ARRAY(m_pstAllEnemyInfo);	//ステージごとの全部の敵の情報
}