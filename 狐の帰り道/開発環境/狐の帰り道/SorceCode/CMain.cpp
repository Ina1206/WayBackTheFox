#include "CMain.h"
#include "Global.h"
#include <crtdbg.h>	
#include "MyMacro.h"

//グローバル変数.
CMain* g_pCMain = nullptr;

//=================================================.
//	メイン関数.
//=================================================.
INT WINAPI WinMain(
	HINSTANCE hInstance,	//インスタンス番号(ウィンドウの番号).
	HINSTANCE hPrevInstance,
	PSTR lpCmdLine,
	INT nCmdShow)
{
	g_pCMain = new CMain();	//初期化＆クラス宣言.

	if (g_pCMain != nullptr) {

		//ウィンドウ作成成功したら.
		if (SUCCEEDED(
			g_pCMain->InitWindow(
				hInstance,
				0, 0,
				WND_W, WND_H,
				WND_TITLE)))
		{
			//Dx11用の初期化.
			if (SUCCEEDED(g_pCMain->InitD3D()))
			{
				//メッセージループ.
				g_pCMain->Loop();
			}
		}
		//終了.
		g_pCMain->DestroyD3D();	//Direct3Dの解放.
		SAFE_DELETE(g_pCMain);	//クラスの破棄.
	}

	return 0;
}

//=================================================.
//	ウィンドウプロシージャー.
//=================================================.
LRESULT CALLBACK WndProc(
	HWND hWnd, UINT uMsg,
	WPARAM wPara, LPARAM lParam)
{
	//プロシージャー.
	return g_pCMain->MsgProc(hWnd, uMsg, wPara, lParam);
}

/**************************************************************
*	メインクラス.
**/
//=================================================.
//	コンストラクタ.
//=================================================.
CMain::CMain()
	: m_hWnd(nullptr)	//初期化リストと呼ぶ.
	, m_pDevice11(nullptr)
	, m_pContext11(nullptr)
	, m_pSwapChain(nullptr)
	, m_pBackBuffer_TexRTV(nullptr)
	, m_pBackBuffer_DSTex(nullptr)
	, m_pBackBuffer_DSTexDSV(nullptr)
	, m_vLight(0.0f, 5.0f, 0.0f)	//ライト方向.
	, m_Camera()
	, m_mView()
	, m_mProj()

	, m_pCSceneManager	(nullptr)
	, m_pCLoad			(nullptr)
	, m_bFullScreenFlag	(false)
{	
	//カメラ(視点)位置.
	m_Camera.vPos = D3DXVECTOR3(0.0f, 3.0f, -5.0f);

	//メモリリーク.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

}


//=================================================.
//	デストラクタ.
//=================================================.
CMain::~CMain()
{
}

//ウィンドウ初期化関数.
HRESULT CMain::InitWindow(
	HINSTANCE hInstance,	//インスタンス.
	INT x, INT y,			//ウィンドウx,y座標.
	INT width, INT height,	//ウィンドウ幅,高さ.
	const char* WindowName)		//ウィンドウ名.
{
	//フルスクリーンを聞く.
	if (MessageBox(nullptr, "フルスクリーンにしますか？.", "選択", MB_YESNO) == IDYES) {
		m_bFullScreenFlag = true;
	}


	//ウィンドウの定義.
	WNDCLASSEX wc;

	ZeroMemory(&wc, sizeof(wc));	//初期化(0を設定).

	wc.cbSize		= sizeof(wc);
	wc.style		= CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc	= WndProc;
	wc.hInstance	= hInstance;
	wc.hIcon		= LoadIcon(nullptr, IDI_APPLICATION);
	wc.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
	wc.lpszClassName = APP_NAME;
	wc.hIconSm		= LoadIcon(nullptr, IDI_APPLICATION);

	//ウィンドウクラスをWindowsに登録.
	if (!RegisterClassEx(&wc)) {
		_ASSERT_EXPR(false, L"ウィンドウクラスの登録に失敗");
		return E_FAIL;
	}

	//ウィンドウの作成.
	m_hWnd = CreateWindow(
		APP_NAME,			//アプリ名.
		WindowName,			//ウィンドウタイトル.
		WS_OVERLAPPEDWINDOW,//ウィンドウ種別(普通).
		x, y,				//表示位置x,y座標.
		width, height,		//ウィンドウ幅,高さ.
		nullptr,			//親ウィンドウハンドル.
		nullptr,			//メニュー設定.
		hInstance,			//インスタンス番号.
		nullptr);			//ウィンドウ作成時に発生するイベントに渡すデータ.
	if (!m_hWnd) {
		_ASSERT_EXPR(false, "ウィンドウ作成失敗");
		return E_FAIL;
	}

	//ウィンドウの表示.
	ShowWindow(m_hWnd, SW_SHOW);
	UpdateWindow(m_hWnd);

	return S_OK;
}

