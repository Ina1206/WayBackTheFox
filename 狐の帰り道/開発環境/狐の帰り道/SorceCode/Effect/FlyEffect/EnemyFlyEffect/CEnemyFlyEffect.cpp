#include "CEnemyFlyEffect.h"

CEnemyFlyEffect::CEnemyFlyEffect()
{
	//�����������֐�.
	Init();
}

CEnemyFlyEffect::~CEnemyFlyEffect()
{
	//��������֐�.
	Release();
}

//=======================================.
//		�X�V�����֐�.
//=======================================.
void CEnemyFlyEffect::UpDate()
{
	//���̕\�������֐�.
	SmokeDisp();
	//���̉�]�����֐�.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		Ratation(smoke, false);
	}
}

//=======================================.
//		�`�揈���֐�.
//=======================================.
void CEnemyFlyEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//�N���X�A�h���X�擾.
		m_ppCSprite[smoke] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Smoke);
		//�ʒu.
		m_ppCSprite[smoke]->SetPosition(m_pvPos[smoke]);
		//�p�x.
		m_ppCSprite[smoke]->SetRotation(m_pvRot[smoke]);
		//�傫��.
		m_ppCSprite[smoke]->SetScale(D3DXVECTOR3(m_pfScale[smoke], m_pfScale[smoke], m_pfScale[smoke]));
		//���ߒl.
		m_ppCSprite[smoke]->SetAlpha(m_pfAlpha[smoke]);
		//�`��
		CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCSprite[smoke]->Render(mView, mProj, vCamePos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//=======================================.
//		�����������֐�.
//=======================================.
void CEnemyFlyEffect::Init()
{
	//�z��̓��I�m��.
	m_pvPos				= new D3DXVECTOR3[SMOKE_MAX]();	//���W.
	m_pvRot				= new D3DXVECTOR3[SMOKE_MAX]();	//�p�x.
	m_pfScale			= new float[SMOKE_MAX]();		//�傫��.
	m_ppCSprite			= new CSprite*[SMOKE_MAX]();	//�X�v���C�g�N���X.
	m_pfAlpha			= new float[SMOKE_MAX]();		//���ߒl.
	m_pbSmokeDispFlag	= new bool[SMOKE_MAX]();		//�����o��t���O.
	
	//����������.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu.
		m_pvRot[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x.
		m_pfScale[smoke]			= 0.0f;								//�傫��.
		m_ppCSprite[smoke]			= nullptr;							//�X�v���C�g�N���X.
		m_pfAlpha[smoke]			= ALPHA_MAX;						//���ߒl.
		m_pbSmokeDispFlag[smoke]	= false;							//�����o��t���O.
	}

	m_SmokeMax				= SMOKE_MAX;		//���̍ő吔.
	m_fStartPos_x			= START_POSITION_X;	//���[�̈ʒu.
	m_Row_Max				= ROW_MAX;			//���̗�̍ő吔.s
	m_fInterval_Width		= INTERVAL_WIDTH;	//���̊Ԋu.
	m_fFoot_Differencial	= FOOT_DIFFERENCIAL;//���S���瑫���̍�.
	m_fMax_Scale			= MAX_SCALE;		//�傫���̍ő吔.

}

//=======================================.
//		��������֐�.
//=======================================.
void CEnemyFlyEffect::Release()
{
	for (int sprite = SMOKE_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}

	//���.
	SAFE_DELETE_ARRAY(m_pbSmokeDispFlag);	//�����o��t���O.
	SAFE_DELETE_ARRAY(m_pfAlpha);			//���ߒl.
	SAFE_DELETE_ARRAY(m_ppCSprite);			//�X�v���C�g�N���X.
	SAFE_DELETE_ARRAY(m_pfScale);			//�傫��.
	SAFE_DELETE_ARRAY(m_pvRot);				//�p�x.
	SAFE_DELETE_ARRAY(m_pvPos);				//���W.
}

