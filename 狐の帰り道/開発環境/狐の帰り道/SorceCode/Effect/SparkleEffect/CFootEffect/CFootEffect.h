#ifndef CFOOT_EFFECT_H
#define CFOOT_EFFECT_H

#include "..\CSparkleEffect.h"

/******************************************
*		�����ɏo��G�t�F�N�g�N���X.
****/
class CFootEffect
	: public CSparkleEffect
{
public:
	CFootEffect();
	~CFootEffect();

	//=================�萔===================//.
	const int	SPARKLE_MAX			= 10;			//�L���L���̍ő吔.
	const int	ROW_MAX				= 2;			//����̍ő吔.
	const float	CENTER_DIFFERENCIAL = 1.5f;			//���S�����ɑ΂��鍷��.
	const float	HEIGHT_WIDTH		= 0.3f;			//�����̕�.
	const float LEFT_INTERVAL		= 0.2f;			//���̕��̊Ԋu.
	const float RIGHT_INTERVAL		= 0.4f;			//�E�̕��̊Ԋu.
	const float LEFTMOST			= -0.7f;		//���[.
	const float RIGHTMOST			= 1.3f;			//�E�[.
	const int	USE_SPARKLE_MAX		= 3;			//�g�p����L���L���摜�̍ő吔.
	const float FLOWING_SPEED		= 0.02f;		//����鑬�x.


	//=================�֐�==================//.
	void Move();															//�ړ������֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`��.

private:
	//=================�֐�==================//.
	void Init();		//�����������֐�.
	void Release();		//��������֐�.

};

#endif	//#ifndef CFOOT_EFFECT_H.