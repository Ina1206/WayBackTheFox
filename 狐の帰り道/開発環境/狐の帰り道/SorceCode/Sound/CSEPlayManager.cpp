#include "CSEPlayManager.h"

/**************************************
*		�T�E���h�Đ��Ǘ��N���X.
**/
CSEPlayManager::CSEPlayManager()
	: m_ppCOneCSound	(nullptr)
	, m_ppCLoopSound	(nullptr)
	, m_pCSoundResource	(nullptr)
	, m_pbPlayOneSE		(nullptr)
	, m_pCnt			(nullptr)
	, m_pbPlayLoopSE	(nullptr)
	, m_PlaySound		(0)
	, m_SoundVolume		(VOLUME_STANDERD_MAX)
	, m_pSEVolume		(nullptr)
{
}

CSEPlayManager::~CSEPlayManager()
{
}

//=======================================.
//		�����������֐�.
//=======================================.
HRESULT CSEPlayManager::Init(HWND hWnd)
{
	//�T�E���h�ǂݍ��݃N���X.
	m_pCSoundResource = new CSoundResource();
	//�����������֐�.
	m_pCSoundResource->Init(hWnd);
	//�ǂݍ��ݏ����֐�.
	m_pCSoundResource->Load();

	//�T�E���h�N���X.
	m_ppCOneCSound = new clsSound*[ALL_ONESE_MAX]();
	m_ppCLoopSound = new clsSound*[LOOP_SE_MAX]();
	//���ꂼ��̃T�E���h�擾.
	for (int sound = 0; sound < ALL_ONESE_MAX; sound++) {
		m_ppCOneCSound[sound] = m_pCSoundResource->GetOneSound(sound);
	}
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_ppCLoopSound[sound] = m_pCSoundResource->GetLoopSound(sound);
	}

	//�Đ��t���O�̔z�񓮓I�m��.
	m_pbPlayOneSE = new bool[ONE_SE_MAX]();
	//SE�̉��ʂ̔z�񓮓I�m��.
	m_pSEVolume = new int[ONE_SE_MAX]();

	//�J�E���g�̔z�񓮓I�m��.
	m_pCnt = new int[ONE_SE_MAX]();
	//�P��SE�Ŏg���ϐ��̏�����.
	for (int sound = 0; sound < ONE_SE_MAX ; sound++) {
		m_pbPlayOneSE[sound] = false;
		m_pSEVolume[sound] = VOLUME_STANDERD_MAX;
		if (sound >= static_cast<int>(CSoundResource::enSoundSE::Great) &&
			sound <= static_cast<int>(CSoundResource::enSoundSE::Bad)) {
			m_pSEVolume[sound] = VOLUME_MAX;
		}
	}

	//���[�v�Đ��t���O�̔z�񓮓I�m��.
	m_pbPlayLoopSE = new bool[LOOP_SE_MAX]();
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_pbPlayLoopSE[sound] = false;
	}

	return S_OK;
}

//=======================================.
//		�Đ������֐�.
//=======================================.
void CSEPlayManager::Play()
{
	//�P��SE�̍Đ�.
	for (int sound = 0; sound < ONE_SE_MAX; sound++) {
		if (m_pbPlayOneSE[sound] == true) {
			if (m_ppCOneCSound[(sound * SE_RESEVE) + m_pCnt[sound]]->IsStopped() == true) {
				//���߂ɖ߂�.
				m_ppCOneCSound[(sound * SE_RESEVE) + m_pCnt[sound]]->SeekToStart();
				//���ʒ���.
				m_ppCOneCSound[(sound * SE_RESEVE) + m_pCnt[sound]]->VolumeConvert(m_pSEVolume[sound]);
				//�Đ�.
				m_ppCOneCSound[(sound * SE_RESEVE) + m_pCnt[sound]]->Play();
				//�t���O������.
				m_pbPlayOneSE[sound] = false;
			}

			//����SE��.
			m_pCnt[sound]++;
			if (m_pCnt[sound] >= SE_RESEVE) {
				m_pCnt[sound] = 0;
			}
		}
	}

	//���[�vSE�̍Đ�.
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		if (m_pbPlayLoopSE[sound] == true) {
			if (m_ppCLoopSound[sound]->IsStopped() == true) {
				//���߂ɖ߂�.
				m_ppCLoopSound[sound]->SeekToStart();
				//�Đ�.
				m_ppCLoopSound[sound]->Play();

				m_PlaySound = sound;
			}
			//���ʒ���.
			m_ppCLoopSound[sound]->VolumeConvert(m_SoundVolume);
		}
		else {
			if (m_ppCLoopSound[sound]->IsPlaying() == true) {
				m_ppCLoopSound[sound]->Stop();
			}
		}
	}

}

//========================================.
//		��������֐�.
//========================================.
HRESULT CSEPlayManager::Release()
{
	//�z����.
	SAFE_DELETE_ARRAY(m_pSEVolume);
	SAFE_DELETE_ARRAY(m_pbPlayLoopSE);
	SAFE_DELETE_ARRAY(m_pCnt);
	SAFE_DELETE_ARRAY(m_pbPlayOneSE);

	//��������֐�.
	m_pCSoundResource->Release();
	//�T�E���h�ǂݍ��݃N���X���.
	SAFE_DELETE(m_pCSoundResource);

	//���[�v�T�E���h�N���X.
	for (int sound = 0; sound < LOOP_SE_MAX; sound++) {
		m_ppCLoopSound[sound] = nullptr;
	}
	//���[�v�T�E���h�N���X�̔z��������.
	SAFE_DELETE_ARRAY(m_ppCLoopSound);

	for (int sound = 0; sound < ALL_ONESE_MAX; sound++) {
		m_ppCOneCSound[sound] = nullptr;
	}
	//�T�E���h�N���X�̔z����.
	SAFE_DELETE_ARRAY(m_ppCOneCSound);

	return S_OK;
}