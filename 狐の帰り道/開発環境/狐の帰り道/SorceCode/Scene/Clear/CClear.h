#ifndef CCLEAR_H
#define CCLEAR_H

#include "..\CSceneManager.h"
#include "..\..\GameObject\UI\CClearUIManager.h"
#include "..\..\Camera\CCameraManager.h"

/*******************************************
*	クリアクラス.
**/
class CClear
	: public CSceneBase
{
public:
	CClear();
	~CClear();

	//==================関数===================//.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.
	void Release();			//解放処理関数.
private:

	//=================クラス==================//.
	CClearUIManager*	m_pCClearUIManager;
	CCameraManager*		m_pCCameraManager;			//CCameraManagerクラス.

};

#endif //#ifndef CCLEAR_H.