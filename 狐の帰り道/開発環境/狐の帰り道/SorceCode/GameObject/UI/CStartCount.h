#ifndef CSTART_COUNT_H
#define CSTART_COUNT_H

#include "CUI_Base.h"

class CStartCount
	: public CUI_Base
{
public:
	CStartCount();
	~CStartCount();

	//=================関数===================//.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.

	//情報置換処理関数.
	void SetDispFlag(bool flag) { m_bDispFlag = flag; }
	//情報取得関数.
	bool GetDispFlag() { return m_bDispFlag; }


private:
	//=================定数===================//.
	const D3DXVECTOR3 POSITION = D3DXVECTOR3(600.0f, 300.0f, 0.0f);
	const D3DXVECTOR3 START_POSITION = D3DXVECTOR3(450.0f, 300.0f, 0.0f);
	const int IMAGE_WIDTH_MAX = 5;
	const int IMAGE_HIGH_MAX = 5;

	//=================関数===================//.
	void Release();							//解放処理関数.
	void Move();

	//=================変数===================//.
	CSpriteUI*		m_pCStartCount;		//SpriteUIクラス.
	CSpriteUI*		m_pCStart;			//SpriteUIクラス.

	D3DXVECTOR2		m_vPattarn;			//数字のパターン.
	int				m_Frame;			//経過時間.
	int				m_Second;			//経過秒数.
	bool			m_bDispFlag;		//描画フラグ.

};

#endif//#ifndef CSTART_COUNT_H