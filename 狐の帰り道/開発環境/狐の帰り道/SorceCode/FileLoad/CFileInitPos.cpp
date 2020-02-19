#include "CFileInitPos.h"

/**********************************************
*		ファイルでの初期位置クラス.
**/
CFileInitPos::CFileInitPos()
	: m_FileNum		(0)
	, m_ColumnMax	(0)
	, m_LineMax		(0)
	, m_ppCFile		(nullptr)
	, m_FileMax		(0)
{
}

CFileInitPos::~CFileInitPos()
{
	//ファイル閉じる.
	ReleaseFile();
}

//=======================================.
//		敵の座標設定.
//=======================================.
void CFileInitPos::SetinngEnemyPos()
{
	//ファイルの読み込み処理関数.
	LoadFile();
}


//========================================.
//		ファイルの読み込み.
//========================================.
void CFileInitPos::LoadFile()
{
	//ファイルパス.
	const char FileName[][256] = {
		"Data\\File\\Stage1_EnemyData.csv",
		"Data\\File\\Stage2_EnemyData.csv",
		"Data\\File\\Stage3_EnemyData.csv",
	};

	//ファイルの最大数取得.
	m_FileMax = sizeof FileName / sizeof FileName[0];
	
	m_ppCFile = new CFile*[m_FileMax]();
	
	for (int file = 0; file < m_FileMax; file++) {
		//ファイル読み込みクラスをファイル数分作成.
		m_ppCFile[file] = new CFile();
		//ファイル番号によって適応するファイルの読み取り.
		m_ppCFile[file]->InputFile(FileName[file]);
	}

}


//========================================.
//		ファイル解放処理関数.
//========================================.
void CFileInitPos::ReleaseFile()
{
	for (int file = m_FileMax - 1; file >= 0; file--) {
		//ファイルを閉じる.
		m_ppCFile[file]->Close();
		//ファイルクラスの解放.
		SAFE_DELETE(m_ppCFile[file]);
	}
	//ファイルクラス配列解放.
	SAFE_DELETE_ARRAY(m_ppCFile);
}

