#include "CHitEffect.h"

CHitEffect::CHitEffect()
	: m_fMoving_Distance	(0.0f)
	, m_enMoveType			(enMoveType::Right)
	, m_vInitPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//作成されてすぐに初期化処理.
	Init();
}

CHitEffect::~CHitEffect()
{
	//解放処理関数.
	Release();
}

//========================================.
//		更新処理関数.
//========================================.
void CHitEffect::UpDate()
{
	//表示しているとき.
	if (m_bDispFlag == true) {
		for (int sprite = 0; sprite < DISP_EFFECT_MAX; sprite++) {
			//表示初めに基準位置に準備.
			if (m_bDispFlag != m_bOldDispFlag) {
				//位置.
				m_pvPos[sprite] = D3DXVECTOR3(m_vCenterPos.x + (BASIC_BLANK_WIDTH * sprite), m_vCenterPos.y + ADD_HIGHT, m_vCenterPos.z);
				m_pvPos[sprite].x -= BASIC_DIFFERENCIAL;

				//角度.
				m_pvRot[sprite].y = START_ROTAITON - (START_ROTAITON * sprite);

				m_vInitPos = m_pvPos[sprite];
			}
			else {
				//移動処理関数.
				Move(sprite);
			}
		}
	}

	//フラグ.
	m_bOldDispFlag = m_bDispFlag;
}

//========================================.
//		描画処理関数.
//========================================.
void CHitEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	if (m_bDispFlag == true) {
		//全部一気に設定しないと描画されない.
		for (int sprite = 0; sprite < DISP_EFFECT_MAX; sprite++) {
			//スプライトクラスのアドレス.
			m_ppCSprite[sprite] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Hit);
			//角度.
			m_ppCSprite[sprite]->SetRotation(m_pvRot[sprite]);
			//座標.
			m_ppCSprite[sprite]->SetPosition(m_pvPos[sprite]);
			//大きさ.
			m_ppCSprite[sprite]->SetScale(D3DXVECTOR3(m_pfScale[sprite], m_pfScale[sprite], m_pfScale[sprite]));
			//描画.
			CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
			m_pCDepth_Stencil->SetDepth(false);
			m_ppCSprite[sprite]->Render(mView, mProj, vCamePos);
			m_pCDepth_Stencil->SetDepth(true);

		}
	}
}

//=========================================.
//		初期化処理関数.
//=========================================.
void CHitEffect::Init()
{
	//動的確保.
	m_pvPos		= new D3DXVECTOR3[DISP_EFFECT_MAX]();	//座標.
	m_pvRot		= new D3DXVECTOR3[DISP_EFFECT_MAX]();	//角度.
	m_pfScale	= new float[DISP_EFFECT_MAX]();			//大きさ.
	m_ppCSprite = new CSprite*[DISP_EFFECT_MAX]();		//スプライトクラス.

	//値の初期化.
	for (int sprite = 0; sprite < DISP_EFFECT_MAX; sprite++) {
		m_pvPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pvRot[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pfScale[sprite] = BASE_SCALE;
	}
}

//=========================================.
//		解放処理関数.
//=========================================.
void CHitEffect::Release()
{
	for (int sprite = DISP_EFFECT_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}
	SAFE_DELETE_ARRAY(m_ppCSprite);	//スプライトクラス.
	SAFE_DELETE_ARRAY(m_pfScale);	//大きさ.
	SAFE_DELETE_ARRAY(m_pvRot);		//角度.
	SAFE_DELETE_ARRAY(m_pvPos);		//座標.
}

//=========================================.
//		移動処理関数
//=========================================.
void CHitEffect::Move(int sprite)
{
	//方向計算.
	const int LEFT_DIRECTION = -1;	//左に向きの方向.
	int Direction = (sprite * 2) + LEFT_DIRECTION;
	//移動.
	switch (m_enMoveType) {
	//右に移動.
	case enMoveType::Right:
		//移動.
		m_pvPos[sprite].x	+= Direction * MOVING_SPEED;
		m_fMoving_Distance	+= MOVING_SPEED;
		//左に戻る.
		if (m_pvPos[sprite].x > MOVING_DISTANCE_MAX + m_vInitPos.x) {
			m_enMoveType = enMoveType::Left;
		}
		break;
	//左に移動.
	case enMoveType::Left:
		//移動.
		m_pvPos[sprite].x	-= Direction * MOVING_SPEED;
		m_fMoving_Distance	-= MOVING_SPEED;
		//表示終了.
		if (m_pvPos[1].x < m_vInitPos.x) {
			m_enMoveType = enMoveType::Right;
			m_bDispFlag = false;
		}
		break;
	}
}

//===================================.
//		大きさ変更処理関数.
//===================================.
void CHitEffect::SetEffectScale(float scale)
{
	for (int effect = 0; effect < DISP_EFFECT_MAX; effect++) {
		m_pfScale[effect] = scale;
	}
}