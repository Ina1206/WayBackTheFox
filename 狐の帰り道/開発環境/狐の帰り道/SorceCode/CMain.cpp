#include "CMain.h"
#include "Global.h"
#include <crtdbg.h>	
#include "MyMacro.h"

//�O���[�o���ϐ�.
CMain* g_pCMain = nullptr;

//=================================================.
//	���C���֐�.
//=================================================.
INT WINAPI WinMain(
	HINSTANCE hInstance,	//�C���X�^���X�ԍ�(�E�B���h�E�̔ԍ�).
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	INT nCmdShow)
{
	g_pCMain = new CMain();	//���������N���X�錾.

	if (g_pCMain != nullptr) {

		//�E�B���h�E�쐬����������.
		if (SUCCEEDED(
			g_pCMain->InitWindow(
				hInstance,
				0, 0,
				WND_W, WND_H,
				WND_TITLE)))
		{
			//Dx11�p�̏�����.
			if (SUCCEEDED(g_pCMain->InitD3D()))
			{
				//���b�Z�[�W���[�v.
				g_pCMain->Loop();
			}
		}
		//�I��.
		g_pCMain->DestroyD3D();	//Direct3D�̉��.
		SAFE_DELETE(g_pCMain);	//�N���X�̔j��.
	}

	return 0;
}

//=================================================.
//	�E�B���h�E�v���V�[�W���[.
//=================================================.
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT uMsg,
	WPARAM wPara, LPARAM lParam)
{
	//�v���V�[�W���[.
	return g_pCMain->MsgProc(hWnd, uMsg, wPara, lParam);
}

/**************************************************************
*	���C���N���X.
**/
//=================================================.
//	�R���X�g���N�^.
//=================================================.
CMain::CMain()
	: m_hWnd(nullptr)	//���������X�g�ƌĂ�.
	, m_pDevice11(nullptr)
	, m_pContext11(nullptr)
	, m_pSwapChain(nullptr)
	, m_pBackBuffer_TexRTV(nullptr)
	, m_pBackBuffer_DSTex(nullptr)
	, m_pBackBuffer_DSTexDSV(nullptr)
	, m_vLight(0.0f, 5.0f, 0.0f)	//���C�g����.
	, m_Camera()
	, m_mView()
	, m_mProj()

	, m_pCSceneManager	(nullptr)
	, m_pCLoad			(nullptr)
	, m_bFullScreenFlag	(false)
{	
	//�J����(���_)�ʒu.
	m_Camera.vPos = D3DXVECTOR3(0.0f, 3.0f, -5.0f);

	//���������[�N.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

}


//=================================================.
//	�f�X�g���N�^.
//=================================================.
CMain::~CMain()
{
}

//�E�B���h�E�������֐�.
HRESULT CMain::InitWindow(
	HINSTANCE hInstance,	//�C���X�^���X.
	INT x, INT y,			//�E�B���h�Ex,y���W.
	INT width, INT height,	//�E�B���h�E��,����.
	const char* WindowName)		//�E�B���h�E��.
{
	//�t���X�N���[���𕷂�.
	if (MessageBox(nullptr, "�t���X�N���[���ɂ��܂����H.", "�I��", MB_YESNO) == IDYES) {
		m_bFullScreenFlag = true;
	}


	//�E�B���h�E�̒�`.
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(wc));	//������(0��ݒ�).

	wc.cbSize		= sizeof(wc);
	wc.style		= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	= WndProc;
	wc.hInstance	= hInstance;
	wc.hIcon		= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = APP_NAME;
	wc.hIconSm		= LoadIcon(nullptr, IDI_APPLICATION);

	//�E�B���h�E�N���X��Windows�ɓo�^.
	if (!RegisterClassEx(&wc)) {
		_ASSERT_EXPR(false, L"�E�B���h�E�N���X�̓o�^�Ɏ��s");
		return E_FAIL;
	}

	//�E�B���h�E�̍쐬.
	m_hWnd = CreateWindow(
		APP_NAME,			//�A�v����.
		WindowName,			//�E�B���h�E�^�C�g��.
		WS_OVERLAPPEDWINDOW,//�E�B���h�E���(����).
		x, y,				//�\���ʒux,y���W.
		width, height,		//�E�B���h�E��,����.
		nullptr,			//�e�E�B���h�E�n���h��.
		nullptr,			//���j���[�ݒ�.
		hInstance,			//�C���X�^���X�ԍ�.
		nullptr);			//�E�B���h�E�쐬���ɔ�������C�x���g�ɓn���f�[�^.
	if (!m_hWnd) {
		_ASSERT_EXPR(false, "�E�B���h�E�쐬���s");
		return E_FAIL;
	}

	//�E�B���h�E�̕\��.
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

