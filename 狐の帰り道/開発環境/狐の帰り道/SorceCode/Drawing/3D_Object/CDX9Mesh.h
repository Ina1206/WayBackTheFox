#ifndef CDX9MESH_H
#define CDX9MESH_H
//�x���ɂẴR�[�h���͂𖳌��ɂ���. 4005:�Ē�`.
#pragma warning( disable:4005)

#include <Windows.h>
#include <d3dx9.h>
#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>	//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>
#include "..\..\MyMacro.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx10.lib")	//�uD3DX�`�v�̒�`�g�p���ɕK�v�ɂȂ�.

#define ALIGN16 _declspec(align(16))

const int SHADOW_MAX = 10;

//�X�t�B�A�\����.
struct SPHERE
{
	D3DXVECTOR3 vCenter;	//���S.
	float		fRadius;	//���a.
};
//�o�E���f�B���O�{�b�N�X�\����.
struct BBOX
{
	D3DXVECTOR3 vPosMax;	//�ő咸�_.
	D3DXVECTOR3 vPosMin;	//�ŏ����_.
	D3DXVECTOR3 vAxisX;		//x��.
	D3DXVECTOR3 vAxisY;		//y��.
	D3DXVECTOR3 vAxisZ;		//z��.
	FLOAT		LenghtX;	//X����.
	FLOAT		LenghtY;	//Y����.
	FLOAT		LenghtZ;	//Z����.

	//������.
	BBOX()
		: vPosMax(), vPosMin()
		, vAxisX(1.0f, 0.0f, 0.0f)
		, vAxisY(0.0f, 1.0f, 0.0f)
		, vAxisZ(0.0f, 0.0f, 1.0f)
		, LenghtX(0.0f), LenghtY(0.0f), LenghtZ(0.0f)
	{}
};

//�J�������.
//�����Y����]�̂ݑΉ�.
struct CAMERA
{
	D3DXVECTOR3	vPos;	//�ʒu.
	D3DXVECTOR3 vLook;	//�����ʒu.
	float		fYaw;	//Y����].
	D3DXMATRIX	mRot;	//��]�s��.
};

//�e���.
struct SHADOW
{
	D3DXVECTOR3 vCasterPos;	//�L���X�^�[�ʒu.
	bool		bDispFlag;	//�\���ؑփt���O.

	SHADOW(const D3DXVECTOR3& vPos, bool bDisp)
		: vCasterPos	(vPos)
		, bDispFlag		(bDisp)
	{}

	SHADOW()
		: SHADOW(D3DXVECTOR3(0.0f, 0.0f, 0.0f), false)
	{}
};

//���b�V���f�[�^���t�@�C��������o���ׂ�����DirectX9���g�p����.
//�������_�����O(�`��)�́ADirectX11�ōs��.
class CDX9Mesh
{
public:
	CDX9Mesh();		//�R���X�g���N�^.
	~CDX9Mesh();	//�f�X�g���N�^.

	HRESULT Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice9,ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, const char* fileName);
	//���b�V���ǂݍ���.
	HRESULT LoadXMesh(const char* fileName);
	//����֐�.
	void Release();

	//�V�F�[�_�쐬.
	HRESULT InitShader();

	//�����_�����O�p.
	void Render(D3DXMATRIX& mView, D3DXMATRIX& mProj,
		D3DXVECTOR3& vLight, D3DXVECTOR3& vCamPos);

	//�ʒu����ݒ�.
	//inline void ��inline�͊֐����̂𒼐ړW�J���邽�ߑ��x���オ��.
	void SetPosition(float x, float y, float z) {
		m_vPos.x = x;
		m_vPos.y = y;
		m_vPos.z = z;
	}
	void SetPosition(const D3DXVECTOR3& vPos) {
		m_vPos = vPos;
	}
	//�ʒu�����擾.
	D3DXVECTOR3 GetPosition()
	{
		return m_vPos;
	}
	//��]����ݒ�.
	void SetRotation(const D3DXVECTOR3& vRot) {
		m_vRot = vRot;
	}
	//��]�����擾.
	D3DXVECTOR3 GetRotation() {
		return m_vRot;
	}
	//�g�k����ݒ�.
	void SetScale(float Scale)	{ m_fScale = Scale; }
	//�g�k�����擾.
	float GetScale()			{ return m_fScale; }

	//�����ʒu�����炷.
	void SetPrePos(D3DXVECTOR3 vPrePos) { m_vPrePos = vPrePos; }

	//���b�V�����擾.
	LPD3DXMESH GetMesh() {
		return m_pMesh;
	}

	SPHERE m_Sphere;			//�X�t�B�A�\����.
	BBOX   m_BBox;				//B�{�b�N�X�\����.


	LPD3DXMESH	m_pMeshForRay;	//���C�ƃ��b�V���p.

