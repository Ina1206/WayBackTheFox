#include "CEnemyFlyEffect.h"

CEnemyFlyEffect::CEnemyFlyEffect()
{
	//初期化処理関数.
	Init();
}

CEnemyFlyEffect::~CEnemyFlyEffect()
{
	//解放処理関数.
	Release();
}

//=======================================.
//		更新処理関数.
//=======================================.
void CEnemyFlyEffect::UpDate()
{
	//煙の表示処理関数.
	SmokeDisp();
	//煙の回転処理関数.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		Ratation(smoke, false);
	}
}

//=======================================.
//		描画処理関数.
//=======================================.
void CEnemyFlyEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//クラスアドレス取得.
		m_ppCSprite[smoke] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Smoke);
		//位置.
		m_ppCSprite[smoke]->SetPosition(m_pvPos[smoke]);
		//角度.
		m_ppCSprite[smoke]->SetRotation(m_pvRot[smoke]);
		//大きさ.
		m_ppCSprite[smoke]->SetScale(D3DXVECTOR3(m_pfScale[smoke], m_pfScale[smoke], m_pfScale[smoke]));
		//透過値.
		m_ppCSprite[smoke]->SetAlpha(m_pfAlpha[smoke]);
		//描画
		CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCSprite[smoke]->Render(mView, mProj, vCamePos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//=======================================.
//		初期化処理関数.
//=======================================.
void CEnemyFlyEffect::Init()
{
	//配列の動的確保.
	m_pvPos				= new D3DXVECTOR3[SMOKE_MAX]();	//座標.
	m_pvRot				= new D3DXVECTOR3[SMOKE_MAX]();	//角度.
	m_pfScale			= new float[SMOKE_MAX]();		//大きさ.
	m_ppCSprite			= new CSprite*[SMOKE_MAX]();	//スプライトクラス.
	m_pfAlpha			= new float[SMOKE_MAX]();		//透過値.
	m_pbSmokeDispFlag	= new bool[SMOKE_MAX]();		//煙が出るフラグ.
	
	//初期化処理.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置.
		m_pvRot[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度.
		m_pfScale[smoke]			= 0.0f;								//大きさ.
		m_ppCSprite[smoke]			= nullptr;							//スプライトクラス.
		m_pfAlpha[smoke]			= ALPHA_MAX;						//透過値.
		m_pbSmokeDispFlag[smoke]	= false;							//煙が出るフラグ.
	}

	m_SmokeMax				= SMOKE_MAX;		//煙の最大数.
	m_fStartPos_x			= START_POSITION_X;	//左端の位置.
	m_Row_Max				= ROW_MAX;			//横の列の最大数.s
	m_fInterval_Width		= INTERVAL_WIDTH;	//幅の間隔.
	m_fFoot_Differencial	= FOOT_DIFFERENCIAL;//中心から足元の差.
	m_fMax_Scale			= MAX_SCALE;		//大きさの最大数.

}

//=======================================.
//		解放処理関数.
//=======================================.
void CEnemyFlyEffect::Release()
{
	for (int sprite = SMOKE_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}

	//解放.
	SAFE_DELETE_ARRAY(m_pbSmokeDispFlag);	//煙が出るフラグ.
	SAFE_DELETE_ARRAY(m_pfAlpha);			//透過値.
	SAFE_DELETE_ARRAY(m_ppCSprite);			//スプライトクラス.
	SAFE_DELETE_ARRAY(m_pfScale);			//大きさ.
	SAFE_DELETE_ARRAY(m_pvRot);				//角度.
	SAFE_DELETE_ARRAY(m_pvPos);				//座標.
}

