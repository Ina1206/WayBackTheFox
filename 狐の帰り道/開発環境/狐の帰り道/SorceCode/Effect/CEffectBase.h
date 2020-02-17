#ifndef _CEFFECT_BASE_H
#define _CEFFECT_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"

/***********************************************
*		�G�t�F�N�g���N���X.
**/
class CEffectBase
{
public:
	CEffectBase();
	virtual ~CEffectBase();

	//==================�֐�====================//.
	virtual void	UpDate() = 0;															//�X�V�����֐�.
	virtual void	Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos) = 0;	//�`�揈���֐�.

	//----- ���u�������֐� ----//.
	void SetCenterPos(D3DXVECTOR3 vPos) { m_vCenterPos = vPos; }	//���S�ʒu.
	void SetEffectStart(bool bFlag) { m_bDispFlag = bFlag; }		//�J�n�t���O.

	//----- ���擾�����֐� ----//.
	bool GetEffectStartFlag() { return m_bDispFlag; }				//�J�n�t���O.
protected:
	//==================�֐�=====================//.
	virtual void	Init() = 0;				//�����������֐�.
	virtual void	Release() = 0;			//��������֐�.

	//==================�ϐ�=====================//.
	D3DXVECTOR3			m_vCenterPos;		//���S�ʒu.
	D3DXVECTOR3*		m_pvPos;			//�ʒu.
	D3DXVECTOR3*		m_pvRot;			//�p�x.
	float*				m_pfScale;			//�L���L���̑傫��.
	bool				m_bDispFlag;		//�\���t���O.
	bool				m_bOldDispFlag;		//�O��̕\���t���O.
	CSprite**			m_ppCSprite;		//�X�v���C�g�N���X.
	CResourceManager*	m_pCResourceManager;//���\�[�X�Ǘ��N���X.

private:
};

#endif	//#ifndef _CEFFECT_BASE_H.