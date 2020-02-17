#include "CGreatEffect.h"

CGreatEffect::CGreatEffect()
{
	//�����������֐�.
	Init();
}

CGreatEffect::~CGreatEffect()
{
	//��������֐�.
	Release();
}

//===========================================.
//		�`�揈���֐�.
//===========================================.
void CGreatEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		//�X�v���C�g�N���X�A�h���X�擾.
		//3��ނ̃L���L�����擾.
		int spriteNo = static_cast<int>(CResourceSprite::enSprite::Punch) + (sparkle % USE_SPARKLE_MAX);

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
void CGreatEffect::Init()
{
	//���I�m��.
	m_pvPos				= new D3DXVECTOR3[SPARKLE_MAX]();	//�ʒu.
	m_pvRot				= new D3DXVECTOR3[SPARKLE_MAX]();	//�p�x.
	m_ppCSprite			= new CSprite*[SPARKLE_MAX]();		//�X�v���C�g�N���X.
	m_pfScale			= new float[SPARKLE_MAX]();			//�傫��.
	m_penScalingType	= new enScalingType[SPARKLE_MAX]();//�g�k�����^�C�v.

	//�l�ݒ�.
	m_Sparkle_max			= SPARKLE_MAX;			//�L���L���̍ő吔.
	m_fCenterDifferencial	= CENTER_DIFFERENCIAL;	//��������̍����̍�.
	m_RowMax				= ROW_MAX;				//����̃L���L���̍ő吔.
	m_fHeight_Width			= HEIGHT_WIDTH;			//�����̕�.
	m_fLeftInterval			= LEFT_INTERVAL;		//�����̊Ԋu.
	m_fRightInterval		= RIGHT_INTERVAL;		//�E���̊Ԋu.
	m_fLeftMost				= LEFTMOST;				//���[.
	m_fRightMost			= RIGHTMOST;			//�E�[.
	m_fScaleMax				= SCALE_MAX;			//�傫��.
}

//===========================================.
//		��������֐�.
//===========================================.
void CGreatEffect::Release()
{
	//������.
	for (int sprite = SPARKLE_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}

	//���.
	SAFE_DELETE_ARRAY(m_penScalingType);//�g�k�����^�C�v.
	SAFE_DELETE_ARRAY(m_pfScale);		//�傫��.
	SAFE_DELETE_ARRAY(m_ppCSprite);		//�X�v���C�g�N���X.
	SAFE_DELETE_ARRAY(m_pvRot);			//�p�x.
	SAFE_DELETE_ARRAY(m_pvPos);			//�ʒu.
}

