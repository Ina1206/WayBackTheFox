#include "CFallDownEffect.h"

/**********************************
*		倒れる時のエフェクト.
********/
CFallDownEffect::CFallDownEffect()
	: m_pfAlpha			(nullptr)
	, m_pFadeStartCnt	(nullptr)
	, m_pvInitPos		(nullptr)
	, m_pfMoveSpeed		(nullptr)
	, m_fSpeed			(MOVE_SPEED_MAX)
{
	//初期化処理関数.
	Init();
}

CFallDownEffect::~CFallDownEffect()
{
	//解放処理関数.
	Release();
}

//====================================.
//		更新処理関数.
//====================================.
void CFallDownEffect::Update()
{
	if (m_bDispFlag != m_bOldDispFlag) {
		//表示処理関数.
		Disp();
	}

	//移動処理関数.
	Move();

	m_bOldDispFlag = m_bDispFlag;
}

//====================================.
//		描画処理関数.
//====================================.
void CFallDownEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//アドレス取得.
		m_ppCSprite[smoke] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Smoke);
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

//====================================.
//		初期化処理関数.
//====================================.
void CFallDownEffect::Init()
{
	//動的確保.
	m_pvPos			= new D3DXVECTOR3[SMOKE_MAX]();	//位置.
	m_pvRot			= new D3DXVECTOR3[SMOKE_MAX]();	//角度.
	m_pfScale		= new float[SMOKE_MAX]();		//大きさ.
	m_ppCSprite		= new CSprite*[SMOKE_MAX]();	//スプライトクラス.
	m_pfAlpha		= new float[SMOKE_MAX]();		//透過値.
	m_pFadeStartCnt = new int[SMOKE_MAX]();			//フェード開始カウント.
	m_pvInitPos		= new D3DXVECTOR3[SMOKE_MAX]();	//初期位置.
	m_pfMoveSpeed	= new float[SMOKE_MAX]();		//移動速度.

	//初期化処理.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pvRot[smoke]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pfScale[smoke]		= SCALE_MIN;
		m_ppCSprite[smoke]		= nullptr;
		m_pfAlpha[smoke]		= ALPHA_MAX;
		m_pFadeStartCnt[smoke]	= 0;
		m_pvInitPos[smoke]		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pfMoveSpeed[smoke]	= 0.0f;
	}
}

//=====================================.
//		解放処理関数.
//=====================================.
void CFallDownEffect::Release()
{
	//解放.
	SAFE_DELETE_ARRAY(m_pfMoveSpeed);
	SAFE_DELETE_ARRAY(m_pvInitPos);
	SAFE_DELETE_ARRAY(m_pFadeStartCnt);
	SAFE_DELETE_ARRAY(m_pfAlpha);
	SAFE_DELETE_ARRAY(m_ppCSprite);
	SAFE_DELETE_ARRAY(m_pfScale);
	SAFE_DELETE_ARRAY(m_pvRot);
	SAFE_DELETE_ARRAY(m_pvPos);
}

//======================================.
//		表示処理関数.
//======================================.
void CFallDownEffect::Disp()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvInitPos[smoke]		= m_vCenterPos;
		m_pvInitPos[smoke].x	-= (START_POSITION - (smoke * SMOKE_WIDTH_ADJUST));
		m_pvInitPos[smoke].y	-= SMOKE_HIGHT - (SMOKE_HIGHT_ADJUST * (smoke % ODD_EVEN_JUDGE));
		m_pfMoveSpeed[smoke]	= 0.0f;
	}
}

//======================================.
//		行動処理関数.
//======================================.
void CFallDownEffect::Move()
{
	//速度変更.
	m_fSpeed -= SPEED_DECREMENT;
	if (m_fSpeed < MOVE_SPEED_MIN) {
		m_fSpeed = MOVE_SPEED_MIN;
	}

	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//速度.
		m_pfMoveSpeed[smoke] -= m_fSpeed;
		//中央
		int halfSmokeNum = smoke / 2;
		int smokeNum = abs((SMOKE_MAX / 2) - smoke);
		D3DXVECTOR3 TargetPos			= D3DXVECTOR3(m_pvInitPos[smoke].x,  MOVE_TARGET_HEIGHT, m_vCenterPos.z);
		D3DXVECTOR3 ControlPosStart		= D3DXVECTOR3(m_pvInitPos[smoke].x + (CONTROL_POINT_WIDTH -( halfSmokeNum * CONTROL_WIDTH_ADJUST )), CONTROL_POINT_START - (smokeNum * CONTROL_ADJUST_HEI), m_vCenterPos.z);
		D3DXVECTOR3 ControlPosEnd		= D3DXVECTOR3(m_pvInitPos[smoke].x, CONTROL_POINT_END, m_vCenterPos.z);
		D3DXVECTOR3 InitPos				= D3DXVECTOR3(m_pvInitPos[smoke].x, m_pvInitPos[smoke].y, m_vCenterPos.z);
		//移動.
		float TimeSpeed = 1 - m_pfMoveSpeed[smoke];
		//煙の移動計算.
		m_pvPos[smoke].x =	powf(TimeSpeed, 3.0f) * InitPos.x
							+ 3 * powf(TimeSpeed, 2.0f) * m_pfMoveSpeed[smoke] * ControlPosStart.x
							+ 3 * TimeSpeed * powf(m_pfMoveSpeed[smoke], 2.0f) * ControlPosEnd.x
							+ powf(m_pfMoveSpeed[smoke], 3.0f) * TargetPos.x;

		m_pvPos[smoke].y =	powf(TimeSpeed, 3.0f) * InitPos.y
							+ 3 * powf(TimeSpeed, 2.0f) * m_pfMoveSpeed[smoke] * ControlPosStart.y
							+ 3 * TimeSpeed * powf(m_pfMoveSpeed[smoke], 2.0f) * ControlPosEnd.y
							+ powf(m_pfMoveSpeed[smoke], 3.0f) * TargetPos.y;

		m_pvPos[smoke].z = m_vCenterPos.z;

		//大きさ変更処理関数.
		Scaling(smoke);
		//煙の回転処理関数.
		Rotation(smoke);

		if (m_pFadeStartCnt[smoke] >= FADE_WAIT_TIME) {
			//透過値の変更処理関数.
			ChangeAlpha(smoke);
		}
		else {
			m_pFadeStartCnt[smoke]++;
		}
	}
}

//=======================================.
//		大きさ変更処理関数.
//=======================================.
void CFallDownEffect::Scaling(int smoke)
{
	if (m_pfScale[smoke] < SCALE_MAX) {
		m_pfScale[smoke] += SCALE_SPEED;
	}
}

//=======================================.
//		透過値の変更処理関数.
//=======================================.
void CFallDownEffect::ChangeAlpha(int smoke)
{
	if (m_pfAlpha[smoke] > ALPHA_MIN) {
		m_pfAlpha[smoke] -= ALPHA_SPEED;
	}
}

//========================================.
//		煙の回転処理関数.
//========================================.
void CFallDownEffect::Rotation(int smoke)
{
	//左右の回転方向.
	int Direction = LEFT_DIRECTION;
	if (smoke >= SMOKE_MAX / 2) {
		Direction = RIGHT_DIRECTION;
	}
	m_pvRot[smoke].z += Direction * ROTATION_SPEED;

	if (fabs(m_pvRot[smoke].z) > ROTATION_MAX) {
		m_pvRot[smoke].z = ROTATION_MIN;
	}
}