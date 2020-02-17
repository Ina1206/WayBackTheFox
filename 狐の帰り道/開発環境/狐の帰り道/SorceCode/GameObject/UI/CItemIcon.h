#ifndef CITEMICON_H
#define CITEMICON_H

#include "CUI_Base.h"

class CItemIcon
	: public CUI_Base
{
public:
	CItemIcon();
	~CItemIcon();

	//=================�֐�===================//.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

	D3DXVECTOR3 GetPosition() { return m_vPos; }
	D3DXVECTOR3 GetIconPosition(int num);

private:
	//=================�萔===================//.
	const int ITEM_SPRITE_MAX	= 4;		//�X�v���C�g�̍ő吔.
	const int ITEM_MEAT			= 0;		//���̔ԍ�.
	const int ITEM_FISH			= 1;		//���̔ԍ�.
	const int ITEM_VEGETABLES	= 2;		//��؂̔ԍ�.
	const int ITEM_RICE			= 3;		//�Ă̔ԍ�.

	const D3DXVECTOR2 ICON_POS	= D3DXVECTOR2(0.0f, 0.0f);			//���A�C�R���̈ʒu.
	const float FISH_POS_Y		= ICON_POS.y + 80.0f;					//���A�C�R����y���W.
	const float VEGETABLES_POS_Y= FISH_POS_Y + 100.0f;					//��؃A�C�R����y���W.
	const float RICE_POS_Y		= VEGETABLES_POS_Y + 110.0f;			//�ăA�C�R����y���W.

	//=================�֐�===================//.
	void Release();			//��������֐�.

	//=================�ϐ�===================//.
	CSpriteUI**		m_ppCItemIcon;		//SpriteUI�N���X.

	D3DXVECTOR3		m_vVegetable_Pos;
	D3DXVECTOR3		m_vMeat_Pos;
	D3DXVECTOR3		m_vFish_Pos;
	D3DXVECTOR3		m_vRice_Pos;
};

#endif	//#ifndef CITEMICON_H
