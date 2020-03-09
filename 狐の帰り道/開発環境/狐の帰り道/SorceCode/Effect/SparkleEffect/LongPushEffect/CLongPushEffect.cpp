#include "CLongPushEffect.h"

/*****************************************
*		長押し時のエフェクトクラス.
***/
CLongPushEffect::CLongPushEffect()
	: m_PopTime_Cnt			(0)
	, m_pbIndividual_Disp	(nullptr)
{
	//初期化処理関数.
	Init();
}

CLongPushEffect::~CLongPushEffect()
{
	//解放処理関数.
	Release();
}

//============================.
//		更新処理関数.
//============================.
void CLongPushEffect::Update()
{
	//表示処理関数.
	Disp();

	//移動処理関数.
	Move();
}

//============================.
//		描画処理関数.
//============================.
void CLongPushEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		//スプライトクラスアドレス取得.
		//3種類のキラキラのスプライトを取得.
		int spriteNo = static_cast<int>(CResourceSprite::enSprite::Punch) + (sparkle % USE_SPARKLE_MAX);
		m_ppCSprite[sparkle] = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(spriteNo));
		//位置.
		m_ppCSprite[sparkle]->SetPosition(m_pvPos[sparkle]);
		//大きさ.
		m_ppCSprite[sparkle]->SetScale(D3DXVECTOR3(m_pfScale[sparkle], m_pfScale[sparkle], m_pfScale[sparkle]));
		//角度.
		m_ppCSprite[sparkle]->SetRotation(m_pvRot[sparkle]);
		//描画.
		CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCSprite[sparkle]->Render(mView, mProj, vCamePos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//============================.
//		初期化処理関数.
//============================.
void CLongPushEffect::Init()
{
	//配列動的確保.
	m_pvPos				= new D3DXVECTOR3[SPARKLE_MAX]();					
	m_pvRot				= new D3DXVECTOR3[SPARKLE_MAX]();					
	m_pfScale			= new float[SPARKLE_MAX]();							
	m_ppCSprite			= new CSprite*[SPARKLE_MAX]();						
	m_pbIndividual_Disp = new bool[SPARKLE_MAX]();							

	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		m_pvPos[sparkle]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置.
		m_pvRot[sparkle]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度.
		m_pfScale[sparkle]				= SCALE_MAX;						//大きさ.
		m_ppCSprite[sparkle]			= nullptr;							//スプライトクラス.
		m_pbIndividual_Disp[sparkle]	= false;							//個別表示フラグ.
	}
}

//============================.
//		解放処理関数.
//============================.
void CLongPushEffect::Release()
{
	//配列動的確保.
	SAFE_DELETE_ARRAY(m_pbIndividual_Disp);
	SAFE_DELETE_ARRAY(m_ppCSprite);
	SAFE_DELETE_ARRAY(m_pfScale);
	SAFE_DELETE_ARRAY(m_pvRot);
	SAFE_DELETE_ARRAY(m_pvPos);
}

//============================.
//		表示処理関数.
//============================.
void CLongPushEffect::Disp()
{
	//キラキラのカウント.
	int m_Sparkle_Cnt = 0;

	//出現タイムカウントの加算.
	m_PopTime_Cnt++;

	if (m_PopTime_Cnt > SPARKLE_POP_TIME) {
		for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
			if (m_pbIndividual_Disp[sparkle] == false && m_Sparkle_Cnt < SPARKLE_HORIZON_MAX) {
				//位置座標設定処理関数.
				SettingPosition(sparkle);
				m_pbIndividual_Disp[sparkle] = true;
				//カウント.
				m_Sparkle_Cnt++;
			}
		}
		//タイムカウントの初期化.
		m_PopTime_Cnt = 0;
	}
}

//============================.
//		個別表示フラグ.
//============================.
void CLongPushEffect::SettingPosition(int sparkle)
{
	//引く値(奇数になれば引く).
	float Start_Distance = ((sparkle / SPARKLE_HORIZON_MAX) % 2) * INTERVAL.x;		//左側.
	float Interval_Distance = ((sparkle / SPARKLE_HORIZON_MAX) % 2) * INTERVAL.y;	//右側.
	//基準のx座標計算.
	float Criteria_PosX = (MOST.x + Start_Distance) + ((sparkle % SPARKLE_HORIZON_MAX) * (MOST.y - Interval_Distance));
	//プレイヤーの中心に合わせる.
	m_pvPos[sparkle].x = m_vCenterPos.x + Criteria_PosX;

	m_pvPos[sparkle].z = m_vCenterPos.z;
	m_pvPos[sparkle].y = STANDERD_HEIGHT;
}

//============================.
//		移動処理関数.
//============================.
void CLongPushEffect::Move()
{
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		if (m_pbIndividual_Disp[sparkle] == true) {
			//奥にキラキラを流す.
			m_pvPos[sparkle].z -= FLOW_SPEED;
			//拡縮処理関数.
			Scaling(sparkle);
		}
	}
}

//=============================.
//		拡縮処理関数.
//=============================.
void CLongPushEffect::Scaling(int sparkle)
{
	//縮小処理.
	m_pfScale[sparkle] -= SCALING_SPEED;

	if (m_pfScale[sparkle] < SCALE_MIN) {
		m_pbIndividual_Disp[sparkle] = false;
		//初期に戻す.
		m_pfScale[sparkle] = SCALE_MAX;
	}
}
