#include "CLandingEffect.h"

/*************************************
*		���n�G�t�F�N�g�N���X.
***************/
CLandingEffect::CLandingEffect()
	: m_pfAlpha	(nullptr)
{
	//�����������֐�.
	Init();
}

CLandingEffect::~CLandingEffect()
{
	//��������֐�.
	Release();
}

//================================.
//		�X�V�����֐�.
//================================.
void CLandingEffect::Update()
{
	if (m_bDispFlag != m_bOldDispFlag) {
		for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
			//�ʒu�ݒ菈���֐�.
			Position_Setting(smoke);
		}
	}

	if (m_bDispFlag == true) {
		//�ړ������֐�.
		Move();
	}
	m_bOldDispFlag = m_bDispFlag;
}

//================================.
//		�`�揈���֐�.
//================================.
void CLandingEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//�A�h���X�擾.
		m_ppCSprite[smoke] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Smoke);
		m_ppCSprite[smoke]->SetCancelRotationFlag(false);
		//�p�x.
		m_ppCSprite[smoke]->SetRotation(m_pvRot[smoke]);
		//�ʒu.
		m_ppCSprite[smoke]->SetPosition(m_pvPos[smoke]);
		//���ߒl.
		m_ppCSprite[smoke]->SetAlpha(m_pfAlpha[smoke]);
		//�傫��.
		m_ppCSprite[smoke]->SetScale(D3DXVECTOR3(m_pfScale[smoke], m_pfScale[smoke], m_pfScale[smoke]));
		//�`��.
		CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepthStencil->SetDepth(false);
		m_ppCSprite[smoke]->Render(mView, mProj, vCamePos);
		m_pCDepthStencil->SetDepth(true);
	}

}

//================================.
//		�����������֐�.
//================================.
void CLandingEffect::Init()
{
	//�z�񓮓I�m��.
	m_pvPos		= new D3DXVECTOR3[SMOKE_MAX]();	//�ʒu.
	m_pvRot		= new D3DXVECTOR3[SMOKE_MAX]();	//�p�x.
	m_pfScale	= new float[SMOKE_MAX]();		//�傫��.
	m_ppCSprite = new CSprite*[SMOKE_MAX]();	//�X�v���C�g�N���X.
	m_pfAlpha	= new float[SMOKE_MAX]();		//���ߒl.

	//����������.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu.
		m_pvRot[smoke]		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x.
		m_pfScale[smoke]	= SCALE_MIN;						//�傫��.
		m_ppCSprite[smoke]	= nullptr;							//�X�v���C�g�N���X.
		m_pfAlpha[smoke]	= ALPHA_MAX;						//���ߒl.
	}
}

//================================.
//		��������֐�.
//================================.
void CLandingEffect::Release()
{
	SAFE_DELETE_ARRAY(m_pfAlpha);	//���ߒl.
	SAFE_DELETE_ARRAY(m_ppCSprite);	//�X�v���C�g�N���X.
	SAFE_DELETE_ARRAY(m_pfScale);	//�傫��.
	SAFE_DELETE_ARRAY(m_pvRot);		//�p�x.
	SAFE_DELETE_ARRAY(m_pvPos);		//�ʒu.
}

//================================.
//		�ʒu�ݒ菈���֐�.
//================================.
void CLandingEffect::Position_Setting(int smoke)
{
	m_pvPos[smoke].x = (m_vCenterPos.x - START_POS) + ((smoke % 2) * INTERVAL_WIDTH);
	m_pvPos[smoke].y = m_vCenterPos.y;
	m_pvPos[smoke].z = m_vCenterPos.z;
}

//================================.
//		�ړ������֐�.
//================================.
void CLandingEffect::Move()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//������.
		const int LeftDirection = -1;
		//�ړ�����(�O���Ɉړ�).
		const int TravelDirection = LeftDirection + ((smoke % 2) * 2);
		//�ړ�����.
		m_pvPos[smoke].x += MOVE_SPEED.x * TravelDirection;
		m_pvPos[smoke].y += MOVE_SPEED.y;

		//��]����.
		m_pvRot[smoke].z += ROTATION_SPEED * TravelDirection;
		if (fabsf(m_pvRot[smoke].z) > ROTATION_MAX) {
			m_pvRot[smoke].z = 0.0f;
		}
		
		//���ߊg�又���֐�.
		Alpha_Scaling(smoke);
	}
}

//================================.
//		���߂Ɗg�又���֐�.
//================================.
void CLandingEffect::Alpha_Scaling(int smoke)
{
	//�g�又��.
	m_pfScale[smoke] += SCALE_SPEED;
	if (m_pfScale[smoke] > SCALE_MAX) {
		m_pfScale[smoke] = SCALE_MAX;
	}

	//���ߏ���.
	m_pfAlpha[smoke] -= TRANS_SPEED;
	if (m_pfAlpha[smoke] < ALPHA_MIN) {
		//������.
		m_pfAlpha[smoke] = ALPHA_MAX;
		m_pfScale[smoke] = SCALE_MIN;
		//�\���I��.
		m_bDispFlag = false;
	}

	
}