#ifndef CBOSS_CAMERA_H
#define CBOSS_CAMERA_H

#include "..\CCameraBase.h"

/*******************************************
*		ボス戦のカメラ.
**/
class CBossBadCamera
	: public CCameraBase
{
public:
	CBossBadCamera();
	~CBossBadCamera();


	//==================関数=====================//.
	void UpDate(bool CameraFlag);	//更新処理関数.
private:
	//==================関数=====================//.
	void Move();					//移動処理関数.
};

#endif	//#ifndef CBOSS_CAMERA_H.