#include "CSoundResource.h"
#include <stdio.h>

/**********************************************
*	�T�E���h�ǂݍ��݃N���X.
******/
CSoundResource::CSoundResource()
	: m_hWnd		(nullptr)
	, m_ppCOneSound	(nullptr)
	, m_ppOneSoundSE(nullptr)
	, m_ppCLoopSound	(nullptr)
	, m_ppLoopSoundSE(nullptr)
{
}

CSoundResource::~CSoundResource()
{
}

//==================================.
//		�����������֐�.
//==================================.
HRESULT CSoundResource::Init(HWND hWnd)
{
	//�E�B���h�E�n���h���擾.
	m_hWnd = hWnd;

	//���I�m��.
	//�T�E���h�N���X.
	m_ppCOneSound = new clsSound*[ALL_SE_MAX]();
	//SE�̃G�C���A�X��.
	m_ppOneSoundSE = new char*[ALL_SE_MAX]();
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		m_ppOneSoundSE[sound] = new char[LENGTH_MAX]();
	}

	//������.
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		m_ppCOneSound[sound] = nullptr;
	}

	//�T�E���h�N���X.
	m_ppCLoopSound = new clsSound*[LOOP_SE_MAX]();
	//SE�̃G�C���A�X��.
	m_ppLoopSoundSE = new char*[LOOP_SE_MAX]();
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_ppLoopSoundSE[sound] = new char[LENGTH_MAX]();
		m_ppCLoopSound[sound] = nullptr;
	}

	return S_OK;
}

