#include "pch.h"
#include "Application.h"

Application::Application(HINSTANCE hInstance, INT nCmdShow) {
	this->window = std::make_unique<Window>(hInstance, nCmdShow);
	this->device = std::make_unique<Device>();

	InitDeltaTime();
}

Application::~Application() {
	SAFE_SMART_DELETE(this->window);
	SAFE_SMART_DELETE(this->device);
}

HRESULT Application::InitApplication() {
	// Init WindowsAPI
	if (window->InitWindow() != S_OK) {
		std::wstring message = L"Init Window Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}
	if (window->FloatWindow() != S_OK) {
		std::wstring message = L"Float Window Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	// Init DirectX Devices
	if (device->InitD3D11Device(*window->getWindowHandle()) != S_OK) {
		std::wstring message = L"InitD3DDevice Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}
	if (device->InitD2DDevice(*window->getWindowHandle()) != S_OK) {
		std::wstring message = L"InitD2DDevice Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	return S_OK;
}

INT Application::DoMainLoop() {
	MSG Message = { 0, };

	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else {
			// Update Framework State
			window->WindowLoop();
			InputManagerInstance->UpdateKeyState();
			SceneManagerInstance->Update(getDeltaTime());

			// Render Graphic Elements
			device->RenderStart();
			SceneManagerInstance->Render();
			device->RenderEnd();
		}
	}
	return static_cast<INT>(Message.wParam);
}

HRESULT Application::InitManager() {
	// Init System Managers
	TextureManagerInstance->Init(device->getD2DContext().Get(), device->getD3DDevice().Get());
	if (TextureManagerInstance->getInstance() == nullptr) {
		std::wstring message = L"Init TextureManager Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	ObjectManagerInstance->Init(device->getD3DDevice().Get());
	if (ObjectManagerInstance->getInstance() == nullptr) {
		std::wstring message = L"Init ObjectManager Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	SceneManagerInstance->Init(device->getD3DContext().Get(), device->getD2DContext().Get());
	if (SceneManagerInstance->getInstance() == nullptr) {
		std::wstring message = L"Init SceneManager Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	InputManagerInstance->Init(window->getWindowHandle());
	if (InputManagerInstance->getInstance() == nullptr) {
		std::wstring message = L"Init InputManager Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	ShaderManagerInstance->Init();
	if (ShaderManagerInstance->getInstance() == nullptr) {
		std::wstring message = L"Init ShaderManager Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	// If Need More Managers, Add Them Below
	// ManagerInstance->Init();
	// if (ManagerInstance->getInstance() == nullptr) {
	//	 std::wstring message = L"Init Manager Failed\n" + std::to_wstring(GetLastError());
	//	 MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
	//	 return E_FAIL;
	// }

	return S_OK;
}

void Application::InitDeltaTime() {
	this->beforeInterval = std::make_unique<LARGE_INTEGER>();
	this->currentInterval = std::make_unique<LARGE_INTEGER>();
	this->frequency = std::make_unique<LARGE_INTEGER>();

	QueryPerformanceCounter(beforeInterval.get());
	QueryPerformanceCounter(currentInterval.get());
	QueryPerformanceFrequency(frequency.get());
}

float Application::getDeltaTime() {
	QueryPerformanceCounter(currentInterval.get());

	LONGLONG interval = (currentInterval->QuadPart - beforeInterval->QuadPart);
	// *WARNING* This Line May Happen 'Division by Zero' Problem
	float deltaTime = static_cast<float>(interval) / static_cast<float>(frequency->QuadPart);

	// Swap Memory R-Value to L-Value *Like 'beforeInterval = currentInterval'*
	beforeInterval.swap(currentInterval);

	return deltaTime;
}