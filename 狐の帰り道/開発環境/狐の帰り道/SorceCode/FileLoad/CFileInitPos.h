#ifndef CFILE_INITPOS_H
#define CFILE_INITPOS_H

#include "CFileLoad.h"
#include "..\Global.h"
#include "..\GameObject\Chara\Enemy\EnemyType.h"

/**********************************************
*		�t�@�C���ł̏����ʒu�N���X.
**/
class CFileInitPos
{
public:
	CFileInitPos();
	~CFileInitPos();
	//=====================�萔=======================//.
	const int	MAP_MAX	= 3;	//�}�b�v�̑S�̐�.


	//===============�֐�===================//.
	void SetinngEnemyPos();		//�G�̍��W�ݒ�.
	void ReleaseFile();			//�t�@�C����������֐�.

	//==========���擾�����֐�=============//.
	//�G�̃f�[�^�擾�����֐�.
	int GetEnemyFile(int fileNum, int column, int line) { return m_ppCFile[fileNum]->GetData(column, line); }
	//�s�̎擾�����֐�.
	int GetFileColumnMax(int fileNum) { return m_ppCFile[fileNum]->GetColumnDataMax(); }
	//��̎擾�����֐�.
	int GetFileLineMax(int fileNum) { return m_ppCFile[fileNum]->GetLineDataMax(); }
	//�t�@�C���ő吔�̎擾�����֐�.
	int GetFileMax() { return m_FileMax; }

	//===========���u�������֐�=============//.
	void SetFileNum(int filenum) { m_FileNum = filenum; }
private:
	//===============�֐�===================//.
	void LoadFile();			//�t�@�C���̓ǂݍ���.


	//===================�ϐ�=====================//.
	int			m_FileNum;		//�t�@�C���̔ԍ�.
	int			m_ColumnMax;	//�s�̍ő吔.
	int			m_LineMax;		//��̍ő吔.

	CFile**		m_ppCFile;		//�t�@�C���ǂݍ��݃N���X.
	int			m_FileMax;		//�t�@�C���̍ő吔.

};

#endif	//#ifndef CFILE_INITPOS_H.