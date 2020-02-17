#ifndef _CEFFECT_BASE_H
#define _CEFFECT_BASE_H

#include "..\Drawing\Resource\CResourceManager.h"

/***********************************************
*		エフェクト元クラス.
**/
class CEffectBase
{
public:
	CEffectBase();
	virtual ~CEffectBase();

	//==================関数====================//.
	virtual void	UpDate() = 0;															//更新処理関数.
	virtual void	Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos) = 0;	//描画処理関数.

	//----- 情報置換処理関数 ----//.
	void SetCenterPos(D3DXVECTOR3 vPos) { m_vCenterPos = vPos; }	//中心位置.
	void SetEffectStart(bool bFlag) { m_bDispFlag = bFlag; }		//開始フラグ.

	//----- 情報取得処理関数 ----//.
	bool GetEffectStartFlag() { return m_bDispFlag; }				//開始フラグ.
protected:
	//==================関数=====================//.
	virtual void	Init() = 0;				//初期化処理関数.
	virtual void	Release() = 0;			//解放処理関数.

	//==================変数=====================//.
	D3DXVECTOR3			m_vCenterPos;		//中心位置.
	D3DXVECTOR3*		m_pvPos;			//位置.
	D3DXVECTOR3*		m_pvRot;			//角度.
	float*				m_pfScale;			//キラキラの大きさ.
	bool				m_bDispFlag;		//表示フラグ.
	bool				m_bOldDispFlag;		//前回の表示フラグ.
	CSprite**			m_ppCSprite;		//スプライトクラス.
	CResourceManager*	m_pCResourceManager;//リソース管理クラス.

private:
};

#endif	//#ifndef _CEFFECT_BASE_H.