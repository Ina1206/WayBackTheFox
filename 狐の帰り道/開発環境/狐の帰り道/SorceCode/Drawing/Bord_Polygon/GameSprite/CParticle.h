#ifndef CPARTICLE_H
#define CPARTICLE_H
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )

#include "..\..\CCommon.h"


/********************************************
*	�p�[�e�B�N���N���X.
**/
class CParticle
	: public CCommon	//���ʃN���X���p��.
{
public:
	//�֐��̃I�[�o�[���[�h.
	CParticle();	//�R���X�g���N�^�i�����Ȃ��R���X�g���N�^�܂��̓f�t�H���g�R���X�g���N�^�Ƃ������j.
	~CParticle();	//�f�X�g���N�^.

	//������.
	HRESULT Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContex11, const char* fileName);

	//���.
	void Release();

	//�V�F�[�_�쐬.
	HRESULT InitShader();

	//���f���쐬.
	HRESULT InitModel();

	//�e�N�X�`���ǂݍ��݁��쐬.
	HRESULT InitTexture(const char* fileName);

	//�����_�����O�p.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj, D3DXVECTOR3& vCamPos);


	//�V�F�[�_���O���֐�.
	void DetachShader();

	//�ʒu����ݒ�.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}
	//��]����ݒ�.
	void SetRotation(const D3DXVECTOR3& vRot) {
		m_vRot = vRot;
	}
	//��]�����擾.
	D3DXVECTOR3 GetRotation() {
		return m_vRot;
	}



private:
	//======================================.
	//	�\����.
	//======================================.
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX	mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//���_���W.
	};

	//�p�[�e�B�N���p�\����.
	struct PART
	{
		D3DXVECTOR3 vPos;		//�ʒu.
		D3DXVECTOR3 vDir;		//����.
		float		Speed;		//���x.
		int			BirthFrame;	//�J�n�t���[��.
		//�\���̂̏�����(�R���X�g���N�^).
		PART()
			: vPos(0.0f, 0.0f, 0.0f)
			, vDir(0.0f, 0.0f, 0.0f)
			, Speed(0.0f)
			, BirthFrame(0)
		{};
	};
	
	//�����f���̎�ނ��Ƃɗp��.
	ID3D11VertexShader*		m_pVertexShader;		//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;		//���_���C�A�E�g.
	ID3D11GeometryShader*	m_GeometryShader;		//�W�I���g���V�F�[�_.
	ID3D11PixelShader*		m_pPixelShader;			//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pConstantBuffer;		//�R���X�^���g�o�b�t�@.

	//�����f�����Ƃɗp��.
	ID3D11Buffer*			m_pVertexBuffer;		//���_�o�b�t�@.

	ID3D11SamplerState*		m_pSampleLinear;		//�T���v��:�e�N�X�`���Ɋe��t�B���^��������.
	ID3D11ShaderResourceView*	m_pTexture;			//�e�N�X�`��.

	int						m_AnimCount;			//�J�E���^.
	D3DXVECTOR2				m_UV;					//�e�N�X�`��UV���W.

	D3DXVECTOR3				m_vPos;					//�ʒu.
	float					m_Scale;				//�g�k�l.

	PART*					m_pParticleArray;		//�p�[�e�B�N���z��.
	int						m_Frame;				//�t���[����.


	D3DXVECTOR3				m_vRot;					//��]�l(x,y,z).

};

#endif//#ifndef CPARTICLE_H