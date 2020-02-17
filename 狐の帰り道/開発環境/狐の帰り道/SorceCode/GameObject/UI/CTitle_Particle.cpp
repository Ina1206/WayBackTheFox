#include "CTitle_Particle.h"

CTitle_Particle::CTitle_Particle()
	: m_pstParticleInfo(nullptr)
	, m_Frame(0)
{
}

CTitle_Particle::~CTitle_Particle()
{
	Release();
}

//------------------------------------------.
//	�����ݒ菈���֐�.
//------------------------------------------.
void CTitle_Particle::Init_Process()
{
	m_pstParticleInfo = new stParticleInfo[PARTICLE_MAX];
	ParticleInit();
}

//------------------------------------------.
//	�X�V�����֐�.
//------------------------------------------.
void CTitle_Particle::UpDate()
{
	ParticleMove();
}

//------------------------------------------.
//	�`�揈���֐�.
//------------------------------------------.
void CTitle_Particle::Render()
{
	//�p�[�e�B�N��.
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		m_pstParticleInfo[i].m_pCParticle = m_pCResourceManager->GetParticle(CResourceParticle::enParticle::Maple_First);
		_ASSERT_EXPR(m_pstParticleInfo[i].m_pCParticle != nullptr, L"m_pCParticle == nullptr");
		m_pstParticleInfo[i].m_pCParticle->SetPosition(m_pstParticleInfo[i].m_vPos);
		m_pstParticleInfo[i].m_pCParticle->SetRotation(m_pstParticleInfo[i].m_vRot);
		m_pCDepth_Stencil->SetDepth(false);
		m_pstParticleInfo[i].m_pCParticle->Render(m_mView, m_mProj, m_vCameraPos);
		m_pCDepth_Stencil->SetDepth(true);
	}
}

//------------------------------------------.
//	��������֐�.
//------------------------------------------.
void CTitle_Particle::Release()
{
	for (int i = PARTICLE_MAX - 1; i >= 0; i--)
	{
		if (m_pstParticleInfo[i].m_pCParticle != nullptr) {
			m_pstParticleInfo[i].m_pCParticle = nullptr;
		}
	}
	SAFE_DELETE_ARRAY(m_pstParticleInfo);
}

//------------------------------------------.
//	�p�[�e�B�N���̏���������.
//------------------------------------------.
void CTitle_Particle::ParticleInit()
{
	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (i <= PARTICLE_MAX/2)
		{
			m_pstParticleInfo[i].m_vPos = PARTICLE_POS_F;
		}
		else
		{
			m_pstParticleInfo[i].m_vPos = PARTICLE_POS_S;
		}
		m_pstParticleInfo[i].m_vDir
			= D3DXVECTOR3(
				PARTICLE_DIR.x * ((float)rand() / (float)RAND_MAX) - PARTICLE_ADJ,
				PARTICLE_DIR.y * ((float)rand() / (float)RAND_MAX),
				PARTICLE_DIR.z);

		D3DXVec3Normalize(
			&m_pstParticleInfo[i].m_vDir, &m_pstParticleInfo[i].m_vDir);//���K��.

		m_pstParticleInfo[i].m_fSpeed
			= (PARTICLE_SPEED + (float)rand() / (float)RAND_MAX) * PARTICLE_SPEED_ADJ;

		m_pstParticleInfo[i].m_BirthFrame = rand();
	}
}

//------------------------------------------.
//	�p�[�e�B�N���̈ړ�����.
//------------------------------------------.
void CTitle_Particle::ParticleMove()
{
	m_Frame++;

	for (int i = 0; i < PARTICLE_MAX; i++)
	{
		if (m_Frame > m_pstParticleInfo[i].m_BirthFrame)
		{
			//�����~���x�ňړ�����l���Z�o.
			m_pstParticleInfo[i].m_vPos -= m_pstParticleInfo[i].m_vDir * m_pstParticleInfo[i].m_fSpeed;

			//�d��.
			m_pstParticleInfo[i].m_vDir.y += GRAVITY;
			//��].
			if (i % 2 == 0)
			{
				m_pstParticleInfo[i].m_vRot.z += ROTATION;
			}
			else
			{
				m_pstParticleInfo[i].m_vRot.z -= ROTATION;

			}
		}


		//=========�ǉ�==========================================.
		if (m_pstParticleInfo[i].m_vPos.y <= POSITION_Y_MIN)
		{
			m_pstParticleInfo[i].m_vDir.y = 0;
			m_pstParticleInfo[i].m_vPos.y = POSITION_Y_MAX;
		}
		//=====================================================.
	}
}
