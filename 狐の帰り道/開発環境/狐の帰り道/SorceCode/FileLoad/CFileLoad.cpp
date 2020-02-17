#include <Windows.h>
#include <sstream> 
#include <cctype>
#include <algorithm>
#include "CFileLoad.h"

//コンストラクタ.
CFile::CFile()
{
	stData = nullptr;
}

//デストラクタ.
CFile::~CFile()
{
}

//================================================.
//		ファイル読み込みまとめ処理関数.
//================================================.
void CFile::FileInput(const char* filename) 
{
	//ファイルの読み込み処理関数.
	Load(filename);
	//データ読み込み処理関数.
	DataLoad();
	//行と列に分ける整理処理関数.
	DataArrange();
}

//================================================.
//		ファイル読み込み処理関数.
//================================================.
void CFile::Load(const char* filename)
{
	//ファイルの読み込み.
	ifs.open(filename);
	if (!ifs) {
		MessageBox(NULL, "ファイルの読み込み失敗", "Error", MB_OK);
	}
	//strvecの初期化.
	strvec.erase(strvec.cbegin(), strvec.cend());
}

//================================================.
//		データ読み込み処理関数.
//================================================.
void CFile::DataLoad()
{
	//データの数をコンマ区切りで読み込む.
	line_max = 0;
	m_line = "";
	while (std::getline(ifs, m_line))
	{
		splita(m_line, ',');

		//1行目のデータ数を1行あたりの最大数にする.
		if (line_max <= 0) {
			line_max = static_cast<int>(strvec.size());
		}
	}
}

//================================================.
//		データ分解処理関数.
//================================================.
void CFile::splita(std::string input, char delimiter)
{
	std::stringstream str(input);
	std::string filed;

	//コンマで区切る.
	while (std::getline(str, filed, delimiter))
	{
		//アルファベットと空白以外の文字列を通す.
		if (!(std::any_of(filed.cbegin(), filed.cend(), isalpha) || filed == "")) {
			strvec.push_back(filed);
		}
	}
}

//================================================.
//		行と列に分けて整理処理関数.
//================================================.
void CFile::DataArrange() {
	//列の最大数.
	column_max = static_cast<int>(strvec.size()) / line_max;

	//構造体の動的確保.
	stData = new STDATA[column_max]();
	for (int column = 0; column < column_max; column++) {
		if (stData[column].st != nullptr) {
			stData[column].st = nullptr;
		}
		stData[column].st = new int[line_max];
	}

	//初期化処理.
	for (int column = 0; column < column_max; column++) {
		for (int line = 0; line < line_max ; line++) {
			stData[column].st[line] = 0;
		}
	}

	//データを行と列に分けて格納.
	for (int data_max = 0; data_max < static_cast<int>(strvec.size()); data_max++) {

		int column = data_max / line_max;	//列のデータの要素数.
		int line = data_max % line_max;		//行のデータの要素数.

		stData[column].st[line] = stoi(strvec.at(data_max));
	}
}

//================================================.
//		ファイルを閉じる処理関数.
//================================================.
void CFile::Close()
{
	//===解放処理==.
	//行の中のデータ.
	for (int enemy = (strvec.size() / line_max)-1; enemy >= 0; enemy--) {
		delete[] stData[enemy].st;
		stData[enemy].st = nullptr;
	}
	//構造体.
	if (stData != nullptr) {
		delete[] stData;
		stData = nullptr;
	}

	//ファイルを閉じる.
	ifs.close();
}
