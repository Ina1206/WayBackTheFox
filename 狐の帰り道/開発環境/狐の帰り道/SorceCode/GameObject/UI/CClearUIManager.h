#ifndef CCLEARUI_MANAGER_H
#define CCLEARUI_MANAGER_H

#include "CClearUI.h"
#include "CChar_Evaluation.h"
#include "CPushButton.h"

#include "CUI_Base.h"

//�R���g���[���N���X.
#include"..\..\Controller\CXInput.h"

class CClearUIManager
{
public:
	CClearUIManager();
	~CClearUIManager();

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Init_Process();	//�����ݒ菈���֐�.
	void UpDate();			//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);		//�`�揈���֐�.

	void SetPointSum(int num) { m_PointSum = num; }
	bool GetUIDrawEndFlag() { return m_pCUI_Base[CHAR_EVALUATION]->GetMoveEndFlag(); }

private:
	//------------------------------------------.
	//	�萔.
	//------------------------------------------.
	const int	UI_MAX				= 3;		//UI�̍ő吔.
	const int	CLEAR_UI			= 0;		//�N���AUI�̃N���X�ԍ�.
	const int	CHAR_EVALUATION		= 1;		//�]�������̃N���X�ԍ�.
	const int	PUSH_BUTTON			= 2;		//�{�^���̃N���X�ԍ�.
	const int	DISP_PUSH_BUTTON	= 60;		//�{�^���`�掞��.
	const float FADETIME			= 120.0f;	//�t�F�[�h�J�n����.
	const int	SWITCH_MAX			= 2;		//�؂�ւ��ԍ��ő吔.

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Release();			//��������֐�.

	//------------------------------------------.
	//	�ϐ�.
	//------------------------------------------.
	clsXInput*			m_pCInput;				//�R���g���[���N���X.
	CUI_Base**			m_pCUI_Base;
	float				m_Frame;
	int					m_PointSum;
	bool				m_ButtonDispFlag;
	int					m_PushButtonNum;
	int					m_DispNum;
};

#endif//#ifndef CCLEARUI_MANAGER_H