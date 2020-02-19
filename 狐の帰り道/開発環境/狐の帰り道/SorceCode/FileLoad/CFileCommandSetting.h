#ifndef CFILECOMMANDSETTING_H
#define CFILECOMMANDSETTING_H

#include "CFileLoad.h"
#include "..\GameObject\Chara\Enemy\EnemyType.h"
#include "..\Global.h"
#include "..\Command\enumCommand_Global.h"

/**************************************
*		�R�}���h�ݒ�t�@�C���N���X.
*****/
class CFileCommandSetting
{
public:
	CFileCommandSetting();
	~CFileCommandSetting();


	//================�֐�=====================//.
	void Setting();			//�ݒ菈���֐�.
	void Close();			//���鏈���֐�.

	//�`���l�������֐��`.
	int GetCommandDate(int fileNum, int column, int line) { return m_ppCFile[fileNum]->GetData(column, line); }

	int GetFileMax() { return m_FileMax; }

	//�`���u�������֐��`.
	void SetEnemyMax(enEnemy enemyType, int enemyMax) { m_pstCommandInfo[static_cast<int>(enemyType)].m_pCommandMax = enemyMax; }
	void SetEnemyPos(enEnemy enemyType, int enemy, D3DXVECTOR3 vPos) { m_pstCommandInfo[static_cast<int>(enemyType)].m_pvPos[enemy] = vPos; }
	void SetFileNum(int filenum) { m_FileNum = filenum; }
private:
	//================�֐�=====================//.
	void	Init();						//�����������֐�.
	void	Load();						//�ǂݍ��ݏ����֐�.
	void	Release();					//��������֐�.

	//================�\����====================//.
	//�e��R�}���h�̎�ނ��Ƃ̏��.�ʒu.
	struct stCommandInfo {
		int				m_pCommandMax;	//�R�}���h�̍ő�l.
		D3DXVECTOR3*	m_pvPos;		//�R�}���h�\��

		stCommandInfo()
			: m_pCommandMax	(0)
			, m_pvPos		(nullptr)
		{}
	};

	//=================�ϐ�=====================//.
	CFile*			m_pCFile;			//�t�@�C���̓ǂݍ��݃N���X.
	int				m_FileNum;			//�t�@�C���ԍ�.
	stCommandInfo*	m_pstCommandInfo;	//�R�}���h���̏��.

	int*			m_pEnemyMax;		//�e��G�̍ő吔.

	CFile**			m_ppCFile;			//�t�@�C���̓ǂݍ��݃N���X.
	int				m_FileMax;			//�t�@�C���̍ő吔.
};

#endif	//#ifndef CFILECOMMANDSETTING_H.