#ifndef CCLEAR_H
#define CCLEAR_H

#include "..\CSceneManager.h"
#include "..\..\GameObject\UI\CClearUIManager.h"
#include "..\..\Camera\CCameraManager.h"

/*******************************************
*	�N���A�N���X.
**/
class CClear
	: public CSceneBase
{
public:
	CClear();
	~CClear();

	//==================�֐�===================//.
	void Init_Process();	//�����ݒ菈���֐�.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.
	void Release();			//��������֐�.
private:

	//=================�N���X==================//.
	CClearUIManager*	m_pCClearUIManager;
	CCameraManager*		m_pCCameraManager;			//CCameraManager�N���X.

};

#endif //#ifndef CCLEAR_H.