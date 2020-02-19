#include "CHorizonMoveEffect.h"

/****************************************
*		���ړ����̃G�t�F�N�g�N���X.
******/
CHorizonMoveEffect::CHorizonMoveEffect()
	: m_pfAlpha				(nullptr)
	, m_pbPerson_DispFlag	(nullptr)
	, m_vOldCenterPos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_PopCnt				(0)
	, m_fRotation_Distance	(0.0f)
{
	//�����������֐�.
	Init();
}

CHorizonMoveEffect::~CHorizonMoveEffect()
{
	//��������֐�.
	Release();
}

//======================================.
//		�X�V�����֐�.
//======================================.
void CHorizonMoveEffect::Update()
{
	if (m_vCenterPos.x != m_vOldCenterPos.x) {
		m_PopCnt++;
		if (m_PopCnt >= POP_TIME) {
			//�\�������֐�.
			Disp();
		}
	}

	//�ړ������֐�.
	Move();


	m_vOldCenterPos = m_vCenterPos;
	//�����Ɖ��s�͌Œ�.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke].z = m_vCenterPos.z;
		m_pvPos[smoke].y = DISP_HEIGHT;
	}

}

//======================================.
//		�`�揈���֐�.
//======================================.
void CHorizonMoveEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
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

		if (m_pbPerson_DispFlag[smoke] == true) {
			//�`��.
			CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
			m_pCDepthStencil->SetDepth(false);
			m_ppCSprite[smoke]->Render(mView, mProj, vCamePos);
			m_pCDepthStencil->SetDepth(true);
		}
	}
}

//=======================================.
//		�����������֐�.
//=======================================.
void CHorizonMoveEffect::Init()
{
	//�z�񓮓I�m��.
	m_pvPos				= new D3DXVECTOR3[SMOKE_MAX]();	//�ʒu.
	m_pvRot				= new D3DXVECTOR3[SMOKE_MAX]();	//�p�x.
	m_pfScale			= new float[SMOKE_MAX]();		//�傫��.
	m_ppCSprite			= new CSprite*[SMOKE_MAX]();	//�X�v���C�g�N���X.
	m_pfAlpha			= new float[SMOKE_MAX]();		//���ߒl.
	m_pbPerson_DispFlag = new bool[SMOKE_MAX]();		//�l�̕\���t���O.

	//����������.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu.
		m_pvRot[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x.
		m_pfScale[smoke]			= SCALE_MAX;						//�傫��.
		m_ppCSprite[smoke]			= nullptr;							//�X�v���C�g�N���X.
		m_pfAlpha[smoke]			= ALPHA_MAX;						//���ߒl.
		m_pbPerson_DispFlag[smoke]	= false;							//�l�̕\���t���O.
	}
}

//========================================.
//		��������֐�.
//========================================.
void CHorizonMoveEffect::Release()
{
	//���.
	SAFE_DELETE_ARRAY(m_pbPerson_DispFlag);	//�l�̕\���t���O.
	SAFE_DELETE_ARRAY(m_pfAlpha);			//���ߒl.
	SAFE_DELETE_ARRAY(m_ppCSprite);			//�X�v���C�g�N���X.
	SAFE_DELETE_ARRAY(m_pfScale);			//�傫��.
	SAFE_DELETE_ARRAY(m_pvRot);				//�p�x.
	SAFE_DELETE_ARRAY(m_pvPos);				//�ʒu.
}

//===========================================.
//		�\�������֐�.
//===========================================.
void CHorizonMoveEffect::Disp()
{
	//���ړ����Ă���Ƃ�.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//�\��.
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
//		�ړ������֐�.
//============================================.
void CHorizonMoveEffect::Move()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		if (m_pbPerson_DispFlag[smoke] == true) {
			if (m_fRotation_Distance == 0.0f) {
				//�����𐮐��ɕϊ�.
				m_fRotation_Distance = m_vCenterPos.x - (m_vOldCenterPos.x * INTEFER_CHANGE);
			}
			else {
				//�������o���ĉ�]����.
				m_fRotation_Distance = fabsf(m_fRotation_Distance) / m_fRotation_Distance;
				m_pvRot[smoke].z += ROTATION_SPEED * m_fRotation_Distance;
				//�g��Ɠ��ߏ����֐�.
				Scaling_Transparent(smoke);
			}
		}
	}
}

//============================================.
//		�g��Ɠ��ߏ����֐�.
//============================================.
void CHorizonMoveEffect::Scaling_Transparent(int smoke) 
{
	//�k������.
	m_pfScale[smoke] -= SCALING_SPEED;
	if (m_pfScale[smoke] < SCALE_MIN) {
		m_pfScale[smoke] = SCALE_MIN;
	}

	//���ߏ���.
	m_pfAlpha[smoke] -= ALPHA_SPEED;
	if (m_pfAlpha[smoke] < ALPHA_MIN) {
		m_pfAlpha[smoke] = ALPHA_MAX;
		m_pfScale[smoke] = SCALE_MAX;
		//�\���I��.
		m_pbPerson_DispFlag[smoke] = false;
	}
}