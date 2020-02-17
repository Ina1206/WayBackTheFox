#include "CBran.h"

CBran::CBran()
	: m_ppCSpriteUI			(nullptr)
	, m_pCResourceManager	(nullptr)
	, m_pDepth_Srencil		(nullptr)
	, m_vPos				(nullptr)
	, m_vRot				(nullptr)
	, m_enBran_State		(enBran_Status::MAX)
	, m_bBran_OpenFlag		(true)
	, m_bBran_OpenEndFlag	(false)
	, m_bBran_CloseFlag		(true)
	, m_WaitTime			(0)
	//===================================.
	//		�ǉ�.
	, m_pCSEPlayManager		(nullptr)
	//===================================.
{
	m_ppCSpriteUI	= new CSpriteUI*[BRAN_MAX];
	m_vPos			= new D3DXVECTOR3[BRAN_MAX];
	m_vRot			= new D3DXVECTOR3[BRAN_MAX];

	m_vPos[LEFT]  = LEFT_INIT_POSITION;
	m_vPos[RIGHT] = RIGHT_INIT_POSITION;

	m_vRot[LEFT]  = LEFT_ROTATION;
	m_vRot[RIGHT] = RIGHT_ROTATION;

	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
}

CBran::~CBran()
{
	//��������֐�.
	Release();
}


//------------------------------------.
//	�X�V�����֐�.
//------------------------------------.
void CBran::UpDate()
{
	if (m_enBran_State == enBran_Status::Open)
	{
		Bran_Open();
		m_WaitTime = 0;
	}
	if (m_enBran_State == enBran_Status::Close)
	{
		m_WaitTime++;
		Bran_Close();
	}

	//================================================.
	//		�ǉ�.
	//�ӂ��܂̈ʒu�ɂ���ĉ��ʕύX.
	int Volume = static_cast<int>(((m_vPos[RIGHT].x - CLOSE_POSITION.x) / (RIGHT_INIT_POSITION.x / 2)) * m_pCSEPlayManager->VOLUME_STANDERD_MAX);
	//BGM.
	m_pCSEPlayManager->SetVolume(Volume);
	//SE(�����͒ʏ퉹�ʂ̔���������).
	Volume /= 3;
	m_pCSEPlayManager->SetSE_Volume(CSoundResource::enSoundSE::Player_Step,Volume);
	//================================================.
}

//------------------------------------.
//	�`�揈���֐�.
//------------------------------------.
void CBran::Render()
{
	//�X�v���C�g�N���XUI�̃A�h���X�擾.
	for (int bran = 0; bran < BRAN_MAX; bran++)
	{
		m_ppCSpriteUI[bran] = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::Bran);
		_ASSERT_EXPR(m_ppCSpriteUI != nullptr, L"m_ppCSpriteUI == nullptr");
		m_ppCSpriteUI[bran]->SetPosition(m_vPos[bran]);
		m_ppCSpriteUI[bran]->SetRotation(m_vRot[bran]);
		//�`��.
		m_pDepth_Srencil->SetDepth(false);
		m_ppCSpriteUI[bran]->Render();
		m_pDepth_Srencil->SetDepth(true);
	}
}

//------------------------------------.
//�`���u���֐��`.
//------------------------------------.
void CBran::SetBran_Open()
{
	m_vPos[LEFT] = LEFT_INIT_POSITION;
	m_vPos[RIGHT] = RIGHT_INIT_POSITION;
	m_bBran_OpenFlag = false;

	//�J������J�n.
	m_enBran_State = enBran_Status::Open;

	//=====================================.
	//		�ǉ�.
	//�ӂ��܂��J���鉹.
	m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Fusuma_Open, true);
	//=====================================.
}


void CBran::SetBran_Close()
{
	for (int bran = 0; bran < BRAN_MAX; bran++) {
		m_vPos[bran] = CLOSE_POSITION;
	}
	m_bBran_OpenEndFlag = false;
	m_bBran_CloseFlag = false;

	//�߂铮��J�n.
	m_enBran_State = enBran_Status::Close;

	//======================================.
	//		�ǉ�.
	//�ӂ��܂�߂鉹.
	m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Fusuma_Close, true);
	//======================================.
}

//------------------------------------.
//	�����������֐�.
//------------------------------------.
void CBran::Init()
{
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pDepth_Srencil	= CDepth_Stencil::GetDepthStencilInstance();
}

//------------------------------------.
//	�J��.
//------------------------------------.
void CBran::Bran_Open()
{
	if (m_bBran_OpenFlag == false)
	{
		if (m_vPos[LEFT].x <= CLOSE_POSITION.x) {
			m_vPos[LEFT].x += SPEED;
		}
		if (m_vPos[RIGHT].x >= CLOSE_POSITION.x) {
			m_vPos[RIGHT].x -= SPEED;
		}

		//x���W��ClosePosition�𒴂�����t���O�𗧂Ă�.
		if (m_vPos[0].x >= CLOSE_POSITION.x && m_vPos[1].x <= CLOSE_POSITION.x)
		{
			for (int bran = 0; bran < BRAN_MAX; bran++)
			{
				m_vPos[bran].x = CLOSE_POSITION.x;
			}
			m_bBran_OpenFlag = true;
			m_bBran_OpenEndFlag = true;
		}
	}
}

//------------------------------------.
//	�߂�.
//------------------------------------.
void CBran::Bran_Close()
{
	if (m_bBran_CloseFlag == false)
	{
		if (m_WaitTime > CLOSE_TIME) {
			if (m_vPos[LEFT].x >= LEFT_INIT_POSITION.x) {
				m_vPos[LEFT].x -= SPEED;
			}
			if (m_vPos[RIGHT].x <= RIGHT_INIT_POSITION.x) {
				m_vPos[RIGHT].x += SPEED;
			}

			if (m_vPos[LEFT].x <= LEFT_INIT_POSITION.x && m_vPos[RIGHT].x >= RIGHT_INIT_POSITION.x)
			{
				m_bBran_CloseFlag = true;
			}
		}
	}
}

//------------------------------------.
//	��������֐�.
//------------------------------------.
void CBran::Release()
{
	SAFE_DELETE_ARRAY(m_vRot);
	SAFE_DELETE_ARRAY(m_vPos);
	SAFE_DELETE_ARRAY(m_ppCSpriteUI);
}
