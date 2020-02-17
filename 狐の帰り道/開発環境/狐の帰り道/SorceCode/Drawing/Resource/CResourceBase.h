#ifndef CRESORCEBASE_H
#define CRESORCEBASE_H

#include <crtdbg.h>

#include "..\..\Global.h"
#include "..\..\MyMacro.h"
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")


/*****************************************
*	読み込みベースクラス.
**/
class CResourceBase
{
public:
	CResourceBase();
	~CResourceBase();

	//==================関数=====================//.
	void Init_Replacement(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);	//初期置換処理.
	
	virtual HRESULT	Init() = 0;				//初期設定処理関数.
	virtual HRESULT Load() = 0;				//読み込み処理関数.
	virtual HRESULT ReleaseCalling() = 0;	//解放処理呼び出し関数.
protected:
	HWND					m_hWnd;			//ウィンドウハンドル.
	ID3D11Device*			m_pDevice11;	//デバイスオブジェクト.
	ID3D11DeviceContext*	m_pContext11;	//デバイスコンテキスト.
	LPDIRECT3DDEVICE9		m_pDevice9;		//デバイスコンテキスト.
private:

};

#endif	//#ifndef CRESORCEBASE_H.#pragma once
