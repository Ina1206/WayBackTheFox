#include <Windows.h>
#include <sstream> 
#include <cctype>
#include <algorithm>
#include "CFileLoad.h"

//�R���X�g���N�^.
CFile::CFile()
{
	stData = nullptr;
}

//�f�X�g���N�^.
CFile::~CFile()
{
}

//================================================.
//		�t�@�C���ǂݍ��݂܂Ƃߏ����֐�.
//================================================.
void CFile::FileInput(const char* filename) 
{
	//�t�@�C���̓ǂݍ��ݏ����֐�.
	Load(filename);
	//�f�[�^�ǂݍ��ݏ����֐�.
	DataLoad();
	//�s�Ɨ�ɕ����鐮�������֐�.
	DataArrange();
}

//================================================.
//		�t�@�C���ǂݍ��ݏ����֐�.
//================================================.
void CFile::Load(const char* filename)
{
	//�t�@�C���̓ǂݍ���.
	ifs.open(filename);
	if (!ifs) {
		MessageBox(NULL, "�t�@�C���̓ǂݍ��ݎ��s", "Error", MB_OK);
	}
	//strvec�̏�����.
	strvec.erase(strvec.cbegin(), strvec.cend());
}

//================================================.
//		�f�[�^�ǂݍ��ݏ����֐�.
//================================================.
void CFile::DataLoad()
{
	//�f�[�^�̐����R���}��؂�œǂݍ���.
	line_max = 0;
	m_line = "";
	while (std::getline(ifs, m_line))
	{
		splita(m_line, ',');

		//1�s�ڂ̃f�[�^����1�s������̍ő吔�ɂ���.
		if (line_max <= 0) {
			line_max = static_cast<int>(strvec.size());
		}
	}
}

//================================================.
//		�f�[�^���������֐�.
//================================================.
void CFile::splita(std::string input, char delimiter)
{
	std::stringstream str(input);
	std::string filed;

	//�R���}�ŋ�؂�.
	while (std::getline(str, filed, delimiter))
	{
		//�A���t�@�x�b�g�Ƌ󔒈ȊO�̕������ʂ�.
		if (!(std::any_of(filed.cbegin(), filed.cend(), isalpha) || filed == "")) {
			strvec.push_back(filed);
		}
	}
}

//================================================.
//		�s�Ɨ�ɕ����Đ��������֐�.
//================================================.
void CFile::DataArrange() {
	//��̍ő吔.
	column_max = static_cast<int>(strvec.size()) / line_max;

	//�\���̂̓��I�m��.
	stData = new STDATA[column_max]();
	for (int column = 0; column < column_max; column++) {
		if (stData[column].st != nullptr) {
			stData[column].st = nullptr;
		}
		stData[column].st = new int[line_max];
	}

	//����������.
	for (int column = 0; column < column_max; column++) {
		for (int line = 0; line < line_max ; line++) {
			stData[column].st[line] = 0;
		}
	}

	//�f�[�^���s�Ɨ�ɕ����Ċi�[.
	for (int data_max = 0; data_max < static_cast<int>(strvec.size()); data_max++) {

		int column = data_max / line_max;	//��̃f�[�^�̗v�f��.
		int line = data_max % line_max;		//�s�̃f�[�^�̗v�f��.

		stData[column].st[line] = stoi(strvec.at(data_max));
	}
}

//================================================.
//		�t�@�C������鏈���֐�.
//================================================.
void CFile::Close()
{
	//===�������==.
	//�s�̒��̃f�[�^.
	for (int enemy = (strvec.size() / line_max)-1; enemy >= 0; enemy--) {
		delete[] stData[enemy].st;
		stData[enemy].st = nullptr;
	}
	//�\����.
	if (stData != nullptr) {
		delete[] stData;
		stData = nullptr;
	}

	//�t�@�C�������.
	ifs.close();
}
