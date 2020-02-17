#include "CItem_Rice.h"

//===================================.
//	�R���X�g���N�^.
//===================================.
CItem_Rice::CItem_Rice()
	: m_Num(0)
	, m_CItemMove(nullptr)
	, m_vOldPos(0.0f,0.0f,0.0f)
{
}

//===================================.
//	�f�X�g���N�^.
//===================================.
CItem_Rice::~CItem_Rice()
{
	Release();
}

//===================================.
//	�����������֐�.
//===================================.
void CItem_Rice::Init_Process()
{
	m_CItemMove = new CItemMove[RICE_MAX]();
}

//===================================.
//	�X�V�����֐�.
//===================================.
void CItem_Rice::UpDate()
{
	for (int i = 0; i < RICE_MAX; i++)
	{
		//�X�V�����֐�.
		if (m_enItemJudge == enItemJudge::Success) {
			m_CItemMove[i].UpDate(m_bDispFlag, m_enItemJudge, m_vIconPos);
		}
		m_CItemMove[i].SetBossFlag(m_BossFlag);

		if (m_bDispFlag == true) {
			m_vPos = m_CItemMove[i].GetItemPosition();
		}
		else
		{
			m_CItemMove[i].Init_Process(m_vPos);
		}

		if (m_CollitionNum != m_DropNum)
		{
			m_CollitionNum += m_CItemMove[i].GetCollectionItem();
		}
	}
	ItemCount();
}

//===================================.
//	�`�揈���֐�.
//===================================.
void CItem_Rice::Render()
{
	if (m_bDispFlag == true) {
		ItemRender();
	}
}

//===================================.
//	��������֐�.
//===================================.
void CItem_Rice::Release()
{
	SAFE_DELETE_ARRAY(m_CItemMove);
}

//===================================.
//	�A�C�e���̍��v�����֐�.
//===================================.
void CItem_Rice::ItemCount()
{
	//�A�C�e�����̐ݒ�.
	if (m_enInputDecision == enInput_Decision::Great) { m_DropNum = RICE_MAX; }
	if (m_enInputDecision == enInput_Decision::Good) { m_DropNum = RICE_MAX; }
	if (m_enItemJudge == enItemJudge::failure)
	{
		m_DropNum = ITEM_MIN;
	}

		//�|�C���g�ݒ�.
	m_Point = RICEPOINT * m_DropNum;
}


//===================================.
//	�A�C�e���`�揈���֐�.
//===================================.
void CItem_Rice::ItemRender()
{
	m_pCSprite = new CSprite*[RICE_MAX];

	//�N���X.
	for (int sprite = 0; sprite < m_DropNum; sprite++)
	{
		m_pCSprite[sprite] = m_pCResourceManager->GetSprite(CResourceSprite::enSprite::Rice);
		//�A�C�e���̕\�����ݒ�.
		m_CItemMove[sprite].SetNumber(sprite);

		//�ʒu.
		m_pCSprite[sprite]->SetPosition(m_CItemMove[sprite].GetItemPosition());

		//�`��.
		m_pCDepth_Stencil->SetDepth(false);
		m_pCSprite[sprite]->Render(m_mView, m_mProj, m_vCameraPos);
		m_pCDepth_Stencil->SetDepth(true);
	}

	SAFE_DELETE_ARRAY(m_pCSprite);
}
