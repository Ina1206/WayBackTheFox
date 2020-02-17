#include "CGoodEffect.h"

CGoodEffect::CGoodEffect()
{
	//�����������֐�.
	Init();
}

CGoodEffect::~CGoodEffect()
{
	//��������֐�.
	Release();
}

//===========================================.
//		�`�揈���֐�.
//===========================================.
void CGoodEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int sprite = 0; sprite < SPARKLE_MAX; sprite++) {
		//�X�v���C�g�N���X�̃A�h���X�擾.
		m_ppCSprite[sprite] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Sparkle);
		//�ʒu���W.
		m_ppCSprite[sprite]->SetPosition(m_pvPos[sprite]);
		//�X�P�[��.
		m_ppCSprite[sprite]->SetScale(D3DXVECTOR3(m_pfScale[sprite], m_pfScale[sprite], m_pfScale[sprite]));
		//�`��.
		CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCSprite[sprite]->Render(mView, mProj, vCamePos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//===========================================.
//		�����������֐�.
//===========================================.
void CGoodEffect::Init()
{
	//���I�m��.
	m_pvPos				= new D3DXVECTOR3[SPARKLE_MAX]();	//���W.
	m_pvRot				= new D3DXVECTOR3[SPARKLE_MAX]();	//�p�x.
	m_ppCSprite			= new CSprite*[SPARKLE_MAX]();		//�X�v���C�g�N���X.
	m_pfScale			= new float[SPARKLE_MAX]();			//�傫��.
	m_penScalingType	= new enScalingType[SPARKLE_MAX]();	//�g�k�̏����̃^�C�v.

	m_Sparkle_max			= SPARKLE_MAX;			//�L���L���̍ő吔.
	m_fCenterDifferencial	= CENTER_DIFFECENCIAL;	//��������n�߂鍂���̍���.
	m_RowMax				= ROW_MAX;				//����̃L���L���̍ő吔.
	m_fHeight_Width			= HEIGHT_WIDHT;			//�����̕�.
	m_fLeftInterval			= LEFT_INTERVAL;		//�����̊Ԋu.
	m_fRightInterval		= RIGHT_INTERVAL;		//�E���̊Ԋu.
	m_fLeftMost				= LEFT_MOST;			//���[.
	m_fRightMost			= RIGHT_MOST;			//�E�[.
	m_fScaleMax				= SCALE_MAX;			//�傫��.
}

//===========================================.
//		��������֐�.
//===========================================.
void CGoodEffect::Release()
{
	for (int sprite = SPARKLE_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}

	//��������֐�.
	SAFE_DELETE_ARRAY(m_penScalingType);	//�g�k�̏����̃^�C�v.
	SAFE_DELETE_ARRAY(m_pfScale);			//�傫��.
	SAFE_DELETE_ARRAY(m_ppCSprite);			//�X�v���C�g�N���X.
	SAFE_DELETE_ARRAY(m_pvRot);				//�p�x.
	SAFE_DELETE_ARRAY(m_pvPos);				//���W.
}