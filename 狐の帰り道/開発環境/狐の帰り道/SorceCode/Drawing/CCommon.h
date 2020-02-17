#ifndef CCOMMON_H
#define CCOMMON_H

#include "..\Global.h"

//共通クラス.
/*******************************************
*	共通クラス.
**/
class CCommon
{
public:
	CCommon();
	virtual ~CCommon();		

	HRESULT InitBlend();				//Blend初期化.
	void SetBlend(bool EnableAlpha);	//透過設定切り替え.

protected:
	//↓アプリにひとつ.
	ID3D11Device*			m_pDevice11;			//デバイスオブジェクト.
	ID3D11DeviceContext*	m_pContext11;			//デバイスコンテキスト.

	ID3D11BlendState*		m_pAlphaBlend;			//アルファブレンド有効.
	ID3D11BlendState*		m_pNoAlphaBlend;		//アルファブレンド無効.
};

#endif //#ifndef CCOMMON_H