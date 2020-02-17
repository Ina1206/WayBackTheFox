#ifndef CFILE_LOAD_MANAGER_H
#define CFILE_LOAD_MANAGER_H

#include "CFileInitPos.h"
#include "CFileCommandSetting.h"

class CFileLoadManager
{
public:
	CFileLoadManager();
	~CFileLoadManager();

	//===================�萔======================//.
	const float WIDTH			= 1.5f;				//����.
	const float DEPTH_INTERVAL	= 2.0f;				//�c��.
	const float STANDERD_Y		= 0.0f;				//�Y��.
	const float START_WIDTH		= 1.5f;				//�X�^�[�g�̊Ԋu.
	const float START_DEPTH		= 6.0f;				//�X�^�[�g�̉��s.
	const int	FILE_MAX		= 3;				//�t�@�C���̍ő吔.


	//===================�֐�======================//.
	void ALL_Setting();			//���ׂĂ̐ݒ菈���֐�.

	//�`���l�������֐��`.
	//�G�̍��W.
	D3DXVECTOR3 GetEnemyPos(int enemy)		{ return m_pstAllEnemyInfo[m_FileNum].m_pvInitPos[enemy]; }
	//�e�G�̍ő吔.
	int			GetEnemyMax(int enemyType)	{ return m_pstAllEnemyInfo[m_FileNum].m_pEnemyMax[enemyType]; }
	//�{�^���ԍ�.
	int			GetButtonNum(int enemy)		{ return m_pstAllEnemyInfo[m_FileNum].m_pButtonNum[enemy]; }
	//�G�����̍ő吔.
	int			GetAllEnemyMax()			{ return m_pstAllEnemyInfo[m_FileNum].m_AllEnemyMax; }
	//�t�@�C���̑���.
	int			GetFileMax()				{ return m_FileMax; }

	//�`���u�������֐��`.
	//�t�@�C���ԍ��ݒ�.
	void		SetFileNum(int fileNum)		{ m_FileNum = fileNum; }

	//=================�V���O���g��=================//
	static CFileLoadManager* GetCFileLoadManagerInstance()
	{
		static CFileLoadManager Instance;
		return &Instance;
	}

private:
	//===================�֐�======================//.
	void EnemySetting(int fileNum);							//�G�̐ݒ菈���֐�.
	void NumCheck(int fileNum);								//�ԍ��`�F�b�N�����֐�.
	void EnemyMaxCnt(int fileNum);							//�G�̍ő�l���J�E���g�����֐�.
	void EnemyPosSetting(int fileNum,int column, int line);	//�G�̈ʒu�ݒ菈���֐�.
	void ButtonSetting(int fileNum, int column, int line);	//�{�^���̎�ސݒ菈���֐�.
	void Release();											//��������֐�.

	//==================�\����======================//.
	//�X�e�[�W���Ƃ̑S���̓G�̏��.
	struct stAllEnemyInfo {
		D3DXVECTOR3*	m_pvInitPos;	//�����ʒu.
		int*			m_pButtonNum;	//�{�^���ԍ�.
		int*			m_pEnemyMax;	//�G�̍ő吔.
		int				m_AllEnemyMax;	//�S�Ă̓G�̑����ő吔.

		stAllEnemyInfo()
			: m_pvInitPos	(nullptr)
			, m_pButtonNum	(nullptr)
			, m_pEnemyMax	(nullptr)
			, m_AllEnemyMax	(0)
		{}
	};

	//===================�ϐ�========================//.
	CFileInitPos*			m_pCFileInitPos;	//�G�̈ʒu�ݒ�N���X.
	CFileCommandSetting*	m_pCFileCommandSet;	//�R�}���h�ǂݍ��ݏ����N���X.
	
	stAllEnemyInfo*			m_pstAllEnemyInfo;	//�X�e�[�W���Ƃ̑S�G�̏��.
	int						m_FileMax;			//�t�@�C���ő吔.
	int						m_FileNum;			//�t�@�C���ԍ��w��.
	int*					m_pEnemyCnt;		//�G�̃J�E���g.

};

#endif	//#ifndef CFILE_LOAD_MANAGER_H.