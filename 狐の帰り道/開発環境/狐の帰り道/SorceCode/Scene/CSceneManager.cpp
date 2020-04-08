#include "CSceneManager.h"

#include <crtdbg.h>

CSceneManager::CSceneManager()
	: m_hWnd				(nullptr)
	, m_pDevice11			(nullptr)
	, m_pContext11			(nullptr)
	, m_pCScene				(nullptr)
	, m_pCInput				(nullptr)
	, m_pCBran				(nullptr)
	, m_enScene				(enScene::Title)
	, m_enOperation			(enOperation::Possible)
	, m_Frame				(0)
	, m_BGMnum				()
	, m_BGM_Volume			(BGM_VOLUME_MAX)
	, m_bLoadFinish			(false)
	, m_pStageTypeNum		(nullptr)
	, m_OldStageTypeNum		(-1)
	, m_StageCnt			(0)
	, m_PushButtonCnt		(0)
	, m_SceneChangeCnt		(0)
	, m_bSpecialStageFlag	(false)
{
	m_pCInput	= new clsXInput();
	m_pCBran	= new CBran();
}

CSceneManager::~CSceneManager()
{
	Destroy();
}

//=======================================.
//		�V�[���ݒ菈���֐�.
//=======================================.
void CSceneManager::SceneChange()
{
	m_pCInput->UpdateStatus();//�������Ȃ��Ɠ����Ȃ�.

	//�J���Ĉ�ԏ��߂̃V�[��.
	if (m_pCScene == nullptr) {
		//�N���X�쐬.
		m_pCScene = new CTitle();
		m_pCScene->Init_Process();

		//�Đ�.
		CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
		m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::TestTilte_Part2, true);
	}

	//A�{�^���������ꑱ�����Ƃ��ɐi�ނ̂�h������.
	if ((m_pCInput->IsPress(XINPUT_GAMEPAD_A)) || 
		(GetAsyncKeyState(VK_RETURN) & 0x8000) ||
		(GetAsyncKeyState(VK_SPACE) & 0x8000)) {
		m_SceneChangeCnt++;
	}
	else {
		m_SceneChangeCnt = 0;
	}

	//����\�̎�.
	if (m_enOperation == enOperation::Possible) {
		if (m_enScene != enScene::GameMain)
		{
			//�^�C�g���̃t�F�[�h���I�������.
			if (m_pCScene->GetUIDrawEndFlag() == true)
			{
				if (((m_pCInput->IsPress(XINPUT_GAMEPAD_A)) 
					|| (GetAsyncKeyState(VK_RETURN) & 0x8000)
					|| (GetAsyncKeyState(VK_SPACE) & 0x8000))
					&& m_SceneChangeCnt == 1)
				{
					//�ēx����.
					if (m_PushButtonCnt == 0) {
						if (m_enOperation == enOperation::Possible)
						{
							m_enOperation = enOperation::Impossible;
						}
						//���̃V�[����.
						m_pCBran->SetBran_Open();

						if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
							m_bSpecialStageFlag = true;
						}

						CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
						m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::SceneChange, true);
					}
				}
				else {
					m_PushButtonCnt = 0;
				}
			}
			else
			{
				//�t�F�[�h���I���O��A�{�^���������ꂽ��.
				if ((m_pCInput->IsPress(XINPUT_GAMEPAD_A))
					 || (GetAsyncKeyState(VK_RETURN) & 0x8000)
					|| GetAsyncKeyState(VK_SPACE) & 0x8000)
				{
					m_PushButtonCnt++;
				}
			}
		}

		//GameMain�̎�.
		if (m_enScene == enScene::GameMain && m_pCScene->GetEndGameMain() == true)
		{
			if (m_enOperation == enOperation::Possible)
			{
				m_enOperation = enOperation::Impossible;
			}
			//���̃V�[����.
			if (m_Frame == 0)
			{
				m_pCBran->SetBran_Open();
			}
			m_Frame++;
		}
		else
		{
			m_Frame = 0;
		}
	}
	//�V�[����؂�ւ���.
	SceneSetting();

	//�t�F�[�h�A�E�g���I���Α���\�ɂ���.
	if (m_pCBran->GetBran_CloseFlag() == true && m_pCBran->GetBran_OpenFlag() == true)
	{
		m_enOperation = enOperation::Possible;
	}
	else {
		m_enOperation = enOperation::Impossible;
	}

	//���ӂ��܂̊֐���Open,Close�t�ɂȂ��Ă���.
	g_BranOpenFlag = m_pCBran->GetBran_CloseFlag();

#ifdef _DEBUG
	if (m_enScene != enScene::GameMain) {
		if (m_pCScene->GetUIDrawEndFlag() == true && GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//���̃V�[����.
			m_pCBran->SetBran_Open();
			CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::SceneChange, true);
		}
}
	else {
		if (GetAsyncKeyState(VK_RETURN) & 0x0001) {
			//���̃V�[����.
			m_pCBran->SetBran_Open();
			CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
			m_pCSEPlayManager->SetSEPlayFlag(CSoundResource::enSoundSE::SceneChange, true);
		}
	}
#endif	//#ifdef _DEBUG.
}

