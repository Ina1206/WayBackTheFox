#include "CFileCommandSetting.h"

CFileCommandSetting::CFileCommandSetting()
	: m_pCFile			(nullptr)
	, m_FileNum			(0)
	, m_pstCommandInfo	(nullptr)
	, m_pEnemyMax		(nullptr)
	, m_ppCFile			(nullptr)
	, m_FileMax			(0)
{
}

CFileCommandSetting::~CFileCommandSetting()
{
	Close();
	//解放処理関数.
	Release();
}

//======================================.
//		設定処理関数.
//======================================.
void CFileCommandSetting::Setting()
{
	//読み込み処理関数.
	Load();
}

//======================================.
//		読み込み処理関数.
//======================================.
void CFileCommandSetting::Load()
{
	char FileName[][128] = {
		"Data\\File\\Stage1_CommandDate.csv",
		"Data\\File\\Stage2_CommandDate.csv",
		"Data\\File\\Stage3_CommandDate.csv",
	};
	//char FileName[][128] = {
	//	"Data\\File\\Extra_CommandDate.csv",
	//	"Data\\File\\Extra_CommandDate.csv",
	//	"Data\\File\\Extra_CommandDate.csv",
	//};

	//ファイルの最大数取得s.
	m_FileMax = sizeof FileName / sizeof FileName[0];

	//ファイルの読み込みクラスファイル数分配列動的確保.
	m_ppCFile = new CFile*[m_FileMax]();

	for (int file = 0; file < m_FileMax; file++) {
		//ファイル数分ファイル読み込みクラス作成.
		m_ppCFile[file] = new CFile();
		
		//ファイル数分読み込み.
		m_ppCFile[file]->FileInput(FileName[file]);
	}
	
}

//======================================.
//		初期化処理関数.
//======================================.
void CFileCommandSetting::Init()
{
	//各それぞれのコマンドの最大値の配列動的確保.
	m_pEnemyMax = new int[static_cast<int>(enEnemy::Max)];

	//コマンド情報の各種配列動的確保.
	m_pstCommandInfo = new stCommandInfo[static_cast<int>(enCommandType::Max)]();
	for (int command = 0; command < static_cast<int>(enCommandType::Max); command++) {
		m_pstCommandInfo[command].m_pvPos = new D3DXVECTOR3[m_pCFile->GetColumnDataMax()];
	}
	
}

//========================================.
//		閉じ処理関数.
//========================================.
void CFileCommandSetting::Close()
{

	for (int file = m_FileMax - 1; file >= 0; file--) {
		m_ppCFile[file]->Close();
	}
}

//=========================================.
//		解放処理関数.
//=========================================.
void CFileCommandSetting::Release()
{

	for (int file = m_FileMax - 1; file >= 0; file--) {
		SAFE_DELETE(m_ppCFile[file]);
	}
	SAFE_DELETE_ARRAY(m_ppCFile);
}