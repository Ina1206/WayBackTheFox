#ifndef CMAINUIMANAGER_H
#define CMAINUIMANAGER_H

#include "CItemIcon.h"
#include "CFaceIcon.h"
#include "CStartCount.h"
#include "CItemCount.h"
#include "CItemPoint_Bar.h"

class CMainUIManager
{
public:
	CMainUIManager();
	~CMainUIManager();

	//=================関数===================//.
	void Init_Process();	//初期化関数.
	void UpDate();			//更新処理関数.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//描画処理関数.

	//～情報置換処理関数～.
	void SetItemPointSum(int num) { m_PointSum = num; }									//ポイントの合計取得.
	void SetItemCount(int num, int count) { m_pCItemCount->SetItemCount(num, count); }	//アイテムの個数取得.

	//情報取得処理関数.
	bool GetStartCountDispFlag() { return m_pCStartCount->GetDispFlag(); }				//スタートカウントの描画フラグ取得.

private:
	//=================定数===================//.
	const int ITEM_TYPE_MAX = static_cast<int>(enItemType::MAX);

	//=================関数===================//.
	void Release();			//解放処理関数.

	//=================変数===================//.
	CItemIcon*		m_pCItemIcon;
	CFaceIcon*		m_pCFaceIcon;
	CStartCount*	m_pCStartCount;
	CItemCount*		m_pCItemCount;
	CItemPoint_Bar* m_pCtemPoint_Bar;

	int m_PointSum;
};

#endif	//#ifndef CMAINUIMANAGER_H