//�E�B���h�E�֐�(���b�Z�[�W���̏���).
LRESULT CMain::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg) {
	case WM_DESTROY://�E�B���h�E���j�����ꂽ�Ƃ�.
		//�A�v���P�[�V�����̏I����Windows�ɒʒm����.
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://�L�[�{�[�h�������ꂽ�Ƃ�.
		//�L�[�ʂ̏���.
		switch (static_cast<char>(wParam)) {
		case VK_ESCAPE:	//ESC�L�[.
			if (MessageBox(nullptr,
				"�Q�[�����I�����܂����H", "�x��", MB_YESNO) == IDYES)
			{
				//�E�B���h�E��j������.
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	}

	//���C���ɕԂ����.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//���b�Z�[�W���[�v.
void CMain::Loop()
{

	//�ǂݍ��݃N���X.
	m_pCLoad = new CLoad();
	m_pCLoad->Init(m_hWnd, m_pDevice11, m_pContext11);

	//���b�V���ǂݍ��݊֐�.
	LoadMesh();
	m_pCSceneManager = new CSceneManager();



	//----------------------------------------------------.
	//	�t���[�����[�g��������.
	//----------------------------------------------------.
	float Rate = 0.0f;				//���[�g.
	float FPS = 60.0f;				//FPS�l.
	DWORD sync_old = timeGetTime();	//�ߋ�����.
	DWORD sync_now;					//���ݎ���

	//���ԏ����̂��߁A�ŏ��P�ʂ��P�~���b�ɕύX.
	timeBeginPeriod(1);
	Rate = 1000.0f / FPS;	//���z���Ԃ��Z�o.

	//���b�Z�[�W���[�v.
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		sync_now = timeGetTime();		//���݂̎��Ԃ��擾.

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(sync_now - sync_old >= Rate)
		{
			sync_old = sync_now;		//���ݎ��Ԃɒu������.

			//�X�V�����֐�.
			UpDate();
			//�`�揈���֐�.
			Render();
			//�ǂݍ��ݏ����֐�.
			Load();
		}
	}
	//�A�v���P�[�V�����̏I��.
}

//�ǂݍ��ݏ����֐�.
void CMain::Load()
{
	if (m_pCSceneManager->GetLoadFinish() == false) {
		//�V�[���̓ǂݍ���.
		m_pCSceneManager->InitLoad(m_hWnd,m_pDevice9, m_pDevice11, m_pContext11);
	}
}

//�X�V�����֐�.
void CMain::UpDate()
{
	//�J�[�\���폜.
	ShowCursor(false);

	if (m_pCSceneManager->GetLoadFinish() == true) {
		//---------�V�[���J��-----------//.
		m_pCSceneManager->SceneChange();	//�V�[���ύX����.

		m_pCSceneManager->UpDate();			//�V�[���X�V����.

	}

}

//�����_�����O(�`��).
void CMain::Render()
{
	ClearBackBuffer();
	Camera();
	Proj();
	if (m_pCSceneManager->GetLoadFinish() == true) {
		m_pCSceneManager->Render(m_mProj, m_vLight);
	}
	else {
		m_pCLoad->Render();
	}

	//�����_�����O���ꂽ�C���[�W��\��.
	m_pSwapChain->Present(0, 0);
}

/*****************************************************
*	��������RD.
*/
//DirectX������.
HRESULT CMain::InitD3D()
{
	//m_hWnd = hWnd;

		//�uDirect3D�v�I�u�W�F�N�g�̍쐬.
	m_pD3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3d9 == nullptr) {
		_ASSERT_EXPR(false, L"Dx9�I�u�W�F�N�g�쐬���s");
		return E_FAIL;
	}

	//Direct3D�f�o�C�X�I�u�W�F�N�g�̍쐬.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;			//�o�b�N�o�b�t�@�̃t�H�[�}�b�g�i�f�t�H���g�j.
	d3dpp.BackBufferCount = 1;						//�o�b�N�o�b�t�@�̐�.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//�X���b�v�G�t�F�N��(�f�t�H���g).
	d3dpp.Windowed = true;					//�E�B���h�E���[�h.
	d3dpp.EnableAutoDepthStencil = true;					//�X�e���V���L��.
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				//�X�e���V���̃t�H�[�}�b�g(16bit).

	//�f�o�C�X�쐬(HAL���[�h:�`��ƒ��_������GPU�ōs��).
	if (FAILED(m_pD3d9->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pDevice9)))
	{
		//�f�o�C�X�쐬(HAL���[�h:�`���GPU�A���_������CPU�ōs��).
		if (FAILED(m_pD3d9->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pDevice9)))
		{
			MessageBox(nullptr,
				"HAL���[�h�Ńf�o�C�X�쐬�ł��܂���\nREF���[�h�ōĎ��s���܂�",
				"�x��", MB_OK);

			//�f�o�C�X�쐬(REF���[�h:�`���CPU�A���_������GPU�ōs��).
			if (FAILED(m_pD3d9->CreateDevice(
				D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &m_pDevice9)))
			{
				//�f�o�C�X�쐬(REF���[�h:�`��ƒ��_������CPU�ōs��).
				if (FAILED(m_pD3d9->CreateDevice(
					D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &m_pDevice9)))
				{
					MessageBox(nullptr,
						"Direct3D�f�o�C�X�쐬���s", "�x��", MB_OK);
					return E_FAIL;
				}
			}
		}
	}


	//----------------------------------------------------------.
	// �f�o�C�X�ƃX���b�v�`�F�[���֌W.
	//----------------------------------------------------------.

	//�X���b�v�`�F�[���\����.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));						//0�ŏ�����.
	sd.BufferCount = 1;									//�o�b�N�o�b�t�@�̐�.
	sd.BufferDesc.Width = WND_W;						//�o�b�N�o�b�t�@�̕�.
	sd.BufferDesc.Height = WND_H;						//�o�b�N�o�b�t�@�̍���.
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//�t�H�[�}�b�g�i32�r�b�g�J���[�j.
	sd.BufferDesc.RefreshRate.Numerator = 60;			//���t���b�V�����[�g(����) ��FPS:60.
	sd.BufferDesc.RefreshRate.Denominator = 1;			//���t���b�V�����[�g�i���q�j.
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//�g����(�\����).
	sd.OutputWindow = m_hWnd;							//�E�B���h�E�n���h��.
	sd.SampleDesc.Count = 1;							//�}���`�T���v���̐�.
	sd.SampleDesc.Quality = 0;							//�}���`�T���v���̃N�I���e�B.
	if (m_bFullScreenFlag == false) {
		sd.Windowed = TRUE;
	}
	else {
		sd.Windowed = FALSE;									//�E�B���h�E���[�h(�t���X�N���[������FALSE).
	}
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//�쐬�����݂�@�\���x���̗D����w��.
	//	(GPU���T�|�[�g����@�\�Z�b�g�̒�`).
	//	D3D_FEATURE_LEVEL�񋓌^�̔z��.
	//	D3D_FEATURE_LEVEL_11_0:Direct3D 11.0 �� GPU���x��.
	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;		//�z��̗v�f��.

	

	//�f�o�C�X�ƃX���b�v�`�F�[���̍쐬.
	//�n�[�h�E�F�A(GPU)�f�o�C�X�ł̍쐬.
	if (FAILED(
		D3D11CreateDeviceAndSwapChain(
			nullptr,					//�r�f�I�A�_�v�^�ւ̃|�C���^.
			D3D_DRIVER_TYPE_HARDWARE,	//�쐬����f�o�C�X�̎��.
			nullptr,					//�\�t�g�E�F�A���X�^���C�U����������DLL�̃n���h��.
			0,							//�L���ɂ��郉���^�C�����C���[.
			&pFeatureLevels,			//�쐬�����݂�@�\���x���̏������w�肷��z��ւ̃|�C���^.
			1,							//���̗v�f��.
			D3D11_SDK_VERSION,			//SDK�̃o�[�W����.
			&sd,						//�X���b�v�`�F�[���̏������p�����[�^�̃|�C���^.
			&m_pSwapChain,				//(out)�����_�����O�Ɏg�p����X���b�v�`�F�[��.
			&m_pDevice11,				//(out)�쐬���ꂽ�f�o�C�X.
			pFeatureLevel,				//�@�\���x���̔z��ɂ���ŏ��̗v�f��\���|�C���^.
			&m_pContext11)))			//(out)�f�o�C�X�R���e�L�X�g.
	{
		//WARP�f�o�C�X�̍쐬.
		//	D3D_FEATURE_LEVEL_9_1�`D3D_FEATURE_LEVEL_10_1.
		if (FAILED(
			D3D11CreateDeviceAndSwapChain(
				nullptr,					//�r�f�I�A�_�v�^�ւ̃|�C���^.
				D3D_DRIVER_TYPE_WARP,		//�쐬����f�o�C�X�̎��.
				nullptr,					//�\�t�g�E�F�A���X�^���C�U����������DLL�̃n���h��.
				0,							//�L���ɂ��郉���^�C�����C���[.
				&pFeatureLevels,			//�쐬�����݂�@�\���x���̏������w�肷��z��ւ̃|�C���^.
				1,							//���̗v�f��.
				D3D11_SDK_VERSION,			//SDK�̃o�[�W����.
				&sd,						//�X���b�v�`�F�[���̏������p�����[�^�̃|�C���^.
				&m_pSwapChain,				//(out)�����_�����O�Ɏg�p����X���b�v�`�F�[��.
				&m_pDevice11,				//(out)�쐬���ꂽ�f�o�C�X.
				pFeatureLevel,				//�@�\���x���̔z��ɂ���ŏ��̗v�f��\���|�C���^.
				&m_pContext11)))			//(out)�f�o�C�X�R���e�L�X�g.
		{
			//���t�@�����X�f�o�C�X�̍쐬.
			//	DirectX SDK���C���X�g�[������Ă��Ȃ��Ǝg���Ȃ�.
			if (FAILED(
				D3D11CreateDeviceAndSwapChain(
					nullptr,					//�r�f�I�A�_�v�^�ւ̃|�C���^.
					D3D_DRIVER_TYPE_REFERENCE,	//�쐬����f�o�C�X�̎��.
					nullptr,					//�\�t�g�E�F�A���X�^���C�U����������DLL�̃n���h��.
					0,							//�L���ɂ��郉���^�C�����C���[.
					&pFeatureLevels,			//�쐬�����݂�@�\���x���̏������w�肷��z��ւ̃|�C���^.
					1,							//���̗v�f��.
					D3D11_SDK_VERSION,			//SDK�̃o�[�W����.
					&sd,						//�X���b�v�`�F�[���̏������p�����[�^�̃|�C���^.
					&m_pSwapChain,				//(out)�����_�����O�Ɏg�p����X���b�v�`�F�[��.
					&m_pDevice11,				//(out)�쐬���ꂽ�f�o�C�X.
					pFeatureLevel,				//�@�\���x���̔z��ɂ���ŏ��̗v�f��\���|�C���^.
					&m_pContext11)))			//(out)�f�o�C�X�R���e�L�X�g.
			{
				MessageBox(nullptr, "�f�o�C�X�ƃX���b�v�`�F�[���쐬���s", "Error", MB_OK);
				return E_FAIL;
			}
		}
	}

	//�e��e�N�X�`���Ƃ���ɕt�т���e��r���[�i��ʁj���쐬.

	//------------------------------------------------.
	//	�o�b�N�o�b�t�@����:�J���[�o�b�t�@�ݒ�.
	//------------------------------------------------.
	//�o�b�N�o�b�t�@�e�N�X�`�����擾(���ɂ���̂ō쐬�ł͂Ȃ�).
	ID3D11Texture2D* pBackBuffer_Tex = nullptr;
	m_pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),	// __uuidof:���Ɋ֘A�t�����ꂽGUID���擾.
									//			Texture2D�̗B��̂��̂Ƃ��Ĉ���.
		(LPVOID*)&pBackBuffer_Tex);	//(out)�o�b�N�o�b�t�@�e�N�X�`��.

	//���̃e�N�X�`���ɑ΂��ă����_�[�^�[�Q�b�g�r���[(RTV)���쐬.
	m_pDevice11->CreateRenderTargetView(
		pBackBuffer_Tex,
		nullptr,
		&m_pBackBuffer_TexRTV);		//(out)RTV.

	//�o�b�N�o�b�t�@�e�N�X�`�������.
	SAFE_RELEASE(pBackBuffer_Tex);

	//-----------------------------------------------------.
	//	�o�b�N�o�b�t�@����:�f�v�X(�[�x)�X�e���V���֌W.
	//-----------------------------------------------------.
	//�f�v�X(�[��or�[�x)�X�e���V���r���[�p�̃e�N�X�`�����쐬.
	D3D11_TEXTURE2D_DESC	descDepth;
	descDepth.Width = WND_W;						//��.
	descDepth.Height = WND_H;						//����.
	descDepth.MipLevels = 1;						//�~�j�}�b�v���x���F�P.
	descDepth.ArraySize = 1;						//�z�񐔁F�P.
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;		//32�r�b�g�t�H�[�}�b�g.
	descDepth.SampleDesc.Count = 1;					//�}���`�T���v���̐�.
	descDepth.SampleDesc.Quality = 0;				//�}���`�T���v���̃N�I���e�B.
	descDepth.Usage = D3D11_USAGE_DEFAULT;			//�g�p���@�F�f�t�H���g.
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//�[�x(�X�e���V���Ƃ��Ďg�p).
	descDepth.CPUAccessFlags = 0;					//CPU����̓A�N�Z�X���Ȃ�.
	descDepth.MiscFlags = 0;						//���̑��̐ݒ�Ȃ�.

	m_pDevice11->CreateTexture2D(
		&descDepth,
		nullptr,
		&m_pBackBuffer_DSTex);		//(out)�f�v�X�X�e���V���p�e�N�X�`��.

	//���̃e�N�X�`���ɑ΂��ăf�v�X�X�e���V���r���[(DSV)���쐬.
	m_pDevice11->CreateDepthStencilView(
		m_pBackBuffer_DSTex,
		nullptr,
		&m_pBackBuffer_DSTexDSV);	//(out)DSV.

	//�����_�[�^�[�Q�b�g�r���[�ƃf�v�X�X�e���V���r���[���p�C�v���C���ɃZ�b�g.
	m_pContext11->OMSetRenderTargets(
		1,
		&m_pBackBuffer_TexRTV,
		m_pBackBuffer_DSTexDSV);

	//---------------------------------------------------------------------.
	//	�r���[�|�[�g�ݒ�.
	//---------------------------------------------------------------------.
	D3D11_VIEWPORT vp;
	vp.Width = WND_W;		//��.
	vp.Height = WND_H;		//����.
	vp.MinDepth = 0.0f;		//�ŏ��[�x(��O).
	vp.MaxDepth = 1.0f;		//�ő�[�x(��)0�ɋ߂���΋߂��P�ɋ߂Â���Ή���.
	vp.TopLeftX = 0.0f;		//����ʒux.
	vp.TopLeftY = 0.0f;		//����ʒuy.

	m_pContext11->RSSetViewports(1, &vp);

	//-----------------------------------------------------------------------.
	//	���X�^���C�Y�i�ʂ̓h��Ԃ����j�̐ݒ�.
	//-----------------------------------------------------------------------.
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.FillMode = D3D11_FILL_SOLID;					//�h��Ԃ�(�\���b�h).
	rdc.CullMode = D3D11_CULL_NONE;						//D3D11_CULL_NONE : �J�����O��؂�(���w�ʂ�`�悷��).
	rdc.FrontCounterClockwise = FALSE;					//�|���S���̕\�������肷��t���O.
	rdc.DepthClipEnable = FALSE;						//�����ɂ��ẴN���b�s���O�L��.

	ID3D11RasterizerState* pRs = nullptr;
	m_pDevice11->CreateRasterizerState(&rdc, &pRs);
	m_pContext11->RSSetState(pRs);
	SAFE_RELEASE(pRs);


	return S_OK;
}

