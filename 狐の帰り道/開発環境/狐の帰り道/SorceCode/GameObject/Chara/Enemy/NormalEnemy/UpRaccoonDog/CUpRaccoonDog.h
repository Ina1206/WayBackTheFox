#ifndef CKAPPA_H
#define CKAPPA_H

#include "..\CNormalEnemyBase.h"
#include "..\..\..\..\..\Command\LongPushCommand\CLongPushCommand.h"

/********************************************
*		�オ��K�N���X.
**/
class CUpRaccoonDog
	: public CNormalEnemyBase
{
public:
	CUpRaccoonDog();
	~CUpRaccoonDog();
	//=====================�萔======================//.
	const int	ANIMATION_NUM		= 0;		//�A�j���[�V�����ԍ�.
	const float UP_MOVE_DISTANCE	= 10.0f;	//��ɏオ�鋗��.
	const float START_HIGH			= -1.2f;	//�����̍���.
	const float HIGH_MAX			= 0.1f;		//�����̍ő�l.
	const float UP_MOVE_SPEED		= 0.1f;		//��ɏオ�鑬�x.

	//=====================�֐�======================//.
	void InitProcess();			//�����ݒ菈���֐�.
	void Update();					//�X�V�����֐�.
	void Render();					//�`�揈���֐�.
	void Release();					//��������֐�.

private:
	//=====================�֐�======================//.
	void Move();					//�ړ������֐�.

	//=====================�ϐ�======================//.
	CDX9SkinMesh*				m_pRaccoonDog;		//�K���b�V��.
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;	//�A�j���[�V�����R���g���[��.
	bool						m_bCheckSound;		//�Đ��`�F�b�N.
	CDX9Mesh*					m_pGrassMesh;		//���̃��b�V��.
};

#endif //#ifndef CKAPPA_H.