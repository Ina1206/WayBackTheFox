#ifndef CTITLE_H
#define CTITLE_H

#include "..\CSceneBase.h"
#include "..\..\GameObject\UI\CTitleUIManager.h"
#include "..\..\GameObject\Ground\CGround.h"
#include "..\..\BackGround\CBackGround.h"
#include "..\..\Camera\CCameraManager.h"



/**********************************************
*	タイトルクラス.
**/
class CTitle
	: public CSceneBase
{
public:
	CTitle();
	virtual ~CTitle();
	
	//=================関数====================//.
	void Init_Process();	//初期設定処理関数.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//=================関数====================//.
	void Release();			//解放処理関数.

	//================クラス====================//.
	CResourceManager*	m_pCResourceManager;		//CResourceManagerクラス.
	CTitleUIManager*	m_pCTitleUIManager;			//CTitleUIManagerクラス.
	CGround*			m_pCGround;					//CGroundクラス.
	CBackGround*		m_pCBackGround;				//CBackGroundクラス.
	CCameraManager*		m_pCCameraManager;			//CCameraManagerクラス.


};

#endif	//#ifndef CTITLE_H.