#ifndef CITEM_MOVE_H
#define CITEM_MOVE_H

#include "CItem_Base.h"
#include "..\..\Sound\CSoundResource.h"

class CItemMove
{
public:
	CItemMove();
	~CItemMove();
	//=================�֐�===================//.
	void Init_Process(D3DXVECTOR3 vPos);		//�����������֐�.
	void UpDate(bool disp, enItemJudge judge, D3DXVECTOR3 IconPos);				//�X�V�����֐�.
	void Collection();			//�A�C�e������֐�.
	void Collection_Boss();		//�{�X�A�C�e������֐�.
	void Drop();				//�A�C�e�����Ƃ��֐�.
	void Drop_Boss();			//�{�X�A�C�e�����Ƃ��֐�.

								//�`���u�������֐��`.
	void SetItemPosition(D3DXVECTOR3 vPos)	{ m_vPos = vPos; }				//�A�C�e���ʒu.
	void SetIconPosition(D3DXVECTOR3 vPos)	{ m_vIconPos = vPos; }			//�A�C�R���ʒu.
	void SetDispFlag(bool flag)				{ m_bDispFlag = flag; }			//�`��t���O.
	void SetItemJudge(enItemJudge enJudge)	{ m_enItemJudge = enJudge; }	//�A�C�e���̔���.
	void SetNumber(int Num)					{ m_Num = Num; }				//�A�C�e���ԍ�.
	void SetItemSum(int num)				{ m_Sum = num; }				//�A�C�e���̍��v.
	void SetBossFlag(bool flag)				{ m_BossFlag = flag; }			//�{�X�̃R�}���h�����s������.

	//�`���擾�֐��`
	D3DXVECTOR3 GetItemPosition()	{ return m_vPos; }						//�ʒu���.
	bool GetCollectionItem()		{ return m_CollectionItem; }			//��������A�C�e���̌�.

private:
	//=================�֐�===================//.
	void Release();			//��������֐�.
	void Bounce();				//�A�C�e���o�E���h�֐�.
	void Absorption();			//�A�C�R���ɋz�������֐�.


	//�A�N�V�������.
	enum class enItemAct {
		Bounce = 0,		//�o�E���h.
		Absorption,		//�z��.
		Flow,			//����Ă���.
		Wait,			//�ҋ@.

		MAX,
		Start = Bounce,
	};

	//================�萔==================//.
	const D3DXVECTOR3 DROP_ITEMPOS	= D3DXVECTOR3(0.0f, 0.2f, 0.07f);
	const float DISP_POS			= -1.0f;							//�`��ʒu�ő�.
	const float BOUNCE_POS			= -1.0f;							//�o�E���h�Œ�y���W.
	const float BOUNCE_SPEED		= 0.013f;							//�o�E���h���x.
	const float BOUNCESPEED_BOSS_S	= 0.02f;							//�o�E���h���x.
	const float BOUNCESPEED_BOSS_F	= 0.008f;							//�o�E���h���x.
	const float FJUMP_POWER			= 0.05f;							//�W�����v��.
	const float FGRAVITY			= 0.007f;							//�d��(�����x).
	const float SPEED				= 0.1f;								//���x.
	const float ROTATION			= 10.0f;							//��]�p.
	const double M_PI				= 3.14159265358979323846;			//�~����.
	const float VECTOR_SPEED		= -1.0f;							//�x�N�g�����x.
	const float DEGREE				= 180.0f;							//�x��.
	const int	BOUNCE_COUNR_MAX	= 50;								//�o�E���h�̍ő厞��.
	const int	COLLITION_NUMBER	= 1;								//���Ƃ����A�C�e���̌�.
	const float SPEED_ADJ			= 0.008f;							//��������.
	const float BOSS_SPEED_ADJ		= 0.0f;							//��������.
	const int	WAIT_TIME			= 250;								//�ҋ@����.

	//================�ϐ�==================//.	
	D3DXVECTOR3			m_vPos;					//�A�C�e���̈ʒu.
	D3DXVECTOR3			m_vIconPos;				//�A�C�R���̈ʒu.
	bool				m_bDispFlag;			//�`��t���O.
	enItemJudge			m_enItemJudge;			//�A�C�e���̔���.
	//---�W�����v�֘A---.
	bool				m_bBounceFlag;			//���˂�t���O.
	int					m_BounceCount;			//���˂��񐔃J�E���g.
	float				m_fAcc;					//����.
	float				m_fSpeed;				//�z������鑬�x.
	float				m_fDirect;				//�z����������.
	float				m_fSpdSpin;				//��]�p.

	enItemAct			m_enAction;				//�A�N�V�������.
	int					m_Num;					//�A�C�e���ԍ�;
	bool				m_CollectionFlag;		//�A�C�e�������������.
	int					m_CollectionItem;		//�A�C�e�������������.
	int					m_Sum;					//�A�C�e���̍��v.
	bool				m_BossFlag;				//�{�X�t���O.

	//---SE�֘A---.
	CSEPlayManager*		m_pCSEPlayManager;
	bool				m_bCheckSE;

};		

#endif//#ifndef CITEM_MOVE_H
