#ifndef CITEM_MEAT_H
#define CITEM_MEAT_H

#include "CItem_Base.h"
#include "CItemMove.h"


class CItem_Meat
	: public CItem_Base
{
public:
	CItem_Meat();
	~CItem_Meat();

	//=================�֐�===================//.
	void Init_Process();	//�����������֐�.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.

private:
	//=================�֐�===================//.
	void Release();			//��������֐�.

	void ItemCount();		//�A�C�e���̍��v�����֐�.[
	void ItemRender();		//�A�C�e���`�揈���֐�.

	//=================�萔=================//.
	const int MEATPONIT			= 3;		
	const float POS_ADJ			= 50.0f;	//�ʒu����.

	//=================�ϐ�=================//.
	D3DXVECTOR2* m_pvPattern;		//�摜�p�^�[��.
	CSpriteUI**	 m_ppCNumSprite;	//�A�C�e���̌��\���p.

	int			 m_Num;				//�A�C�e���̌�.
	CItemMove*	 m_CItemMove;		//�A�C�e���̓����N���X.

};


#endif//CITEM_MEAT_H