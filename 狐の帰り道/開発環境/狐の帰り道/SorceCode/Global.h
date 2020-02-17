#pragma once
//警告についてのコード分析を無効にする.4005:再定義.
#pragma warning( disable:4005 )
#include <Windows.h>
#include <crtdbg.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>					//「D3DX～」の定義使用時に必要.
#include <D3D10.h>

#include "MyMacro.h"


#ifdef _DEBUG

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <cstdlib>
#define new  ::new(_NORMAL_BLOCK, __FILE__, __LINE__)

//#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//ライブラリ読み込み.
#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "d3dx11.lib")
#pragma comment( lib, "d3d11.lib")
#pragma comment( lib, "d3dx10.lib")	//「D3DX～」の定義使用時に必要.

//=================================================.
//	定数.
//=================================================.
//定数宣言で#defineは使わない.
const int WND_W = 1280;	//ウィンドウの幅.
const int WND_H = 720;	//ウィンドウの高さ.

