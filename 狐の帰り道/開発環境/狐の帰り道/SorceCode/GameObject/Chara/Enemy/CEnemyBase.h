#ifndef CENEMY_BASE_H
#define CENEMY_BASE_H

#include "..\..\Chara\CChara.h"
#include "..\..\..\Command\enumCommand_Global.h"
#include "..\..\..\Sound\CSEPlayManager.h"
#include "..\..\..\Command\CCommand_Base.h"

/*****************************************
*	�G�̌��N���X.
**/
class CEnemyBase
	: public CChara
{
public:
	CEnemyBase();
	virtual ~CEnemyBase();
	//================�萔=====================//.
	const float	DISP_DISTANCE			= 50.0f;	//�\������͈�.
	const float	ANIM_SPEED				= 0.02f;	//�A�j���[�V�������x.

	//================�֐�=====================//.
	void  FitMoveGround();				//�O���E���h�̓����ɍ��킹�鏈���֐�.
	void  DecisionDisp();				//�\�����菈���֐�.


	//�`���l�������֐��`.
	D3DXVECTOR3			GetPostion()	{ return m_vPos; }												//�ʒu�l������.			//Boss.
	bool				GetDispFlag()		{ return m_bDispFlag; }											//�\���t���O�l������.

	//�`���u�������֐��`.
	void SetInitPosition	(D3DXVECTOR3 vPos)							{ m_vInitPos = vPos; }					//�����ʒu.
	void SetPlayerPos		(D3DXVECTOR3 vPlayerPos)					{ m_vPlayerPos = vPlayerPos; }			//�v���C���[���W.
	void SetSpeed			(float Speed)								{ m_fSpeed = Speed; }					//�n�ʂ̃X�N���[�����x.
	void SetCommandType		(enCommandType enType)						{ m_enCommandType = enType; }			//���̓{�^�����.
	void SetJudgePossible	(bool JudgePossible)						{ m_bJudgePossible = JudgePossible; }	//����\�t���O.
	void SetLongPushCnt		(int LongPush)								{ m_LongPushCnt = LongPush; }			//�������J�E���g.
	
protected:
	
	D3DXVECTOR3			m_vPos;				//�ʒu���W.
	D3DXVECTOR3			m_vInitPos;			//�����ʒu.
	D3DXVECTOR3			m_vPlayerPos;		//�v���C���[�̍��W.
	D3DXVECTOR3			m_vRot;				//�X��.

	float				m_fSpeed;			//�ړ����x.

	CCommand_Base*		m_pCCommand_Base;	//�R�}���h���N���X.
	enCommandType		m_enCommandType;	//���̓{�^�����.
	bool				m_bJudgePossible;	//�R�}���h����\�t���O.
	int					m_LongPushCnt;		//�������J�E���g.

	bool				m_bDispFlag;		//�\���t���O.

	CSEPlayManager*		m_pCSEPlayManager;	//SE�Đ��Ǘ��N���X.

private:
};

#endif	//#ifndef CENEMY_BASE_H.