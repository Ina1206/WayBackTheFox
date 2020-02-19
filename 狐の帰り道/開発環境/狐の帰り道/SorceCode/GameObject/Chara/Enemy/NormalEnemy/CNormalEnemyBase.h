#ifndef CNORMAL_ENEMY_BASE_H
#define CNORMAL_ENEMY_BASE_H

#include "..\CEnemyBase.h"

/******************************************
*		�ʏ�G�̌��N���X.
*********/
class CNormalEnemyBase
	: public CEnemyBase
{
public:
	CNormalEnemyBase();
	~CNormalEnemyBase();

	//================�萔=====================//.
	const float			LEFT_JUMP_ROT			= 0.6f;							//���ɔ�Ԏ��̌X��.		
	const float			RIGHT_JUMP_ROT			= -0.9f;						//�E�ɔ�Ԏ��̌X��.
	const int			STANDERD_USE_COMMAND	= 0;							//��Ŏg���R�}���h�ԍ�.
	const int			DECISION_MAX			= 2;							//���茋�ʂ̍ő吔.
	const int			LEFT_DIRECTION			= -1;							//�������ԍ�.
	const int			RIGHT_DIRECTION			= 1;							//�E�����ԍ�.
	const float			ROT_SPEED				= 0.1f;							//�X�����x.
	const D3DXVECTOR2	FLY_SPEED				= D3DXVECTOR2(0.1f, 0.15f);		//��ԑ��x.

	//===============�񋓑�=====================//.
	//��ԕ���.
	enum class enFlyDirection {
		Left,	//��.
		Right,	//�E.
	};

	//================�֐�======================//.
	void FlyJudge();	//��Ԕ��菈���֐�.
	void FlyMove();		//���ł����ړ������֐�.

	//�`���l�������֐��`.
	int					GetHitNum()						{ return m_HitNum; }									//���������񐔊l������.	
	enInput_Decision	GetInputDecision(int num = 0)	{ return m_pCCommand_Base->GetInputDeision(num); }		//�R�}���h���茋��.


	//�`���u�������֐��`.
	void SetHitNum		(int Num)		{ m_HitNum = Num; }				//���������ԍ�.		
	void SetButtonNum	(int ButtonNum)	{ m_ButtonNum = ButtonNum; }	//�{�^���ԍ�.

	void SetInputDecision(enInput_Decision enDecision, int num = 0) { m_enInputDecision[num] = enDecision; }//�R�}���h���茋��.

protected:

	//===============�ϐ�==================//.
	int					m_HitNum;			//����������.		
	int					m_HitMoveDirection;	//�����������̈ړ�����.
	bool				m_HitFlag;			//���������t���O.		
	int					m_ButtonNum;		//�{�^���ԍ�.
	enInput_Decision*	m_enInputDecision;	//���茋��.


	CEnemyFlyEffect* m_pCEnemyFlyEffect;	//���ōs���G�t�F�N�g�N���X.
private:

};

#endif	//#ifndef CNORMAL_ENEMY_BASE_H.