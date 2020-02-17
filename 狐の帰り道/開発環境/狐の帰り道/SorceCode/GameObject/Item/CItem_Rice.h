#ifndef CITEM_RICE_H
#define CITEM_RICE_H

#include "CItem_Base.h"
#include "CItemMove.h"


class CItem_Rice
	: public CItem_Base
{
public:
	CItem_Rice();
	~CItem_Rice();

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
	const int	RICEPOINT		= 4;		//米のポイント.
	const int   RICE_MAX		= 6;		//米の個数.
	const float POS_ADJ			= 50.0f;	//位置調整.
	const float	ITEM_POS		= 2.0f;		//アイテムの位置.

	//=================変数=================//.
	int			 m_Num;				//アイテムの個数.
	CItemMove*	 m_CItemMove;		//アイテムの動きクラス.

	D3DXVECTOR3 m_vOldPos;			//前の座標.


};

#endif//CITEM_VEGETABLE_H