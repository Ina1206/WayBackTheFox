#ifndef RAY_STRUCT_H
#define RAY_STRUCT_H

#include "..\Global.h"

//レイ構造体.
struct RAY
{
	D3DXVECTOR3 Point[2];	//始点,終点.
	D3DXVECTOR3 Direction;	//方向.
	D3DXVECTOR3 Pos;		//位置.
	FLOAT		fYaw;		//Y軸回転値.
	RAY()
		: Point()
		, Direction()
		, Pos()
		, fYaw(0.0f)
	{}
};


#endif	//#ifndef RAY_STRUCT_H.