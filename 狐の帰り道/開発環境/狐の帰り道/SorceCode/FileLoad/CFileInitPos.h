#ifndef CFILE_INITPOS_H
#define CFILE_INITPOS_H

#include "CFileLoad.h"
#include "..\Global.h"
#include "..\GameObject\Chara\Enemy\EnemyType.h"

/**********************************************
*		ファイルでの初期位置クラス.
**/
class CFileInitPos
{
public:
	CFileInitPos();
	~CFileInitPos();
	//=====================定数=======================//.
	const int	MAP_MAX	= 3;	//マップの全体数.


	//===============関数===================//.
	void SetinngEnemyPos();		//敵の座標設定.
	void ReleaseFile();			//ファイル解放処理関数.

	//==========情報取得処理関数=============//.
	//敵のデータ取得処理関数.
	int GetEnemyFile(int fileNum, int column, int line) { return m_ppCFile[fileNum]->GetData(column, line); }
	//行の取得処理関数.
	int GetFileColumnMax(int fileNum) { return m_ppCFile[fileNum]->GetColumnDataMax(); }
	//列の取得処理関数.
	int GetFileLineMax(int fileNum) { return m_ppCFile[fileNum]->GetLineDataMax(); }
	//ファイル最大数の取得処理関数.
	int GetFileMax() { return m_FileMax; }

	//===========情報置換処理関数=============//.
	void SetFileNum(int filenum) { m_FileNum = filenum; }
private:
	//===============関数===================//.
	void LoadFile();			//ファイルの読み込み.


	//===================変数=====================//.
	int			m_FileNum;		//ファイルの番号.
	int			m_ColumnMax;	//行の最大数.
	int			m_LineMax;		//列の最大数.

	CFile**		m_ppCFile;		//ファイル読み込みクラス.
	int			m_FileMax;		//ファイルの最大数.

};

#endif	//#ifndef CFILE_INITPOS_H.