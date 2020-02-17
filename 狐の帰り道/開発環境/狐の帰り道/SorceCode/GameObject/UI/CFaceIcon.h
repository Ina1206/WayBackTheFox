#ifndef CFACEICON_H
#define CFACEICON_H

#include "..\UI\CUI_Base.h"

//=============================.
//	追加.
#include "..\..\Sound\CSEPlayManager.h"
//=============================.

/***********************************************
*	顔アイコンクラス.
**/

class CFaceIcon
	: public CUI_Base
{
public:
	CFaceIcon();
	~CFaceIcon();

	//=================関数===================//.
	void UpDate();			//更新処理関数.
	void Render();			//描画処理関数.
	//～情報置換処理関数～.
	void SetItemPointSum(int num) { m_PointSum = num; }

private:
	//=================定数===================//.
	const D3DXVECTOR3 FACEICON_AMOUNT_POS	= D3DXVECTOR3(945.0f, -10.0f, 0.0f);
	const D3DXVECTOR3 FACEICON_POS			= D3DXVECTOR3(995.0f, 30.0f, 0.0f);
	const int FACE_SPRITEUI_MAX				= 7;
	const int FACE_NORMAL					= 0;
	const int FACE_SMILE					= 1;
	const int FACE_MAXSMILE					= 2;
	const int FACE_AMOUNT					= 3;
	const int FACE_NORMAL_BACK				= 6;
	const int FACE_SMILE_BACK				= 5;
	const int FACE_MAXSMILE_BACK			= 4;
	const int CHANGE_SMILE					= 25;
	const int CHANGE_MAXSMILE				= 50;

	//=================関数===================//.
	void Release();			//解放処理関数.

	//=================変数===================//.
	CSpriteUI**			m_ppCFaceIcon;
	int					m_PointSum;				//ポイント合計.

	//=============================.
	//	追加.
	CSEPlayManager*		m_pCSEPlayManager;		//SE再生クラス.
	int					m_FaceType;				//顔の種類.
	int					m_OldFaceType;			//前回の顔の種類.
	//=============================.

};

#endif//#ifndef CFACEICON_H.