#ifndef CTITLE_PARTICLE_H
#define CTITLE_PARTICLE_H

#include "CUI_Base.h"

class CTitle_Particle
	: public CUI_Base
{
public:
	CTitle_Particle();
	~CTitle_Particle();

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Init_Process();	//�����ݒ菈���֐�.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

private:
	//------------------------------------------.
	//	�萔.
	//------------------------------------------.
	const D3DXVECTOR3	PARTICLE_POS_F		= D3DXVECTOR3(-2.0f, 4.0f, 5.0f);	//�p�[�e�B�N���ʒu.
	const D3DXVECTOR3	PARTICLE_POS_S		= D3DXVECTOR3(2.0f, 4.0f, 5.0f);	//�p�[�e�B�N���ʒu.
	const D3DXVECTOR3	PARTICLE_DIR		= D3DXVECTOR3(5.0f, 5.0f, 0.0f);	//�p�[�e�B�N������.
	const int			PARTICLE_MAX		= 40;								//�p�[�e�B�N���ő吔.
	const float			PARTICLE_ADJ		= 2.0f;								//����.
	const float			PARTICLE_SPEED		= 2.0f;								//���x.
	const float			PARTICLE_SPEED_ADJ	= 0.0005f;							//���x����.
	const double		GRAVITY				= 0.003;							//�d��.
	const float			ROTATION			= 0.005f;							//��].
	const float			POSITION_Y_MIN		= -2.0f;							//y���W�ŏ��l.
	const float			POSITION_Y_MAX		= 4.0f;								//y���W�ő�l.
	//------------------------------------------.
	//	�\����.
	//------------------------------------------.
	//�p�[�e�B�N���̏��.
	struct stParticleInfo
	{
		D3DXVECTOR3	m_vPos;
		D3DXVECTOR3 m_vDir;
		D3DXVECTOR3 m_vRot;
		int			m_BirthFrame;
		float		m_fSpeed;
		CParticle*	m_pCParticle;

		stParticleInfo()
			: m_vPos(0.0f, 0.0f, 0.0f)
			, m_vDir(0.0f, 0.0f, 0.0f)
			, m_vRot(0.0f, 0.0f, 0.0f)
			, m_BirthFrame(0)
			, m_fSpeed(0.0f)
			, m_pCParticle(nullptr)
		{};
	};

	//------------------------------------------.
	//	�֐�.
	//------------------------------------------.
	void Release();			//��������֐�.
	void ParticleInit();	//�p�[�e�B�N���̏���������.
	void ParticleMove();	//�p�[�e�B�N���̈ړ�����.

	//------------------------------------------.
	//	�ϐ�.
	//------------------------------------------.
	stParticleInfo*	m_pstParticleInfo;
	int				m_Frame;				//�o�ߎ���.

};
#endif//#ifndef CTITLE_PARTICLE_H.