//ウィンドウ関数(メッセージ毎の処理).
LRESULT CMain::MsgProc(
	HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam) 
{
	switch (uMsg) {
	case WM_DESTROY://ウィンドウが破棄されたとき.
		//アプリケーションの終了をWindowsに通知する.
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN://キーボードが押されたとき.
		//キー別の処理.
		switch (static_cast<char>(wParam)) {
		case VK_ESCAPE:	//ESCキー.
			if (MessageBox(nullptr,
				"ゲームを終了しますか？", "警告", MB_YESNO) == IDYES)
			{
				//ウィンドウを破棄する.
				DestroyWindow(hWnd);
			}
			break;
		}
		break;
	}

	//メインに返す情報.
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//メッセージループ.
void CMain::Loop()
{

	//読み込みクラス.
	m_pCLoad = new CLoad();
	m_pCLoad->Init(m_hWnd, m_pDevice11, m_pContext11);

	//メッシュ読み込み関数.
	LoadMesh();
	m_pCSceneManager = new CSceneManager();



	//----------------------------------------------------.
	//	フレームレート調整準備.
	//----------------------------------------------------.
	float Rate = 0.0f;				//レート.
	float FPS = 60.0f;				//FPS値.
	DWORD sync_old = timeGetTime();	//過去時間.
	DWORD sync_now;					//現在時間

	//時間処理のため、最小単位を１ミリ秒に変更.
	timeBeginPeriod(1);
	Rate = 1000.0f / FPS;	//理想時間を算出.

	//メッセージループ.
	MSG msg = { 0 };
	ZeroMemory(&msg, sizeof(msg));

	while (msg.message != WM_QUIT)
	{
		Sleep(1);
		sync_now = timeGetTime();		//現在の時間を取得.

		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(sync_now - sync_old >= Rate)
		{
			sync_old = sync_now;		//現在時間に置き換え.

			//更新処理関数.
			UpDate();
			//描画処理関数.
			Render();
			//読み込み処理関数.
			Load();
		}
	}
	//アプリケーションの終了.
}

//読み込み処理関数.
void CMain::Load()
{
	if (m_pCSceneManager->GetLoadFinish() == false) {
		//シーンの読み込み.
		m_pCSceneManager->InitLoad(m_hWnd,m_pDevice9, m_pDevice11, m_pContext11);
	}
}

//更新処理関数.
void CMain::UpDate()
{
	//カーソル削除.
	ShowCursor(false);

	if (m_pCSceneManager->GetLoadFinish() == true) {
		//---------シーン遷移-----------//.
		m_pCSceneManager->SceneChange();	//シーン変更処理.

		m_pCSceneManager->UpDate();			//シーン更新処理.

	}

}

//レンダリング(描画).
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

	//レンダリングされたイメージを表示.
	m_pSwapChain->Present(0, 0);
}

