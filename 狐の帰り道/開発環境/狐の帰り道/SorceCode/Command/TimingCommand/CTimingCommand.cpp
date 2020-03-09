#include "CTimingCommand.h"

/**************************************
*		�^�C�~���O�R�}���h.
**/
CTimingCommand::CTimingCommand()
	: m_pCSpriteMaru		(nullptr)
	, m_vMaruPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_fScale				(2.0f)
	, m_bCircleDispry		(false)
	, m_bButtonPushFlag		(false)
{
	
}

CTimingCommand::~CTimingCommand()
{
}

//=========================================.
//		�X�V�����֐�.
//=========================================.
void CTimingCommand::Update(enCommandType CommandType) 
{

	//�\�����菈���֐�.
	if (m_penInput_Decision[STANDERD_COMMAND_USE] == enInput_Decision::Max) {
		DecisionDisp();
	}

	if (m_bDispFlag == true) {
		//�ۂ̑傫���̏k��.
		ScaleDownCircle();
		//�������[���ɂ���΃R�}���h����.
		if (m_bCircleDispry == true && m_bJudgePossible == true) {
			if (m_LongPushCnt == 0) {
				//�R�}���h���菈���֐�.
				DecisionCommand(CommandType);
			}
		}

		if (m_bButtonPushFlag == true && m_bButtonLightFinish == false) {
			//�{�^���������Ƃ��̉~�̏����֐�.
			ButtonPushCircle();
		}
	}
}

//==========================================.
//		�`�揈���֐�.
//==========================================.
void CTimingCommand::Render()
{
	if (m_bCircleDispry == true) {
		//�ۂ̕`�揈���֐�.
		RenderCircle();
	}

	if (m_bDispFlag == true) {
		//�{�^���̕`�揈���֐�.
		m_vPos.y += m_fDispHight;
		RenderButton();
	}

	if (m_bButtonPushFlag == true && m_bButtonLightFinish == false) {
		//�{�^�������������̊ۂ̕`�揈���֐�.
		RenderButtonPush();
	}
}

//==========================================.
//		��������֐�.
//==========================================.
void CTimingCommand::Release()
{
	m_pCSprite = nullptr;
	m_pCSpriteMaru = nullptr;
}

//==========================================.
//		�\�����菈���֐�.
//==========================================.
void CTimingCommand::DecisionDisp()
{
	if (m_vPlayerPos.z + DISPRY_DISTANCE > m_vPos.z) {
		//�{�^���摜�\��.
		m_bDispFlag = true;

		//�ۂ̕\����\��.
		if (m_vPlayerPos.x == m_vPos.x) {
			m_bCircleDispry = true;
		}
		else {
			m_bCircleDispry = false;
		}

		//�L��������O�ɗ��������.
		if (m_vPlayerPos.z > m_vPos.z) {
			m_bDispFlag = false;
			m_bCircleDispry = false;
			m_fScale = CIRCLE_SIZE_MAX;
		}
	}
}

//==========================================.
//		�R�}���h���菈���֐�.
//==========================================.
void CTimingCommand::DecisionCommand(enCommandType CommandType)
{
	//�G�̃{�^���Ɠ������̂��������̂�.
	if (m_ButtonNum == static_cast<int>(CommandType)) {
	
		//Good����.
		if (m_fScale >= CIRCLE_GREAT_SIZE) {
			m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Good;
		}
		else {
			//Great�̔���.
			m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Great;
			
			//Bad����.
			if (m_fScale < CIRCLE_BAD_SIZE) {
				m_penInput_Decision[STANDERD_COMMAND_USE] = enInput_Decision::Bad;
			}
		}

		//�{�^���������t���O.
		m_bButtonPushFlag = true;
		m_fButtonLightAlpha = ALPHA_MAX;
		m_fButtonLightScale = LIGHT_SCALE_MIN;
	}
}

//==========================================.
//		�~�̑傫�������������鏈���֐�.
//==========================================.
void CTimingCommand::ScaleDownCircle()
{
	//Player�Ƃ̋����Ŋg�k.
	m_fScale = (((m_vPos.z - START_DIFFERENCE )- m_vPlayerPos.z) / DISPRY_DISTANCE) + CIRCLE_SIZE_MIN;
}

//==========================================.
//		�ۂ̕`�揈��.
//==========================================.
void CTimingCommand::RenderCircle()
{
	//�~�摜.
	m_pCSpriteMaru = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::TimingCommand);

	//�ʒu.
	m_vMaruPos = m_vPos;
	m_vMaruPos.y = m_vPos.y + m_fDispHight;
	m_pCSpriteMaru->SetPosition(m_vMaruPos);
	//�傫��.
	m_pCSpriteMaru->SetScale(D3DXVECTOR3(m_fScale, m_fScale, m_fScale));
	
	//�`��.
	CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepth_Stencil->SetDepth(false);
	m_pCSpriteMaru->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepth_Stencil->SetDepth(true);
}

//================================================.
//		�{�^���������Ƃ��̉~�̏����֐�.
//================================================.
void CTimingCommand::ButtonPushCircle()
{
	//���̑傫������.
	m_fButtonLightScale += LIGHT_SCALE_SPEED;
	if (m_fButtonLightScale > LIGHT_SCALE_MAX) {
		m_fButtonLightScale = LIGHT_SCALE_MAX;
	}

	//���̓��ߒl����.
	m_fButtonLightAlpha -= LIGHT_ALPHA_SPEED;
	if (m_fButtonLightAlpha <= LIGHT_ALPHA_MIN) {
		m_fButtonLightAlpha = LIGHT_ALPHA_MIN;
		//�{�^���Ɗۂ̔|���̔�\��.
		m_bCircleDispry = false;
		m_bDispFlag		= false;
		m_bButtonLightFinish = true;
		m_fScale = CIRCLE_SIZE_MAX;

	}
}

//================================================.
//		�{�^�����������Ƃ��̊ۂ̕`�揈���֐�.
//================================================.
void CTimingCommand::RenderButtonPush()
{
	//�摜�A�h���X�擾.
	m_pCButtonLightSprite = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::HitButton);

	//�ʒu.
	m_pCButtonLightSprite->SetPosition(m_vPos);

	//�傫��.
	m_pCButtonLightSprite->SetScale(D3DXVECTOR3(m_fButtonLightScale, m_fButtonLightScale, m_fButtonLightScale));

	//���ߒl.
	m_pCButtonLightSprite->SetAlpha(m_fButtonLightAlpha);

	//�`��.
	CDepth_Stencil* m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepth_Stencil->SetDepth(false);
	m_pCButtonLightSprite->Render(m_mView, m_mProj, m_vCameraPos);
	m_pCDepth_Stencil->SetDepth(true);
}