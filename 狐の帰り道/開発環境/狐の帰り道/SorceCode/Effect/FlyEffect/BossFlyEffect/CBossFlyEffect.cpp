#include "CBossFlyEffect.h"

/****************************************
*		�{�X����Ԏ��̃G�t�F�N�g.
****/
CBossFlyEffect::CBossFlyEffect()
	: m_pfMoveSpeed			(nullptr)
	, m_pbIndiviDispFlag	(nullptr)
	, m_bMoveFlag			(true)
	, m_bCheckFlag			(false)
{
	//�����������֐�.
	Init();
}

CBossFlyEffect::~CBossFlyEffect()
{
	//��������֐�.
	Release();
}

//=============================================.
//		�X�V�����֐�.
//=============================================.
void CBossFlyEffect::Update()
{
	//�\�����菈���֐�.
	Disp();
	//�ړ������֐�.
	Move();
	//�X�P�[���̕ύX�����֐�.
	Scaling();
	//���ߏ����֐�.
	TransparetProcess();
	//��]�����֐�.
	Rotation();
}

//=============================================.
//		�`�揈���֐�.
//=============================================.
void CBossFlyEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		if (m_pbIndiviDispFlag[smoke] == true) {
			//�N���X�A�h���X�擾.
			m_ppCSprite[smoke] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Smoke);
			//�J�����̌����ɍ��킹�Ȃ�.
			m_ppCSprite[smoke]->SetCancelRotationFlag(false);
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
}

//=============================================.
//		�����������֐�.
//=============================================.
void CBossFlyEffect::Init()
{
	//�z�񓮓I�m��.
	m_pvPos				= new D3DXVECTOR3[SMOKE_MAX]();	//���W.
	m_pvRot				= new D3DXVECTOR3[SMOKE_MAX]();	//�p�x.
	m_pfScale			= new float[SMOKE_MAX]();		//�傫��.
	m_ppCSprite			= new CSprite*[SMOKE_MAX]();	//�X�v���C�g�N���X.
	m_pfAlpha			= new float[SMOKE_MAX]();		//���ߒl.
	m_pbSmokeDispFlag	= new bool[SMOKE_MAX]();		//�����o��t���O.
	m_pfMoveSpeed		= new float[SMOKE_MAX]();		//�ړ����x.
	m_pbIndiviDispFlag	= new bool[SMOKE_MAX]();		//�ʕ\���t���O.

	//����������.
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pvPos[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�ʒu.
		m_pvRot[smoke]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);						//�p�x.
		m_pfScale[smoke]			= SCALE_SIZE_MIN * fabsf(SMOKE_QUATER - (smoke / 2));	//�傫��.
		m_ppCSprite[smoke]			= nullptr;												//�X�v���C�g�N���X.
		m_pfAlpha[smoke]			= ALPHA_MAX;											//���ߒl.
		m_pbSmokeDispFlag[smoke]	= false;												//�����o��t���O.
		m_pfMoveSpeed[smoke]		= POS_UP_SPEED;											//�ړ����x
		m_pbIndiviDispFlag[smoke]	= false;												//�ʕ\���t���O.
	}

	m_SmokeMax				= SMOKE_MAX;		//���̍ő吔.
	m_fStartPos_x			= START_POSITION_X;	//���[�̈ʒu.
	m_fInterval_Width		= INTERVAL_WIDTH;	//���̊Ԋu.
}

//=============================================.
//		��������֐�.
//=============================================.
void CBossFlyEffect::Release()
{
	for (int sprite = SMOKE_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}

	//���.
	SAFE_DELETE_ARRAY(m_pbIndiviDispFlag);	//�ʕ\���t���O.
	SAFE_DELETE_ARRAY(m_pfMoveSpeed);		//�ړ����x.
	SAFE_DELETE_ARRAY(m_pbSmokeDispFlag);	//�����o��t���O.
	SAFE_DELETE_ARRAY(m_pfAlpha);			//���ߒl.
	SAFE_DELETE_ARRAY(m_ppCSprite);			//�X�v���C�g�N���X.
	SAFE_DELETE_ARRAY(m_pfScale);			//�傫��.
	SAFE_DELETE_ARRAY(m_pvRot);				//�p�x.
	SAFE_DELETE_ARRAY(m_pvPos);				//���W.

}

//==============================================.
//		�\�����菈���֐�.
//==============================================.
void CBossFlyEffect::Disp()
{
	if (m_bCheckFlag == false) {
		for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
			int m_Smoke_HorizonNum = smoke / 2;	//���̉���̔ԍ�.
			int m_Smoke_VerticalNum = smoke % 2;//���̏c��̔ԍ�.
			m_pvPos[smoke] = m_vCenterPos;
			m_pvPos[smoke].x += m_fStartPos_x + (m_Smoke_HorizonNum * INTERVAL_WIDTH);
			m_pvPos[smoke].y -= FOOT_DIFFERENCIAL - (m_Smoke_VerticalNum * INTERVAL_HEIGHT);
			m_pbIndiviDispFlag[smoke] = true;
		}
		m_bCheckFlag = true;
	}
}

//==============================================.
//		�ړ������֐�.
//==============================================.
void CBossFlyEffect::Move()
{
	if (m_bMoveFlag == true) {
		for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
			//���̈ړ�.
			m_pvPos[smoke].y += m_pfMoveSpeed[smoke];
			m_pfMoveSpeed[smoke] += (SPEED_UP * fabsf(SMOKE_QUATER - (smoke / 2)));

			if (m_pvPos[smoke].y >= MOVE_UPPER_LIMIT) {
				//�ړ��I��.
				m_bMoveFlag = false;
			}
		}
	}
}

//==============================================.
//		�X�P�[�������֐�.
//==============================================.
void CBossFlyEffect::Scaling()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pfScale[smoke] += SCALE_UP_SPEED;
	}
}

//=============================================.
//		���ߏ����֐�.
//=============================================.
void CBossFlyEffect::TransparetProcess()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		m_pfAlpha[smoke] -= STANDERD_TRAN_SPEED + (TRANS_EXTRA_SPEED * fabsf(SMOKE_QUATER - (smoke / 2)));
		if (m_pfAlpha[smoke] <= 0.0f) {
			m_pbIndiviDispFlag[smoke] = false;
		}
	}
}

//=============================================.
//		��]�����֐�.
//=============================================.
void CBossFlyEffect::Rotation()
{
	for (int smoke = 0; smoke < SMOKE_MAX; smoke++) {
		//�������񂾎��̏c�̔ԍ�.
		const int m_fVerticalNum	= smoke / 2;
		//���[���璆���܂ł���ɂ����ԍ�.
		const float m_fSmokeNum	= SMOKE_QUATER - m_fVerticalNum;
		//��]����������Ȃ��ꍇ�͍���].
		float m_fRotationDirection = RIGHT_ROTATION_NUM;
		if (m_fSmokeNum != 0) {
			//��]�������(��������).
			m_fRotationDirection =  (fabsf(m_fSmokeNum)/ m_fSmokeNum) * RIGHT_ROTATION_NUM;
		}

		m_pvRot[smoke].z += m_fRotationDirection * ROTATION_SPEED;
		if (fabsf(m_pvRot[smoke].z) > ROTATION_MAX) {
			m_pvRot[smoke].z = 0.0f;
		}
	}
}