#include "CLandingEffect.h"

/*************************************
*		着地エフェクトクラス.
***************/
CLandingEffect::CLandingEffect()
	: m_pfAlpha	(nullptr)
{
	//初期化処理関数.
	Init();
}

CLandingEffect::~CLandingEffect()
{
	//解放処理関数.
	Release();
}

//================================.
//		更新処理関数.
//================================.
void CLandingEffect::Update()
{
	if (m_bDispFlag != m_bOldDispFlag) {
		for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
			//位置設定処理関数.
			Position_Setting(smoke);
		}
	}

	if (m_bDispFlag == true) {
		//移動処理関数.
		Move();
	}
	m_bOldDispFlag = m_bDispFlag;
}

//================================.
//		描画処理関数.
//================================.
void CLandingEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//アドレス取得.
		m_ppCSprite[smoke] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Smoke);
		m_ppCSprite[smoke]->SetCancelRotationFlag(false);
		//角度.
		m_ppCSprite[smoke]->SetRotation(m_pvRot[smoke]);
		//位置.
		m_ppCSprite[smoke]->SetPosition(m_pvPos[smoke]);
		//透過値.
		m_ppCSprite[smoke]->SetAlpha(m_pfAlpha[smoke]);
		//大きさ.
		m_ppCSprite[smoke]->SetScale(D3DXVECTOR3(m_pfScale[smoke], m_pfScale[smoke], m_pfScale[smoke]));
		//描画.
		CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepthStencil->SetDepth(false);
		m_ppCSprite[smoke]->Render(mView, mProj, vCamePos);
		m_pCDepthStencil->SetDepth(true);
	}

}

//================================.
//		初期化処理関数.
//================================.
void CLandingEffect::Init()
{
	//配列動的確保.
	m_pvPos		= new D3DXVECTOR3[SMOKE_MAX]();	//位置.
	m_pvRot		= new D3DXVECTOR3[SMOKE_MAX]();	//角度.
	m_pfScale	= new float[SMOKE_MAX]();		//大きさ.
	m_ppCSprite = new CSprite*[SMOKE_MAX]();	//スプライトクラス.
	m_pfAlpha	= new float[SMOKE_MAX]();		//透過値.

	//初期化処理.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置.
		m_pvRot[smoke]		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度.
		m_pfScale[smoke]	= SCALE_MIN;						//大きさ.
		m_ppCSprite[smoke]	= nullptr;							//スプライトクラス.
		m_pfAlpha[smoke]	= ALPHA_MAX;						//透過値.
	}
}

//================================.
//		解放処理関数.
//================================.
void CLandingEffect::Release()
{
	SAFE_DELETE_ARRAY(m_pfAlpha);	//透過値.
	SAFE_DELETE_ARRAY(m_ppCSprite);	//スプライトクラス.
	SAFE_DELETE_ARRAY(m_pfScale);	//大きさ.
	SAFE_DELETE_ARRAY(m_pvRot);		//角度.
	SAFE_DELETE_ARRAY(m_pvPos);		//位置.
}

//================================.
//		位置設定処理関数.
//================================.
void CLandingEffect::Position_Setting(int smoke)
{
	m_pvPos[smoke].x = (m_vCenterPos.x - START_POS) + ((smoke % 2) * INTERVAL_WIDTH);
	m_pvPos[smoke].y = m_vCenterPos.y;
	m_pvPos[smoke].z = m_vCenterPos.z;
}

//================================.
//		移動処理関数.
//================================.
void CLandingEffect::Move()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//左方向.
		const int LeftDirection = -1;
		//移動方向(外側に移動).
		const int TravelDirection = LeftDirection + ((smoke % 2) * 2);
		//移動処理.
		m_pvPos[smoke].x += MOVE_SPEED.x * TravelDirection;
		m_pvPos[smoke].y += MOVE_SPEED.y;

		//回転処理.
		m_pvRot[smoke].z += ROTATION_SPEED * TravelDirection;
		if (fabsf(m_pvRot[smoke].z) > ROTATION_MAX) {
			m_pvRot[smoke].z = 0.0f;
		}
		
		//透過拡大処理関数.
		Alpha_Scaling(smoke);
	}
}

//================================.
//		透過と拡大処理関数.
//================================.
void CLandingEffect::Alpha_Scaling(int smoke)
{
	//拡大処理.
	m_pfScale[smoke] += SCALE_SPEED;
	if (m_pfScale[smoke] > SCALE_MAX) {
		m_pfScale[smoke] = SCALE_MAX;
	}

	//透過処理.
	m_pfAlpha[smoke] -= TRANS_SPEED;
	if (m_pfAlpha[smoke] < ALPHA_MIN) {
		//初期化.
		m_pfAlpha[smoke] = ALPHA_MAX;
		m_pfScale[smoke] = SCALE_MIN;
		//表示終了.
		m_bDispFlag = false;
	}

	
}