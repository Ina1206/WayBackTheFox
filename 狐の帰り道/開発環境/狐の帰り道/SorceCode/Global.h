#pragma once
//�x���ɂ��ẴR�[�h���͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning( disable:4005 )
#include <Windows.h>
#include <crtdbg.h>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>					//�uD3DX�`�v�̒�`�g�p���ɕK�v.
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

//���C�u�����ǂݍ���.
#pragma comment( lib, "winmm.lib")
#pragma comment( lib, "d3dx11.lib")
#pragma comment( lib, "d3d11.lib")
#pragma comment( lib, "d3dx10.lib")	//�uD3DX�`�v�̒�`�g�p���ɕK�v.

//=================================================.
//	�萔.
//=================================================.
//�萔�錾��#define�͎g��Ȃ�.
const int WND_W = 1280;	//�E�B���h�E�̕�.
const int WND_H = 720;	//�E�B���h�E�̍���.

