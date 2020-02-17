#ifndef CITEMICON_H
#define CITEMICON_H

#include "CUI_Base.h"

class CItemIcon
	: public CUI_Base
{
public:
	CItemIcon();
	~CItemIcon();

	//=================関数===================//.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

	D3DXVECTOR3 GetPosition() { return m_vPos; }
	D3DXVECTOR3 GetIconPosition(int num);

private:
	//=================定数===================//.
	const int ITEM_SPRITE_MAX	= 4;		//スプライトの最大数.
	const int ITEM_MEAT			= 0;		//肉の番号.
	const int ITEM_FISH			= 1;		//魚の番号.
	const int ITEM_VEGETABLES	= 2;		//野菜の番号.
	const int ITEM_RICE			= 3;		//米の番号.

	const D3DXVECTOR2 ICON_POS	= D3DXVECTOR2(0.0f, 0.0f);			//肉アイコンの位置.
	const float FISH_POS_Y		= ICON_POS.y + 80.0f;					//魚アイコンのy座標.
	const float VEGETABLES_POS_Y= FISH_POS_Y + 100.0f;					//野菜アイコンのy座標.
	const float RICE_POS_Y		= VEGETABLES_POS_Y + 110.0f;			//米アイコンのy座標.

	//=================関数===================//.
	void Release();			//解放処理関数.

	//=================変数===================//.
	CSpriteUI**		m_ppCItemIcon;		//SpriteUIクラス.

	D3DXVECTOR3		m_vVegetable_Pos;
	D3DXVECTOR3		m_vMeat_Pos;
	D3DXVECTOR3		m_vFish_Pos;
	D3DXVECTOR3		m_vRice_Pos;
};

#endif	//#ifndef CITEMICON_H
