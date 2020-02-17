#ifndef C_SE_PLAYMANAGER_H
#define C_SE_PLAYMANAGER_H

#include "CSoundResource.h"

/**************************************
*		�T�E���h�Đ��Ǘ��N���X.
**/
class CSEPlayManager
{
public:
	CSEPlayManager();
	~CSEPlayManager();

	//==================�萔==================//.
	const int ONE_SE_MAX			= static_cast<int>(CSoundResource::enSoundSE::Max);		//SE�̍ő吔.
	const int SE_RESEVE				= 10;													//SE�̕⌇.
	const int ALL_ONESE_MAX			= ONE_SE_MAX * SE_RESEVE;								//�⌇���킹��SE�̍ő吔.
	const int LOOP_SE_MAX			= static_cast<int>(CSoundResource::enLoopSound::Max);	//���[�v���̍ő吔.
	const int VOLUME_MAX			= 1000;													//�T�E���h�̍ő剹��.
	const int VOLUME_STANDERD_MAX	= 500;

	//=============�V���O���g����==============//.
	static CSEPlayManager* GetSEPlayManagerInstance()
	{
		static CSEPlayManager s_Instance;
		return &s_Instance;
	}

	//==================�֐�==================//.
	HRESULT Init(HWND hWnd);			//�����������֐�.
	void	Play();						//�Đ������֐�.
	HRESULT Release();					//��������֐�.

	//�`���u�������֐��`.
	//SE�Đ��t���O.
	void SetSEPlayFlag(CSoundResource::enSoundSE SoundSE,bool flag) { m_pbPlayOneSE[static_cast<int>(SoundSE)] = flag; }
	//LoopSE�Đ��t���O.
	void SetLoopSEPlay(CSoundResource::enLoopSound LoopSE, bool flag) { m_pbPlayLoopSE[static_cast<int>(LoopSE)] = flag;}
	//���ʒu�������֐�.
	void SetVolume(int volume) { m_SoundVolume = volume; }
	//SE�̉��ʒu�������֐�.
	void SetSE_Volume(CSoundResource::enSoundSE SoundSE, int Volume) { m_pSEVolume[static_cast<int>(SoundSE)] = Volume; }

	clsSound*	GetSound() { return m_ppCOneCSound[static_cast<int>(CSoundResource::enSoundSE::Hit)]; }
	int	GetPlaySound() { return m_PlaySound; }
private:
	clsSound**			m_ppCOneCSound;		//�T�E���h�N���X.
	clsSound**			m_ppCLoopSound;		//���[�vSE�N���X.
	CSoundResource*		m_pCSoundResource;	//�T�E���h�ǂݍ��݃N���X.

	bool*				m_pbPlayOneSE;		//���̍Đ��t���O.
	int*				m_pCnt;				//�J�E���g.

	bool*				m_pbPlayLoopSE;		//���[�v���Đ��t���O.
	int					m_PlaySound;		//�Đ�����BGM.
	int					m_SoundVolume;		//����.
	int*				m_pSEVolume;		//SE�̉���.
};

#endif	//#ifndef C_SE_PLAYMANAGER_H.