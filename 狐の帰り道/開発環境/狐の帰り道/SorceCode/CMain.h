#ifndef MAIN_H
#define MAIN_H
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )
#include <Windows.h>
#include <stdio.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>					//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>


#include "Drawing\Bord_Polygon\CDepth_Stencil.h"

#include "Scene\CSceneManager.h"
#include "Scene\Load\CLoad.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.

//#include "CEffect.h"				//Effekseer�𐧌䂷��N���X.

//���C�u�����ǂݍ���.
#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "d3dx11.lib")
#pragma comment( lib, "d3d11.lib")
#pragma comment( lib, "d3dx10.lib")	//�uD3DX�`�v�̒�`�g�p���ɕK�v.

//=================================================.
//	�萔.
//=================================================.
const char WND_TITLE[] = "�ς̋A�蓹";
const char APP_NAME[] = "�ς̋A�蓹";

//++++++++++++++++++++++++++++++++++++++++.
const int ENEMY_MAX = 2;
const int ITEMMAX = 3;
//++++++++++++++++++++++++++++++++++++++++.

/********************************************
*	���C���N���X.
**/
class CMain
{
public:
	//======================================.
	//	�񋓑�.
	//======================================.
	//����.
	enum class enDirection
	{
		Stop = 0,	//��~.
		Forward,		//�S�g.
		Backward,		//���.
		Left,			//��.
		Right,			//�E.
	};

	
	//======================================.
	//	�\����.
	//======================================.

	CMain();	//�R���X�g���N�^.
	~CMain();	//�f�X�g���N�^.

	//�E�B���h�E�������֐�.
	HRESULT InitWindow(
		HINSTANCE hInstance,
		INT x, INT y, INT width, INT height,
		const char* WindowName);
	
	//�E�B���h�E�֐�(���b�Z�[�W���̏���).
	LRESULT MsgProc(
		HWND hWnd, UINT uMsg,
		WPARAM wParam, LPARAM lParam);
	
	//���b�Z�[�W���[�v.
	void Loop();
	
	//�ǂݍ��ݏ����֐�.
	void Load();
	//�X�V�����֐�.
	void UpDate();
	//�����_�����O(�`��).
	void Render();

	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.
		//�̨��쐬.
	HRESULT InitSphere(CDX9Mesh* pMesh);


	//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.

//------------------------------.
//	��������RD�֌W.

	//DirectX������.
	HRESULT InitD3D();
	//Direct3D�I������.
	void DestroyD3D();

	////���b�V���̓ǂݍ��݊֐�.
	HRESULT LoadMesh();

	////�o�b�N�o�b�t�@�N���A�֐�.
	void ClearBackBuffer();
	//�J�����֐�.
	void Camera();
	//�v���W�F�N�V�����֐�.
	void Proj();
	

	//=============���u�������֐�===========//.
	void SethWnd(HWND hWnd) {
		m_hWnd = hWnd;
	}
private:
	HWND m_hWnd;	//�E�B���h�E�n���h��.

//------------------------------.
//	��������RD�֌W.


	//���A�v���ɂЂƂ�.
	ID3D11Device*			m_pDevice11;			//�f�o�C�X�I�u�W�F�N�g.
	ID3D11DeviceContext*	m_pContext11;			//�f�o�C�X�R���e�L�X�g.
	IDXGISwapChain*			m_pSwapChain;			//�X���b�v�`�F�[��.
	ID3D11RenderTargetView* m_pBackBuffer_TexRTV;	//�����_�[�^�[�Q�b�g�r���[.
	ID3D11Texture2D*		m_pBackBuffer_DSTex;	//�f�v�X�X�e���V���p�e�N�X�`��.
	ID3D11DepthStencilView*	m_pBackBuffer_DSTexDSV;	//�f�v�X�X�e���V���r���[.
	LPDIRECT3D9				m_pD3d9;				//Dx9�I�u�W�F�N�g.
	LPDIRECT3DDEVICE9		m_pDevice9;				//Dx9�f�o�C�X.

	//�����錾�\.
	D3DXVECTOR3				m_vLight;				//���C�g�̕���.

	CAMERA					m_Camera;		//�J�������.

	D3DXMATRIX				m_mView;		//�r���[�s��.
	D3DXMATRIX				m_mProj;		//�v���W�F�N�V�����s��.

	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.
																				//
	//���ޯ��÷�ĸ׽.															//
	CDebugText*		m_pDbgText;													//
	CDebugText*		m_pDbgText2;												//
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++.



	CDepth_Stencil m_CDepth_Stencil;

	CSceneManager*  m_pCSceneManager;			//�V�[���Ǘ��N���X.
	CLoad*			m_pCLoad;					//�ǂݍ��ݒ��N���X.
	bool			m_bFullScreenFlag;			//�t���X�N���[���I���t���O.
	
};

#endif//#ifndef MAIN_H
