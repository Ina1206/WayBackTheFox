#include "CCommand_Base.h"

/************************************************
*		�R�}���h���N���X.
**/
CCommand_Base::CCommand_Base()
	: m_mView				()
	, m_mProj				()
	, m_vCameraPos			()
	, m_pCResourceManager	(nullptr)
	, m_pCSprite			(nullptr)
	, m_pCDepth_Stencil		(nullptr)
	, m_fAlpha				(1.0f)
	, m_vPos				(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_vInitPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_ButtonNum			(0)
	, m_pButtonNum			(nullptr)
	, m_penInput_Decision	(nullptr)
	, m_penOld_Decision		(nullptr)
	, m_bDispFlag			(false)
	, m_bJudgePossible		(false)
	, m_LongPushCnt			(0)
	, m_vPlayerPos			(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
	, m_pCSEPlayManager		(nullptr)
	, m_ppCEffectBase		(nullptr)
	, m_pCButtonLightSprite	(nullptr)
	, m_fButtonLightAlpha	(LIGHT_ALPHA_MAX)
	, m_fButtonLightScale	(LIGHT_SCALE_MIN)
	, m_bButtonLightFinish	(false)

{
	//�����������֐�.
	Init();
}

CCommand_Base::~CCommand_Base()
{
	//�G�t�F�N�g.
	for (int effect = static_cast<int>(enInput_Decision::Good); effect >= 0; effect--) {
		SAFE_DELETE(m_ppCEffectBase[effect]);
	}
	SAFE_DELETE_ARRAY(m_ppCEffectBase);

	//SE�Đ��N���X.
	m_pCSEPlayManager = nullptr;

	//�O��̔���t���O.
	SAFE_DELETE_ARRAY(m_penOld_Decision);
	//��������t���O.
	SAFE_DELETE_ARRAY(m_penInput_Decision);
	//�f�v�X�X�e���V���N���X.
	if (m_pCDepth_Stencil != nullptr) {
		m_pCDepth_Stencil = nullptr;
	}
	//�X�v���C�g�N���X.
	if (m_pCSprite != nullptr) {
		m_pCSprite = nullptr;
	}
	//�ǂݍ��݊Ǘ��N���X.
	if (m_pCResourceManager != nullptr) {
		m_pCResourceManager = nullptr;
	}
}

//============================================.
//		�l�ݒ菈���֐�.
//============================================.
void CCommand_Base::SetValue(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	//�ǂݍ��݃N���X.
	m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	//�f�v�X�X�e���V���N���X.
	m_pCDepth_Stencil = CDepth_Stencil::GetDepthStencilInstance();

	m_mView			= mView;
	m_mProj			= mProj;
	m_vCameraPos	= vCamePos;

}

//===========================================.
//		�����������֐�.
//===========================================.
void CCommand_Base::Init()
{
	//��������t���O.
	m_penInput_Decision = new enInput_Decision[COMMAND_DECISION_MAX]();
	//�O��̔���.
	m_penOld_Decision = new enInput_Decision[COMMAND_DECISION_MAX]();
	//��������t���O������.
	for (int command = 0; command < COMMAND_DECISION_MAX; command++) {
		m_penInput_Decision[command] = enInput_Decision::Max;
		m_penOld_Decision[command] = enInput_Decision::Max;
	}

	//SE�Đ��N���X.
	m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();

	//�G�t�F�N�g.
	int effect_Max = static_cast<int>(enInput_Decision::Bad);
	m_ppCEffectBase = new CEffectBase*[effect_Max]();
	//�N���X�擾.
	m_ppCEffectBase[static_cast<int>(enInput_Decision::Great)]	= new CGreatEffect();
	m_ppCEffectBase[static_cast<int>(enInput_Decision::Good)]	= new CGoodEffect();
}

//===========================================.
//		�{�^���`�揈���֐�.
//===========================================.
void CCommand_Base::RenderButton()
{
	//����������.
	if (m_vPos.x == m_vPlayerPos.x) {
		m_fAlpha = ALPHA_MAX;
	}
	else {
		m_fAlpha = ALPHA_MIN;
	}

	//�摜�̗񋓑̂̃R�}���h�J�n�ԍ�.
	int m_SpriteStart = static_cast<int>(CResourceSprite::enSprite::CommandStart);


	//�{�^���ԍ��Ɖ摜�J�n�ԍ��𑫂��ĉ摜�񋓑̂Ɠ���ɂ���.
	int m_CommandSprite = m_ButtonNum + m_SpriteStart;

	//���ݍ���Ă��Ȃ��{�^���ŃG���[���N����Ȃ��悤��.
	if (m_CommandSprite >= static_cast<int>(CResourceSprite::enSprite::YButton)) {
		m_CommandSprite = static_cast<int>(CResourceSprite::enSprite::YButton);
	}

	//�N���X.
	m_pCSprite = m_pCResourceManager->GetSprite(static_cast<CResourceSprite::enSprite>(m_CommandSprite));

	//�ʒu.
	m_pCSprite->SetPosition(m_vPos);
	//���ߒl.
	m_pCSprite->SetAlpha(m_fAlpha);

	//�`��.
	m_pCSprite->Render(m_mView, m_mProj, m_vCameraPos);

	//���ɉe�����o�Ȃ��悤�ɖ߂��Ă���.
	m_pCSprite->SetAlpha(ALPHA_MAX);

}

//==================================================.
//		SE�Đ������֐�.
//==================================================.
void CCommand_Base::PlayEffectAndSE()
{
	//�G�t�F�N�g�X�V����.
	for (int effect = 0; effect < static_cast<int>(enInput_Decision::Bad); effect++) {
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->UpDate();
		}
	}

	//���育�Ƃ̉��̏���.
	for (int command = 0; command < COMMAND_DECISION_MAX; command++) {
		if (m_penInput_Decision[command] != enInput_Decision::Max) {
			
			//�O��̃R�}���h�ƈ���Ă�����炷.
			if (m_penInput_Decision[command] != m_penOld_Decision[command]) {
				//���茋��.
				const int m_Decision = static_cast<int>(m_penInput_Decision[command]);					
				//�������ԍ�.
				const int m_SoundNum = m_Decision + static_cast<int>(CSoundResource::enSoundSE::Great);	
				
				//�G�t�F�N�g�Đ�.
				if (m_Decision < static_cast<int>(enInput_Decision::Bad)) {
					m_ppCEffectBase[m_Decision]->SetCenterPos(m_vPlayerPos);
					m_ppCEffectBase[m_Decision]->SetEffectStart(true);
				}

				//SE�Đ�.
				m_pCSEPlayManager->SetSEPlayFlag(static_cast<CSoundResource::enSoundSE>(m_SoundNum), true);

				m_penOld_Decision[command] = m_penInput_Decision[command];
			}
		}
	}

}

//==================================================.
//		�G�t�F�N�g�`�揈���֐�.
//==================================================.
void CCommand_Base::RenderEffect()
{
	for (int effect = 0; effect < static_cast<int>(enInput_Decision::Bad); effect++) {
		//�`�揈���֐�.
		if (m_ppCEffectBase[effect]->GetEffectStartFlag() == true) {
			m_ppCEffectBase[effect]->Render(m_mView, m_mProj, m_vCameraPos);
		}
	}
}