#ifndef _CHIT_EFFECT_H
#define _CHIT_EFFECT_H

#include "..\CEffectBase.h"

/**********************************************
*		�����������̃G�t�F�N�g.
**/
class CHitEffect 
	: public CEffectBase
{
public:
	CHitEffect();
	~CHitEffect();

	//================�萔======================//.
	const int	DISP_EFFECT_MAX		= 2;		//�\���G�t�F�N�g�ő吔.
	const float BASIC_DIFFERENCIAL	= 0.5f;		//�\����{x������.
	const float BASIC_BLANK_WIDTH	= 1.0f;		//��{�󔒕�.
	const float ADD_HIGHT			= 0.8f;		//���Z����鍂��.
	const float START_ROTAITON		= 3.5f;		//���߂̊p�x.
	const float MOVING_DISTANCE_MAX = 0.1f;		//�ړ������ő吔.
	const float MOVING_SPEED		= 0.02f;	//�ړ����x.
	const float BASE_SCALE			= 0.65f;	//��{�̑傫��.

	//===============�񋓑�=====================//.
	enum class enMoveType {
		Right = 0,	//�E. 
		Left,		//��.

		Nothing,	//����.
	};

	//================�֐�======================//.
	void Update();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.

	//�`���擾�����֐��`.
	//�傫���ύX�����֐�.
	void SetEffectScale(float Scale); 
private:
	//================�֐�======================//.
	void Init();			//�����������֐�.
	void Release();			//��������֐�.
	void Move(int sprite);	//�ړ������֐�.

	//================�ϐ�=====================//.
	float		m_fMoving_Distance;	//�ړ�����.
	enMoveType	m_enMoveType;		//�ړ����.
	D3DXVECTOR3 m_vInitPos;			//�͂��߂̍��W.

};

#endif	//#ifndef _CHIT_EFFECT_H.