/*****************************************************
*	ここから３D.
*/
//DirectX初期化.
HRESULT CMain::InitD3D()
{
	//m_hWnd = hWnd;

		//「Direct3D」オブジェクトの作成.
	m_pD3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3d9 == nullptr) {
		_ASSERT_EXPR(false, L"Dx9オブジェクト作成失敗");
		return E_FAIL;
	}

	//Direct3Dデバイスオブジェクトの作成.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;			//バックバッファのフォーマット（デフォルト）.
	d3dpp.BackBufferCount = 1;						//バックバッファの数.
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//スワップエフェクと(デフォルト).
	d3dpp.Windowed = true;					//ウィンドウモード.
	d3dpp.EnableAutoDepthStencil = true;					//ステンシル有効.
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;				//ステンシルのフォーマット(16bit).

	//デバイス作成(HALモード:描画と頂点処理をGPUで行う).
	if (FAILED(m_pD3d9->CreateDevice(
		D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp, &m_pDevice9)))
	{
		//デバイス作成(HALモード:描画はGPU、頂点処理をCPUで行う).
		if (FAILED(m_pD3d9->CreateDevice(
			D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp, &m_pDevice9)))
		{
			MessageBox(nullptr,
				"HALモードでデバイス作成できません\nREFモードで再試行します",
				"警告", MB_OK);

			//デバイス作成(REFモード:描画はCPU、頂点処理をGPUで行う).
			if (FAILED(m_pD3d9->CreateDevice(
				D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd,
				D3DCREATE_HARDWARE_VERTEXPROCESSING,
				&d3dpp, &m_pDevice9)))
			{
				//デバイス作成(REFモード:描画と頂点処理をCPUで行う).
				if (FAILED(m_pD3d9->CreateDevice(
					D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, m_hWnd,
					D3DCREATE_SOFTWARE_VERTEXPROCESSING,
					&d3dpp, &m_pDevice9)))
				{
					MessageBox(nullptr,
						"Direct3Dデバイス作成失敗", "警告", MB_OK);
					return E_FAIL;
				}
			}
		}
	}


	//----------------------------------------------------------.
	// デバイスとスワップチェーン関係.
	//----------------------------------------------------------.

	//スワップチェーン構造体.
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));						//0で初期化.
	sd.BufferCount = 1;									//バックバッファの数.
	sd.BufferDesc.Width = WND_W;						//バックバッファの幅.
	sd.BufferDesc.Height = WND_H;						//バックバッファの高さ.
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;	//フォーマット（32ビットカラー）.
	sd.BufferDesc.RefreshRate.Numerator = 60;			//リフレッシュレート(分母) ※FPS:60.
	sd.BufferDesc.RefreshRate.Denominator = 1;			//リフレッシュレート（分子）.
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	//使い方(表示先).
	sd.OutputWindow = m_hWnd;							//ウィンドウハンドル.
	sd.SampleDesc.Count = 1;							//マルチサンプルの数.
	sd.SampleDesc.Quality = 0;							//マルチサンプルのクオリティ.
	if (m_bFullScreenFlag == false) {
		sd.Windowed = TRUE;
	}
	else {
		sd.Windowed = FALSE;									//ウィンドウモード(フルスクリーン時はFALSE).
	}
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	//作成を試みる機能レベルの優先を指定.
	//	(GPUがサポートする機能セットの定義).
	//	D3D_FEATURE_LEVEL列挙型の配列.
	//	D3D_FEATURE_LEVEL_11_0:Direct3D 11.0 の GPUレベル.
	D3D_FEATURE_LEVEL pFeatureLevels = D3D_FEATURE_LEVEL_11_0;
	D3D_FEATURE_LEVEL* pFeatureLevel = nullptr;		//配列の要素数.

	

	//デバイスとスワップチェーンの作成.
	//ハードウェア(GPU)デバイスでの作成.
	if (FAILED(
		D3D11CreateDeviceAndSwapChain(
			nullptr,					//ビデオアダプタへのポインタ.
			D3D_DRIVER_TYPE_HARDWARE,	//作成するデバイスの種類.
			nullptr,					//ソフトウェアラスタライザを実装するDLLのハンドル.
			0,							//有効にするランタイムレイヤー.
			&pFeatureLevels,			//作成を試みる機能レベルの順序を指定する配列へのポインタ.
			1,							//↑の要素数.
			D3D11_SDK_VERSION,			//SDKのバージョン.
			&sd,						//スワップチェーンの初期化パラメータのポインタ.
			&m_pSwapChain,				//(out)レンダリングに使用するスワップチェーン.
			&m_pDevice11,				//(out)作成されたデバイス.
			pFeatureLevel,				//機能レベルの配列にある最初の要素を表すポインタ.
			&m_pContext11)))			//(out)デバイスコンテキスト.
	{
		//WARPデバイスの作成.
		//	D3D_FEATURE_LEVEL_9_1～D3D_FEATURE_LEVEL_10_1.
		if (FAILED(
			D3D11CreateDeviceAndSwapChain(
				nullptr,					//ビデオアダプタへのポインタ.
				D3D_DRIVER_TYPE_WARP,		//作成するデバイスの種類.
				nullptr,					//ソフトウェアラスタライザを実装するDLLのハンドル.
				0,							//有効にするランタイムレイヤー.
				&pFeatureLevels,			//作成を試みる機能レベルの順序を指定する配列へのポインタ.
				1,							//↑の要素数.
				D3D11_SDK_VERSION,			//SDKのバージョン.
				&sd,						//スワップチェーンの初期化パラメータのポインタ.
				&m_pSwapChain,				//(out)レンダリングに使用するスワップチェーン.
				&m_pDevice11,				//(out)作成されたデバイス.
				pFeatureLevel,				//機能レベルの配列にある最初の要素を表すポインタ.
				&m_pContext11)))			//(out)デバイスコンテキスト.
		{
			//リファレンスデバイスの作成.
			//	DirectX SDKがインストールされていないと使えない.
			if (FAILED(
				D3D11CreateDeviceAndSwapChain(
					nullptr,					//ビデオアダプタへのポインタ.
					D3D_DRIVER_TYPE_REFERENCE,	//作成するデバイスの種類.
					nullptr,					//ソフトウェアラスタライザを実装するDLLのハンドル.
					0,							//有効にするランタイムレイヤー.
					&pFeatureLevels,			//作成を試みる機能レベルの順序を指定する配列へのポインタ.
					1,							//↑の要素数.
					D3D11_SDK_VERSION,			//SDKのバージョン.
					&sd,						//スワップチェーンの初期化パラメータのポインタ.
					&m_pSwapChain,				//(out)レンダリングに使用するスワップチェーン.
					&m_pDevice11,				//(out)作成されたデバイス.
					pFeatureLevel,				//機能レベルの配列にある最初の要素を表すポインタ.
					&m_pContext11)))			//(out)デバイスコンテキスト.
			{
				MessageBox(nullptr, "デバイスとスワップチェーン作成失敗", "Error", MB_OK);
				return E_FAIL;
			}
		}
	}

	//各種テクスチャとそれに付帯する各種ビュー（画面）を作成.

	//------------------------------------------------.
	//	バックバッファ準備:カラーバッファ設定.
	//------------------------------------------------.
	//バックバッファテクスチャを取得(既にあるので作成ではない).
	ID3D11Texture2D* pBackBuffer_Tex = nullptr;
	m_pSwapChain->GetBuffer(
		0,
		__uuidof(ID3D11Texture2D),	// __uuidof:式に関連付けされたGUIDを取得.
									//			Texture2Dの唯一のものとして扱う.
		(LPVOID*)&pBackBuffer_Tex);	//(out)バックバッファテクスチャ.

	//そのテクスチャに対してレンダーターゲットビュー(RTV)を作成.
	m_pDevice11->CreateRenderTargetView(
		pBackBuffer_Tex,
		nullptr,
		&m_pBackBuffer_TexRTV);		//(out)RTV.

	//バックバッファテクスチャを解放.
	SAFE_RELEASE(pBackBuffer_Tex);

	//-----------------------------------------------------.
	//	バックバッファ準備:デプス(深度)ステンシル関係.
	//-----------------------------------------------------.
	//デプス(深さor深度)ステンシルビュー用のテクスチャを作成.
	D3D11_TEXTURE2D_DESC	descDepth;
	descDepth.Width = WND_W;						//幅.
	descDepth.Height = WND_H;						//高さ.
	descDepth.MipLevels = 1;						//ミニマップレベル：１.
	descDepth.ArraySize = 1;						//配列数：１.
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;		//32ビットフォーマット.
	descDepth.SampleDesc.Count = 1;					//マルチサンプルの数.
	descDepth.SampleDesc.Quality = 0;				//マルチサンプルのクオリティ.
	descDepth.Usage = D3D11_USAGE_DEFAULT;			//使用方法：デフォルト.
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//深度(ステンシルとして使用).
	descDepth.CPUAccessFlags = 0;					//CPUからはアクセスしない.
	descDepth.MiscFlags = 0;						//その他の設定なし.

	m_pDevice11->CreateTexture2D(
		&descDepth,
		nullptr,
		&m_pBackBuffer_DSTex);		//(out)デプスステンシル用テクスチャ.

	//そのテクスチャに対してデプスステンシルビュー(DSV)を作成.
	m_pDevice11->CreateDepthStencilView(
		m_pBackBuffer_DSTex,
		nullptr,
		&m_pBackBuffer_DSTexDSV);	//(out)DSV.

	//レンダーターゲットビューとデプスステンシルビューをパイプラインにセット.
	m_pContext11->OMSetRenderTargets(
		1,
		&m_pBackBuffer_TexRTV,
		m_pBackBuffer_DSTexDSV);

	//---------------------------------------------------------------------.
	//	ビューポート設定.
	//---------------------------------------------------------------------.
	D3D11_VIEWPORT vp;
	vp.Width = WND_W;		//幅.
	vp.Height = WND_H;		//高さ.
	vp.MinDepth = 0.0f;		//最小深度(手前).
	vp.MaxDepth = 1.0f;		//最大深度(奥)0に近ければ近く１に近づければ遠い.
	vp.TopLeftX = 0.0f;		//左上位置x.
	vp.TopLeftY = 0.0f;		//左上位置y.

	m_pContext11->RSSetViewports(1, &vp);

	//-----------------------------------------------------------------------.
	//	ラスタライズ（面の塗りつぶし方）の設定.
	//-----------------------------------------------------------------------.
	D3D11_RASTERIZER_DESC rdc;
	ZeroMemory(&rdc, sizeof(rdc));
	rdc.FillMode = D3D11_FILL_SOLID;					//塗りつぶし(ソリッド).
	rdc.CullMode = D3D11_CULL_NONE;						//D3D11_CULL_NONE : カリングを切る(正背面を描画する).
	rdc.FrontCounterClockwise = FALSE;					//ポリゴンの表裏を決定するフラグ.
	rdc.DepthClipEnable = FALSE;						//距離についてのクリッピング有効.

	ID3D11RasterizerState* pRs = nullptr;
	m_pDevice11->CreateRasterizerState(&rdc, &pRs);
	m_pContext11->RSSetState(pRs);
	SAFE_RELEASE(pRs);


	return S_OK;
}

