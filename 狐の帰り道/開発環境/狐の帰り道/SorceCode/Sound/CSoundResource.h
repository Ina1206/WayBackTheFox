#ifndef CSOUND_RESOURCE_H
#define CSOUND_RESOURCE_H

#include "..\Global.h"
#include "CSound.h"

/**********************************************
*	�T�E���h�ǂݍ��݃N���X.
******/
class CSoundResource
{
public:
	CSoundResource();
	~CSoundResource();

	//============�񋓑�=============//.
	//���[�v���Ȃ���.
	enum class enSoundSE {
		Hit,				//�����������̉�.
		EnemyFly,			//�G����Ԏ��̉�.
		Jump,				//�W�����v��.
		Great,				//Great���莞�̉�.
		Good,				//Good���莞�̉�.
		Bad,				//Bad���莞�̉�.
		App,				//�o����.
		Player_Move,		//�v���C���[���ړ���.
		Ghost_Move,			//�^�k�L���ړ�.
		Time,				//�^�C����.
		SceneChange,		//�V�[���J��.
		ItemGet,			//�A�C�e���A�C�R���ɃA�C�e�����������̉�.
		Poko_Hit,			//���鎞�̓���������.
		Player_Step,		//�v���C���[�̑���.
		Fall_Down,			//�|�ꂽ�Ƃ��̉�.
		Boss_Fly,			//�{�X����Ԏ��̉�.
		Boss_Star,			//�{�X�����ɂȂ鎞.
		Button_push,		//�{�^�����������Ƃ�.
		Facial_UpChange,	//�\��i�K���オ�������̉�.
		Facial_DownChange,	//�\��i�K�������������̉�.
		ButtonChage,		//�A�Ń{�^���ύX��.
		Fusuma_Open,		//�ӂ��܂��J����.
		Fusuma_Close,		//�ӂ��܂�߂�.
		Evaluation_Disp,	//�]�������\����.
		Char_Disp,			//�����\����.
		GageDown,			//�Q�[�W����.

		Max,				//�ő吔.
		Start = Hit,		//�ŏ�.
	};
	//���[�v���鉹.
	enum class enLoopSound {
		LongPush,			//���������̉�.
		TestTilte_Part2,	//�e�X�g�^�C�g��.
		GameMain_BGM,		//�Q�[����BGM.
		Boss_BGM,			//�{�X���BGM.
		EndingHight_BGM,	//�G���f�B���O�DBGM.
		EndingMiddle_BGM,	//�G���f�B���O��BGM.
		EndingLow_BGM,		//�G���f�B���O��BGM.

	
		Max,				//�ő吔.
		Start = LongPush,	//�ŏ�.
	};

	//=============�萔==============//.
	const int SE_RESEVE		= 10;											//SE�̕⌇.

	const int ONE_SE_MAX	= static_cast<int>(enSoundSE::Max);				//�P��SE�̍ő吔.
	const int LENGTH_MAX	= 256;											//�������ő吔.
	const int ALL_SE_MAX	= ONE_SE_MAX * SE_RESEVE;						//�⌇�����킹�����ׂĂ̒P��SE�̍ő吔.
	
	const int LOOP_SE_MAX	= static_cast<int>(enLoopSound::Max);			//���[�vSE�̍ő吔.

	//=============�֐�==============//.
	HRESULT Init(HWND hWnd);												//�����������֐�.
	HRESULT Load();															//�ǂݍ��ݏ����֐�.
	HRESULT Release();														//��������֐�.

	//���擾�����֐�.
	clsSound* GetOneSound(int SoundSE) { return m_ppCOneSound[SoundSE]; }	//�P��SE�N���X�l�������֐�.
	clsSound* GetLoopSound(int SoundSE) { return m_ppCLoopSound[SoundSE]; }	//���[�vSE�N���X�l�������֐�.
private:
	//=============�֐�==============//.
	HRESULT Create(int sound, const char* pfilename, 
				   clsSound* pCSound, char* paliasname);				//�쐬�����֐�.
	HRESULT Check(int sound, clsSound* pCSound);							//���ׂ鏈���֐�.
	void	AddAliasName(char* alias_name, int name);						//�G�C���A�X���̌��������֐�.												
	HRESULT	OneceLoadSE();													//�P��SE�̓ǂݍ��ݏ����֐�.
	HRESULT LoopLoadSound();												//���[�vSE�̓ǂݍ��ݏ����֐�.

	//=============�ϐ�==============//.
	HWND		m_hWnd;				//�E�B���h�E�n���h��.

	clsSound**	m_ppCOneSound;		//�T�E���h�N���X.
	char**		m_ppOneSoundSE;		//SE�̃G�C���A�X��.

	clsSound**	m_ppCLoopSound;		//���[�v�T�E���h.
	char**		m_ppLoopSoundSE;		
};

#endif	//#ifndef CSOUND_RESOURCE_H.