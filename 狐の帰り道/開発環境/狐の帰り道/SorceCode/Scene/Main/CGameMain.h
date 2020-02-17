#ifndef CGAME_MAIN_H
#define CGAME_MAIN_H

#include "..\CSceneBase.h"

#include "..\..\BackGround\CBackGround.h"

//�L�����N�^�֌W.
#include "..\..\GameObject\Chara\Player\CPlayer.h"
#include "..\..\GameObject\Chara\Enemy\CEnemyManager.h"
#include "..\..\GameObject\Chara\Enemy\Boss\Big_Raccoon_Dog\CBig_Raccoon_Dog.h"
#include "..\..\GameObject\Ground\CGround.h"

#include "..\..\Camera\StamderdCamera\CStanderdCamera.h"
#include "..\..\Camera\CCameraManager.h"
//�A�C�e��.
#include "..\..\GameObject\Item\CItemManager.h"
//�����蔻��.
#include "..\..\GameObject/Collider_Detection/CCollision_Detection.h"
#include "..\..\GameObject\Collider_Detection\CDebugCollisionSphere.h"


//UI.
#include "..\..\GameObject\UI\CMainUIManager.h"


//�T�E���h.
#include "..\..\Sound\CSEPlayManager.h"

/*************************************
*	�Q�[�����C���N���X.
**/
class CGameMain
	: public CSceneBase
{
public:
	CGameMain();
	~CGameMain();

	//=============�萔===============//.
	const D3DXVECTOR3	BOSS_COMMANDDISP_POS = D3DXVECTOR3(0.0f, 6.0f, 3.5f);	//�{�X�̎��̃J�����ʒu.


	//=============�֐�==============//.
	void Init_Process();	//�����ݒ菈���֐�.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

private:
	//=============�萔===============//.
	const float			HIT_SCALE = 0.5f;
	const float			HIT_SCALE_COW = 1.5f;
	const int           INVINCIBLETIME = 2500;
	const int			ITEM_BOUNCE_TIME = 60;
	const int			GAME_END_TIME = 300;


	//=============�֐�==============//.
	void Release();			//��������֐�.

	void SetCommndDecision(int enemyType, int enemy);	//�R�}���h����ƃA�C�e���̓��������֐�.
	void SetHit_Test(int enemyType, int enemy);			//�����蔻�菈���֐�.
	void SetHit_Test_Jump(int enemyType, int enemy);	//�W�����v�̂��߂̓����蔻�菈���֐�.
	void SetItemPosition(int enemyType, int enemy);		//�A�C�e���̈ʒu�ݒ�֐�.

	//============�N���X=============//.
	CPlayer*				m_pCPlayer;				//�v���C���[�N���X.
	CEnemyManager*			m_pCEnemyManager;		//�G�̊Ǘ��N���X.
	CBackGround*			m_pCBackGround;			//�w�i.
	CGround*				m_pCGround;				//�n��.
	CCameraManager*			m_pCCameraManager;		//�J����.

	CCollision_Detection*	m_CHit;					//�����蔻��.
	bool**					m_ppbCheckSound;		//������������SE.


	CMainUIManager*			m_pCUIManager;			//UI�Ǘ��N���X.

	///======================.
	//	����.
	CEffectBase*		m_pCEffectBase;				//�G�t�F�N�g�x�[�X.
	//=======================.

	int				m_frame;
	int				m_waittime;

	int				m_Count;
	int            m_HitCount;


	int				m_EndCount;

};

#endif //#ifndef CGAME_MAIN_H.