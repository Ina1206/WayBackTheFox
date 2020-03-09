#include "CLongPushEffect.h"

/*****************************************
*		���������̃G�t�F�N�g�N���X.
***/
CLongPushEffect::CLongPushEffect()
	: m_PopTime_Cnt			(0)
	, m_pbIndividual_Disp	(nullptr)
{
	//�����������֐�.
	Init();
}

CLongPushEffect::~CLongPushEffect()
{
	//��������֐�.
	Release();
}

//============================.
//		�X�V�����֐�.
//============================.
void CLongPushEffect::Update()
{
	//�\�������֐�.
	Disp();

	//�ړ������֐�.
	Move();
}

//============================.
//		�`�揈���֐�.
//============================.
void CLongPushEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		//�X�v���C�g�N���X�A�h���X�擾.
		//3��ނ̃L���L���̃X�v���C�g���擾.
		int spriteNo = static_cast<int>(CResourceSprite::enSprite::Punch) + (sparkle % USE_SPARKLE_MAX);
		m_ppCSprite[sparkle] = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(spriteNo));
		//�ʒu.
		m_ppCSprite[sparkle]->SetPosition(m_pvPos[sparkle]);
		//�傫��.
		m_ppCSprite[sparkle]->SetScale(D3DXVECTOR3(m_pfScale[sparkle], m_pfScale[sparkle], m_pfScale[sparkle]));
		//�p�x.
		m_ppCSprite[sparkle]->SetRotation(m_pvRot[sparkle]);
		//�`��.
		CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCSprite[sparkle]->Render(mView, mProj, vCamePos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//============================.
//		�����������֐�.
//============================.
void CLongPushEffect::Init()
{
	//�z�񓮓I�m��.
	m_pvPos				= new D3DXVECTOR3[SPARKLE_MAX]();					
	m_pvRot				= new D3DXVECTOR3[SPARKLE_MAX]();					
	m_pfScale			= new float[SPARKLE_MAX]();							
	m_ppCSprite			= new CSprite*[SPARKLE_MAX]();						
	m_pbIndividual_Disp = new bool[SPARKLE_MAX]();							

	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		m_pvPos[sparkle]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu.
		m_pvRot[sparkle]				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�p�x.
		m_pfScale[sparkle]				= SCALE_MAX;						//�傫��.
		m_ppCSprite[sparkle]			= nullptr;							//�X�v���C�g�N���X.
		m_pbIndividual_Disp[sparkle]	= false;							//�ʕ\���t���O.
	}
}

//============================.
//		��������֐�.
//============================.
void CLongPushEffect::Release()
{
	//�z�񓮓I�m��.
	SAFE_DELETE_ARRAY(m_pbIndividual_Disp);
	SAFE_DELETE_ARRAY(m_ppCSprite);
	SAFE_DELETE_ARRAY(m_pfScale);
	SAFE_DELETE_ARRAY(m_pvRot);
	SAFE_DELETE_ARRAY(m_pvPos);
}

//============================.
//		�\�������֐�.
//============================.
void CLongPushEffect::Disp()
{
	//�L���L���̃J�E���g.
	int m_Sparkle_Cnt = 0;

	//�o���^�C���J�E���g�̉��Z.
	m_PopTime_Cnt++;

	if (m_PopTime_Cnt > SPARKLE_POP_TIME) {
		for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
			if (m_pbIndividual_Disp[sparkle] == false && m_Sparkle_Cnt < SPARKLE_HORIZON_MAX) {
				//�ʒu���W�ݒ菈���֐�.
				SettingPosition(sparkle);
				m_pbIndividual_Disp[sparkle] = true;
				//�J�E���g.
				m_Sparkle_Cnt++;
			}
		}
		//�^�C���J�E���g�̏�����.
		m_PopTime_Cnt = 0;
	}
}

//============================.
//		�ʕ\���t���O.
//============================.
void CLongPushEffect::SettingPosition(int sparkle)
{
	//�����l(��ɂȂ�Έ���).
	float Start_Distance = ((sparkle / SPARKLE_HORIZON_MAX) % 2) * INTERVAL.x;		//����.
	float Interval_Distance = ((sparkle / SPARKLE_HORIZON_MAX) % 2) * INTERVAL.y;	//�E��.
	//���x���W�v�Z.
	float Criteria_PosX = (MOST.x + Start_Distance) + ((sparkle % SPARKLE_HORIZON_MAX) * (MOST.y - Interval_Distance));
	//�v���C���[�̒��S�ɍ��킹��.
	m_pvPos[sparkle].x = m_vCenterPos.x + Criteria_PosX;

	m_pvPos[sparkle].z = m_vCenterPos.z;
	m_pvPos[sparkle].y = STANDERD_HEIGHT;
}

//============================.
//		�ړ������֐�.
//============================.
void CLongPushEffect::Move()
{
	for (int sparkle = 0; sparkle < SPARKLE_MAX; sparkle++) {
		if (m_pbIndividual_Disp[sparkle] == true) {
			//���ɃL���L���𗬂�.
			m_pvPos[sparkle].z -= FLOW_SPEED;
			//�g�k�����֐�.
			Scaling(sparkle);
		}
	}
}

//=============================.
//		�g�k�����֐�.
//=============================.
void CLongPushEffect::Scaling(int sparkle)
{
	//�k������.
	m_pfScale[sparkle] -= SCALING_SPEED;

	if (m_pfScale[sparkle] < SCALE_MIN) {
		m_pbIndividual_Disp[sparkle] = false;
		//�����ɖ߂�.
		m_pfScale[sparkle] = SCALE_MAX;
	}
}
