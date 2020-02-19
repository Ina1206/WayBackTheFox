#ifndef CSTANDERD_CAMERA_H
#define CSTANDERD_CAMERA_H

#include "..\CCameraBase.h"

/*******************************************
*	基準のカメラ.
**/
class CStanderdCamera
	: public CCameraBase
{
public:
	CStanderdCamera();
	~CStanderdCamera();

	//==================関数======================//.
	void Update(bool CameraFlag);	//更新処理関数.

private:
	//==================関数======================//.
	void Move();					//行動処理関数.
};

#endif	//#ifndef CSTANDERD_CAMERA_H.