//Direct3D�I������.
void CMain::DestroyD3D()
{
	SAFE_DELETE(m_pCLoad);
	SAFE_DELETE(m_pCSceneManager);		//�V�[���Ǘ��N���X.

	//Direct3D�I�u�W�F�N�g�����.
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pContext11);
	SAFE_RELEASE(m_pDevice11);
}

//���b�V���̓ǂݍ��݊֐�.
HRESULT CMain::LoadMesh()
{

	m_CDepth_Stencil.Init(m_pDevice11, m_pContext11);

	_ASSERT_EXPR(m_hWnd != nullptr, L"CMain.cpp����");


	//�J�����̐ݒ�.
	m_Camera.vPos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 1.0f, 6.0f);

	return S_OK;
}

//�o�b�N�o�b�t�@�N���A�֐�.
void CMain::ClearBackBuffer()
{
	//��ʂ̃N���A.
	//float ClearColor[4] = { 242.0f/255.0f, 171.0f / 255.0f, 145.0f / 255.0f, 1.0f };		//�N���A�F(RGBA�̏�).
	float ClearColor[4] = { 0.0f, 0.0f, 0.5f, 1.0f };		//�N���A�F(RGBA�̏�).
	//�J���[�o�b�N�o�b�t�@.
	m_pContext11->ClearRenderTargetView(
		m_pBackBuffer_TexRTV, ClearColor);
	//�f�v�X�X�e���V���o�b�N�o�b�t�@.
	m_pContext11->ClearDepthStencilView(
		m_pBackBuffer_DSTexDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0);
}

//�J�����֐�.
void CMain::Camera()
{
	//------------------------------------------------------------.
	//		�Ǐ]�J�����ݒ�.
	//------------------------------------------------------------.
	//�J�����ʒu(���@�̔w������)�̐ݒ�.
	m_Camera.vPos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);	//���@�̈ʒu���R�s�[.
	m_Camera.vLook = D3DXVECTOR3(0.0f, 1.0f, 6.0f);

	//�r���[(�J����)�ϊ�.
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//���(�x�N�g��).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)�r���[�v�Z����.
		&m_Camera.vPos, &m_Camera.vLook, &vUpVec);

}

//�v���W�F�N�V�����֐�.
void CMain::Proj()
{
	//�v���W�F�N�V����(�ˉe)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,												//(out)�v���W�F�N�V�����v�Z����.
		static_cast<FLOAT>(D3DX_PI / 4.0),						//y�����̎���(���W�A���w��)���l��傫�������王�삪�����Ȃ�.
		static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H),	//�A�X�y�N�g��(��������).
		0.1f,													//�߂��r���[���ʂ�z�l.
		100.0f);												//�����r���[���ʂ�z�l.

}

