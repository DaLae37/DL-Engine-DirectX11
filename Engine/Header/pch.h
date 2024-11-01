#pragma once
//Project Setting
#define LOCALE "kor" // std::locale parameter
#define CURRENT_LANGUAGE = MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL)

//Program Setting
#define PROGRAM_NAME TEXT("DL-Engine")
#define CONSOLE_NAME TEXT("Console")

//Static Library
#pragma comment (lib,"dxgi.lib")
#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3dcompiler.lib")
#pragma comment (lib,"d2d1.lib")
#pragma comment (lib,"dwrite.lib")
#pragma comment (lib,"WindowsCodecs.lib")
#pragma comment (lib,"winmm.lib")

//Windows Header
#include <Windows.h>
#include <wincodec.h>
#include <wrl.h>
#define WRL Microsoft::WRL

//DiectX Header
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <dwrite.h>
#include <xaudio2.h>

//DirectX11
#include <d3d11_4.h>
#include <d3dcompiler.h>

//Direct2D
#include <d2d1_3.h>
#include <d2d1_3helper.h>

//Debug Header
#include <iostream>
#include <string>
#include <io.h>
#include <fcntl.h>

//Smart Pointer
#include <memory>

//Thread
#include <thread>
#include <mutex>
#define THREAD_NUM 2

//STL
#include <map>
#include <unordered_map>
#include <vector>
#include <list>
#include <set>
#include <algorithm>

//Macro Define
#define KEY_NONE 0
#define KEY_UP 1
#define KEY_DOWN 2
#define KEY_ON 3

#define SAFE_RELEASE(p) {if(p) {p->Release(); (p) = nullptr;}}
#define SAFE_DELETE(p) {if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p) {if(p){delete [](p); (p) = nullptr;}}
#define SAFE_SMART_DELETE(p) {if(p) {p.reset();}}

//Color
namespace Color {
	const D2D_COLOR_F red = { 1.0f, 0.0f, 0.0f, 1.0f };
	const D2D_COLOR_F green = { 0.0f, 1.0f, 0.0f, 1.0f };
	const D2D_COLOR_F blue = { 0.0f, 0.0f, 1.0f, 1.0f };
	const D2D_COLOR_F black = { 0.0f, 0.0f, 0.0f, 1.0f };
}