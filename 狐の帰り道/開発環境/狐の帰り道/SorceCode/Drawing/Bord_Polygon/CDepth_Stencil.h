#ifndef CDEPTH_STENCIL_H
#define CDEPTH_STENCIL_H

#include "..\..\MyMacro.h"	//�}�N��.
#include "..\..\Global.h"	//�O���[�o��.
#include <crtdbg.h>			//_ASSERT_EXPR()�ŕK�v.


/*******************************************
*	�f�v�X�X�e���V���N���X.
**/
class CDepth_Stencil 
{
public:
	CDepth_Stencil();
	~CDepth_Stencil();

	//========�֐�=========//.
	HRESULT Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11); //�ݒ菈���֐�.
	void	SetDepth(bool flag);											//�[�x(Z)�e�X�gON/OFF�؂�ւ������֐�.

	static CDepth_Stencil* GetDepthStencilInstance()
	{
		static CDepth_Stencil s_Instance;
		return &s_Instance;
	}

private:
	//========�֐�=========//.
	void Destroy();											//�������.

	//========�ϐ�=========//.
	ID3D11Device*				m_pDevice11;				//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*		m_pContext11;				//�f�o�C�X�R���e�L�X�g.

	//�[�x.
	ID3D11DepthStencilState*	m_pDepthStencilState;		//�f�v�X�X�e���V��.
	ID3D11DepthStencilState*	m_pDepthStencilStateOff;	//�f�v�X�X�e���V���I�t.
};

#endif	//#ifndef CDEPTH_STENCIL_H.