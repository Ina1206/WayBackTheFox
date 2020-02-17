#ifndef CRAY_DRAW_H
#define CRAY_DRAW_H

#include "..\Drawing\CCommon.h"
#include "RayStruct.h"

//���C�\���N���X.
class CRayDraw
	: public CCommon
{
public:

	CRayDraw();
	~CRayDraw();

	//������.
	HRESULT Init(ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11);

	//�`��.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj);

	//���u�������֐�.
	void SetRay(RAY Ray) { m_Ray = Ray; }

	//================�V���O���g��=================//.
	static CRayDraw* GetRayDrawInstance()
	{
		static CRayDraw s_Instance;
		return &s_Instance;
	}


private:
	//�V�F�[�_�쐬.
	HRESULT InitShader();

	//���C������.
	HRESULT InitModel();

	//======================================.
	//	�\����.
	//======================================.
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.
		D3DXVECTOR4 vColor;		//�J���[(RGBA�̌^�ɍ��킹��).
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//���_���W.
	};

	//�����f���̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;		//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;		//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;			//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;		//�R���X�^���g�o�b�t�@.

	//�����f�����Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;		//���_�o�b�t�@.

	//���C�\����.
	RAY		m_Ray;

};

#endif //#ifndef CRAY_DRAW_H.