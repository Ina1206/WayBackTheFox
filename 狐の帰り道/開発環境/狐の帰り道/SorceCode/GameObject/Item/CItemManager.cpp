#include "CItemManager.h"

CItemManager::CItemManager()
	: m_enEnemy			(enEnemy::Max)
	, m_ppCItemBase		(nullptr)
	, m_enInput_Decision(enInput_Decision::Max)
	, m_pCCollision		(nullptr)
	, m_ItemJudge		(enItemJudge::Max)
	, m_vInitPos		(0.0f, 0.0f, 0.0f)
	, m_vPlayerPos		(0.0f, 0.0f, 0.0f)
	, m_vIconPos		(0.0f, 0.0f, 0.0f)
	, m_bDispFlag		(false)
	, m_bBossFlag		(false)
	, m_pSum			(nullptr)
{
}

CItemManager::~CItemManager()
{
	Release();
}

//========================================.
//		�����������֐�.
//========================================.
void CItemManager::Init_Process()
{
	m_ppCItemBase = new CItem_Base*[ITEM_TYPE_MAX];
	m_pCCollision = new CCollision_Detection();

	m_ppCItemBase[VEGETABlE] = new CItem_Vegetables();
	m_ppCItemBase[MEAT] = new CItem_Meat();
	m_ppCItemBase[FISH] = new CItem_Fish();
	m_ppCItemBase[RICE] = new CItem_Rice();

	m_pSum = new int[ITEM_TYPE_MAX];

	//����������.
	for (int item = 0; item < ITEM_TYPE_MAX; item++)
	{
		m_ppCItemBase[item]->Init_Process();
	}

	m_ppCItemBase[VEGETABlE]->SetIconPos(ICONPOS_VEG);
	m_ppCItemBase[MEAT]->SetIconPos(ICONPOS_MEAT);
	m_ppCItemBase[FISH]->SetIconPos(ICONPOS_FISH);
	m_ppCItemBase[RICE]->SetIconPos(ICONPOS_RICE);
}

//========================================.
//		�X�V�����֐�.
//========================================.
void CItemManager::UpDate()
{
	for (int item = 0; item < ITEM_TYPE_MAX; item++) {
		//�����ʒu�ݒ�.
		m_ppCItemBase[item]->SetPotition(m_vInitPos);
		//�v���C���[�ʒu�ݒ�.
		m_ppCItemBase[item]->SetPlayerPos(m_vPlayerPos);
		//�A�C�e�����v�̎擾.
		m_ppCItemBase[item]->SetItemSum(m_pSum[item]);
		//�R�}���h���茋�ʐݒ�.
		m_ppCItemBase[item]->SetInputDecision(m_enInput_Decision);
		//�A�C�e�����茋�ʐݒ�.
		m_ppCItemBase[item]->SetItemJudge(m_ItemJudge);
		//�`��t���O�ݒ�.
		m_ppCItemBase[item]->SetDispFlag(m_bDispFlag);
		//�{�X�t���O�ݒ�.
		m_ppCItemBase[item]->SetBossFlag(m_bBossFlag);
	}

	switch (m_enEnemy)
	{
	case enEnemy::RaccoonDog:
		m_ppCItemBase[VEGETABlE]->UpDate();
		break;
	case enEnemy::Cow_Ghost:
		m_ppCItemBase[MEAT]->UpDate();
		break;
	case enEnemy::UpRaccoonDog:
		m_ppCItemBase[FISH]->UpDate();
		break;
	case enEnemy::Big_RaccoonDog:
		if (m_enInput_Decision == enInput_Decision::Bad){
			for (int item = 0; item < ITEM_TYPE_MAX - 1; item++){
				m_ppCItemBase[item]->UpDate();
			}
		}
		else {
			m_ppCItemBase[RICE]->UpDate();
		}
		break;
	default:
		break;
	}
}

//========================================.
//		�`�揈���֐�.
//========================================.
void CItemManager::Render(D3DXMATRIX mView, D3DXMATRIX mProj, D3DXVECTOR3 vCamePos)
{
	for (int item = 0; item < ITEM_TYPE_MAX; item++) {
		m_ppCItemBase[item]->Value_Set(mView, mProj, vCamePos);
		m_ppCItemBase[item]->Render();
	}
}

//========================================.
//		�A�C�e���̍��v.
//========================================.
void CItemManager::SetItemSum(int itemType, int num)
{
	{
		m_pSum[itemType] = num;;
	}
}

D3DXVECTOR3 CItemManager::GetIconPos(int itemType)
{

	switch (itemType)
	{
	case 0:
		m_vIconPos = ICONPOS_VEG;
		break;
	case 1:
		m_vIconPos = ICONPOS_MEAT;
		break;
	case 2:
		m_vIconPos = ICONPOS_FISH;
		break;
	case 3:
		m_vIconPos = ICONPOS_RICE;
		break;
	default:
		break;
	}

	return m_vIconPos;
}

//========================================.
//		��������֐�.
//========================================.
void CItemManager::Release()
{
	SAFE_DELETE(m_pCCollision);
	SAFE_DELETE_ARRAY(m_pSum);
	for (int item = ITEM_TYPE_MAX - 1; item >= 0; item--)
	{
		SAFE_DELETE(m_ppCItemBase[item]);
	}
	SAFE_DELETE_ARRAY(m_ppCItemBase);
}
