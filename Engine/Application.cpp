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

	if (device->InitD3D11Device(window->getWindowHandle()) != S_OK) {
		std::wstring message = L"InitD3DDevice Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}
	if (device->InitD2DDevice(window->getWindowHandle()) != S_OK) {
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
			window->WindowLoop();
			device->RenderStart();
			SceneManagerInstance->Render();
			SceneManagerInstance->Update(getDeltaTime());
			device->RenderEnd();
		}
	}

	return static_cast<INT>(Message.wParam);
}

HRESULT Application::InitManager() {
	TextureManagerInstance->Init(device->getD2DContext(), device->getWicFactory());
	if (TextureManagerInstance->getInstance() == nullptr) {
		std::wstring message = L"Init TextureManager Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	SceneManagerInstance->Init(device->getD2DContext());
	if (SceneManagerInstance->getInstance() == nullptr) {
		std::wstring message = L"Init SceneManager Failed\n" + std::to_wstring(GetLastError());
		MessageBoxEx(nullptr, message.c_str(), PROGRAM_NAME, NULL, NULL);
		return E_FAIL;
	}

	return S_OK;
}

void Application::InitDeltaTime() {
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceCounter(&currentInterval);
	QueryPerformanceFrequency(&frequency);
}

float Application::getDeltaTime() {
	QueryPerformanceCounter(&currentInterval);

	LONGLONG interval = (currentInterval.QuadPart - beforeInterval.QuadPart);
	float deltaTime = static_cast<float>(interval) / static_cast<float>(frequency.QuadPart);

	beforeInterval = currentInterval;

	return deltaTime;
}