#include "CBarrageCommand.h"

/****************************************
*		�A�ŃR�}���h�N���X.
***************/
CBarrageCommand::CBarrageCommand()
	: m_fAlpha				(MAX_ALPHA)
	, m_ppCGageSprite		(nullptr)
	, m_pvGagePos			(nullptr)
	, m_fPushCnt			(0)
	, m_BarrageButtonNum	(0)
	, m_OldBarrageButtonNum	(0)
	, m_ChangeButtonCnt		(0)
	, m_ChangeAfterCnt		(0)
	, m_pCPushButtonSprite	(nullptr)
	, m_fPushButtonAlpha	(PUSH_ALPHA_MIN)
	, m_fPushButtonSize		(PUSH_SCALE_MIN)
	, m_bButtonChangeSE		(false)
	, m_BarrageCheckCnt		(0)
	, m_fButtonScale		(BUTTONSCALE_MIN)
	, m_Timer				(MAX_TIME)
	, m_Timer_num			(0)
	, m_ppCTimeSprite		(nullptr)
	, m_pCHitEffect			(nullptr)
	, m_bBGMChange			(false)
{
	//�z�񓮓I�m��.
	m_ppCGageSprite = new CSpriteUI*[GAGE_SPRITE_MAX]();	//�Q�[�W�X�v���C�gUI�N���X.
	m_pvGagePos		= new D3DXVECTOR3[GAGE_SPRITE_MAX]();	//�Q�[�W�̕\���ʒu.
	m_ppCTimeSprite = new CSpriteUI*[TIME_SPRITE_MAX]();	//�^�C��UI�N���X.
	m_pButtonNum	= new int[USE_BUTTON_MAX]();			//�{�^���ԍ�.

	//�G�t�F�N�g�N���X�̃C���X�^���X.
	m_pCHitEffect	= new CHitEffect();						//�{�^���������Ƃ��̃G�t�F�N�g�N���X.
	m_pCHitEffect->SetEffectScale(HIT_EFFECT_SCALE);		//�G�t�F�N�g�̑傫��.
}

CBarrageCommand::~CBarrageCommand()
{
	//��������֐�.
	Release();
}

//============================================.
//		�X�V�����֐�.
//============================================.
void CBarrageCommand::Update(enCommandType CommandType)
{
	if (m_bDispFlag == true && m_penInput_Decision[STANDERD_COMMAND_USE] == enInput_Decision::Max) {
		//�R�}���h���菈���֐�.
		DecisionCommand(CommandType);
		//���ԏ����֐�.
		Time();
		//�G�t�F�N�g�X�V�����֐�.
		m_pCHitEffect->Update();
	}

	if (m_bBGMChange == false && m_bDispFlag == true) {
		//BGM�ύX.
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::GameMain_BGM, false);
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::Boss_BGM, true);
		//����.
		m_pCSEPlayManager->SetVolume(m_pCSEPlayManager->VOLUME_STANDERD_MAX);
		m_bBGMChange = true;
	}

}

//============================================.
//		�`�揈���֐�.
//============================================.
void CBarrageCommand::Render()
{
	if (m_bDispFlag == true) {
		//�{�^���̕`��.
		RenderButton();

		//�{�^���̌��̕`��.
		RenderPushButton();

		//�Q�[�W�̕`��.
		RenderGage();

		//���ԕ`�揈���֐�.
		RenderTime();

		//�G�t�F�N�g�̕`��.
		m_pCHitEffect->Render(m_mView, m_mProj, m_vCameraPos);
	}
}

//============================================.
//		��������֐�.
//============================================.
void CBarrageCommand::Release()
{
	//�G�t�F�N�g�N���X���.
	SAFE_DELETE(m_pCHitEffect);

	//���I�m�ۉ��.
	SAFE_DELETE_ARRAY(m_pButtonNum);
	SAFE_DELETE_ARRAY(m_ppCTimeSprite);
	SAFE_DELETE_ARRAY(m_pvGagePos);
	SAFE_DELETE_ARRAY(m_ppCGageSprite);


	m_pCSprite = nullptr;

}

