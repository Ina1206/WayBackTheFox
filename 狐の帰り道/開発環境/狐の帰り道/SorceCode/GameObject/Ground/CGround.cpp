#include "CGround.h"

CGround::CGround()
	: m_ppGround			(nullptr)
	, m_pvPos				(nullptr)
	, m_fScroll_Speed		(0.0f)
	, m_bDeceleration_Start	(false)
	, m_bMoveCamera			(false)
	, m_fMoving_Distance	(0.0f)
	, m_BackCnt				(0)
	, m_BackNum				(0)
	, m_fSwingUpMax			(0.0f)
	, m_vBossRot			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_enSwingType			(enSwingType::Up)
	, m_fUpDistance			(0.0f)
	, m_SwingCount			(0)
	, m_enInputDecision		(enInput_Decision::Max)
	, m_vGatePos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vInitGatePos		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

CGround::~CGround()
{
	Release();
}

//=====================================.
//		�����������֐�.
//=====================================.
void CGround::InitProcess()
{
	//�v�f�����I�m��.
	m_ppGround	= new CDX9Mesh*[STAGE_MAX_BACK * STAGE_MAX_HORIZON];		//���b�V��.
	m_pvPos		= new D3DXVECTOR3[STAGE_MAX_BACK * STAGE_MAX_HORIZON];	//���W.
	//������.
	for (int stage = 0; stage < STAGE_MAX_BACK * STAGE_MAX_HORIZON; stage++) {
		m_ppGround[stage] = nullptr;
		m_pvPos[stage].x = ((stage % STAGE_MAX_HORIZON) * GROUND_WIDTH ) - GROUND_WIDTH;
		m_pvPos[stage].y = GROUND_HIGHT_ADJUSTMENT * (stage / STAGE_MAX_HORIZON);
		m_pvPos[stage].z = STAGE_START_POS +((stage / STAGE_MAX_HORIZON) * GROUND_WIDTH);
	}

	//�X�N���[�����x.
	if (m_bMoveCamera == false) {
		m_fScroll_Speed = STANDERD_SPEED;
	}
	else {
		m_fScroll_Speed = UP_LOOK_SPEED;
	}
	//�����J�n.
	m_bDeceleration_Start = false;
	//�h���ő吔.
	m_fSwingUpMax = SWING_UP_MAX;

	//��Ԍ��̔ԍ��̐ݒ�.
	m_BackNum = (STAGE_MAX_BACK * STAGE_MAX_HORIZON) - STAGE_MAX_HORIZON;

	//�Q�[�g�̏����ʒu.
	//m_vGatePos.z = GOAL_DISTANCE;
}

//=====================================.
//		�X�V�����֐�.
//=====================================.
void CGround::Update()
{
	//�S�̂̈ړ�����.
	m_fMoving_Distance += m_fScroll_Speed;

	//�n�ʂ̈ړ�.
	Move();

	//�h��鏈���֐�.
	if (m_enInputDecision == enInput_Decision::Bad) {
		if (m_vBossRot.x <= SWING_START_ROTATION && m_SwingCount <= SWING_MAX) {
			Swing();
			//�n�ʂ�h�炷.
			for (int stage = 0; stage < STAGE_MAX_BACK * STAGE_MAX_HORIZON; stage++) {
				m_pvPos[stage].y = STANDERD_POS_HIGHT + m_fUpDistance;
			}
			//�Q�[�g��h�炷.
			m_vGatePos.y = STANDERD_POS_HIGHT + m_fUpDistance;
		}
	}

}

//=====================================.
//		�`�揈���֐�.
//=====================================.
void CGround::Render()
{
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	
	////�e�̍��W��������������.
	////�^�C�g���ł͏������Ȃ�.
	//if (m_vPlayerShadowPos.z > 0) {
	//	m_vPlayerShadowPos.y += 0.9f;
	//	for (int enemy = 0; enemy < 9; enemy++) {
	//		m_pvEnemyShadowPos[enemy].y += 1.0f;
	//	}
	//}

	//-------�n��--------//.
	for (int stage = 0; stage < STAGE_MAX_BACK *STAGE_MAX_HORIZON; stage++) {
		m_ppGround[stage] = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::AroundGround);
		//���������I�u�W�F�N�g���Ⴄ.
		if (stage % STAGE_MAX_HORIZON == CENTER_GROUND_NUM) {
			m_ppGround[stage] = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Ground);
		}
		if (stage % 6 == 4) {
			m_ppGround[stage] = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Ground2);
		}
		//�m�F.
		_ASSERT_EXPR(m_ppGround[stage] != nullptr, L"m_pGround == nullptr");
		//�`��ł̐ݒ�.
		//�傫��.
		m_ppGround[stage]->SetScale(SCALE_SIZE);									//�傫��.
		//���W.
		m_ppGround[stage]->SetPosition(m_pvPos[stage]);								//���W.
		//�p�x.
		m_ppGround[stage]->SetRotation(D3DXVECTOR3(0.0f, STANDERD_ROT_Y, 0.0f));	//�p�x.
		//�e.
		//�^�C�g���͏������Ȃ�.
		//if (m_vPlayerShadowPos.z > 0) {
		//	SHADOW m_shadow[10];
		//	m_shadow[0] = { m_vPlayerShadowPos, true };
		//	for (int enemy = 0; enemy < 9; enemy++) {
		//		m_shadow[enemy + 1] = { m_pvEnemyShadowPos[enemy], true };
		//		if (m_pvEnemyShadowPos[enemy].y > 10) {
		//			m_shadow[enemy + 1].bDispFlag = false;
		//		}
		//	}

		//	
		//	//SHADOW m_ss[] = {
		//	//	{D3DXVECTOR3(m_vPlayerShadowPos), true},
		//	//	
		//	//};
		//	m_ppGround[stage]->SetShadow(m_shadow, 10);
		//}
		//�`��.
		m_ppGround[stage]->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);
	}

	//-------����--------//.
	if (m_vGatePos.z < GAET_DISP_DISTANCE) {
		m_pCGate = m_pCResourceManager->GetStaticMesh(CResourceStaticMesh::enStaticMesh::Gate);
		_ASSERT_EXPR(m_pCGate != nullptr, L"m_pCGate == nullptr");
		m_pCGate->SetScale(SCALE_SIZE);
		m_pCGate->SetPosition(m_vGatePos);
		m_pCGate->SetRotation(D3DXVECTOR3(0.0f, 3.2f, 0.0f));
		m_pCGate->Render(m_mView, m_mProj, m_vLight, m_vCameraPos);
	}
}

