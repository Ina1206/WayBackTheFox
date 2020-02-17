#ifndef CDEPTH_STENCIL_H
#define CDEPTH_STENCIL_H

#include "..\..\MyMacro.h"	//マクロ.
#include "..\..\Global.h"	//グローバル.
#include <crtdbg.h>			//_ASSERT_EXPR()で必要.


/*******************************************
*	デプスステンシルクラス.
**/
class CDepth_Stencil 
{
public:
	CDepth_Stencil();
	~CDepth_Stencil();

	//========関数=========//.
	HRESULT Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11); //設定処理関数.
	void	SetDepth(bool flag);											//深度(Z)テストON/OFF切り替え処理関数.

	static CDepth_Stencil* GetDepthStencilInstance()
	{
		static CDepth_Stencil s_Instance;
		return &s_Instance;
	}

private:
	//========関数=========//.
	void Destroy();											//解放処理.

	//========変数=========//.
	ID3D11Device*				m_pDevice11;				//デバイスオブジェクト.
	ID3D11DeviceContext*		m_pContext11;				//デバイスコンテキスト.

	//深度.
	ID3D11DepthStencilState*	m_pDepthStencilState;		//デプスステンシル.
	ID3D11DepthStencilState*	m_pDepthStencilStateOff;	//デプスステンシルオフ.
};

#endif	//#ifndef CDEPTH_STENCIL_H.