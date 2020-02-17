#ifndef CTITLEUIMANAGER_H
#define CTITLEUIMANAGER_H

#include "CPushButton.h"
#include "CTitle_Character.h"
#include "CTitle_Particle.h"

/*****************************************
*	タイトルUIクラス.
**/
class CTitleUIManager
{
public:
	CTitleUIManager();
	~CTitleUIManager();
	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vCameraPos);			//描画処理関数.

	bool GetUIDrawEndFlag() { return m_pCTitle_Character->GetMoveEndFlag(); }

private:
	//------------------------------------------.
	//	関数.
	//------------------------------------------.
	void Release();			//解放処理関数.

	//------------------------------------------.
	//	変数.
	//------------------------------------------.
	CTitle_Particle*	m_pCTitle_Particle;
	CPushButton*		m_pCPushButton;
	CTitle_Character*	m_pCTitle_Character;
};


#endif //#ifndef CTITLEUIMANAGER_H.