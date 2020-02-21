#ifndef GOURND_H
#define GOURND_H

#include "..\..\Command\enumCommand_Global.h"
#include "..\CGameObject.h"						//�Q�[���I�u�W�F�N�g.
#include "..\..\Drawing\Resource\ResourceBordPolygon\ResourceParticle\CResourceParticle.h"
/*****************************************
*	�n�ʃN���X.
**/
class CGround
	: public CGameObject
{
public:
	CGround();
	virtual ~CGround();

	//==========�萔=========//.
	const int	STAGE_MAX_BACK			= 8;			//�X�e�[�W�̉��s�̃I�u�W�F�N�g�̐�.
	const int	STAGE_MAX_HORIZON		= 3;			//�X�e�[�W�̉��̃I�u�W�F�N�g��.
	const int	CENTER_GROUND_NUM		= 1;			//�����̒n�ʂ̔ԍ�.
	const float STANDERD_ROT_Y			= 3.14f;		//�X�e�[�W��y���̌X��.
	const float STAGE_DEPTH_WIDTH		= 7.8f;			//�X�e�[�W�̉��s�̕�.
	const float GROUND_WIDTH			= 7.9f;			//�n�ʂ̉���.
	const float	GROUND_BACK_POSITION	= -15.0f;		//�n�ʂ��܂����ɖ߂�ʒu.
	const float GROUND_HIGHT_ADJUSTMENT = 0.0001f;		//�n�ʂ̍�������.
	const float STAGE_START_POS			= -4.0f;		//�X�e�[�W�J�n���̈ʒu.
	const float SET_POS					= 1.0f;			//�X�e�[�W�̈ʒu.
	const float STANDERD_SPEED			= 0.05f;		//�X�N���[���X�s�[�h.
	const float UP_LOOK_SPEED			= 0.04f;		//��ɃJ�������������̃X�N���[���X�s�[�h.
	const float SCROLL_DECELETARATION	= 0.0008f;		//�����X�s�[�h.
	const float SWING_START_ROTATION	= -3.4f;		//�h��n�߂�{�X�̊p�x.
	const float	SWING_UP_MAX			= 0.8f;			//�オ��ő吔.
	const float STANDERD_POS_HIGHT		= 0.0f;			//�n�ʂ̊�̍����ő吔.
	const float SWING_SPEED				= 0.1f;			//�h��鑬�x.
	const int	SWING_MAX				= 5;			//�h���񐔍ő吔.
	const float	SWING_REDUCE_SPEED		= 0.4f;			//�h���傫�������炷���x.
	const float SWING_REDUCE_ADJU		= 0.08f;		//�h���傫���̔�����.
	const float GOAL_DISTANCE			= 150.0f;		//�S�[���̋���.
	const float	GAET_DISP_DISTANCE		= 25.0f;		//��̕\������.

	//==========�֐�=========//.	
	void InitProcess();								//�����������֐�.
	void Update();										//�X�V�����֐�.
	void Render();										//�`�揈���֐�.
	void Release();										//��������֐�.

	//====���l�������֐�=====//.
	float GetMoveSpeed() { return m_fScroll_Speed; }
	float GetMovingDistance() { return m_fMoving_Distance; }
	float GetUpDistance() { return m_fUpDistance; }

	//====���u�������֐�=====//.
	//�J��������ɂ�����t���O.
	void SetUpCamera(bool flag) { m_bMoveCamera = flag; }
	//�X�N���[�����x�����J�n�t���O.
	void SetDeceleration_StartFlag(bool flag) { m_bDeceleration_Start = flag; };
	//�{�X�̊p�x.
	void SetBossRotation(D3DXVECTOR3 vRot) { m_vBossRot = vRot; }
	//�{�X�̔���.
	void SetBossCommand(enInput_Decision enInput) { m_enInputDecision = enInput; }
	//�Q�[�g�̍��W�ݒ�.
	void SetGatePosition(D3DXVECTOR3 vPos) { m_vInitGatePos.z = vPos.z + 5.0f; }
	

	//==========�񋓑�========//.
	//�h��̎��.
	enum class enSwingType {
		Up,			//�オ��.
		Down,		//������.
		Nothing,	//����.

		Max,		//�ő吔.
		Start = Up,	//�ŏ�.
	};
private:
	//===========�֐�=========//.
	void Move();										//�ړ������֐�.
	void ScrollSpeedDeceleration();					//�X�N���[���X�s�[�h�̌��������֐�.
	void Swing();										//�h��鏈���֐�.

	//=========�N���X========//.
	CDX9Mesh**		m_ppGround;							//CDX9Mesh�N���X.
	CDX9Mesh*		m_pCGate;							//������CDX9Mesh�N���X.
	CDepth_Stencil	m_CDepth_Stencil;					//�f�v�X�X�e���V��.

	//===========�ϐ�===========//.
	D3DXVECTOR3*		m_pvPos;							//���W.
	float				m_fScroll_Speed;					//�X�N���[�����x.
	bool				m_bDeceleration_Start;				//�X�N���[�����x�����J�n.
	bool				m_bMoveCamera;						//�J���������������̃t���O.
	float				m_fMoving_Distance;					//�ړ�����.
	int					m_BackCnt;							//���ɖ߂����J�E���g.
	int					m_BackNum;							//��Ԍ��̔ԍ�.
	float				m_fSwingUpMax;						//�h��̍ő吔.

	D3DXVECTOR3			m_vBossRot;							//�{�X�̊p�x.
	enSwingType			m_enSwingType;						//�h��̎��.
	float				m_fUpDistance;						//��ɏオ��
	int					m_SwingCount;						//�h���J�E���g.
	enInput_Decision	m_enInputDecision;					//�R�}���h����.


	D3DXVECTOR3			m_vGatePos;							//�Q�[�g�̍��W.
	D3DXVECTOR3			m_vInitGatePos;						//�����Q�[�g���W.
};

#endif	//#ifndef GOURND_H.