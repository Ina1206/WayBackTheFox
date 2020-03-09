#ifndef CENEMYMANAGER_H
#define CENEMYMANAGER_H

//===========�G�̃w�b�_�[�t�@�C��=========//.
#include "NormalEnemy/Raccoon_Dog/CRaccoon_Dog.h"
#include "NormalEnemy/Kappa/CKappa.h"
#include "NormalEnemy/Cow_Ghost/CCow_Ghost.h"
#include "Boss/Big_Raccoon_Dog/CBig_Raccoon_Dog.h"

//========�A�C�e���̃w�b�_�t�@�C��=========//.
#include "..\..\Item\CItemManager.h"

//�ǂݍ��݃t�@�C��.
#include "..\..\..\FileLoad\CFileInitPos.h"
#include "..\..\..\FileLoad\CFileLoadManager.h"

//�R���g���[���N���X.
#include"..\..\..\Controller\CXInput.h"

//���C.
#include "..\..\..\Ray\CRay.h"

/***************************************************
*	�G�̊Ǘ��p�N���X.
**/
class CEnemyManager
{
public:
	CEnemyManager();
	~CEnemyManager();

	//=====================�萔=======================//.
	const float DECELERATION_DISTANCE	= 3.0f;											//�����X�^�[�g����.	
	const int	BOSS_TYPE_NUM			= static_cast<int>(enEnemy::Big_RaccoonDog);	//�{�X�̔ԍ�.
	const int	NORMAL_ENEMY_MAX		= static_cast<int>(enEnemy::NormalEnemyMax);	//�ʏ�G�̍ő吔.
	const int	ENEMY_MAX				= static_cast<int>(enEnemy::Max);				//�G�̍ő吔.
	const int	BOSS_SINGLE_NUM			= 1;											//�{�X�P�̔ԍ�.
	const int	COMMAND_DECISION_MAX	= 2;											//�R�}���h���茋�ʍő吔.
	const float	DECISION_START_WIDTH	= 0.8f;											//����J�n���̔���.
	const float	DECISION_END_BACK		= 0.5f;											//����I����player�̍��W����̉��s.

	//=====================�֐�=======================//.
	void InitProcess();																					//�����������֐�.
	void Update();																						//�X�V�����֐�.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vLight, D3DXVECTOR3& vCameraPos);	//�`�揈���֐�.
	void Release();																						//��������֐�.
	bool JudgeCameraUp();																				//�J�����̏オ�邩���菈���֐�.

	//�`�`���l�������֐��`�`.
	//�G�̍ő吔.
	int	GetEnemyMax(int enemyType) { return m_pEnemyMax[enemyType]; }
	//�G�̑����ő吔.
	int GetAllEnemySumMax() { return m_AllEnemyMax; }
	//�R�}���h�̍ő吔.
	int GetCommandMax(int enemyType) { return m_pCommandMax[enemyType]; }
	//�G�̍��W.
	D3DXVECTOR3 GetEnemyPos(int enemyType, int enemy = 0);
	//�G�̊p�x.	
	D3DXVECTOR3 GetEnemyRot(int enemyType, int enemy = 0) { return m_pCBigRaccoon_Dog->GetRotation(); }
	//�����t���O.
	bool GetDeceleration() { return m_bDecelerationStart; }			
	//�\���t���O.
	bool GetBossDispFlag() { return m_pCBigRaccoon_Dog->GetDispFlag(); }
	//�{�X�R�}���h�\���J�n�t���O.
	bool GetBossCommandDisp() { return m_pCBigRaccoon_Dog->GetCommandStart(); }
	//�R�}���h����.
	enInput_Decision GetEnemyInputDecision(int enemy, int num = 0);
	//�J�������グ��t���O.
	bool GetMoveUpCamera() { return m_bMoveUpCamera; }

	//�`�`���u�������֐��`�`.
	//�ړ����x.
	void SetSpeed(float Speed) { m_fMoveSpeed = Speed; }						
	//�ړ�����.
	void SetMovingDistance(float Distance) { m_fMovingDistance = Distance; }	
	//�R�}���h���茋��.
	void SetInputDecision(int enemy, enInput_Decision Decision) { m_penInputDecision[enemy] = Decision; }
	//�v���C���[���W.
	void SetPlayerPos(D3DXVECTOR3 vPos) { m_vPlayerPos = vPos; }	
	//�オ�鋗��.
	void SetUpDistance(float Distance) { m_fUpDistance = Distance; }	
	//�^�C�}�[.
	void SetMoveFlag(bool flag) { m_bMoveFlag = flag; }									

