#pragma once

//===============================================.
//	�}�N��(define��`�͊�{1�s).
//===============================================.

//���.
#define SAFE_RELEASE(p) if(p!=nullptr){(p)->Release();(p)=nullptr;}

//�j��.
#define SAFE_DELETE(p) if(p!=nullptr){delete (p);(p)=nullptr;}
//�u\�v�͂܂������Ƃ����Ӗ��Ȃ̂ōŌ�̍s�ɂ͕t���Ȃ�.
#define SAFE_DELETE_ARRAY(p)	\
{								\
	if (p != nullptr) {			\
		delete[](p);			\
		(p) = nullptr;			\
	}							\
}