#ifndef CRESORCEBASE_H
#define CRESORCEBASE_H

#include <crtdbg.h>

#include "..\..\Global.h"
#include "..\..\MyMacro.h"
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


/*****************************************
*	�ǂݍ��݃x�[�X�N���X.
**/
class CResourceBase
{
public:
	CResourceBase();
	~CResourceBase();

	//==================�֐�=====================//.
	void Init_Replacement(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);	//�����u������.
	
	virtual HRESULT	Init() = 0;				//�����ݒ菈���֐�.
	virtual HRESULT Load() = 0;				//�ǂݍ��ݏ����֐�.
	virtual HRESULT ReleaseCalling() = 0;	//��������Ăяo���֐�.
protected:
	HWND					m_hWnd;			//�E�B���h�E�n���h��.
	ID3D11Device*			m_pDevice11;	//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;	//�f�o�C�X�R���e�L�X�g.
	LPDIRECT3DDEVICE9		m_pDevice9;		//�f�o�C�X�R���e�L�X�g.
private:

};

#endif	//#ifndef CRESORCEBASE_H.#pragma once
