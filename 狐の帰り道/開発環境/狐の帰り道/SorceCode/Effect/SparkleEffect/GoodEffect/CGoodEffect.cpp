#include "CGoodEffect.h"

CGoodEffect::CGoodEffect()
{
	//初期化処理関数.
	Init();
}

CGoodEffect::~CGoodEffect()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		描画処理関数.
//===========================================.
void CGoodEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int sprite = 0; sprite < SPARKLE_MAX; sprite++) {
		//スプライトクラスのアドレス取得.
		m_ppCSprite[sprite] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Sparkle);
		//位置座標.
		m_ppCSprite[sprite]->SetPosition(m_pvPos[sprite]);
		//スケール.
		m_ppCSprite[sprite]->SetScale(D3DXVECTOR3(m_pfScale[sprite], m_pfScale[sprite], m_pfScale[sprite]));
		//描画.
		CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCSprite[sprite]->Render(mView, mProj, vCamePos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CGoodEffect::Init()
{
	//動的確保.
	m_pvPos				= new D3DXVECTOR3[SPARKLE_MAX]();	//座標.
	m_pvRot				= new D3DXVECTOR3[SPARKLE_MAX]();	//角度.
	m_ppCSprite			= new CSprite*[SPARKLE_MAX]();		//スプライトクラス.
	m_pfScale			= new float[SPARKLE_MAX]();			//大きさ.
	m_penScalingType	= new enScalingType[SPARKLE_MAX]();	//拡縮の処理のタイプ.

	m_Sparkle_max			= SPARKLE_MAX;			//キラキラの最大数.
	m_fCenterDifferencial	= CENTER_DIFFECENCIAL;	//中央から始める高さの差分.
	m_RowMax				= ROW_MAX;				//横列のキラキラの最大数.
	m_fHeight_Width			= HEIGHT_WIDHT;			//高さの幅.
	m_fLeftInterval			= LEFT_INTERVAL;		//左側の間隔.
	m_fRightInterval		= RIGHT_INTERVAL;		//右側の間隔.
	m_fLeftMost				= LEFT_MOST;			//左端.
	m_fRightMost			= RIGHT_MOST;			//右端.
	m_fScaleMax				= SCALE_MAX;			//大きさ.
}

//===========================================.
//		解放処理関数.
//===========================================.
void CGoodEffect::Release()
{
	for (int sprite = SPARKLE_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}

	//解放処理関数.
	SAFE_DELETE_ARRAY(m_penScalingType);	//拡縮の処理のタイプ.
	SAFE_DELETE_ARRAY(m_pfScale);			//大きさ.
	SAFE_DELETE_ARRAY(m_ppCSprite);			//スプライトクラス.
	SAFE_DELETE_ARRAY(m_pvRot);				//角度.
	SAFE_DELETE_ARRAY(m_pvPos);				//座標.
}