#ifndef CTITLEUIMANAGER_H
#define CTITLEUIMANAGER_H

#include "CPushButton.h"
#include "CTitle_Character.h"
#include "CTitle_Particle.h"

/*****************************************
*	�^�C�g��UI�N���X.
**/
class CTitleUIManager
{
public:
	CTitleUIManager();
	~CTitleUIManager();
	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Init_Process();	//�����ݒ菈���֐�.
	void UpDate();			//�X�V�����֐�.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vCameraPos);			//�`�揈���֐�.

	bool GetUIDrawEndFlag() { return m_pCTitle_Character->GetMoveEndFlag(); }

private:
	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Release();			//��������֐�.

	//------------------------------------------.
	//	�ϐ�.
	//------------------------------------------.
	CTitle_Particle*	m_pCTitle_Particle;
	CPushButton*		m_pCPushButton;
	CTitle_Character*	m_pCTitle_Character;
};


#endif //#ifndef CTITLEUIMANAGER_H.