//=============================================.
//		�R�}���h���菈���֐�.
//=============================================.
void CBarrageCommand::DecisionCommand(enCommandType CommandType)
{
	//�{�^���ύX�����֐�.
	ChangeButton();

	//�ύX��̃J�E���g.
	m_ChangeAfterCnt++;

	//�G�̏������Ă���{�^���ԍ��Ɠ��̓{�^���ԍ�����v���Ă��邩�ǂ���.
	if (m_ButtonNum == static_cast<int>(CommandType)) {
		//�������h�~.
		m_BarrageCheckCnt++;
		if (m_BarrageCheckCnt == 1) {
			if (m_fPushCnt < BARRAGE_MAX) {
				
				//�����ꂽ��J�E���g.
				m_fPushCnt++;

				//�G�t�F�N�g�̕\�����W�ݒ�.
				D3DXVECTOR3 m_vEffectPos = m_vPos;
				m_vEffectPos.y += EFFECT_HIGH;
				m_pCHitEffect->SetCenterPos(m_vEffectPos);
				
				//�G�t�F�N�g�\���J�n.
				m_pCHitEffect->SetEffectStart(true);

				//�{�^�������炷.
				m_fPushButtonAlpha = PUSH_ALPHA_MAX;
			}

			//SE�̍Đ�.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Button_push, true);
		}

		//���̓���.
		m_fPushButtonAlpha -= PUSH_ALPHA_SPEED;
		if (m_fPushButtonAlpha <= PUSH_ALPHA_MIN) {
			m_fPushButtonAlpha = PUSH_ALPHA_MIN;
		}
		//���̊g�k.
		m_fPushButtonSize += PUSH_SCALE_SPEED;
		if (m_fPushButtonSize > PUSH_SCALE_MAX) {
			m_fPushButtonSize = PUSH_SCALE_MAX;
		}
	}
	else {
		//�{�^���̌�������.
		m_fPushButtonAlpha = PUSH_ALPHA_MIN;
		m_fPushButtonSize = PUSH_SCALE_MIN;
		
		if (CommandType == enCommandType::Max) {
			m_BarrageCheckCnt = 0;
			return;
		}
		m_BarrageCheckCnt++;
		if (m_BarrageCheckCnt == 1 && m_ChangeAfterCnt > CHANGE_WAIT_TIME) {
			if (m_fPushCnt > 0) {
				m_fPushCnt--;
				m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::GageDown, true);
			}
		}
	}


	//���ԓ��ɉ����I����Great����.
	if (m_fPushCnt >= BARRAGE_MAX) {
		m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Great;
		m_bDispFlag = false;
	}

}

//============================================.
//		���ԏ������菈���֐�.
//============================================.
void CBarrageCommand::Time()
{

	m_Timer_num++;
	//��b���ĂΌ��炷.
	if (m_Timer_num % FRAME == 0) {
		//�������Ԍ��炷.
		m_Timer--;

		//5�b�O����Đ�.
		if (m_Timer <= SOUND_TIME) {
			//SE�Đ�.
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::Time, true);
		}

		m_Timer_num = 0;
	}

	//�������Ԃ��I���Δ�\��.
	if (m_Timer <= 0) {
		m_bDispFlag = false;
		//���Ԃ܂łɉ����Ȃ�������Bad.
		m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Bad;
	}

}

//===========================================.
//		���ԕ`�揈���֐�.
//===========================================.
void CBarrageCommand::RenderTime()
{
	//�摜�p�^�[���̐ݒ�.
	D3DXVECTOR2* Pattern = nullptr;
	Pattern = new D3DXVECTOR2[TIME_SPRITE_MAX]();
	Pattern[TIME_TENS_PLACE] = D3DXVECTOR2(static_cast<float>((m_Timer / TIME_TENS) % IMAGE_WIDTH_MAX), static_cast<float>((m_Timer / TIME_TENS) / IMAGE_HIGH_MAX));
	Pattern[TIME_ONE_RANK] = D3DXVECTOR2(static_cast<float>(m_Timer % IMAGE_WIDTH_MAX), static_cast<float>(m_Timer / IMAGE_HIGH_MAX));

	//�`��.
	for (int timenum = 0; timenum < 2; timenum++) {
		//�X�v���C�gUI�N���X�̃A�h���X�擾.
		m_ppCTimeSprite[timenum] = m_pCResourceManager->GetSpriteUI(CResourceSpriteUI::enSpriteUI::TimerNum);
		//�ʒu.
		D3DXVECTOR3	TimePos = TIME_DISP_POS;
		TimePos.x += timenum * TIME_WIDTH;
		m_ppCTimeSprite[timenum]->SetPosition(TimePos);
		//�p�^�[��.
		m_ppCTimeSprite[timenum]->SetPattern(Pattern[timenum]);
		//�`��.
		m_ppCTimeSprite[timenum]->Render();
	}

	//Pattern�z��������.
	SAFE_DELETE_ARRAY(Pattern);
}

//===========================================.
//		�{�^���ύX�����֐�.
//===========================================.
void CBarrageCommand::ChangeButton()
{
	//�A�ŃQ�[�W�̋�؂�.
	int m_BurrageButton_Delimiter = BARRAGE_MAX / USE_BUTTON_MAX;
	//�g����R�}���h�̍ő吔����؂��ĘA�ŉ񐔂Ń{�^����ς���.
	m_BarrageButtonNum = m_fPushCnt / m_BurrageButton_Delimiter;
	
	if (m_BarrageButtonNum < USE_BUTTON_MAX) {
		
		m_ButtonNum = m_pButtonNum[m_BarrageButtonNum];

		//�{�^���ύX���o����.
		if (m_BarrageButtonNum != m_OldBarrageButtonNum) {
			//m_ChangeButtonCnt	= m_fPushCnt;
			m_fButtonScale		= BUTTONSCALE_MAX;
			m_bButtonChangeSE	= true;
			m_ChangeAfterCnt	= 0;
		}
	}

	m_fButtonScale -= SCALE_SPEED_BUT;
	if (m_fButtonScale < BUTTONSCALE_MIN) {
		m_fButtonScale = BUTTONSCALE_MIN;
		//SE.
		if (m_bButtonChangeSE == true) {
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::ButtonChage, true);
			m_bButtonChangeSE = false;
		}
	}


	m_OldBarrageButtonNum = m_BarrageButtonNum;
}

