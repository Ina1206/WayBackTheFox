#ifndef CITEM_BASE
#define CITEM_BASE

#include "..\..\GameObject\CGameObject.h"
#include "..\..\Command\enumCommand_Global.h"
#include "enItemType.h"

/******************************************************
*		�A�C�e���̌��ƂȂ�N���X.
*/
class CItem_Base
{
public:
	//====================�萔======================//.
	const int ITEM_MIN = 1;
	const int ITEM_MAX = 2;
	const float BOSS_ITEM_POSITION_X = 2.0f;
	const float BOSS_ITEM_POSITION_Z = 1.0f;

	CItem_Base();
	virtual ~CItem_Base();

	//=================�֐�===================//.
	void Value_Set(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);
	virtual void Init_Process()	= 0;	//�������֐�.
	virtual void UpDate()		= 0;	//�X�V�����֐�.
	virtual void Render()		= 0;	//�`�揈���֐�.
	virtual void Release()		= 0;	//��������֐�.
	virtual void ItemCount()	= 0;	//�A�C�e���̍��v�����֐�.

	//�`���l���֐��`.
	D3DXVECTOR3		GetPosition() { return m_vPos; }
	int				GetPointSum() { return m_Point; }
	bool			GetDispFlag() { return m_bDispFlag; }
	int				GetDropNum() { return m_DropNum; }
	int				GetCollitionNum() { return m_CollitionNum; }
	enInput_Decision GetInput_Decision(){ return m_enInputDecision; }
	enItemJudge     GetItemJudge() { return m_enItemJudge; }

	//�`���u�������֐��`.
	void SetPotition(D3DXVECTOR3 vPos)			{ m_vPos = vPos; }									//�ʒu.
	void SetPlayerPos(D3DXVECTOR3 vPlayerPos)	{ m_vPlayerPos = vPlayerPos; }				//�v���C���[�ʒu.
	void SetIconPos(D3DXVECTOR3 vIconPos)		{ m_vIconPos = vIconPos; }						//�A�C�R���ʒu.
	void SetInputDecision(enInput_Decision enDecision) { m_enInputDecision = enDecision; }	//�R�}���h���茋��.
	void SetItemJudge(enItemJudge enJudge)		{ m_enItemJudge = enJudge; }
	void SetDispFlag(bool flag)					{ m_bDispFlag = flag; }										//�\������.
	void SetItemSum(int num)					{ m_Sum = num; }
	void SetBossFlag(bool flag)					{ m_BossFlag = flag; }										//�{�X�t���O.

protected:

	//=================�ϐ�===================//.
	D3DXVECTOR3			m_vCameraPos;			//�J�����ʒu.
	D3DXMATRIX			m_mView;				//�r���[�s��.
	D3DXMATRIX			m_mProj;				//�v���W�F�N�V�����s��.

	CResourceManager*	m_pCResourceManager;	//�ǂݍ��݊Ǘ��N���X.
	CSprite**			m_pCSprite;				//�X�v���C�g�N���X.
	CDepth_Stencil*		m_pCDepth_Stencil;		//�f�v�X�X�e���V���N���X.

	D3DXVECTOR3			m_vPos;					//�ʒu���.
	D3DXVECTOR3			m_vInitPos;				//�����l.
	D3DXVECTOR3			m_vPlayerPos;			//�v���C���[���W.
	D3DXVECTOR3			m_vIconPos;				//�A�C�R�����W.

	enInput_Decision	m_enInputDecision;		//���茋��.
	enItemJudge			m_enItemJudge;
	int					m_DropNum;				//�A�C�e���̗����鐔.
	int					m_CollitionNum;			//��������A�C�e���̐�.
	bool				m_bDispFlag;			//�\���t���O.
	int					m_Sum;					//�����v.
	int					m_Point;				//�|�C���g.
	bool				m_BossFlag;				//�{�X�̃R�}���h���s������.
	bool				m_bCheckBossFlag;		//�{�X�t���O�̃`�F�b�N.


private:
};

#endif//#ifndef CITEM_BASE
