#ifndef CSTANDERD_CAMERA_H
#define CSTANDERD_CAMERA_H

#include "..\CCameraBase.h"

/*******************************************
*	��̃J����.
**/
class CStanderdCamera
	: public CCameraBase
{
public:
	CStanderdCamera();
	~CStanderdCamera();

	//==================�֐�======================//.
	void Update(bool CameraFlag);	//�X�V�����֐�.

private:
	//==================�֐�======================//.
	void Move();					//�s�������֐�.
};

#endif	//#ifndef CSTANDERD_CAMERA_H.