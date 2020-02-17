#ifndef CDEBUG_TEXT_H
#define CDEBUG_TEXT_H
//UI�Ȃǂ̉�ʂɓ\��t���������͓̂������e�łȂ����s���e�̂ق�������.

#include "..\..\..\Global.h"

//�f�o�b�O�e�L�X�g�N���X.
class CDebugText
{
public:
	const float DIMENSION = 12.0f;
	const float WDIMENSION = 10.0f;
	const float TEX_DIMENSION = 128.0f;

	//======================================.
	//	�\����.
	//======================================.
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.
		D3DXVECTOR4 vColor;		//�J���[(RGBA�̌^�ɍ��킹��).
		D3DXVECTOR4 fAlpha;		//�A���t�@�l(x�̂ݎg�p).
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//���_���W.
		D3DXVECTOR2 Tex;		//�e�N�X�`�����W.
	};

	CDebugText();				//�R���X�g���N�^.
	~CDebugText();				//�f�X�g���N�^.

	//�������֐�.
	HRESULT Init(ID3D11DeviceContext* pContext11,
		DWORD Width, DWORD Height, 
		float Scale, D3DXVECTOR4 vColor);

	//�A���t�@�u�����h�؂�ւ��ݒ�.
	void SetBlend(bool EnableAlpha);

	//�����_�����O�֐�.
	void Render(const char* text, int x, int y);

	//�t�H���g�����_�����O�֐�.
	void RenderFont(int FontIndex, int x, int y);

	static CDebugText* GetDebugTextInstance() 
	{
		static CDebugText s_Instance;
		return &s_Instance;
	}

private:
	//�V�F�[�_�쐬.
	HRESULT InitShader();

	//�u�����h�X�e�[�g�쐬.
	HRESULT InitBlend();

	//���A�v���ɂЂƂ�.
	ID3D11Device*			m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;			//�f�o�C�X�R���e�L�X�g.

	//�����f���̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;		//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;		//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;			//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;		//�R���X�^���g�o�b�t�@.

	//�����f�����Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer[100];	//���_�o�b�t�@.

	ID3D11SamplerState*		m_pSampleLinear;		//�T���v��:�e�N�X�`���Ɋe��t�B���^��������.
	ID3D11ShaderResourceView*	m_pAsciiTexture;	//�e�N�X�`��.

	ID3D11BlendState*		m_pAlphaBlend;			//�A���t�@�u�����h�L��.
	ID3D11BlendState*		m_pNoAlphaBlend;		//�A���t�@�u�����h����.

	DWORD					m_dwWindowWidth;		//�E�B���h�E��.
	DWORD					m_dwWindowHeight;		//�E�B���h�E����.

	float					m_fKerning[100];		//�J�[�j���O�i100���j.
	float					m_fAlpha;				//���ߒl.
	float					m_fScale;				//�g�k�l(25pixel���25pixel = 1.0f).
	D3DXVECTOR4				m_vColor;				//�F.

	D3DXVECTOR3				m_vPos;					//�ʒu.
	D3DXMATRIX				m_mView;				//�r���[�s��.
	D3DXMATRIX				m_mProj;				//�v���W�F�N�V�����s��.
};

#endif	//#ifndef CDEBUG_TEXT_H