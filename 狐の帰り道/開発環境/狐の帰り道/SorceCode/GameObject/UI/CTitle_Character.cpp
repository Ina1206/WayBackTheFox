#include "CTitle_Character.h"

CTitle_Character::CTitle_Character()
	:  m_pCInput		(nullptr)
	, m_ppCTitleSpriteUI(nullptr)
	, m_enTitle_Status	(enTitle_Status::Character_Display)
	, m_vTitlePos		(nullptr)
	, m_fTitleAlpha		(nullptr)
	, m_Frame			(0)
	, m_DispFlag		(nullptr)
	, m_DispNum			(0)
	, m_LineSCale		(0.0f)
	
{
}

CTitle_Character::~CTitle_Character()
{
	Release();
}

//------------------------------------------.
//	�����ݒ菈���֐�.
//------------------------------------------.
void CTitle_Character::Init_Process()
{
	//�R���g���[���̏�����.
	m_pCInput = new clsXInput();

	m_ppCTitleSpriteUI = new CSpriteUI*[SPRITEUI_MAX];

	m_vTitlePos = new D3DXVECTOR2[SPRITEUI_MAX];
	m_vTitlePos[KITUNE_NUM] = KITUNE_POS;
	m_vTitlePos[NO_NUM]		= NO_POS;
	m_vTitlePos[KAE_NUM]	= KAE_POS;
	m_vTitlePos[RI_NUM]		= RI_POS;
	m_vTitlePos[MITI_NUM]	= MITI_POS;
	m_vTitlePos[LINE_NUM]	= LINE_POS;
	m_vTitlePos[MAPLE_NUM]	= MAPLE_POS;

	m_fTitleAlpha = new float[SPRITEUI_MAX];
	for (int alpha = 0; alpha < SPRITEUI_MAX; alpha++)
	{
		m_fTitleAlpha[alpha] = 0.0f;
	}

	m_DispFlag = new bool[SPRITEUI_MAX];
	for (int disp = 0; disp < SPRITEUI_MAX; disp++)
	{
		m_DispFlag[disp] = false;
	}
}

//------------------------------------------.
//	�X�V�����֐�.
//------------------------------------------.
void CTitle_Character::UpDate()
{
	m_Frame++;

	static int pushCnt = 0;	//�ēx���͂����߂邽�߂̃J�E���g.


	//�^�C�g����ʂł����^�C�g�����\������Ȃ��悤�ɂ��鏈��.
	if (m_Frame < INPUT_OK || g_BranOpenFlag == false) {
		if (m_pCInput->IsPress(XINPUT_GAMEPAD_A) || 
			(GetAsyncKeyState(VK_RETURN) & 0x8000) ||
			(GetAsyncKeyState(VK_SPACE) & 0x8000)){
			pushCnt++;
		}
	}

	m_pCInput->UpdateStatus();//�������Ȃ��Ɠ����Ȃ�.

	if (((m_pCInput->IsPress(XINPUT_GAMEPAD_A)) || 
		(GetAsyncKeyState(VK_RETURN) & 0x8000) ||
		(GetAsyncKeyState(VK_SPACE) & 0x8000)) && 
		g_BranOpenFlag == true)
	{
		if (m_Frame >= INPUT_OK && pushCnt == 0) {
			m_bMoveEndFlag = true;
		}
	}
	else {
		pushCnt = 0;
	}

#if _DEBUG
	if (GetAsyncKeyState(VK_RETURN)& 0x0001)
	{
		m_bMoveEndFlag = true;
	}
#endif

	if (m_bMoveEndFlag == false) {
		if (m_enTitle_Status == enTitle_Status::Character_Display)
		{
			//������1�����\��.
			if (m_Frame >= DISPLAY_TIME) {
				if (m_DispNum < SPRITEUI_MAX)
				{
					m_DispFlag[m_DispNum] = true;
					m_DispNum++;
					m_Frame = 0;
				}
				else
				{
					m_Frame = 0;
				}
			}
			for (int disp = 1; disp < SPRITEUI_MAX - 1; disp++)
			{
				if (m_DispFlag[disp] == true) {
					TitleFade(disp);
				}
			}
			//������\�����I����������`��.
			if (m_fTitleAlpha[MITI_NUM] >= TITLE_ALPHA_MAX) {
				m_enTitle_Status = enTitle_Status::Draw_Line;
			}
		}

		TitleMove();
	}
	else {
		for (int spriteUI = 0; spriteUI < SPRITEUI_MAX; spriteUI++) {
			m_fTitleAlpha[spriteUI] = 1.0f;
		}
		m_LineSCale = 1.0f;
		m_vTitlePos[MAPLE_NUM].y = POSITION_Y;
	}


}

