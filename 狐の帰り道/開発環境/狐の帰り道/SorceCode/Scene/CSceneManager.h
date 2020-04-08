#ifndef CSCENEMANAGER_H
#define CSCENEMANAGER_H


#include "..\MyMacro.h"						//�}�N��.
#include "..\Drawing\3D_Object\CDX9Mesh.h"	//CDX9Mesh�N���X.
#include "..\FileLoad\CFileLoadManager.h"
#include "..\Drawing\Resource\CResourceManager.h"
#include "..\Drawing\Bord_Polygon\CDepth_Stencil.h"
#include "..\Sound\CSEPlayManager.h"
#include "..\Fade\CBran.h"

#include "Load/CLoad.h"

//�R���g���[���N���X.
#include"..\Controller\CXInput.h"


//--------�V�[��---------//.
#include "CSceneBase.h"						//�V�[���x�[�X�N���X.
#include "Title\CTitle.h"					//�^�C�g���N���X.
#include "Main/CGameMain.h"					//�Q�[�����C���N���X.
#include "Clear/CClear.h"					//�N���A.

//===========�񋓑�=============//.
//�V�[���̎�ނ̗񋓑�.
enum class enScene
{
	Title = 0,			//�^�C�g��.
	GameMain,			//�Q�[����.
	Clear				//�N���A.
};					

/***********************************
*	�V�[���Ǘ��N���X.
**/
class CSceneManager
{
public:
	CSceneManager();
	~CSceneManager();

	//============�֐�==============//.
	void SceneChange();																		//�V�[���ύX�����֐�.
	void InitLoad(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);		//�ǂݍ��ݏ����֐�.
	void UpDate();																			//�X�V�����֐�.
	void Render(D3DXMATRIX& mProj, D3DXVECTOR3& vLight);									//�`�揈���֐�.
	
	//=======���擾�����֐�========//.
	bool GetLoadFinish() { return m_bLoadFinish; }
private:
	//============�萔==============//.		
	const float ALPHA_MAX		= 1.0f;	//���ߒl�ő吔.
	const int	BGM_VOLUME_MAX	= 1000;	//BGM�̉��ʍő�l.

	//============�񋓑�==============//.
	//�s������p.
	enum class enOperation
	{
		Possible = 0,		//�\.
		Impossible,			//�s�\.

		Max,				//�ő�.
		Start = Possible,	//�ŏ�.
	};

	//============�֐�==============//.		
	void SceneSetting();		//�V�[���ݒ�.
	void Destroy();				//��������֐�.
	void StageSelect();			//�X�e�[�W�I�������֐�.

	//============�ϐ�==============//.
	HWND					m_hWnd;				//�E�B���h�E�n���h��.
	ID3D11Device*			m_pDevice11;		//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;		//�f�o�C�X�R���e�L�X�g.

	CSceneBase*				m_pCScene;			//���݂̃V�[��.
	clsXInput*				m_pCInput;			//�R���g���[���N���X.
	CBran*					m_pCBran;			//�ӂ��܃N���X.

	enScene					m_enScene;			//�V�[���̎�ނ̗񋓑�.
	enOperation				m_enOperation;		//����񋓑�.
	int						m_Frame;			//�V�[���؂�ւ��p.

	int						m_BGMnum;			//BGM�̔ԍ�.
	int						m_BGM_Volume;		//BGM�̉���.

	bool					m_bLoadFinish;		//�ǂݍ��ݏI���t���O.

	int*					m_pStageTypeNum;	//�X�e�[�W�̎��.
	int						m_OldStageTypeNum;	//�O��̃X�e�[�W�ԍ�.
	int						m_StageCnt;			//�X�e�[�W�J�E���g.

	int						m_PushButtonCnt;	//�{�^���J�E���g.
	int						m_SceneChangeCnt;	//�V�[���؂�ւ����̃{�^���J�E���g.
	bool					m_bSpecialStageFlag;//���ʃX�e�[�W�t���O.
	bool					m_bControllerFlag;	//�R���g���[���t���O.
};

#endif //#ifndef CSCENEMANAGER_H.