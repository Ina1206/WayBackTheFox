#ifndef CITEM_FISH_H
#define CITEM_FISH_H

#include "CItem_Base.h"
#include "CItemMove.h"

class CItem_Fish
	: public CItem_Base
{
public:
	CItem_Fish();
	~CItem_Fish();

	//=================関数===================//.
	void Init_Process();	//初期化処理関数.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

private:
	//=================関数===================//.
	void Release();			//解放処理関数.

	void ItemCount();		//アイテムの合計処理関数.[
	void ItemRender();		//アイテム描画処理関数.

	//=================定数=================//.
	const int	FISHPOINT		= 2;		//魚のポイント.
	const float POS_ADJ			= 50.0f;	//位置調整.

	//=================変数=================//.
	D3DXVECTOR2* m_pvPattern;		//画像パターン.
	CSpriteUI**	 m_ppCNumSprite;	//アイテムの個数表示用.

	int			 m_Num;				//アイテムの個数.
	CItemMove*	 m_CItemMove;		//アイテムの動きクラス.

};


#endif//CITEM_FISH_H