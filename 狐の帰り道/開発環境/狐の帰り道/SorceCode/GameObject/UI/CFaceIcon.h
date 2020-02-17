#ifndef CFACEICON_H
#define CFACEICON_H

#include "..\UI\CUI_Base.h"

//=============================.
//	�ǉ�.
#include "..\..\Sound\CSEPlayManager.h"
//=============================.

/***********************************************
*	��A�C�R���N���X.
**/

class CFaceIcon
	: public CUI_Base
{
public:
	CFaceIcon();
	~CFaceIcon();

	//=================�֐�===================//.
	void UpDate();			//�X�V�����֐�.
	void Render();			//�`�揈���֐�.
	//�`���u�������֐��`.
	void SetItemPointSum(int num) { m_PointSum = num; }

private:
	//=================�萔===================//.
	const D3DXVECTOR3 FACEICON_AMOUNT_POS	= D3DXVECTOR3(945.0f, -10.0f, 0.0f);
	const D3DXVECTOR3 FACEICON_POS			= D3DXVECTOR3(995.0f, 30.0f, 0.0f);
	const int FACE_SPRITEUI_MAX				= 7;
	const int FACE_NORMAL					= 0;
	const int FACE_SMILE					= 1;
	const int FACE_MAXSMILE					= 2;
	const int FACE_AMOUNT					= 3;
	const int FACE_NORMAL_BACK				= 6;
	const int FACE_SMILE_BACK				= 5;
	const int FACE_MAXSMILE_BACK			= 4;
	const int CHANGE_SMILE					= 25;
	const int CHANGE_MAXSMILE				= 50;

	//=================�֐�===================//.
	void Release();			//��������֐�.

	//=================�ϐ�===================//.
	CSpriteUI**			m_ppCFaceIcon;
	int					m_PointSum;				//�|�C���g���v.

	//=============================.
	//	�ǉ�.
	CSEPlayManager*		m_pCSEPlayManager;		//SE�Đ��N���X.
	int					m_FaceType;				//��̎��.
	int					m_OldFaceType;			//�O��̊�̎��.
	//=============================.

};

#endif//#ifndef CFACEICON_H.