//------------------------------------------.
//	�`�揈���֐�.
//------------------------------------------.
void CTitle_Character::Render()
{
	//�^�C�g������.
	m_ppCTitleSpriteUI[MAPLE_NUM] = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::Maple);
	for (int spriteUI = KITUNE_NUM; spriteUI < SPRITEUI_MAX; spriteUI++) {
		int spriteNum = (static_cast<int>(CResourceSpriteUI::enSpriteUI::Kitune)-1) + spriteUI;
		m_ppCTitleSpriteUI[spriteUI] = m_pCResourceManager->GetSpriteUI(static_cast<CResourceSpriteUI::enSpriteUI>(spriteNum));
	}

	//�X�P�[���̐ݒ�.
	m_ppCTitleSpriteUI[LINE_NUM]->SetScale(m_LineSCale);

	//�A���t�@�l�ݒ�.
	for (int spriteUI = KITUNE_NUM; spriteUI < SPRITEUI_MAX-1; spriteUI++) {
		m_ppCTitleSpriteUI[spriteUI]->SetAlpha(m_fTitleAlpha[spriteUI]);
	}
	m_ppCTitleSpriteUI[LINE_NUM]->SetAlpha(m_fTitleAlpha[LINE_NUM]);
	m_ppCTitleSpriteUI[MAPLE_NUM]->SetAlpha(m_fTitleAlpha[MAPLE_NUM]);

	//�`��.
	for (int spriteUI = 0; spriteUI < SPRITEUI_MAX; spriteUI++)
	{
		_ASSERT_EXPR(m_ppCTitleSpriteUI != nullptr, L"m_ppCTitleSpriteUI == nullptr");
		m_ppCTitleSpriteUI[spriteUI]->SetPosition(D3DXVECTOR3(m_vTitlePos[spriteUI].x, m_vTitlePos[spriteUI].y, 0.0f));
		m_pCDepth_Stencil->SetDepth(false);
		m_ppCTitleSpriteUI[spriteUI]->Render();
		m_pCDepth_Stencil->SetDepth(true);
	}

}

//------------------------------------------.
//	��������֐�.
//------------------------------------------.
void CTitle_Character::Release()
{
	SAFE_DELETE(m_pCInput);
	SAFE_DELETE(m_fTitleAlpha);
	SAFE_DELETE(m_DispFlag);
	SAFE_DELETE(m_vTitlePos);
	SAFE_DELETE_ARRAY(m_ppCTitleSpriteUI);
}

//------------------------------------------.
//	�^�C�g���������쏈���֐�.
//------------------------------------------.
void CTitle_Character::TitleMove()
{
	if (m_enTitle_Status == enTitle_Status::Draw_Line) {
		if (m_LineSCale <= SCALE_MAX) {
			m_LineSCale += SCALE_SPEED;
		}
		m_fTitleAlpha[LINE_NUM] = SCALE_MAX;

		//����`�悵�I���������݂��̕`��.
		if (m_LineSCale >= SCALE_MAX) {
			m_enTitle_Status = enTitle_Status::Maple_Display;
		}
	}

	if (m_enTitle_Status == enTitle_Status::Maple_Display)
	{

		if (m_vTitlePos[MAPLE_NUM].y <= POSITION_Y)
		{
			m_vTitlePos[MAPLE_NUM].y += TITLE_MOVE_SPEED;
		}
		else
		{
			m_bMoveEndFlag = true;
		}
		TitleFade(MAPLE_NUM);
	}
}

//------------------------------------------.
//	�^�C�g���������ߏ����֐�.
//------------------------------------------.
void CTitle_Character::TitleFade(int num)
{
	if (m_fTitleAlpha[num] <= TITLE_ALPHA_MAX)
	{
		m_fTitleAlpha[num] += TITLE_ALPHA_SPEED;
	}
}