//===========================================.
//		�{�^���̕`��.
//===========================================.
void CBarrageCommand::RenderButton()
{
	//�摜�̗񋓑̂̃R�}���h�J�n�ԍ�.
	int m_SpriteStart;
	if (m_bControllerFlag == true) {
		m_SpriteStart = static_cast<int>(CResourceSprite::enSprite::ControllerCommandStart);
	}
	else {
		m_SpriteStart = static_cast<int>(CResourceSprite::enSprite::KeybordCommandStart);
	}

	//�{�^���ԍ��Ɖ摜�J�n�ԍ��𑫂��ĉ摜�񋓑̂Ɠ���ɂ���.
	int m_CommandSprite = m_ButtonNum + m_SpriteStart;

	//���ݍ���Ă��Ȃ��{�^���ŃG���[���N����Ȃ��悤��.
	if (m_bControllerFlag == true) {
		if (m_CommandSprite >= static_cast<int>(CResourceSprite::enSprite::YButton)) {
			m_CommandSprite = static_cast<int>(CResourceSprite::enSprite::YButton);
		}
	}
	else {
		if (m_CommandSprite >= static_cast<int>(CResourceSprite::enSprite::UpButton)) {
			m_CommandSprite = static_cast<int>(CResourceSprite::enSprite::UpButton);
		}
	}

	//�N���X.
	m_pCSprite = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(m_CommandSprite));


	//�ʒu.
	m_vPos.y = BUTTON_POS_Y;
	m_vPos.z -= BUTTON_POS_Z;
	m_pCSprite->SetPosition(m_vPos);

	//�傫��.
	m_pCSprite->SetScale(D3DXVECTOR3(m_fButtonScale, m_fButtonScale, m_fButtonScale));

	//�ݒ肵�������ߒl.
	m_pCSprite->SetAlpha(m_fAlpha);

	//�`��.
	m_pCDepth_Stencil->SetDepth(false);
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepth_Stencil->SetDepth(true);

	//���̂Ƃ���ɉe�����o�Ȃ��悤�ɓ��ߒl�𒼂��Ă���.
	m_pCSprite->SetAlpha(ALPHA_MAX);
	m_pCSprite->SetScale(D3DXVECTOR3(BUTTONSCALE_MIN, BUTTONSCALE_MIN, BUTTONSCALE_MIN));
}

//===========================================.
//		�Q�[�W�̕`��.
//===========================================.
void CBarrageCommand::RenderGage()
{
	for (int gagenum = 0; gagenum < GAGE_SPRITE_MAX; gagenum++) {
		int sprite = static_cast<int>(CResourceSpriteUI::enSpriteUI::GageGround) + gagenum;
		m_ppCGageSprite[gagenum] = m_pCResourceManager->GetSpriteUI(static_cast<CResourceSpriteUI::enSpriteUI>(sprite));
	}

	//�T�C�Y.
	float SizeW = m_fPushCnt / static_cast<float>(BARRAGE_MAX);
	m_ppCGageSprite[GAGE_NUM]->SetScale(SizeW);
	
	//�Q�[�W�̈ʒu.
	m_vPos.x = GAGE_POS.x;
	m_vPos.y = GAGE_POS.y;
	m_vPos.z = GAGE_POS.z;
	D3DXVECTOR3 GagePos = D3DXVECTOR3(m_vPos.x + (((SizeW * GAGE_LENGTH_MAX) / GAGE_HALF) - GAGE_POS_START), m_vPos.y, m_vPos.z);
	//�Q�[�W����.
	GagePos.x += GAGE_POS_ADJUST.x;
	GagePos.y += GAGE_POS_ADJUST.y;
	GagePos.z -= GAGE_POS_ADJUST.z;
	m_ppCGageSprite[GAGE_NUM]->SetPosition(GagePos);

	//�Q�[�W���n�̈ʒu.
	m_ppCGageSprite[GAGE_GROUN_NUM]->SetPosition(m_vPos);

	//�`��.
	for (int gage_num = 0; gage_num < GAGE_SPRITE_MAX; gage_num++) {
		m_ppCGageSprite[gage_num]->Render();
	}
}

//================================================.
//		�{�^�����������Ƃ��̕`�揈���֐�.
//================================================.
void CBarrageCommand::RenderPushButton()
{
	m_pCPushButtonSprite = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::HitButton);
	//���W.
	m_pCPushButtonSprite->SetPosition(m_vPos);
	//���ߒl.
	m_pCPushButtonSprite->SetAlpha(m_fPushButtonAlpha);
	//�傫��.
	m_pCPushButtonSprite->SetScale(D3DXVECTOR3(m_fPushButtonSize, m_fPushButtonSize, m_fPushButtonSize));

	//�`��.
	m_pCPushButtonSprite->Render(m_mView, m_mProj, m_vCameraPos);
}

//=================================================.
//		�\�����菈���֐�.
//=================================================.
void CBarrageCommand::DecisionDisp()
{

}