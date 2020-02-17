#ifndef CLOAD_H
#define CLOAD_H

#include "..\..\Drawing\Bord_Polygon\GameSprite\CSpriteUI.h"

/*******************************************
*	���[�h�N���X.
*****/
class CLoad
{
public:
	CLoad();
	~CLoad();

	//==============�֐�==================//.
	void Init(HWND hWnd, ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);	//�����������֐�.
	void Render();																	//�`�揈���֐�.

private:
	//==============�֐�==================//.
	HRESULT	Load();					//�ǂݍ��ݏ����֐�

	//==============�ϐ�==================//.
	CSpriteUI*	m_pLoadScreen;		//���[�h���.
};

#endif	//#ifndef CLOAD_H.