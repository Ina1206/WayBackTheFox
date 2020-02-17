#ifndef CITEM_COUNT_H
#define CITEM_COUNT_H

#include "CUI_Base.h"
#include "..\Item\enItemType.h"

class CItemCount
	: public CUI_Base
{
public:
	CItemCount();
	~CItemCount();

	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

	//�`���u�������֐��`//.
	void SetItemCount(int ItemNum, int Count);												//�A�C�e���̌��擾.
	void SetIconPos(int num, D3DXVECTOR3 vPos) { m_pstItemInfo[num].m_vIconPos = vPos; }	//�A�C�R���ʒu.

private:
	//==================�萔==================.
	const int ITEM_TYPE_MAX = static_cast<int>(enItemType::MAX);	//�A�C�e���^�C�v�̍ő�.
	const int IMAGE_WIDTH_MAX = 5;									//�摜�̉���.
	const int IMAGE_HIGH_MAX  = 5;									//�摜�̏c��
	const int NUM_SPRITE_MAX  = 2;									//�X�v���C�g�̍ő�.
	const int TEN			  = 10;									//10�̈�.

	//==================�\����==================.
	struct stItemInfo {
		D3DXVECTOR3		m_vIconPos;			//�A�C�R���ʒu.
		D3DXVECTOR2*	m_pvPattern;		//�摜�p�^�[��.
		CSpriteUI**		m_ppCNumSprite;		//�����̃X�v���C�g.

		stItemInfo()
			: m_vIconPos	 (0.0f,0.0f,0.0f)
			, m_pvPattern	 (nullptr)
			, m_ppCNumSprite (nullptr)
		{}
	};

	//==================�֐�==================.
	void Release();		//��������֐�.

	//==================�ϐ�==================.
	stItemInfo*		m_pstItemInfo;		//�A�C�e�����\�z��.
	int				m_Vegetable_Count;	//��؂̌�.
	int				m_Meat_Count;		//���̌�.
	int				m_Fish_Count;		//���̌�.
	int				m_Rice_Count;		//�Ă̌�.

};

#endif//#ifndef CITEM_COUNT_H.