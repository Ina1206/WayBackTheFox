#ifndef CCAMERA_MANAGER_H
#define CCAMERA_MANAGER_H

#include "StamderdCamera/CStanderdCamera.h"
#include "UpCamera/CUpCamera.h"
#include "CameraBoss/CBossBadCamera.h"
#include "CameraBoss/CBossGreatCamera.h"
#include "..\Command\enumCommand_Global.h"

/***************************************
*		�J�����Ǘ��N���X.
**/
class CCameraManager
{
public:
	CCameraManager();
	~CCameraManager();

	//===============�񋓑�=================//.
	//�J�����̎��.
	enum class enCamera {
		Standerd = 0,	//��{�ʒu.
		Up,				//��̈ʒu.
		Boss,			//�{�X�̎�.
	};

	//================�֐�==================//.
	void ChangeCamera();	//�J�����ύX�����֐�.
	void UpDate();			//�X�V�����֐�.

	//===========���l�������֐�=============//.
	D3DXVECTOR3 GetvPos() { return m_vPos; }
	D3DXMATRIX	GetmView() { return m_mView; }

	//===========���u�������֐�=============//.
	//���������̃J�����ړ��t���O.
	void SetLongPush(bool flag) { m_bLongPush = flag; }
	//�{�X��̎��̃J�����ړ��t���O.
	void SetChangeCamera(bool flag) { m_bChangeMove = flag; }
	//�{�X�펞�p�̃R�}���h����.
	void SetInputDecision(enInput_Decision InputDecision) { m_enInput_Decision = InputDecision; }
	//�J�����ŉf���������W.
	void SetTargetPos(D3DXVECTOR3 vTargetPos) { m_vTargetPos = vTargetPos; }
private:
	//================�֐�==================//.
	void Release();			//��������֐�.

	//================�ϐ�==================//.
	CCameraBase*		m_pCCamera;				//�J�����؂�ւ��p.
	D3DXVECTOR3			m_vPos;					//���W.
	D3DXMATRIX			m_mView;				//�r���[�s��.
	
	bool				m_bLongPush;			//�������t���O.
	bool				m_bOldLongPush;			//�������t���O����.

	enInput_Decision	m_enInput_Decision;		//�R�}���h�̔���.
	enInput_Decision	m_enOldInput_Decision;
	bool				m_bChangeMove;			//�J�����̈ړ�.

	D3DXVECTOR3			m_vTargetPos;			//�J�����ŉf���������W.
};

#endif	//#ifndef CCAMERA_MANAGER_H.