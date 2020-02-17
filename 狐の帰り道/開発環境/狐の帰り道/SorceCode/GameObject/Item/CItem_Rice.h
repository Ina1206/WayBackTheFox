#ifndef CITEM_RICE_H
#define CITEM_RICE_H

#include "CItem_Base.h"
#include "CItemMove.h"


class CItem_Rice
	: public CItem_Base
{
public:
	CItem_Rice();
	~CItem_Rice();

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
	const int	RICEPOINT		= 4;		//�Ẵ|�C���g.
	const int   RICE_MAX		= 6;		//�Ă̌�.
	const float POS_ADJ			= 50.0f;	//�ʒu����.
	const float	ITEM_POS		= 2.0f;		//�A�C�e���̈ʒu.

	//=================�ϐ�=================//.
	int			 m_Num;				//�A�C�e���̌�.
	CItemMove*	 m_CItemMove;		//�A�C�e���̓����N���X.

	D3DXVECTOR3 m_vOldPos;			//�O�̍��W.


};

#endif//CITEM_VEGETABLE_H