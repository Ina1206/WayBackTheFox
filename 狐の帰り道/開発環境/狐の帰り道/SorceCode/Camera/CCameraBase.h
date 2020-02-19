#ifndef CCAMERABASE_H
#define CCAMERABASE_H

#include "..\Drawing\3D_Object\CDX9Mesh.h"
#include "..\Global.h"

/*********************************************
*		�J�������N���X.
**/
class CCameraBase
{
public:
	CCameraBase();
	virtual ~CCameraBase();

	//================�萔====================//.
	//�`�J�����̍��W�`.
	const D3DXVECTOR3	STANDERD_CAMERA_POS		= D3DXVECTOR3(0.0f, 2.5f, 0.0f);					//�Q�[����ł̃J�����ʒu.
	const D3DXVECTOR3	UP_CAMERA_POS			= D3DXVECTOR3(0.0f, 6.0f, 3.5f);					//�J��������ɗ������̃J�����ʒu.
	const D3DXVECTOR3	BAD_BOSS_CAMERA_POS		= D3DXVECTOR3(0.0f, 1.0f, -1.5f);					//�{�X�̎��̃J�����ʒu.
	//�`�����_�`.
	const D3DXVECTOR3	CAMERA_LOOK				= D3DXVECTOR3(0.0f, 1.0f, 6.0f);					//�����_.
	const D3DXVECTOR3	UP_CAMERA_LOOK			= D3DXVECTOR3(0.0f, 1.0f, 5.2f);					//�J��������ɗ������̒����_.
	const D3DXVECTOR3	BOSS_CAMERA_LOOK		= D3DXVECTOR3(0.0f, 1.0f, 5.0f);					//�{�X�̎��̒����_.
	//�`�ړ��`.
	const float			MOVE_SPEED				= 0.08f;											//�S�̊�ړ����x.
	const float			UP_ORIGINARU_NUM		= UP_CAMERA_POS.y - STANDERD_CAMERA_POS.y;			//��ɏオ��Ƃ��̊����̌��̐�.
	const float			UP_RATIO_Z				= UP_CAMERA_POS.z / (UP_ORIGINARU_NUM);				//�オ��Ƃ���Z���̊���.
	const float			UP_RATIO_LOOK			= UP_CAMERA_LOOK.z / (UP_ORIGINARU_NUM);			//��ɏオ��Ƃɂ̒����_�̊���.
	const float			BAD_BOSS_ORIGINARU_NUM	= BAD_BOSS_CAMERA_POS.y - STANDERD_CAMERA_POS.y ;	//�{�X��̎��̊����̌��̐�.
	const float			BAD_BOSS_RATIO_Z		= BAD_BOSS_CAMERA_POS.z / (BAD_BOSS_ORIGINARU_NUM);	//�{�X��̎���Z���̊���.
	const float			BAD_BOSS_RATIO_LOOK		= BOSS_CAMERA_LOOK.z / (BAD_BOSS_ORIGINARU_NUM);	//�{�X��̎��̒����_�̊���.
	//�`�r���[�`.
	const D3DXVECTOR3	UP_VECTOR				= D3DXVECTOR3(0.0f, 1.0f, 0.0f);					//����x�N�g��.


	//================�֐�====================//.
	void ChangeView();													//�r���[�ϊ������֐�.
	virtual void Update(bool CameraFlag) = 0;							//�X�V�����֐�.

	//===========���擾�����֐�==============//.
	D3DXVECTOR3 GetCameraPos() { return m_Camera.vPos; }				//�J�������W.
	D3DXMATRIX	GetMatrixView() { return m_mView; }					//�r���[�s��.
	bool		GetCameraChangeFlag() { return m_CameraChangeFlag; }	//�J������ޕύX�t���O.
	
	//===========���u�������֐�==============//.
	void SetTargetPos(D3DXVECTOR3 vPos) { m_vTargetPos = vPos; }		//����̍��W.
protected:
	//================�֐�====================//.
	virtual void Move() = 0;											//�ړ������֐�.

	//================�ϐ�====================//.
	CAMERA					m_Camera;									//�J�������.
	D3DXMATRIX				m_mView;									//�r���[�s��.
	bool					m_CameraChangeFlag;							//�J�����̎�ޕύX�t���O.

	D3DXVECTOR3				m_vTargetPos;								//�J�����ŉf����������̍��W.
private:
};

#endif //#ifndef CCAMERABASE_H.