#ifndef CUPCAMERA_H
#define CUPCAMERA_H

#include "..\CCameraBase.h"

/*******************************************
*		上に上がるカメラ.
**/
class CUpCamera
	: public CCameraBase
{
public:
	CUpCamera();
	~CUpCamera();

	//==================関数===================//.
	void UpDate(bool CameraFlag);	//更新処理関数.
private:
	//==================関数===================//.
	void Move();					//行動処理関数.
	void Return();					//元に戻す処理関数.

};

#endif	//#ifndef CUPCAMERA_H.