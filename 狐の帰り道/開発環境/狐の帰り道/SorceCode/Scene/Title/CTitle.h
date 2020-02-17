#ifndef CTITLE_H
#define CTITLE_H

#include "..\CSceneBase.h"
#include "..\..\GameObject\UI\CTitleUIManager.h"
#include "..\..\GameObject\Ground\CGround.h"
#include "..\..\BackGround\CBackGround.h"
#include "..\..\Camera\CCameraManager.h"



/**********************************************
*	�^�C�g���N���X.
**/
class CTitle
	: public CSceneBase
{
public:
	CTitle();
	virtual ~CTitle();
	
	//=================�֐�====================//.
	void Init_Process();	//�����ݒ菈���֐�.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

private:
	//=================�֐�====================//.
	void Release();			//��������֐�.

	//================�N���X====================//.
	CResourceManager*	m_pCResourceManager;		//CResourceManager�N���X.
	CTitleUIManager*	m_pCTitleUIManager;			//CTitleUIManager�N���X.
	CGround*			m_pCGround;					//CGround�N���X.
	CBackGround*		m_pCBackGround;				//CBackGround�N���X.
	CCameraManager*		m_pCCameraManager;			//CCameraManager�N���X.


};

#endif	//#ifndef CTITLE_H.