//=====================================.
//		��������֐�.
//=====================================.
void CGround::Release()
{	

	//-----���b�V��------//.
	for (int stage = 0; stage < STAGE_MAX_BACK * STAGE_MAX_HORIZON; stage++) {
		if (m_ppGround[stage] != nullptr) {
			m_ppGround[stage] = nullptr;
		}
	}

	//�v�f�����.
	SAFE_DELETE_ARRAY(m_pvPos);		//���W.
	SAFE_DELETE_ARRAY(m_ppGround);	//���b�V��.
}

//=====================================.
//		�ړ������֐�.
//=====================================.
void CGround::Move()
{
	for (int stage = 0; stage < STAGE_MAX_BACK * STAGE_MAX_HORIZON; stage++) {
		//�ړ����x.
		m_pvPos[stage].z -= m_fScroll_Speed;

		//�߂�.
		if (m_pvPos[stage].z <= GROUND_BACK_POSITION) {
			
			if (m_BackCnt >= STAGE_MAX_HORIZON) {
				//��ԉ��ɂ���n�ʂ̔ԍ���ݒ�.
				m_BackNum = stage - STAGE_MAX_HORIZON;
				if (m_BackNum < 0) {
					m_BackNum = (STAGE_MAX_BACK * STAGE_MAX_HORIZON) - STAGE_MAX_HORIZON;
				}
				m_BackCnt = 0;
			}
			//���Ɉړ�.
			m_pvPos[stage].z = m_pvPos[m_BackNum].z + STAGE_DEPTH_WIDTH;
			m_BackCnt++;
		}
	}

	//�X�N���[�����x.
	if (m_bDeceleration_Start == true) {
		ScrollSpeedDeceleration();
	}
	else {
		if (m_bMoveCamera == false) {
			//�ʏ펞�̑��x.
			m_fScroll_Speed = STANDERD_SPEED;
		}
		else {
			//�㎋�_���̑��x.
			m_fScroll_Speed = UP_LOOK_SPEED;
		}
	}

	//�Q�[�g�̈ړ�.
	m_vGatePos.z = m_vInitGatePos.z - m_fMoving_Distance;
}

//=====================================.
//	�X�N���[���X�s�[�h�̌��������֐�.
//=====================================.
void CGround::ScrollSpeedDeceleration()
{
	//��������.
	if (m_fScroll_Speed > 0.0f) {
		m_fScroll_Speed -= SCROLL_DECELETARATION;
	}
	//���̐��ɂȂ�Ȃ��悤�Ɏ~�߂�.
	else if (m_fScroll_Speed < 0.0f) {
		m_fScroll_Speed = 0.0f;
	}
}

//=====================================.
//		�h��鏈���֐�.
//=====================================.
void CGround::Swing()
{
	switch (m_enSwingType) {
		//��ɏオ��.
	case enSwingType::Up:
		m_fUpDistance += SWING_SPEED;
		//����܂ňړ�.
		if (m_fUpDistance > m_fSwingUpMax) {
			m_enSwingType = enSwingType::Down;
		}
		break;
		//���ɉ�����.
	case enSwingType::Down:
		m_fUpDistance -= SWING_SPEED;
		//���܂ňړ�.
		if (m_fUpDistance < STANDERD_POS_HIGHT) {
			m_enSwingType = enSwingType::Up;
			//�J�E���g.
			m_SwingCount++;
			//��Ɉړ�����ő吔�ύX.
			m_fSwingUpMax = SWING_REDUCE_SPEED - (SWING_REDUCE_ADJU * (m_SwingCount/2));
		}
		break;
	}
}