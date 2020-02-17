#ifndef CCLEARUI_MANAGER_H
#define CCLEARUI_MANAGER_H

#include "CClearUI.h"
#include "CChar_Evaluation.h"
#include "CPushButton.h"

#include "CUI_Base.h"

//コントローラクラス.
#include"..\..\Controller\CXInput.h"

class CClearUIManager
{
public:
	CClearUIManager();
	~CClearUIManager();

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);		//描画処理関数.

	void SetPointSum(int num) { m_PointSum = num; }
	bool GetUIDrawEndFlag() { return m_pCUI_Base[CHAR_EVALUATION]->GetMoveEndFlag(); }

private:
	//------------------------------------------.
	//	定数.
	//------------------------------------------.
	const int	UI_MAX				= 3;		//UIの最大数.
	const int	CLEAR_UI			= 0;		//クリアUIのクラス番号.
	const int	CHAR_EVALUATION		= 1;		//評価文字のクラス番号.
	const int	PUSH_BUTTON			= 2;		//ボタンのクラス番号.
	const int	DISP_PUSH_BUTTON	= 60;		//ボタン描画時間.
	const float FADETIME			= 120.0f;	//フェード開始時間.
	const int	SWITCH_MAX			= 2;		//切り替え番号最大数.

	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Release();			//解放処理関数.

	//------------------------------------------.
	//	変数.
	//------------------------------------------.
	clsXInput*			m_pCInput;				//コントローラクラス.
	CUI_Base**			m_pCUI_Base;
	float				m_Frame;
	int					m_PointSum;
	bool				m_ButtonDispFlag;
	int					m_PushButtonNum;
	int					m_DispNum;
};

#endif//#ifndef CCLEARUI_MANAGER_H