	//�A�C�e���̐ݒ�.
	void SetItem(int enemyType, int num, enItemJudge enJudge);
	int  GetPoint_WholeSum() { return m_Point_WholeSum; };
	int GetItem_Sum(int enItem);								//�A�C�e���̍��v.


private:
	//====================�֐�========================//.
	void NormalEnemyUpDate();					//�ʏ�G�̍X�V�����֐�.
	void BossUpDate();							//�{�X�̍X�V�����֐�.
	void Command_Possible();					//�R�}���h����\�����֐�.
	HRESULT Command_Entry();					//�R�}���h���͏����֐�.
	void CheckCommandLongPush();				//�R�}���h�������m�F�����֐�.

	//�A�C�e��.
	void ItemUpDate();							//�A�C�e���̍X�V�����֐�.
	void Point_WholeSum(int item);				//�|�C���g���v�̌v�Z�����֐�.
	void Item_WholeSum(int item);				//�A�C�e���̍��v�v�Z�����֐�.


	//===================�\����=======================//.
	//�ʏ�G�̏��.
	struct stNormalEnemyInfo {
		CNormalEnemyBase**	m_ppCEnemy;				//�G�S�̂̃N���X.
		
		//������.
		stNormalEnemyInfo()
			: m_ppCEnemy	(nullptr)
		{}
	};

	//====================�ϐ�========================//.
	//�G�֌W.
	stNormalEnemyInfo*	m_pstNormalEnemyInfo;		//�ʏ�G�̍\����.
	CNormalEnemyBase**	m_ppCNormalEnemy;			//�G�S�̂̃N���X.
	CBig_Raccoon_Dog*	m_pCBigRaccoon_Dog;			//�f�J�^�k�L�N���X.
	int*				m_pEnemyMax;				//�G�̍ő吔.
	int					m_AllNormalEnemyMax;		//�ʏ�G�̂��ׂĂ̐�.
	int					m_AllEnemyMax;				//�S�Ă̓G�̑���.
	int					m_EnemyHit;					//�ʏ�G�̓���������.

	//�R�}���h�֌W.
	int*				m_pCommandMax;				//�R�}���h�̍ő吔.
	enInput_Decision**	m_ppenInputDecision;		//�R�}���h���茋��.
	enInput_Decision*	m_penInputDecision;			//�R�}���h���茋��.
	bool*				m_pbDecisionPossible;		//����\�t���O.
	enCommandType		m_eninputInformation;		//�R�}���h�̓��͏��.
	enCommandType		m_enOldInputInformation;	//�R�}���h�̑O��̓��͏��.
	int					m_LongPushCnt;				//�{�^���𒷉������Ă���J�E���g.

	int*				m_pButtonNum;				//�{�^���ԍ�.

	//�ړ�.
	float				m_fMoveSpeed;				//�ړ����x.
	float				m_fMovingDistance;			//�ړ�����.
	float				m_fUpDistance;				//�オ�鋗��.	
	bool				m_bDecelerationStart;		//�����X�^�[�g.	
	bool				m_bMoveFlag;				//�^�C�}�[.		

	//Player.
	D3DXVECTOR3			m_vPlayerPos;				//�v���C���[���W.

	//�t�@�C��.
	CFileLoadManager*	m_pCFileManager;			//�t�@�C���ǂݍ��݊Ǘ��N���X.

	clsXInput*			m_pCInput;					//�R���g���[���N���X.

	bool				m_bMoveUpCamera;			//��ɃJ�������オ�鎞�̃t���O.

	//�A�C�e���֘A.
	CItemManager*		m_pCItemManager;			//�A�C�e���}�l�[�W���[�N���X.
	int					m_Point_WholeSum;			//�|�C���g�̑S�̍��v.
	int					m_VegetablesSum;			//��،����v.
	int					m_VegetablesPoint;			//��؃|�C���g���v.
	int					m_MeatSum;					//�������v.
	int					m_MeatPoint;				//���|�C���g���v.
	int					m_FishSum;					//�������v.
	int					m_FishPoint;				//���|�C���g���v.
	int					m_RiceSum;					//�Č����v.
	int					m_RicePoint;				//�ă|�C���g���v.
	bool				m_bCheckItem_Point;			//�A�C�e���|�C���g�̌��Z�Ɏg�p.
	bool				m_bCheckItem_Number;		//�A�C�e�����̌��Z�Ɏg�p.
	enItemJudge*		m_OldenJudge;				//�O����.


};


#endif	//#ifndef CENEMYMANAGER_H.