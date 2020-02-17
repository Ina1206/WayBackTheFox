#include "CStepEffect.h"

CStepEffect::CStepEffect()
{
	//初期化処理関数.
	Init();
}

CStepEffect::~CStepEffect()
{
	//解放処理関数.
	Release();
}

//===========================================.
//		描画処理関数.
//===========================================.
void CStepEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		//スプライトクラスアドレス取得.
		int spriteNo = static_cast<int>(CResourceSprite::enSprite::Sparkle) + (sparkle % USE_SPARKLE_MAX);
		if (sparkle % USE_SPARKLE_MAX > 1) {
			spriteNo = static_cast<int>(CResourceSprite::enSprite::Sparkle);
		}
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
void CStepEffect::Init()
{
	//配列動的確保.
	m_pvPos				= new D3DXVECTOR3[SPARKLE_MAX]();	//位置.
	m_pvRot				= new D3DXVECTOR3[SPARKLE_MAX]();	//角度.
	m_pfScale			= new float[SPARKLE_MAX]();			//大きさ.
	m_ppCSprite			= new CSprite*[SPARKLE_MAX]();		//スプライトクラス.
	m_penScalingType	= new enScalingType[SPARKLE_MAX]();	//拡縮処理のタイプ.

	//初期化.
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		m_pvPos[sparkle]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置.
		m_pvRot[sparkle]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度.
		m_pfScale[sparkle]			= 0.5f;								//大きさ.
		m_ppCSprite[sparkle]		= nullptr;							//スプライトクラス.
		m_penScalingType[sparkle]	= enScalingType::Large;				//拡縮処理のタイプ.
	}

	//値設定.
	m_Sparkle_max			= SPARKLE_MAX;
	m_fCenterDifferencial	= START_POSITION.y;
	m_RowMax				= HORIZON_SPARKLE;
	m_fHeight_Width			= ARRANGEMENT_INTERVAL.y;
	m_fLeftInterval			= INTERVAL.x;
	m_fRightInterval		= INTERVAL.y;
	m_fLeftMost				= MOST.x;
	m_fRightMost			= MOST.y;
	m_fScaleMax				= SCALE_MAX;
}

//===========================================.
//		解放処理関数.
//===========================================.
void CStepEffect::Release()
{
	//解放処理.
	SAFE_DELETE_ARRAY(m_penScalingType);
	SAFE_DELETE_ARRAY(m_ppCSprite);
	SAFE_DELETE_ARRAY(m_pfScale);
	SAFE_DELETE_ARRAY(m_pvRot);
	SAFE_DELETE_ARRAY(m_pvPos);
}

