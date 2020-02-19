#ifndef CRACCOON_DOG_H
#define CRACCOON_DOG_H

#include "..\CNormalEnemyBase.h"
#include "..\..\..\..\..\Command\TimingCommand\CTimingCommand.h"


/****************************************
*	�^�k�L�N���X.
**/
class CRaccoon_Dog
	: public CNormalEnemyBase
{
public:
	//================�萔==================//.
	const float			SCALE_MAX		= 0.02f;					//�傫��.
	const float			MOVE_SPEED		= 0.05f;					//�ړ����x.
	const D3DXVECTOR2	FLY_SPEED		= D3DXVECTOR2(0.1f, 0.09f);	//��ԑ��x.
	const float			COMMAND_DISP_H	= 1.5f;						//�R�}���h�\������.
	const float			SHADOW_UP_LIMIT = 2.5f;						//�e�̕\������l.

	CRaccoon_Dog();
	~CRaccoon_Dog();

	//================�֐�==================//.
	void InitProcess();	//�����ݒ菈���֐�.
	void Update();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.
	void Release();			//��������֐�.

private:
	//================�֐�==================//.
	void Move();			//�ړ������֐�.

	//===============�񋓑�=================//.
	//�A�j���[�V�����̎��.
	enum class enAnimType {
		Hit = 0,		//�U���󂯂��Ƃ�.
		Run,			//����.
		Nothing,		//�Ȃ�.

		Max,			//�ő�l.
		Start = Hit,	//�ŏ��l.
	};

	//================�ϐ�==================//.
	CDX9SkinMesh*				m_pRacconAnim;			//�^�k�L.
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;		//�A�j���[�V�����R���g���[��.
	bool						m_bOldHit;				//�O��̃q�b�g�t���O.
	CSEPlayManager*				m_pCSEHit;				//��������SE.
	CTimingCommand*				m_pCTimingCommand;		//�^�C�~���O
};

#endif	//#ifndef CRACCOON_DOG_H.