private:
	//======================================.
	//	�\����.
	//======================================.
	//�R���X�^���g�o�b�t�@�̃A�v�����̒�`.
	//���V�F�[�_���̃R���X�^���g�o�b�t�@�ƈ�v���Ă���K�v����.
	struct CBUFFER_PER_MESH
	{
		D3DXMATRIX	mW;			//���[���h�s��.
		D3DXMATRIX	mWVP;		//���[���h,�r���[,�v���W�F�N�V�����̍����ϊ��s��.
	};
	struct CBUFFER_PRE_MATERIAL
	{
		D3DXVECTOR4 vAmbient;	//�A���r�G���g�F(���F).
		D3DXVECTOR4	vDiffuse;	//�f�B�t���[�Y�F(�g�U���ːF).
		D3DXVECTOR4 vSpecular;	//�X�y�L�����F(���ʔ��ːF).
	};
	//�t���[���P�ʂœn�����.
	struct CBUFFER_PER_FRAME
	{
		D3DXVECTOR4			vCamPos;				//�J�����ʒu(���_�ʒu).
		D3DXVECTOR4			vLightDir;				//���C�g����.
		ALIGN16 D3DXVECTOR4 vCasterToLight;			//�e�𗎂Ƃ����f���ƃ��C�g�����ԃx�N�g��.
		ALIGN16	D3DXVECTOR4 vCasterPos[SHADOW_MAX];	//�e�𗎂Ƃ��L���X�^�[�̈ʒu.
	};
	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3	Pos;		//���_���W.
		D3DXVECTOR3 Normal;		//�@��(�A�e�v�Z�ɕK�{).
		D3DXVECTOR2 Tex;		//�e�N�X�`�����W.
	};
	//�}�e���A���\����.
	struct MY_MATERIAL
	{
		D3DXVECTOR4					Ambient;			//�A���r�G���g.
		D3DXVECTOR4					Diffuse;			//�f�B�t���[�Y.
		D3DXVECTOR4					Specular;			//�X�y�L�����[.
		char						szTextureName[128];	//�e�N�X�`���t�@�C����.
		ID3D11ShaderResourceView*	pTexture;			//�e�N�X�`��.
		DWORD						dwNumFace;			//���̃}�e���A���̃|���S����.
		//�R���X�g���N�^.
		MY_MATERIAL()
			:Ambient(),Diffuse(),Specular(), szTextureName()
			,pTexture(nullptr), dwNumFace(0)
		{
		}
		//�f�X�g���N�^.
		~MY_MATERIAL(){
			SAFE_RELEASE(pTexture);
		}
	};


	HWND					m_hWnd;					//�E�B���h�E�n���h��.

	//Dx9.
	LPDIRECT3D9				m_pD3d9;				//Dx9�I�u�W�F�N�g.
	LPDIRECT3DDEVICE9		m_pDevice9;				//Dx9�f�o�C�X�I�u�W�F�N�g.

	//Dx11.
	ID3D11Device*			m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;			//�f�o�C�X�R���e�L�X�g.

	ID3D11VertexShader*		m_pVertexShader;		//���_�V�F�[�_.
	ID3D11InputLayout*		m_pVertexLayout;		//���_���C�A�E�g.
	ID3D11PixelShader*		m_pPixelShader;			//�s�N�Z���V�F�[�_.
	ID3D11Buffer*			m_pCBufferPerMesh;		//�R���X�^���g�o�b�t�@(���b�V����).
	ID3D11Buffer*			m_pCBufferPerMaterial;	//�R���X�^���g�o�b�t�@(�}�e���A����).
	ID3D11Buffer*			m_pCBufferPerFrame;		//�R���X�^���g�o�b�t�@(�t���[����)

	ID3D11Buffer*			m_pVertexBuffer;		//���_�o�b�t�@.
	ID3D11Buffer**			m_ppIndexBuffer;		//�C���f�b�N�X�o�b�t�@.
	ID3D11SamplerState*		m_pSampleLinear;		//�T���v��:�e�N�X�`���Ɋe��t�B���^��������.

	LPD3DXMESH				m_pMesh;				//���b�V���I�u�W�F�N�g.
	DWORD					m_NumMaterials;			//�}�e���A����.

	MY_MATERIAL*			m_pMaterials;			//�}�e���A���\����.
	DWORD					m_NumAttr;				//������.
	DWORD					m_AttrID[300];			//����ID�@��300�����܂�.

	bool					m_EnableTexture;		//�e�N�X�`������.

	float					m_fScale;				//�g��k���l(x,y,z���{).
	D3DXVECTOR3				m_vRot;					//��]�l(x,y,z).
													//��x = Pitch, y = Yaw, z = Roll.
	D3DXVECTOR3				m_vPos;					//�ʒu(x,y,z).
	D3DXVECTOR3				m_vPrePos;

	SHADOW*					m_pstShadow;			//�e�̏��.
	int						m_ShadowMax;			//�e�̍ő吔.

	//�����_�����O�֐�(�N���X���ł̂ݎg�p).
	void RenderMesh(D3DXMATRIX& mWorld, D3DXMATRIX& mView, D3DXMATRIX& mProj);

public:
	//�e�֌W�̏���ݒ菈���֐�.
	void SetShadow(SHADOW* shadow, int shadowMax) {
		m_pstShadow = shadow;
		m_ShadowMax = shadowMax;
	}
};


#endif	//#ifndef CDX9MESH_H