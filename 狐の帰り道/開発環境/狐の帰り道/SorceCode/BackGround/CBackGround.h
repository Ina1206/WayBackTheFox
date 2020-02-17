#ifndef CBACK_GROUND_H
#define CBACK_GROUND_H

#include "..\Global.h"
#include "..\Drawing\Resource\CResourceManager.h"

/********************************************
*		背景オブジェクトクラス.
*****/
class CBackGround
{
public:
	CBackGround();
	~CBackGround();
	//====================定数=======================//.
	const D3DXVECTOR3	POSITION	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置設定.
	const float			SCALE		= 0.01f;							//大きさ.
	const D3DXVECTOR3	ROTATION	= D3DXVECTOR3(0.0f, 3.2f, 0.0f);	//回転角度.

	//====================関数=======================//.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos);	//描画処理関数.

private:
	void Init();		//初期化処理関数.
	void Release();		//解放処理関数.

	//====================変数=========================//.
	CDX9Mesh*		m_pCDx9Mesh;	//メッシュクラス.
};

#endif	//#ifndef CBACK_GROUND_H.