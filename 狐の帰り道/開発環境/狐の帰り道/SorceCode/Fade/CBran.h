#ifndef CBRAN_H
#define CBRAN_H

#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Drawing\Bord_Polygon\CDepth_Stencil.h"

#include "..\Sound\CSEPlayManager.h"

/*******************************************
*	ふすまクラス.
**/
class CBran
{
public:
	CBran();
	~CBran();
	//===============列挙体==================//.
	enum class enBran_Status
	{
		Open = 0,		//開く.
		Close,			//閉まる.

		MAX,			//最大数.
		Start = Open,	//最初.
	};

	//===============関数==================//.
	void Init();		//初期化処理関数.
	void UpDate();	//更新処理関数.
	void Render();	//描画処理関数.

	//～情報置換関数～.
	void SetBran_Open();
	void SetBran_Close();

	//～情報取得処理関数～.
	bool GetBran_OpenEnd() { return m_bBran_OpenEndFlag; }
	bool GetBran_OpenFlag()	{ return m_bBran_OpenFlag; }
	bool GetBran_CloseFlag(){ return m_bBran_CloseFlag; }

private:
	//===============定数==================//.
	const D3DXVECTOR3	LEFT_INIT_POSITION	= D3DXVECTOR3(   0.0f,  0.0f, 0.0f);	//開始位置.
	const D3DXVECTOR3	RIGHT_INIT_POSITION	= D3DXVECTOR3(1280.0f,  0.0f, 0.0f);	//開始位置.
	const D3DXVECTOR3	CLOSE_POSITION		= D3DXVECTOR3( 640.0f,  0.0f, 0.0f);	//閉める位置.
	const D3DXVECTOR3	LEFT_ROTATION		= D3DXVECTOR3(   0.0f, 3.15f, 0.0f);	//回転値.
	const D3DXVECTOR3	RIGHT_ROTATION		= D3DXVECTOR3(   0.0f,  0.0f, 0.0f);	//回転値.
	const float			SPEED				= 30.0f;								//開閉速度.
	const int			BRAN_MAX			= 2;									//ふすま最大数.
	const int			CLOSE_TIME			= 20;									//閉じている時間.
	const int			LEFT				= 0;
	const int			RIGHT				= 1;
	
	//===============関数==================//.
	void Bran_Open();	//開く.
	void Bran_Close();	//閉まる.
	void Release();		//解放処理関数.

	//===============変数==================//.
	CSpriteUI**			m_ppCSpriteUI;			//スプライトUIクラス.
	CResourceManager*	m_pCResourceManager;	//リソース管理クラス.
	CDepth_Stencil*		m_pDepth_Srencil;		//デプスステンシルクラス.
	D3DXVECTOR3*		m_vPos;					//座標.
	D3DXVECTOR3*		m_vRot;					//座標.
	enBran_Status		m_enBran_State;			//ふすま状態列挙体.
	bool				m_bBran_OpenFlag;
	bool				m_bBran_OpenEndFlag;	//開き終わったか.
	bool				m_bBran_CloseFlag;
	int					m_WaitTime;

	CSEPlayManager*		m_pCSEPlayManager;
};

#endif//##ifndef CBRAN_H.
