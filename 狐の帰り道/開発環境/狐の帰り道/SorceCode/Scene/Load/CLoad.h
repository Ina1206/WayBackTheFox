#ifndef CLOAD_H
#define CLOAD_H

#include "..\..\Drawing\Bord_Polygon\GameSprite\CSpriteUI.h"

/*******************************************
*	ロードクラス.
*****/
class CLoad
{
public:
	CLoad();
	~CLoad();

	//==============関数==================//.
	void Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);	//初期化処理関数.
	void Render();																	//描画処理関数.

private:
	//==============関数==================//.
	HRESULT	Load();					//読み込み処理関数

	//==============変数==================//.
	CSpriteUI*	m_pLoadScreen;		//ロード画面.
};

#endif	//#ifndef CLOAD_H.