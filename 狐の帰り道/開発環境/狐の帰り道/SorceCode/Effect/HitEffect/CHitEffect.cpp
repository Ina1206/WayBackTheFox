#include "CHitEffect.h"

CHitEffect::CHitEffect()
	: m_fMoving_Distance	(0.0f)
	, m_enMoveType			(enMoveType::Right)
	, m_vInitPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
	//�쐬����Ă����ɏ���������.
	Init();
}

CHitEffect::~CHitEffect()
{
	//��������֐�.
	Release();
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CHitEffect::UpDate()
{
	//�\�����Ă���Ƃ�.
	if (m_bDispFlag == true) {
		for (int sprite = 0; sprite < DISP_EFFECT_MAX; sprite++) {
			//�\�����߂Ɋ�ʒu�ɏ���.
			if (m_bDispFlag != m_bOldDispFlag) {
				//�ʒu.
				m_pvPos[sprite] = D3DXVECTOR3(m_vCenterPos.x + (BASIC_BLANK_WIDTH * sprite), m_vCenterPos.y + ADD_HIGHT, m_vCenterPos.z);
				m_pvPos[sprite].x -= BASIC_DIFFERENCIAL;

				//�p�x.
				m_pvRot[sprite].y = START_ROTAITON - (START_ROTAITON * sprite);

				m_vInitPos = m_pvPos[sprite];
			}
			else {
				//�ړ������֐�.
				Move(sprite);
			}
		}
	}

	//�t���O.
	m_bOldDispFlag = m_bDispFlag;
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CHitEffect::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	if (m_bDispFlag == true) {
		//�S����C�ɐݒ肵�Ȃ��ƕ`�悳��Ȃ�.
		for (int sprite = 0; sprite < DISP_EFFECT_MAX; sprite++) {
			//�X�v���C�g�N���X�̃A�h���X.
			m_ppCSprite[sprite] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Hit);
			//�p�x.
			m_ppCSprite[sprite]->SetRotation(m_pvRot[sprite]);
			//���W.
			m_ppCSprite[sprite]->SetPosition(m_pvPos[sprite]);
			//�傫��.
			m_ppCSprite[sprite]->SetScale(D3DXVECTOR3(m_pfScale[sprite], m_pfScale[sprite], m_pfScale[sprite]));
			//�`��.
			CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
			m_pCDepth_Stencil->SetDepth(false);
			m_ppCSprite[sprite]->Render(mView, mProj, vCamePos);
			m_pCDepth_Stencil->SetDepth(true);

		}
	}
}

//=========================================.
//		�����������֐�.
//=========================================.
void CHitEffect::Init()
{
	//���I�m��.
	m_pvPos		= new D3DXVECTOR3[DISP_EFFECT_MAX]();	//���W.
	m_pvRot		= new D3DXVECTOR3[DISP_EFFECT_MAX]();	//�p�x.
	m_pfScale	= new float[DISP_EFFECT_MAX]();			//�傫��.
	m_ppCSprite = new CSprite*[DISP_EFFECT_MAX]();		//�X�v���C�g�N���X.

	//�l�̏�����.
	for (int sprite = 0; sprite < DISP_EFFECT_MAX; sprite++) {
		m_pvPos[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pvRot[sprite] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_pfScale[sprite] = BASE_SCALE;
	}
}

//=========================================.
//		��������֐�.
//=========================================.
void CHitEffect::Release()
{
	for (int sprite = DISP_EFFECT_MAX - 1; sprite >= 0; sprite--) {
		m_ppCSprite[sprite] = nullptr;
	}
	SAFE_DELETE_ARRAY(m_ppCSprite);	//�X�v���C�g�N���X.
	SAFE_DELETE_ARRAY(m_pfScale);	//�傫��.
	SAFE_DELETE_ARRAY(m_pvRot);		//�p�x.
	SAFE_DELETE_ARRAY(m_pvPos);		//���W.
}

//=========================================.
//		�ړ������֐�
//=========================================.
void CHitEffect::Move(int sprite)
{
	//�����v�Z.
	const int LEFT_DIRECTION = -1;	//���Ɍ����̕���.
	int Direction = (sprite * 2) + LEFT_DIRECTION;
	//�ړ�.
	switch (m_enMoveType) {
	//�E�Ɉړ�.
	case enMoveType::Right:
		//�ړ�.
		m_pvPos[sprite].x	+= Direction * MOVING_SPEED;
		m_fMoving_Distance	+= MOVING_SPEED;
		//���ɖ߂�.
		if (m_pvPos[sprite].x > MOVING_DISTANCE_MAX + m_vInitPos.x) {
			m_enMoveType = enMoveType::Left;
		}
		break;
	//���Ɉړ�.
	case enMoveType::Left:
		//�ړ�.
		m_pvPos[sprite].x	-= Direction * MOVING_SPEED;
		m_fMoving_Distance	-= MOVING_SPEED;
		//�\���I��.
		if (m_pvPos[1].x < m_vInitPos.x) {
			m_enMoveType = enMoveType::Right;
			m_bDispFlag = false;
		}
		break;
	}
}

//===================================.
//		�傫���ύX�����֐�.
//===================================.
void CHitEffect::SetEffectScale(float scale)
{
	for (int effect = 0; effect < DISP_EFFECT_MAX; effect++) {
		m_pfScale[effect] = scale;
	}
}