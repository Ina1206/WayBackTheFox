#ifndef CITEM_VEGETABLE_H
#define CITEM_VEGETABLE_H

#include "CItem_Base.h"
#include "CItemMove.h"

class CItem_Vegetables
	: public CItem_Base
{
public:
	CItem_Vegetables();
	~CItem_Vegetables();

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
	const int	VEGETABLEPOINT	= 1;		//野菜のポイント.
	const float POS_ADJ			= 50.0f;	//位置調整.

	//=================変数=================//.
	int			 m_Num;				//アイテムの個数.
	CItemMove*	 m_CItemMove;		//アイテムの動きクラス.


};


#endif//CITEM_VEGETABLE_H