//Direct3D終了処理.
void CMain::DestroyD3D()
{
	SAFE_DELETE(m_pCLoad);
	SAFE_DELETE(m_pCSceneManager);		//シーン管理クラス.

	//Direct3Dオブジェクトを解放.
	SAFE_RELEASE(m_pBackBuffer_DSTexDSV);
	SAFE_RELEASE(m_pBackBuffer_DSTex);
	SAFE_RELEASE(m_pBackBuffer_TexRTV);
	SAFE_RELEASE(m_pSwapChain);
	SAFE_RELEASE(m_pContext11);
	SAFE_RELEASE(m_pDevice11);
}

//メッシュの読み込み関数.
HRESULT CMain::LoadMesh()
{

	m_CDepth_Stencil.Init(m_pDevice11, m_pContext11);

	_ASSERT_EXPR(m_hWnd != nullptr, L"CMain.cpp無し");


	//カメラの設定.
	m_Camera.vPos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);
	m_Camera.vLook = D3DXVECTOR3(0.0f, 1.0f, 6.0f);

	return S_OK;
}

//バックバッファクリア関数.
void CMain::ClearBackBuffer()
{
	//画面のクリア.
	//float ClearColor[4] = { 242.0f/255.0f, 171.0f / 255.0f, 145.0f / 255.0f, 1.0f };		//クリア色(RGBAの順).
	float ClearColor[4] = { 0.0f, 0.0f, 0.5f, 1.0f };		//クリア色(RGBAの順).
	//カラーバックバッファ.
	m_pContext11->ClearRenderTargetView(
		m_pBackBuffer_TexRTV, ClearColor);
	//デプスステンシルバックバッファ.
	m_pContext11->ClearDepthStencilView(
		m_pBackBuffer_DSTexDSV,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f, 0);
}

