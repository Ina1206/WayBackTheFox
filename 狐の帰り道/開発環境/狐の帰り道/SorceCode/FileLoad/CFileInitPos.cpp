#include "CFileInitPos.h"

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
	//�t�@�C������.
	FileRelease();
}

//=======================================.
//		�G�̍��W�ݒ�.
//=======================================.
void CFileInitPos::SetinngEnemyPos()
{
	//�t�@�C���̓ǂݍ��ݏ����֐�.
	FileLoad();
}


//========================================.
//		�t�@�C���̓ǂݍ���.
//========================================.
void CFileInitPos::FileLoad()
{
	//�t�@�C���p�X.
	const char FileName[][256] = {
		"Data\\File\\Stage1_EnemyData.csv",
		"Data\\File\\Stage2_EnemyData.csv",
		"Data\\File\\Stage3_EnemyData.csv",
	};
	//const char FileName[][256] = {
	//	"Data\\File\\Extra_EnemyData.csv",
	//	"Data\\File\\Extra_EnemyData.csv",
	//	"Data\\File\\Extra_EnemyData.csv",
	//};
	//�t�@�C���̍ő吔�擾.
	m_FileMax = sizeof FileName / sizeof FileName[0];
	
	m_ppCFile = new CFile*[m_FileMax]();
	
	for (int file = 0; file < m_FileMax; file++) {
		//�t�@�C���ǂݍ��݃N���X���t�@�C�������쐬.
		m_ppCFile[file] = new CFile();
		//�t�@�C���ԍ��ɂ���ēK������t�@�C���̓ǂݎ��.
		m_ppCFile[file]->FileInput(FileName[file]);
	}

}


//========================================.
//		�t�@�C����������֐�.
//========================================.
void CFileInitPos::FileRelease()
{
	for (int file = m_FileMax - 1; file >= 0; file--) {
		//�t�@�C�������.
		m_ppCFile[file]->Close();
		//�t�@�C���N���X�̉��.
		SAFE_DELETE(m_ppCFile[file]);
	}
	//�t�@�C���N���X�z����.
	SAFE_DELETE_ARRAY(m_ppCFile);
}

