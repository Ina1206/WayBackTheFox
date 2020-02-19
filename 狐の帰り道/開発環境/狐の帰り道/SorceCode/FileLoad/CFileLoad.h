#ifndef FILELOAD
#define FILELOAD
#include <string>
#include <vector>	
#include <iostream>	
#include <fstream>	

/***********************************
*		�t�@�C���ǂݍ��݃N���X.
**/
class CFile {
public:
	CFile();
	~CFile();

	//========�֐�==========//.
	void InputFile(const char* filename);					//�t�@�C���ǂݍ��݂܂Ƃ�.
	void Close();											//�t�@�C������鏈���֐�.

	//=====���擾�֐�=====//.
	int GetLineDataMax() { return line_max; }				//�P�s������̃f�[�^�̍ő吔.
	int GetColumnDataMax() {
		return static_cast<int>(strvec.size()) / line_max;	//1�񓖂���̃f�[�^�̍ő吔. 
	}
	int GetData(int data_column, int data_line) {
		return stData[data_column].st[data_line];			//���ꂼ��̃f�[�^.
	}

private:
	//==========�֐�==========//.
	void Load(const char* filename);						//�t�@�C���ǂݍ��ݏ����֐�.
	void LoadData();										//�f�[�^�ǂݍ��ݏ����֐�.
	void ArrangeData();										//�s�Ɨ�ɕ����Đ��������֐�.
	
	void splita(std::string input, char delimiter);			//�f�[�^���������֐�.

	//=========�\����========//.
	//��ƍs�ɕ����邽�߂̍\����.
	struct STDATA {
		int *st;					//�s�̒��̃f�[�^.
	};
	STDATA *stData;

	//==========�ϐ�==========//.
	std::ifstream ifs;				//�t�@�C��.
	std::string m_line;				//�ǂݎ�����S�Ẵf�[�^.
	std::vector<std::string> strvec;//�R���}�ŋ�؂�����̂��ꂼ��̃f�[�^.

	int line_max;					//�f�[�^�̍s�̍ő吔.
	int column_max ;				//�f�[�^�̗�̍ő吔.
};
#endif //ifndef FILELOAD.