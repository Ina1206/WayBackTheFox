#ifndef CGOOD_EFFECT_H
#define CGOOD_EFFECT_H

#include "..\CSparkleEffect.h"

/*********************************************
*		Good����̃G�t�F�N�g.
***/
class CGoodEffect
	: public CSparkleEffect
{
public:
	CGoodEffect();
	~CGoodEffect();

	//================�萔=====================//.
	const int	SPARKLE_MAX			= 4;	//�L���L���̑����ő吔.   
	const int	ROW_MAX				= 2;	//����̃L���L���̍ő吔.
	const float	CENTER_DIFFECENCIAL = 1.0f;	//��������n�߂鍂���̍���.
	const float	HEIGHT_WIDHT		= 0.5f;	//�����̕�.
	const float	LEFT_INTERVAL		= 0.2f;	//�����̊Ԋu.
	const float RIGHT_INTERVAL		= 0.4f;	//�E���̊Ԋu.
	const float LEFT_MOST			= -0.5f;//���[.
	const float	RIGHT_MOST			= 0.9f;	//�E�[.
	const float SCALE_MAX			= 0.8f;	//�傫��.

	//================�֐�=====================//.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.
private:
	//================�֐�=====================//.
	void Init();															//�����������֐�.
	void Release();															//��������֐�.
};

#endif	//#ifndef CGOOD_EFFECT_H.