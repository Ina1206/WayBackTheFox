#include "CPunchEffect.h"

/**********************************************
*		パンチエフェクトクラス.
*****/
CPunchEffect::CPunchEffect()
	: m_StartNum	(0)
	, m_pbDispFlag	(nullptr)
	, m_EndStarNum	(0)
{
	//初期化処理関数.
	Init();
}

CPunchEffect::~CPunchEffect()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CPunchEffect::Update()
{

	if (m_bDispFlag != m_bOldDispFlag) {
		
		//表示する星を取得.
		m_StartNum++;
		if (m_StartNum >= DISP_STAR) {
			m_StartNum = 0;
		}

		m_EndStarNum = SPARKLE_MAX - m_StartNum;
		if (m_pbDispFlag[m_StartNum] == false) {
			m_pfScale[m_StartNum] = 0.0f;
			InitPos(m_StartNum);
		}

	}

	//縮小処理.
	if (m_pbDispFlag[m_StartNum] == true) {
		if (m_pfScale[m_StartNum] < SCALE_MAX) {
			m_pfScale[m_StartNum] += SCALING_SPEED;
		}
		else {
			//表示終了.
			m_pbDispFlag[m_StartNum] = false;
		}
	}
	else {
		m_bDispFlag = false;
	}
	m_bOldDispFlag = m_bDispFlag;
}

//========================================.
//		描画処理関数.
//========================================.
void CPunchEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	//スプライトクラスアドレス取得.
	int spriteNo = static_cast<int>(CResourceSprite::enSprite::Sparkle) + (m_StartNum % USE_SPARKLE_MAX);
	if (m_StartNum % USE_SPARKLE_MAX > 1) {
		spriteNo = static_cast<int>(CResourceSprite::enSprite::Sparkle);
	}
	m_ppCSprite[m_StartNum] = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(spriteNo));
	//位置.
	m_ppCSprite[m_StartNum]->SetPosition(m_pvPos[m_StartNum]);
	//大きさ.
	m_ppCSprite[m_StartNum]->SetScale(D3DXVECTOR3(m_pfScale[m_StartNum], m_pfScale[m_StartNum], m_pfScale[m_StartNum]));
	//描画.
	CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepth_Stencil->SetDepth(false);
	m_ppCSprite[m_StartNum]->Render(mView, mProj, vCamePos);
	m_pCDepth_Stencil->SetDepth(true);
		
	
}

//========================================.
//		初期化処理関数.
//========================================.
void CPunchEffect::Init()
{
	//配列動的確保.
	m_pvPos			= new D3DXVECTOR3[SPARKLE_MAX]();
	m_pvRot			= new D3DXVECTOR3[SPARKLE_MAX]();
	m_pfScale		= new float[SPARKLE_MAX]();
	m_ppCSprite		= new CSprite*[SPARKLE_MAX]();
	m_pbDispFlag	= new bool[SPARKLE_MAX]();

	//初期化.
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		m_pvPos[sparkle]		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pvRot[sparkle]		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pfScale[sparkle]		= 0.0f;
		m_ppCSprite[sparkle]	= nullptr;
		m_pbDispFlag[sparkle]	= false;
	}

}

//=========================================.
//		解放処理関数.
//=========================================.
void CPunchEffect::Release()
{
	//解放.
	SAFE_DELETE_ARRAY(m_pbDispFlag);
	SAFE_DELETE_ARRAY(m_ppCSprite);
	SAFE_DELETE_ARRAY(m_pfScale);
	SAFE_DELETE_ARRAY(m_pvRot);
	SAFE_DELETE_ARRAY(m_pvPos);
}

//=========================================.
//		初期位置設定処理関数.
//=========================================.
void CPunchEffect::InitPos(int sparkle)
{
	//初期位置.
	m_pvPos[sparkle].x = (m_vCenterPos.x - CENTER_ADJUST_X) - (START_POS.x - ((sparkle % 2) * INTERVAL_WIDTH));
	m_pvPos[sparkle].y = m_vCenterPos.y + START_POS.y;
	m_pvPos[sparkle].z = m_vCenterPos.z;
	//表示開始.
	m_pbDispFlag[sparkle] = true;
}