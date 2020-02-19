#include "CBossFlyEffect.h"

/****************************************
*		ボスが飛ぶ時のエフェクト.
****/
CBossFlyEffect::CBossFlyEffect()
	: m_pfMoveSpeed			(nullptr)
	, m_pbIndiviDispFlag	(nullptr)
	, m_bMoveFlag			(true)
	, m_bCheckFlag			(false)
{
	//初期化処理関数.
	Init();
}

CBossFlyEffect::~CBossFlyEffect()
{
	//解放処理関数.
	Release();
}

//=============================================.
//		更新処理関数.
//=============================================.
void CBossFlyEffect::Update()
{
	//表示判定処理関数.
	Disp();
	//移動処理関数.
	Move();
	//スケールの変更処理関数.
	Scaling();
	//透過処理関数.
	TransparetProcess();
	//回転処理関数.
	Rotation();
}

//=============================================.
//		描画処理関数.
//=============================================.
void CBossFlyEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		if (m_pbIndiviDispFlag[smoke] == true) {
			//クラスアドレス取得.
			m_ppCSprite[smoke] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Smoke);
			//カメラの向きに合わせない.
			m_ppCSprite[smoke]->SetCancelRotationFlag(false);
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
}

//=============================================.
//		初期化処理関数.
//=============================================.
void CBossFlyEffect::Init()
{
	//配列動的確保.
	m_pvPos				= new D3DXVECTOR3[SMOKE_MAX]();	//座標.
	m_pvRot				= new D3DXVECTOR3[SMOKE_MAX]();	//角度.
	m_pfScale			= new float[SMOKE_MAX]();		//大きさ.
	m_ppCSprite			= new CSprite*[SMOKE_MAX]();	//スプライトクラス.
	m_pfAlpha			= new float[SMOKE_MAX]();		//透過値.
	m_pbSmokeDispFlag	= new bool[SMOKE_MAX]();		//煙が出るフラグ.
	m_pfMoveSpeed		= new float[SMOKE_MAX]();		//移動速度.
	m_pbIndiviDispFlag	= new bool[SMOKE_MAX]();		//個別表示フラグ.

	//初期化処理.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//位置.
		m_pvRot[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//角度.
		m_pfScale[smoke]			= SCALE_SIZE_MIN * fabsf(SMOKE_QUATER - (smoke / 2));	//大きさ.
		m_ppCSprite[smoke]			= nullptr;												//スプライトクラス.
		m_pfAlpha[smoke]			= ALPHA_MAX;											//透過値.
		m_pbSmokeDispFlag[smoke]	= false;												//煙が出るフラグ.
		m_pfMoveSpeed[smoke]		= POS_UP_SPEED;											//移動速度
		m_pbIndiviDispFlag[smoke]	= false;												//個別表示フラグ.
	}

	m_SmokeMax				= SMOKE_MAX;		//煙の最大数.
	m_fStartPos_x			= START_POSITION_X;	//左端の位置.
	m_fInterval_Width		= INTERVAL_WIDTH;	//幅の間隔.
}

//=============================================.
//		解放処理関数.
//=============================================.
void CBossFlyEffect::Release()
{
	for (int sprite = SMOKE_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}

	//解放.
	SAFE_DELETE_ARRAY(m_pbIndiviDispFlag);	//個別表示フラグ.
	SAFE_DELETE_ARRAY(m_pfMoveSpeed);		//移動速度.
	SAFE_DELETE_ARRAY(m_pbSmokeDispFlag);	//煙が出るフラグ.
	SAFE_DELETE_ARRAY(m_pfAlpha);			//透過値.
	SAFE_DELETE_ARRAY(m_ppCSprite);			//スプライトクラス.
	SAFE_DELETE_ARRAY(m_pfScale);			//大きさ.
	SAFE_DELETE_ARRAY(m_pvRot);				//角度.
	SAFE_DELETE_ARRAY(m_pvPos);				//座標.

}

//==============================================.
//		表示判定処理関数.
//==============================================.
void CBossFlyEffect::Disp()
{
	if (m_bCheckFlag == false) {
		for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
			int m_Smoke_HorizonNum = smoke / 2;	//煙の横列の番号.
			int m_Smoke_VerticalNum = smoke % 2;//煙の縦列の番号.
			m_pvPos[smoke] = m_vCenterPos;
			m_pvPos[smoke].x += m_fStartPos_x + (m_Smoke_HorizonNum * INTERVAL_WIDTH);
			m_pvPos[smoke].y -= FOOT_DIFFERENCIAL - (m_Smoke_VerticalNum * INTERVAL_HEIGHT);
			m_pbIndiviDispFlag[smoke] = true;
		}
		m_bCheckFlag = true;
	}
}

//==============================================.
//		移動処理関数.
//==============================================.
void CBossFlyEffect::Move()
{
	if (m_bMoveFlag == true) {
		for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
			//煙の移動.
			m_pvPos[smoke].y += m_pfMoveSpeed[smoke];
			m_pfMoveSpeed[smoke] += (SPEED_UP * fabsf(SMOKE_QUATER - (smoke / 2)));

			if (m_pvPos[smoke].y >= MOVE_UPPER_LIMIT) {
				//移動終了.
				m_bMoveFlag = false;
			}
		}
	}
}

//==============================================.
//		スケール処理関数.
//==============================================.
void CBossFlyEffect::Scaling()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pfScale[smoke] += SCALE_UP_SPEED;
	}
}

//=============================================.
//		透過処理関数.
//=============================================.
void CBossFlyEffect::TransparetProcess()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pfAlpha[smoke] -= STANDERD_TRAN_SPEED + (TRANS_EXTRA_SPEED * fabsf(SMOKE_QUATER - (smoke / 2)));
		if (m_pfAlpha[smoke] <= 0.0f) {
			m_pbIndiviDispFlag[smoke] = false;
		}
	}
}

//=============================================.
//		回転処理関数.
//=============================================.
void CBossFlyEffect::Rotation()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//煙が並んだ時の縦の番号.
		const int m_fVerticalNum	= smoke / 2;
		//両端から中央までを基準にした番号.
		const float m_fSmokeNum	= SMOKE_QUATER - m_fVerticalNum;
		//回転する方向がない場合は左回転.
		float m_fRotationDirection = RIGHT_ROTATION_NUM;
		if (m_fSmokeNum != 0) {
			//回転する方向(正か負か).
			m_fRotationDirection =  (fabsf(m_fSmokeNum)/ m_fSmokeNum) * RIGHT_ROTATION_NUM;
		}

		m_pvRot[smoke].z += m_fRotationDirection * ROTATION_SPEED;
		if (fabsf(m_pvRot[smoke].z) > ROTATION_MAX) {
			m_pvRot[smoke].z = 0.0f;
		}
	}
}