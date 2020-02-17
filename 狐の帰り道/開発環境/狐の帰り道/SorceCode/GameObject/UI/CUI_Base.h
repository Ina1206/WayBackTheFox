#ifndef CUI_BASE_H
#define CUI_BASE_H

#include "..\..\Drawing\Resource\CResourceManager.h"
#include "..\..\Drawing\Bord_Polygon\CDepth_Stencil.h"

extern bool g_BranOpenFlag;

/***************************************************
*		UIの元となるクラス.
**/
class CUI_Base
{
public:
	//=================定数===================//.
	const int MIDDLE_POINT	= 24;
	const int HIGH_POINT	= 48;

	//------------------------------------------.
	//	列挙体.
	//------------------------------------------.
	enum class enFade
	{
		Fade_In = 0,		//フェードイン.
		Fade_Out,			//フェードアウト.

	};

	//クリアの状態.
	enum class enClear_Status
	{
		High = 0,		//高.
		Middle,			//中.
		Low,			//低.

		Max,			//最大.
		Start = High,	//最初.

	};

	CUI_Base();
	~CUI_Base();

	//=================関数===================//.
	void Value_Set(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);
	virtual void UpDate() = 0;		//更新処理関数.
	virtual void Render() = 0;		//描画処理関数.
	virtual void Release() = 0;		//解放処理関数.

	void SetPointSum(int num) { m_PointSum = num; }

	//～情報取得関数～.
	bool GetMoveEndFlag() { return m_bMoveEndFlag; }


protected:
	//=================変数===================//.
	D3DXVECTOR3			m_vCameraPos;			//カメラ位置.
	D3DXMATRIX			m_mView;				//ビュー行列.
	D3DXMATRIX			m_mProj;				//プロジェクション行列.

	CResourceManager*	m_pCResourceManager;	//読み込み管理クラス.
	CDepth_Stencil*		m_pCDepth_Stencil;		//デプスステンシルクラス.

	D3DXVECTOR3			m_vPos;					//位置情報.
	int					m_PointSum;				//ポイントの合計.
	bool				m_bMoveEndFlag;		    //停止確認用フラグ.

private:
};

#endif//#ifndef CUI_BASE_H.
