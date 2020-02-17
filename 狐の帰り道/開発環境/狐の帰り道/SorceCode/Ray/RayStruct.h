#ifndef RAY_STRUCT_H
#define RAY_STRUCT_H

#include "..\Global.h"

//���C�\����.
struct RAY
{
	D3DXVECTOR3 Point[2];	//�n�_,�I�_.
	D3DXVECTOR3 Direction;	//����.
	D3DXVECTOR3 Pos;		//�ʒu.
	FLOAT		fYaw;		//Y����]�l.
	RAY()
		: Point()
		, Direction()
		, Pos()
		, fYaw(0.0f)
	{}
};


#endif	//#ifndef RAY_STRUCT_H.