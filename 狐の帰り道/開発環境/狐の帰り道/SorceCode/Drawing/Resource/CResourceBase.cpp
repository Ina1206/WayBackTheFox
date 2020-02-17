#include "CResourceBase.h"

CResourceBase::CResourceBase()
	: m_hWnd		(nullptr)
	, m_pDevice11	(nullptr)
	, m_pContext11	(nullptr)
	, m_pDevice9	(nullptr)
{
}

CResourceBase::~CResourceBase()
{
	m_pDevice9		= nullptr;
	m_pContext11	= nullptr;
	m_pDevice11		= nullptr;
	m_hWnd			= nullptr;
}

//===============================.
//		èâä˙íuä∑èàóù.
//===============================.
void CResourceBase::Init_Replacement(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd			= hWnd;
	m_pDevice11		= pDevice11;
	m_pContext11	= pContext11;
	m_pDevice9		= pDevice9;
}