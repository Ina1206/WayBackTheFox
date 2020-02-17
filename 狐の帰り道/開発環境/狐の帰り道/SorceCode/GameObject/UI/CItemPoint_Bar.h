#ifndef CITEMPOINT_BAR_H
#define CITEMPOINT_BAR_H

#include "CUI_Base.h"

class CItemPoint_Bar
	: public CUI_Base
{
public:
	CItemPoint_Bar();
	~CItemPoint_Bar();

	void UpDate();
	void Render();
	//～情報置換処理関数～.
	void SetItemPointSum(int num) { m_PointSum = num; }

private:
	void Release();

	//==============定数====================//.
	const D3DXVECTOR3 BER_BACK_POSITION = D3DXVECTOR3(970.0f, 310.0f, 0.0);
	const D3DXVECTOR2 BER_POSITION      = D3DXVECTOR2(29.0f, 23.5f);
	const float SCALE_MAX				= 1.0f;
	const float SCALE_SPEED				= 0.01f;
	const int   BER_MAX					= 4;
	const int   BER_BACK				= 0;
	const int   BER_BLUEMAX				= 1;
	const int   BER_REDMAX				= 2;
	const int   BER_RAINBOWMAX			= 3;

	//==============変数====================//.
	CSpriteUI** m_ppCBarSprite;
	float*		m_pfScale;
	int			m_PointSum;				//ポイント合計.
};

#endif//#ifndef CITEMPOINT_BAR_H
