#ifndef CCOMMON_H
#define CCOMMON_H

#include "..\Global.h"

//���ʃN���X.
/*******************************************
*	���ʃN���X.
**/
class CCommon
{
public:
	CCommon();
	virtual ~CCommon();		

	HRESULT InitBlend();				//Blend������.
	void SetBlend(bool EnableAlpha);	//���ߐݒ�؂�ւ�.

protected:
	//���A�v���ɂЂƂ�.
	ID3D11Device*			m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;			//�f�o�C�X�R���e�L�X�g.

	ID3D11BlendState*		m_pAlphaBlend;			//�A���t�@�u�����h�L��.
	ID3D11BlendState*		m_pNoAlphaBlend;		//�A���t�@�u�����h����.
};

#endif //#ifndef CCOMMON_H