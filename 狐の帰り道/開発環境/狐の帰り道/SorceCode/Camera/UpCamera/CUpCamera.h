#ifndef CUPCAMERA_H
#define CUPCAMERA_H

#include "..\CCameraBase.h"

/*******************************************
*		��ɏオ��J����.
**/
class CUpCamera
	: public CCameraBase
{
public:
	CUpCamera();
	~CUpCamera();

	//==================�֐�===================//.
	void UpDate(bool CameraFlag);	//�X�V�����֐�.
private:
	//==================�֐�===================//.
	void Move();					//�s�������֐�.
	void Return();					//���ɖ߂������֐�.

};

#endif	//#ifndef CUPCAMERA_H.