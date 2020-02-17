#include "CStepEffect.h"

CStepEffect::CStepEffect()
{
	//�����������֐�.
	Init();
}

CStepEffect::~CStepEffect()
{
	//��������֐�.
	Release();
}

//===========================================.
//		�`�揈���֐�.
//===========================================.
void CStepEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		//�X�v���C�g�N���X�A�h���X�擾.
		int spriteNo = static_cast<int>(CResourceSprite::enSprite::Sparkle) + (sparkle % USE_SPARKLE_MAX);
		if (sparkle % USE_SPARKLE_MAX > 1) {
			spriteNo = static_cast<int>(CResourceSprite::enSprite::Sparkle);
		}
		m_ppCSprite[sparkle] = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(spriteNo));
		//�ʒu.
		m_ppCSprite[sparkle]->SetPosition(m_pvPos[sparkle]);
		//�傫��.
		m_ppCSprite[sparkle]->SetScale(D3DXVECTOR3(m_pfScale[sparkle], m_pfScale[sparkle], m_pfScale[sparkle]));
		//�`��.
		CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCSprite[sparkle]->Render(mView, mProj, vCamePos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//===========================================.
//		�����������֐�.
//===========================================.
void CStepEffect::Init()
{
	//�z�񓮓I�m��.
	m_pvPos				= new D3DXVECTOR3[SPARKLE_MAX]();	//�ʒu.
	m_pvRot				= new D3DXVECTOR3[SPARKLE_MAX]();	//�p�x.
	m_pfScale			= new float[SPARKLE_MAX]();			//�傫��.
	m_ppCSprite			= new CSprite*[SPARKLE_MAX]();		//�X�v���C�g�N���X.
	m_penScalingType	= new enScalingType[SPARKLE_MAX]();	//�g�k�����̃^�C�v.

	//������.
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		m_pvPos[sparkle]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu.
		m_pvRot[sparkle]			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x.
		m_pfScale[sparkle]			= 0.5f;								//�傫��.
		m_ppCSprite[sparkle]		= nullptr;							//�X�v���C�g�N���X.
		m_penScalingType[sparkle]	= enScalingType::Large;				//�g�k�����̃^�C�v.
	}

	//�l�ݒ�.
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
//		��������֐�.
//===========================================.
void CStepEffect::Release()
{
	//�������.
	SAFE_DELETE_ARRAY(m_penScalingType);
	SAFE_DELETE_ARRAY(m_ppCSprite);
	SAFE_DELETE_ARRAY(m_pfScale);
	SAFE_DELETE_ARRAY(m_pvRot);
	SAFE_DELETE_ARRAY(m_pvPos);
}

