#ifndef CITEM_VEGETABLE_H
#define CITEM_VEGETABLE_H

#include "CItem_Base.h"
#include "CItemMove.h"

class CItem_Vegetables
	: public CItem_Base
{
public:
	CItem_Vegetables();
	~CItem_Vegetables();

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
	const int	VEGETABLEPOINT	= 1;		//��؂̃|�C���g.
	const float POS_ADJ			= 50.0f;	//�ʒu����.

	//=================�ϐ�=================//.
	int			 m_Num;				//�A�C�e���̌�.
	CItemMove*	 m_CItemMove;		//�A�C�e���̓����N���X.


};


#endif//CITEM_VEGETABLE_H