#include "CGreatEffect.h"

CGreatEffect::CGreatEffect()
{
	//初期化処理関数.
	Init();
}

CGreatEffect::~CGreatEffect()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		描画処理関数.
//===========================================.
void CGreatEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		//スプライトクラスアドレス取得.
		//3種類のキラキラを取得.
		int spriteNo = static_cast<int>(CResourceSprite::enSprite::Punch) + (sparkle % USE_SPARKLE_MAX);

		m_ppCSprite[sparkle] = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(spriteNo));
		//位置.
		m_ppCSprite[sparkle]->SetPosition(m_pvPos[sparkle]);
		//大きさ.
		m_ppCSprite[sparkle]->SetScale(D3DXVECTOR3(m_pfScale[sparkle], m_pfScale[sparkle], m_pfScale[sparkle]));
		//描画.
		CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCSprite[sparkle]->Render(mView, mProj, vCamePos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//===========================================.
//		初期化処理関数.
//===========================================.
void CGreatEffect::Init()
{
	//動的確保.
	m_pvPos				= new D3DXVECTOR3[SPARKLE_MAX]();	//位置.
	m_pvRot				= new D3DXVECTOR3[SPARKLE_MAX]();	//角度.
	m_ppCSprite			= new CSprite*[SPARKLE_MAX]();		//スプライトクラス.
	m_pfScale			= new float[SPARKLE_MAX]();			//大きさ.
	m_penScalingType	= new enScalingType[SPARKLE_MAX]();//拡縮処理タイプ.

	//値設定.
	m_Sparkle_max			= SPARKLE_MAX;			//キラキラの最大数.
	m_fCenterDifferencial	= CENTER_DIFFERENCIAL;	//中央からの高さの差.
	m_RowMax				= ROW_MAX;				//横列のキラキラの最大数.
	m_fHeight_Width			= HEIGHT_WIDTH;			//高さの幅.
	m_fLeftInterval			= LEFT_INTERVAL;		//左側の間隔.
	m_fRightInterval		= RIGHT_INTERVAL;		//右側の間隔.
	m_fLeftMost				= LEFTMOST;				//左端.
	m_fRightMost			= RIGHTMOST;			//右端.
	m_fScaleMax				= SCALE_MAX;			//大きさ.
}

//===========================================.
//		解放処理関数.
//===========================================.
void CGreatEffect::Release()
{
	//初期化.
	for (int sprite = SPARKLE_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}

	//解放.
	SAFE_DELETE_ARRAY(m_penScalingType);//拡縮処理タイプ.
	SAFE_DELETE_ARRAY(m_pfScale);		//大きさ.
	SAFE_DELETE_ARRAY(m_ppCSprite);		//スプライトクラス.
	SAFE_DELETE_ARRAY(m_pvRot);			//角度.
	SAFE_DELETE_ARRAY(m_pvPos);			//位置.
}

