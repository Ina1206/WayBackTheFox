#include "CHorizonMoveEffect.h"

/****************************************
*		横移動時のエフェクトクラス.
******/
CHorizonMoveEffect::CHorizonMoveEffect()
	: m_pfAlpha				(nullptr)
	, m_pbPerson_DispFlag	(nullptr)
	, m_vOldCenterPos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_PopCnt				(0)
	, m_fRotation_Distance	(0.0f)
{
	//初期化処理関数.
	Init();
}

CHorizonMoveEffect::~CHorizonMoveEffect()
{
	//解放処理関数.
	Release();
}

//======================================.
//		更新処理関数.
//======================================.
void CHorizonMoveEffect::Update()
{
	if (m_vCenterPos.x != m_vOldCenterPos.x) {
		m_PopCnt++;
		if (m_PopCnt >= POP_TIME) {
			//表示処理関数.
			Disp();
		}
	}

	//移動処理関数.
	Move();


	m_vOldCenterPos = m_vCenterPos;
	//高さと奥行は固定.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke].z = m_vCenterPos.z;
		m_pvPos[smoke].y = DISP_HEIGHT;
	}

}

//======================================.
//		描画処理関数.
//======================================.
void CHorizonMoveEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
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

		if (m_pbPerson_DispFlag[smoke] == true) {
			//描画.
			CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
			m_pCDepthStencil->SetDepth(false);
			m_ppCSprite[smoke]->Render(mView, mProj, vCamePos);
			m_pCDepthStencil->SetDepth(true);
		}
	}
}

//=======================================.
//		初期化処理関数.
//=======================================.
void CHorizonMoveEffect::Init()
{
	//配列動的確保.
	m_pvPos				= new D3DXVECTOR3[SMOKE_MAX]();	//位置.
	m_pvRot				= new D3DXVECTOR3[SMOKE_MAX]();	//角度.
	m_pfScale			= new float[SMOKE_MAX]();		//大きさ.
	m_ppCSprite			= new CSprite*[SMOKE_MAX]();	//スプライトクラス.
	m_pfAlpha			= new float[SMOKE_MAX]();		//透過値.
	m_pbPerson_DispFlag = new bool[SMOKE_MAX]();		//個人の表示フラグ.

	//初期化処理.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置.
		m_pvRot[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//角度.
		m_pfScale[smoke]			= SCALE_MAX;						//大きさ.
		m_ppCSprite[smoke]			= nullptr;							//スプライトクラス.
		m_pfAlpha[smoke]			= ALPHA_MAX;						//透過値.
		m_pbPerson_DispFlag[smoke]	= false;							//個人の表示フラグ.
	}
}

//========================================.
//		解放処理関数.
//========================================.
void CHorizonMoveEffect::Release()
{
	//解放.
	SAFE_DELETE_ARRAY(m_pbPerson_DispFlag);	//個人の表示フラグ.
	SAFE_DELETE_ARRAY(m_pfAlpha);			//透過値.
	SAFE_DELETE_ARRAY(m_ppCSprite);			//スプライトクラス.
	SAFE_DELETE_ARRAY(m_pfScale);			//大きさ.
	SAFE_DELETE_ARRAY(m_pvRot);				//角度.
	SAFE_DELETE_ARRAY(m_pvPos);				//位置.
}

//===========================================.
//		表示処理関数.
//===========================================.
void CHorizonMoveEffect::Disp()
{
	//横移動しているとき.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//表示.
		if (m_pbPerson_DispFlag[smoke] == false) {
			m_pvPos[smoke] = m_vCenterPos;
			m_pbPerson_DispFlag[smoke] = true;
			m_PopCnt = 0;

			if (smoke == 0) {
				m_fRotation_Distance = 0.0f;
			}

			break;
		}
	}
}

//============================================.
//		移動処理関数.
//============================================.
void CHorizonMoveEffect::Move()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		if (m_pbPerson_DispFlag[smoke] == true) {
			if (m_fRotation_Distance == 0.0f) {
				//差分を整数に変換.
				m_fRotation_Distance = m_vCenterPos.x - (m_vOldCenterPos.x * INTEFER_CHANGE);
			}
			else {
				//方向を出して回転する.
				m_fRotation_Distance = fabsf(m_fRotation_Distance) / m_fRotation_Distance;
				m_pvRot[smoke].z += ROTATION_SPEED * m_fRotation_Distance;
				//拡大と透過処理関数.
				Scaling_Transparent(smoke);
			}
		}
	}
}

//============================================.
//		拡大と透過処理関数.
//============================================.
void CHorizonMoveEffect::Scaling_Transparent(int smoke) 
{
	//縮小処理.
	m_pfScale[smoke] -= SCALING_SPEED;
	if (m_pfScale[smoke] < SCALE_MIN) {
		m_pfScale[smoke] = SCALE_MIN;
	}

	//透過処理.
	m_pfAlpha[smoke] -= ALPHA_SPEED;
	if (m_pfAlpha[smoke] < ALPHA_MIN) {
		m_pfAlpha[smoke] = ALPHA_MAX;
		m_pfScale[smoke] = SCALE_MAX;
		//表示終了.
		m_pbPerson_DispFlag[smoke] = false;
	}
}