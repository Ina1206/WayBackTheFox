#ifndef CITEMMANAGER_H
#define CITEMMANAGER_H

#include "CItem_Meat.h"
#include "CItem_Fish.h"
#include "CItem_Vegetables.h"
#include "CItem_Rice.h"
#include "..\Collider_Detection\CCollision_Detection.h"

#include "..\Chara\Enemy\EnemyType.h"

/***************************************************
*	�A�C�e���Ǘ��p�N���X.
**/
class CItemManager
{
public:
	CItemManager();
	~CItemManager();

	//=====================�֐�=======================//.
	void Init_Process();													//�����������֐�.
	void UpDate();															//�X�V�����֐�.
	void Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos);	//�`�揈���֐�.

	//�`���u�������֐��`.
	void SetEnemyType(enEnemy enemyType) { m_enEnemy = enemyType; }						//�G�̃^�C�v.
	void SetInput_Decision(enInput_Decision enInput) { m_enInput_Decision = enInput; }	//�R�}���h���茋��.
	void SetInitPosition(D3DXVECTOR3 vPos) { m_vInitPos = vPos; }						//�����ʒu. 
	void SetPlayerPosition(D3DXVECTOR3 vPos) { m_vPlayerPos = vPos; }					//�v���C���[�ʒu.
	void SetItemJudge(enItemJudge enJudge) { m_ItemJudge = enJudge; }					//�A�C�e���̔���.
	void SetDispFlag(bool flag) { m_bDispFlag = flag; }									//�`��t���O.
	void SetBossFlag(bool flag) { m_bBossFlag = flag; }									//�{�X�t���O.
	void SetItemSum(int itemType, int num);												//�A�C�e���̍��v.


	//�`���擾�����֐��`.
	enEnemy		GetEnemyType()   { return m_enEnemy; }			//�G�̃^�C�v.
	enItemJudge	GetItemJudge() { return m_ItemJudge; }
	int			GetPointSum(int itemType) { return m_ppCItemBase[itemType]->GetPointSum(); };
	int			GetCollitionNum(int itemType) { return m_ppCItemBase[itemType]->GetCollitionNum(); }
	int			GetDropNum(int itemType) { return m_ppCItemBase[itemType]->GetDropNum(); }
	bool		GetBossFlag() { return m_bBossFlag; }
	bool		GetDispFlag(int itemType) { return m_ppCItemBase[itemType]->GetDispFlag(); }

	D3DXVECTOR3 GetPosition(int itemType) { return m_ppCItemBase[itemType]->GetPosition(); }
	D3DXVECTOR3 GetIconPos (int itemType);

private:
	//=====================�֐�=======================//.
	void Release();		//��������֐�.

	//==================�萔==================.
	const D3DXVECTOR3 ICONPOS_VEG  = D3DXVECTOR3(-2.5f, 1.4f, 0.0f);
	const D3DXVECTOR3 ICONPOS_MEAT = D3DXVECTOR3(-2.5f, 2.8f, 0.0f);
	const D3DXVECTOR3 ICONPOS_FISH = D3DXVECTOR3(-2.5f, 2.3f, 0.0f);
	const D3DXVECTOR3 ICONPOS_RICE = D3DXVECTOR3(-2.5f, 1.4f, 0.0f);
	const D3DXVECTOR3 ITEMNUM_POS  = D3DXVECTOR3(125.0f, 25.0f, 0.0f);
	const D3DXVECTOR2 ITEMNUM_POS_ADJ = D3DXVECTOR2(75.0f, 95.0f);

	const int ENEMYTYPE_MAX		= static_cast<int>(enEnemy::Max);				//�G�̍ő吔.
	const int VEGETABlE			= 0;
	const int MEAT				= 1;
	const int FISH				= 2;
	const int RICE				= 3;
	const int ITEM_TYPE_MAX		= static_cast<int>(enItemType::MAX);		//�A�C�e���̍ő吔.
	const int NUM_SPRITE_MAX	= 2;
	const int TEN_PLACE			= 0;
	const int ONE_RANK			= 1;
	const int IMAGE_WIDTH_MAX	= 5;
	const int IMAGE_HIGH_MAX	= 5;
	const int TEN				= 10;

	//==================�ϐ�=======================//.
	enEnemy					m_enEnemy;			//�G�̎��.
	CItem_Base**			m_ppCItemBase;		//CItem_Base�N���X.
	CCollision_Detection*	m_pCCollision;		//�����蔻��N���X.
	enInput_Decision		m_enInput_Decision;	//�R�}���h����.
	enItemJudge				m_ItemJudge;		//�A�C�e���̔���.

	D3DXVECTOR3				m_vInitPos;			//�����ʒu.
	D3DXVECTOR3				m_vPlayerPos;		//�v���C���[�ʒu.
	D3DXVECTOR3				m_vIconPos;			//�A�C�R���ʒu.

	bool					m_bDispFlag;		//�`��t���O.
	bool					m_bBossFlag;		//�{�X�t���O.

	int*					m_pSum;				//��؍��v.

};


#endif//#ifndef CITEMMANAGER_H