//=======================================.
//		�V�[���ύX�����֐�.
//=======================================.
void CSceneManager::SceneSetting()
{
	if (m_pCBran->GetBran_OpenEnd() == true)
	{
		//�������.
		if (m_pCScene != nullptr) {
			SAFE_DELETE(m_pCScene);
		}

		//�T�E���h.
		CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
		//�t�@�C��.
		CFileLoadManager* m_pCFielLoadManager = CFileLoadManager::GetCFileLoadManagerInstance();

		//���̃V�[���ݒ�.
		switch (m_enScene) {
		//�^�C�g��.
		case enScene::Title:
			m_enScene = enScene::GameMain;
			m_pCScene = new CGameMain();

			//�X�e�[�W�ԍ��̎w��.
			{
				const int NormalStageMax = m_pCFielLoadManager->GetFileMax() - 1;
				if (m_StageCnt >= NormalStageMax) {
					//�X�e�[�W�I�������֐�.
					StageSelect();
					m_StageCnt = 0;
				}

				//���ʃX�e�[�W�ԍ��ݒ�.
				if (m_bSpecialStageFlag == true) {
					const int SpecialStageNum = 3;	//���ʃX�e�[�W�ԍ�.
					m_StageCnt = SpecialStageNum;
				}
			}

			m_pCFielLoadManager->SetFileNum(m_pStageTypeNum[m_StageCnt]);
			m_OldStageTypeNum = m_pStageTypeNum[m_StageCnt];

			m_StageCnt++;

			m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::TestTilte_Part2, false);
			m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::GameMain_BGM, true);
			break;
		//�Q�[����.
		case enScene::GameMain:
			m_enScene = enScene::Clear;
			m_pCScene = new CClear();
			m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::Boss_BGM, false);
			break;
		//�N���A.
		case enScene::Clear:
			m_enScene = enScene::Title;
			m_pCScene = new CTitle();
			m_pCSEPlayManager->SetLoopSEPlay(static_cast<CSoundResource::enLoopSound>(m_pCSEPlayManager->GetPlaySound()), false);
			m_pCSEPlayManager->SetLoopSEPlay(CSoundResource::enLoopSound::TestTilte_Part2, true);
			break;
		}

		//����������.
		if (m_pCScene != nullptr) {
			m_pCScene->Init_Process();
		}

		m_pCBran->SetBran_Close();
	}
}

//========================================.
//		�ǂݍ��ݏ����֐�.
//========================================.
void CSceneManager::InitLoad(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11)
{
	m_hWnd		= hWnd;
	m_pDevice11	= pDevice11;
	m_pContext11 = pContext11;

	//�t�@�C���ǂݍ��݃N���X.
	CFileLoadManager* m_pCFileLoadManager = CFileLoadManager::GetCFileLoadManagerInstance();
	m_pCFileLoadManager->ALL_Setting();
	//�X�e�[�W�̍ő吔.
	m_pStageTypeNum = new int[m_pCFileLoadManager->GetFileMax()]();
	for (int stage = 0; stage < m_pCFileLoadManager->GetFileMax(); stage++) {
		m_pStageTypeNum[stage] = stage;
	}

	//�ǂݍ��݃N���X.
	CResourceManager* m_pCResourceManager = CResourceManager::GetResourceManagerInstance();
	m_pCResourceManager->Load(m_hWnd, pDevice9, m_pDevice11, m_pContext11);

	//�f�v�X�X�e���V���N���X.
	CDepth_Stencil* m_pCDepthStencil = CDepth_Stencil::GetDepthStencilInstance();
	m_pCDepthStencil->Init(m_pDevice11, m_pContext11);

	//�T�E���h�N���X.
	CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
	m_pCSEPlayManager->Init(m_hWnd);

	m_pCBran->Init();

	//�ǂݍ��ݏI��.
	m_bLoadFinish = true;
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CSceneManager::UpDate()
{
	m_pCBran->UpDate();
	m_pCScene->UpDate();

	//�T�E���h�n��.
	CSEPlayManager* m_pCSEPlayManager = CSEPlayManager::GetSEPlayManagerInstance();
	//�T�E���h�Đ�.
	m_pCSEPlayManager->Play();
	//�T�E���h����.
	m_pCSEPlayManager->SetVolume(m_BGM_Volume);

	//�I��.
	if (GetAsyncKeyState(VK_F1) & 0x8000) {
		PostQuitMessage(0);
	}
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CSceneManager::Render(D3DXMATRIX& mProj, D3DXVECTOR3& vLight)
{
	m_pCScene->Value(mProj, vLight);
	m_pCScene->Render();
	m_pCBran->Render();
}

//========================================.
//		��������֐�.
//========================================.
void CSceneManager::Destroy()
{
	//�T�E���h�N���X.
	CSEPlayManager::GetSEPlayManagerInstance()->Release();

	//�ǂݍ��݃N���X.
	CResourceManager::GetResourceManagerInstance()->Release();			

	SAFE_DELETE(m_pCBran);
	SAFE_DELETE(m_pCInput);
	//�V�[��.
	SAFE_DELETE(m_pCScene);

	//�z����.
	SAFE_DELETE_ARRAY(m_pStageTypeNum);

	m_pContext11	= nullptr;
	m_pDevice11		= nullptr;
	m_hWnd			= nullptr;
}

//==============================================.
//		�X�e�[�W�I�������֐�.
//==============================================.
void CSceneManager::StageSelect()
{
	//�X�e�[�W�̍ő吔�擾.
	int stageMax = CFileLoadManager::GetCFileLoadManagerInstance()->GetFileMax();

	//�����_���̃X�e�[�W�̏d��������邽��.
	for (;;) {
		while (stageMax > 1)
		{
			int stageNum = rand() % stageMax;
			stageMax--;

			int StageType = m_pStageTypeNum[stageMax];
			m_pStageTypeNum[stageMax] = m_pStageTypeNum[stageNum];
			m_pStageTypeNum[stageNum] = StageType;
		}
		//���̃X�e�[�W�ԍ��ƈ�v���Ȃ��Əo�Ȃ�.
		if (m_pStageTypeNum[0] != m_OldStageTypeNum) {
			break;
		}
		//�X�e�[�W�ő吔�̒l������.
		stageMax = CFileLoadManager::GetCFileLoadManagerInstance()->GetFileMax();
	}
}