//==================================.
//		�ǂݍ��ݏ����֐�.
//==================================.
HRESULT CSoundResource::Load()
{
	if (FAILED(OneceLoadSE())) {
		_ASSERT_EXPR(false, L"�P��SE�̓ǂݍ��ݎ��s.");
		return E_FAIL;
	}

	if (FAILED(LoopLoadSound())) {
		_ASSERT_EXPR(false, L"���[�vSE�̓ǂݍ��ݎ��s");
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		��������֐�.
//==================================.
HRESULT CSoundResource::Release()
{
	//���[�vSE.
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		//���ꂼ��̃G�C���A�X���z����.
		SAFE_DELETE_ARRAY(m_ppLoopSoundSE[sound]);
		//���ꂼ��̃T�E���h�N���X���.
		SAFE_DELETE(m_ppCLoopSound[sound]);
	}
	//�G�C���A�X���z����.
	SAFE_DELETE_ARRAY(m_ppLoopSoundSE);
	//�T�E���h�N���X���.
	SAFE_DELETE_ARRAY(m_ppCLoopSound);

	for (int sound = 0; sound < ALL_SE_MAX; sound++) {
		//���ꂼ��̃G�C���A�X���z����.
		SAFE_DELETE_ARRAY(m_ppOneSoundSE[sound]);
		//���ꂼ��̃T�E���h�N���X���.
		SAFE_DELETE(m_ppCOneSound[sound]);
	}
	//�G�C���A�X���z����.
	SAFE_DELETE_ARRAY(m_ppOneSoundSE);
	//�T�E���h�N���X�z����.
	SAFE_DELETE_ARRAY(m_ppCOneSound);

	return S_OK;
}

//==================================.
//		�쐬�����֐�.
//==================================.
HRESULT CSoundResource::Create(int sound, const char* pfilename,
							   clsSound* pCSound, char* paliasname)
{
	//���̓ǂݍ���.
	if (FAILED(pCSound->Open(pfilename, paliasname, m_hWnd))) {
		return E_FAIL;
	}
	return S_OK;
}

//==================================.
//		���ׂ鏈���֐�.
//==================================.
HRESULT CSoundResource::Check(int sound, clsSound* pCSound)
{
	if (sound < static_cast<int>(enSoundSE::Start) || ONE_SE_MAX < sound) {
		return E_FAIL;
	}

	if (pCSound != nullptr) {
		return E_FAIL;
	}

	return S_OK;
}

//==================================.
//		�G�C���A�X���̌���.
//==================================.
void CSoundResource::AddAliasName(char* alias_name, int name)
{
	//�G�C���A�X���Ɣԍ��̌���.
	char m_Addname[256];	//�ǉ��������.
	char m_SoundName[256];	//�ǉ��O�̃G�C���A�X��.

	//�G�C���A�X���̌����R�s�[.
	strcpy_s(m_SoundName, LENGTH_MAX, alias_name);

	//�G�C���A�X���̔ԍ��ƌ��̖��O�ǉ�.
	sprintf_s(m_Addname, "%d", name % SE_RESEVE);
	strcat_s(m_SoundName, m_Addname);

	//�G�C���A�X���R�s�[.
	strcpy_s(m_ppOneSoundSE[name], sizeof(m_SoundName), m_SoundName);
}

//=================================================.
//			�P��SE�̓ǂݍ��ݏ����֐�.
//=================================================.
HRESULT CSoundResource::OneceLoadSE()
{
	//�t�@�C���p�X.
	const char m_filename[][256] =
	{
		"Data\\Sound\\SE\\Hit.mp3",				//�G�ƃv���C���[������������.
		"Data\\Sound\\SE\\EnemyFly.mp3",		//�G����Ԏ��̉�.
		"Data\\Sound\\SE\\Jump.mp3",			//�W�����v.
		"Data\\Sound\\SE\\Good.mp3",			//Great����.
		"Data\\Sound\\SE\\Great.mp3",			//Good����.
		"Data\\Sound\\SE\\Bad.mp3",				//Bad����.
		"Data\\Sound\\SE\\UpRaccoon.mp3",		//�^�k�L�o�Ă��鉹.
		"Data\\Sound\\SE\\PlayerMove.mp3",		//�v���C���[���ړ���.
		"Data\\Sound\\SE\\CowMove.mp3",			//�^�k�L���ړ�.
		"Data\\Sound\\SE\\Time.mp3",			//�^�C����.
		"Data\\Sound\\SE\\SceneChange.wav",		//�V�[���J��.
		"Data\\Sound\\SE\\ItemGet.mp3",			//�A�C�e���A�C�R���ɃA�C�e�����������̉�.
		"Data\\Sound\\SE\\Punch.mp3",			//���鎞�̓���������.
		"Data\\Sound\\SE\\Walk.mp3",			//�v���C���[�̑���.
		"Data\\Sound\\SE\\FallDown.mp3",		//�|�ꂽ�Ƃ��̉�.
		"Data\\Sound\\SE\\BossFly.mp3",			//�{�X����Ԏ��̉�.
		"Data\\Sound\\SE\\BossStar.mp3",		//�{�X�����ɂȂ鎞.
		"Data\\Sound\\SE\\ButtonPush.mp3",		//�{�^�����������Ƃ�.
		"Data\\Sound\\SE\\FaceChange.mp3",		//�\��i�K���オ�������̉�.
		"Data\\Sound\\SE\\FaceDown.mp3",		//�\��i�K�������������̉�.
		"Data\\Sound\\SE\\ButtonChange.mp3",	//�\��i�K�������������̉�.
		"Data\\Sound\\SE\\fusuma_open.mp3",		//�ӂ��܂��J����.
		"Data\\Sound\\SE\\fusuma_close.mp3",	//�ӂ��܂�߂�.
		"Data\\Sound\\SE\\Evaluation_Disp.mp3",	//�]�������\����.
		"Data\\Sound\\SE\\Char_Disp.mp3",		//�����\����.
		"Data\\Sound\\SE\\GageDown.mp3",		//�Q�[�W���鎞.
	};

	//�G�C���A�X���̌�.
	char m_Sound[][256] =
	{
		"Hit",							//�G�ƃv���C���[������������.
		"EnemyFly",						//�G����Ԏ��̉�.
		"Jump",							//�W�����v.
		"Great",						//Great����.
		"Good",							//Good����.
		"Bad",							//Bad����.
		"App",							//�o����.
		"Player_Move",					//�v���C���[���ړ���.
		"Ghost_Move",					//�^�k�L���ړ�.
		"Time",							//�^�C����.
		"SceneChange",					//�V�[���J��.
		"ItemGet",						//�A�C�e���A�C�R���ɃA�C�e�����������̉�.
		"Poko_Hit",						//���鎞�̓���������.
		"Player_Step",					//�v���C���[�̑���.
		"Fall_Down",					//�|�ꂽ�Ƃ��̉�.
		"Boss_Fly",						//�{�X����Ԏ��̉�.
		"Boss_Star",					//�{�X�����ɂȂ鎞.
		"Button_push",					//�{�^�����������Ƃ�.
		"Facial_UpChange",				//�\��i�K���オ�������̉�.
		"Facial_DownChange",			//�\��i�K�������������̉�.
		"ButtonChange",					//�A�Ń{�^���ύX��.
		"Fusuma_Open",					//�ӂ��܂��J����.
		"Fusuma_Close",					//�ӂ��܂�߂�.
		"Evaluation_Disp",				//�]�������\����.
		"Char_Disp",					//�����\����.
		"GageDown",						//�Q�[�W���鎞.
	};

	//�G�C���A�X���̌���.
	for (int name = 0; name < ALL_SE_MAX; name++) {
		AddAliasName(m_Sound[name / SE_RESEVE], name);
	}


	//�쐬�����֐�.
	for (int sound = 0; sound < ALL_SE_MAX; sound++) {

		//�͈͊O���`�F�b�N.
		if (Check(sound / SE_RESEVE, m_ppCOneSound[sound])) {
			return E_FAIL;
		}

		m_ppCOneSound[sound] = new clsSound();

		if (FAILED(Create(sound, m_filename[sound / SE_RESEVE],
				   m_ppCOneSound[sound], m_ppOneSoundSE[sound]))) {
			return E_FAIL;
		}
	}

	return S_OK;
}

//===============================================.
//		���[�vSE�̓ǂݍ��ݏ����֐�.
//===============================================.
HRESULT CSoundResource::LoopLoadSound()
{
	//�t�@�C����.
	const char filename[][256]=
	{
		"Data\\Sound\\SE\\LongPush.mp3",			//��������.
		"Data\\Sound\\BGM\\Title_Part1.mp3",		//�^�C�g��BGM.
		"Data\\Sound\\BGM\\GameMain.mp3",			//�Q�[����BGM.
		"Data\\Sound\\BGM\\BossWar.mp3",			//�{�X���BGM.
		"Data\\Sound\\BGM\\Clear_Hight.mp3",		//�N���A�DBGM.
		"Data\\Sound\\BGM\\Clear_Middle_Part1.mp3",	//�N���A��BGM.
		"Data\\Sound\\BGM\\Clear_Low.mp3",			//�N���A��BGM.
	};

	//�G�C���A�X��.
	const char alias_name[][256]=
	{
		"Long_Push",		//��������.
		"Title_BGM",		//�^�C�g��BGM.
		"GameMain_BGM",		//�Q�[����BGM.
		"Ending_BGM",		//�G���f�B���OBGM.
		"EndingHight_BGM",	//�G���f�B���O�DBGM.
		"EndingMiddle_BGM",	//�G���f�B���O��BGM.
		"EndingLow_BGM",	//�G���f�B���O��BGM.

		"TestTilte_Part2",	//�e�X�g�^�C�g��.
		"TestClear_Middle",	//�e�X�g�N���A��.

	};

	//�ǂݍ��ݏ���.
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		//�G�C���A�X��.
		strcpy_s(m_ppLoopSoundSE[sound], LENGTH_MAX, alias_name[sound]);
		m_ppCLoopSound[sound] = new clsSound();
		//�쐬�����֐�.
		if (FAILED(Create(sound, filename[sound], m_ppCLoopSound[sound], m_ppLoopSoundSE[sound]))) {
			return E_FAIL;
		}
	}

	return S_OK;
}