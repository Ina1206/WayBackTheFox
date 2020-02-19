#include"CFileLoadManager.h"
#include <time.h>

/*****************************************
*		�t�@�C���ǂݍ��݊Ǘ��N���X.
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
	//��������֐�.
	Release();
}

//==========================================.
//		���ׂĂ̐ݒ菈���֐�.
//==========================================.
void CFileLoadManager::ALL_Setting()
{
	m_pCFileInitPos = new CFileInitPos();
	m_pCFileCommandSet = new CFileCommandSetting();
	
	m_pCFileInitPos->SetinngEnemyPos();
	m_pCFileCommandSet->Setting();

	//�t�@�C���̍ő吔�擾.
	if (m_pCFileInitPos->GetFileMax() <= m_pCFileCommandSet->GetFileMax()) {
		m_FileMax = m_pCFileInitPos->GetFileMax();
	}
	else {
		m_FileMax = m_pCFileCommandSet->GetFileMax();
	}

	//�X�e�[�W���Ƃ̑S�G�̏��z�񓮓I�m��.
	m_pstAllEnemyInfo = new stAllEnemyInfo[m_FileMax]();
	m_pEnemyCnt = new int[static_cast<int>(enEnemy::Max)]();

	//�G�̐ݒ菈���֐�.
	for (int file = 0; file < m_FileMax; file++) {
		SettingEnemy(file);
	}

	//���ꂼ��̃t�@�C��������Ă���.
	SAFE_DELETE(m_pCFileCommandSet);
	SAFE_DELETE(m_pCFileInitPos);

}

//==========================================.
//		�G�̐ݒ菈���֐�.
//==========================================.
void CFileLoadManager::SettingEnemy(int fileNum)
{
	//�ԍ��`�F�b�N�����֐�.
	CheckNum(fileNum);

	m_pstAllEnemyInfo[fileNum].m_pEnemyMax = new int[static_cast<int>(enEnemy::Max)]();

	//�G�̍ő吔�J�E���g�����֐�.
	EnemyMaxCnt(fileNum);
	//�G�̏��z�񓮓I�m��.
	m_pstAllEnemyInfo[fileNum].m_pvInitPos = new D3DXVECTOR3[m_pstAllEnemyInfo[fileNum].m_AllEnemyMax]();
	m_pstAllEnemyInfo[fileNum].m_pButtonNum = new int[m_pstAllEnemyInfo[fileNum].m_AllEnemyMax]();

	for (int enemy = 0; enemy < static_cast<int>(enEnemy::Max); enemy++) {
		m_pEnemyCnt[enemy] = 0;
	}

	for (int column = 0; column < m_pCFileInitPos->GetFileColumnMax(fileNum); column++) {
		for (int line = 0; line < m_pCFileInitPos->GetFileLineMax(fileNum); line++) {
			if (m_pCFileInitPos->GetEnemyFile(fileNum, column, line) > 0) {
				//�G�̈ʒu�ݒ�.
				SettingEnemyPos(fileNum, column, line);
				//�G���ɏ������Ă���{�^���ԍ��ݒ�.
				SettingButton(fileNum, column, line);

				//�ǉ�.
				m_pEnemyCnt[m_pCFileInitPos->GetEnemyFile(fileNum, column, line) - 1]++;
			}
		}
	}
}

//==========================================.
//		�ԍ��`�F�b�N�����֐�.
//==========================================.
void CFileLoadManager::CheckNum(int filenum)
{
	for (int column = 0; column < m_pCFileInitPos->GetFileColumnMax(filenum); column++) {
		for (int line = 0; line < m_pCFileInitPos->GetFileLineMax(filenum); line++) {
			if( m_pCFileInitPos->GetEnemyFile(filenum,column, line) > 0 ){
				_ASSERT_EXPR(m_pCFileInitPos->GetEnemyFile(filenum,column, line) > 0, L"�f�[�^�Ȃ�");
				_ASSERT_EXPR(m_pCFileCommandSet->GetCommandDate(filenum, column, line) > 0, L"�ǂ��炩�̃f�[�^���s�����Ă��܂�.");
			}
		}
	}
}

//==========================================.
//		�G�̍ő�l���J�E���g�����֐�.
//==========================================.
void CFileLoadManager::EnemyMaxCnt(int fileNum)
{
	for (int column = 0; column < m_pCFileInitPos->GetFileColumnMax(fileNum); column++) {
		for (int line = 0; line < m_pCFileInitPos->GetFileLineMax(fileNum); line++) {
			if (m_pCFileInitPos->GetEnemyFile(fileNum,column, line) > 0) {
				//��ޕʍő吔.
				m_pstAllEnemyInfo[fileNum].m_pEnemyMax[m_pCFileInitPos->GetEnemyFile(fileNum, column, line) - 1]++;
				//�S�G�̑����̍ő吔.
				m_pstAllEnemyInfo[fileNum].m_AllEnemyMax++;
			}
		}
	}
}

//==========================================.
//		�G�̈ʒu�ݒ菈���֐�.
//==========================================.
void CFileLoadManager::SettingEnemyPos(int fileNum, int column, int line)
{
	//�G�̔ԍ�.
	int m_pEnemyNum = m_pCFileInitPos->GetEnemyFile(fileNum,column, line) - 1;
	//�G�̎�ނ̏��߂̔ԍ�.
	int EnemyStartNum = 0;
	for (int enemy = 0; enemy < m_pEnemyNum; enemy++) {
		EnemyStartNum += m_pstAllEnemyInfo[fileNum].m_pEnemyMax[enemy];
	}

	//�G�ԍ�.
	int enemyNum = EnemyStartNum + m_pEnemyCnt[m_pEnemyNum];
	m_pstAllEnemyInfo[fileNum].m_pvInitPos[enemyNum] = D3DXVECTOR3((line * WIDTH) - START_WIDTH, STANDERD_Y, (DEPTH_INTERVAL*column) + START_DEPTH);
}

//==========================================.
//		�{�^���̎�ސݒ菈���֐�.
//==========================================.
void CFileLoadManager::SettingButton(int fileNum, int column, int line)
{
	int m_pEnemyNum = m_pCFileInitPos->GetEnemyFile(fileNum, column, line) - 1;

	//�G�̎�ނ̏��߂̔ԍ�.
	int EnemyStartNum = 0;
	for (int enemy = 0; enemy < m_pEnemyNum; enemy++) {
		EnemyStartNum += m_pstAllEnemyInfo[fileNum].m_pEnemyMax[enemy];
	}
	//�G�ԍ�.
	int enemyNum = EnemyStartNum + m_pEnemyCnt[m_pEnemyNum];
	m_pstAllEnemyInfo[fileNum].m_pButtonNum[enemyNum] = m_pCFileCommandSet->GetCommandDate(fileNum, column, line);
}

//==========================================.
//		��������֐�.
//==========================================.
void CFileLoadManager::Release()
{
	//���ꂼ��̔z����.
	for (int file = m_FileMax - 1; file >= 0; file--) {
		SAFE_DELETE_ARRAY(m_pstAllEnemyInfo[file].m_pEnemyMax);	//�G���Ƃ̍ő吔.
		SAFE_DELETE_ARRAY(m_pstAllEnemyInfo[file].m_pButtonNum);//�{�^���ԍ�.
		SAFE_DELETE_ARRAY(m_pstAllEnemyInfo[file].m_pvInitPos);	//�����ʒu.
	}
	SAFE_DELETE_ARRAY(m_pEnemyCnt);			//�G�̃J�E���g.
	SAFE_DELETE_ARRAY(m_pstAllEnemyInfo);	//�X�e�[�W���Ƃ̑S���̓G�̏��
}