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
	//��������֐�.
	Release();
}

//======================================.
//		�ݒ菈���֐�.
//======================================.
void CFileCommandSetting::Setting()
{
	//�ǂݍ��ݏ����֐�.
	Load();
}

//======================================.
//		�ǂݍ��ݏ����֐�.
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

	//�t�@�C���̍ő吔�擾s.
	m_FileMax = sizeof FileName / sizeof FileName[0];

	//�t�@�C���̓ǂݍ��݃N���X�t�@�C�������z�񓮓I�m��.
	m_ppCFile = new CFile*[m_FileMax]();

	for (int file = 0; file < m_FileMax; file++) {
		//�t�@�C�������t�@�C���ǂݍ��݃N���X�쐬.
		m_ppCFile[file] = new CFile();
		
		//�t�@�C�������ǂݍ���.
		m_ppCFile[file]->FileInput(FileName[file]);
	}
	
}

//======================================.
//		�����������֐�.
//======================================.
void CFileCommandSetting::Init()
{
	//�e���ꂼ��̃R�}���h�̍ő�l�̔z�񓮓I�m��.
	m_pEnemyMax = new int[static_cast<int>(enEnemy::Max)];

	//�R�}���h���̊e��z�񓮓I�m��.
	m_pstCommandInfo = new stCommandInfo[static_cast<int>(enCommandType::Max)]();
	for (int command = 0; command < static_cast<int>(enCommandType::Max); command++) {
		m_pstCommandInfo[command].m_pvPos = new D3DXVECTOR3[m_pCFile->GetColumnDataMax()];
	}
	
}

//========================================.
//		�������֐�.
//========================================.
void CFileCommandSetting::Close()
{

	for (int file = m_FileMax - 1; file >= 0; file--) {
		m_ppCFile[file]->Close();
	}
}

//=========================================.
//		��������֐�.
//=========================================.
void CFileCommandSetting::Release()
{

	for (int file = m_FileMax - 1; file >= 0; file--) {
		SAFE_DELETE(m_ppCFile[file]);
	}
	SAFE_DELETE_ARRAY(m_ppCFile);
}