//カメラ関数.
void CMain::Camera()
{
	//------------------------------------------------------------.
	//		追従カメラ設定.
	//------------------------------------------------------------.
	//カメラ位置(自機の背中から)の設定.
	m_Camera.vPos = D3DXVECTOR3(0.0f, 3.0f, 0.0f);	//自機の位置をコピー.
	m_Camera.vLook = D3DXVECTOR3(0.0f, 1.0f, 6.0f);

	//ビュー(カメラ)変換.
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);	//上方(ベクトル).
	D3DXMatrixLookAtLH(
		&m_mView,								//(out)ビュー計算結果.
		&m_Camera.vPos, &m_Camera.vLook, &vUpVec);

}

//プロジェクション関数.
void CMain::Proj()
{
	//プロジェクション(射影)変換.
	D3DXMatrixPerspectiveFovLH(
		&m_mProj,												//(out)プロジェクション計算結果.
		static_cast<FLOAT>(D3DX_PI / 4.0),						//y方向の視野(ラジアン指定)数値を大きくしたら視野が狭くなる.
		static_cast<FLOAT>(WND_W) / static_cast<FLOAT>(WND_H),	//アスペクト比(幅÷高さ).
		0.1f,													//近いビュー平面のz値.
		100.0f);												//遠いビュー平面のz値.

}

