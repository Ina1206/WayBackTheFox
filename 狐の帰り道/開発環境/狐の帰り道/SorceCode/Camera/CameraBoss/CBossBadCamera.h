#ifndef CBOSS_CAMERA_H
#define CBOSS_CAMERA_H

#include "..\CCameraBase.h"

/*******************************************
*		�{�X��̃J����.
**/
class CBossBadCamera
	: public CCameraBase
{
public:
	CBossBadCamera();
	~CBossBadCamera();


	//==================�֐�=====================//.
	void UpDate(bool CameraFlag);	//�X�V�����֐�.
private:
	//==================�֐�=====================//.
	void Move();					//�ړ������֐�.
};

#endif	//#ifndef CBOSS_CAMERA_H.