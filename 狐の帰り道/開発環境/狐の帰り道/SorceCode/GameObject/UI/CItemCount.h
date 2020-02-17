#ifndef CITEM_COUNT_H
#define CITEM_COUNT_H

#include "CUI_Base.h"
#include "..\Item\enItemType.h"

class CItemCount
	: public CUI_Base
{
public:
	CItemCount();
	~CItemCount();

	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

	//～情報置換処理関数～//.
	void SetItemCount(int ItemNum, int Count);												//アイテムの個数取得.
	void SetIconPos(int num, D3DXVECTOR3 vPos) { m_pstItemInfo[num].m_vIconPos = vPos; }	//アイコン位置.

private:
	//==================定数==================.
	const int ITEM_TYPE_MAX = static_cast<int>(enItemType::MAX);	//アイテムタイプの最大.
	const int IMAGE_WIDTH_MAX = 5;									//画像の横幅.
	const int IMAGE_HIGH_MAX  = 5;									//画像の縦幅
	const int NUM_SPRITE_MAX  = 2;									//スプライトの最大.
	const int TEN			  = 10;									//10の位.

	//==================構造体==================.
	struct stItemInfo {
		D3DXVECTOR3		m_vIconPos;			//アイコン位置.
		D3DXVECTOR2*	m_pvPattern;		//画像パターン.
		CSpriteUI**		m_ppCNumSprite;		//数字のスプライト.

		stItemInfo()
			: m_vIconPos	 (0.0f,0.0f,0.0f)
			, m_pvPattern	 (nullptr)
			, m_ppCNumSprite (nullptr)
		{}
	};

	//==================関数==================.
	void Release();		//解放処理関数.

	//==================変数==================.
	stItemInfo*		m_pstItemInfo;		//アイテム情報構想体.
	int				m_Vegetable_Count;	//野菜の個数.
	int				m_Meat_Count;		//肉の個数.
	int				m_Fish_Count;		//魚の個数.
	int				m_Rice_Count;		//米の個数.

};

#endif//#ifndef CITEM_COUNT_H.