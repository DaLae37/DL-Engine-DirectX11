#include "pch.h"
#include "Window.h"

Window::Window(HINSTANCE hInstance, INT nCmdShow) {
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;
}

Window::~Window() {
	
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	case WM_CLOSE:
		if (MessageBoxEx(hWnd, L"Exit Program?", PROGRAM_NAME, MB_OKCANCEL, NULL) == IDOK) {
			DestroyWindow(hWnd);
			return 0;
		}		
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

HRESULT Window::InitWindow() {
	WNDCLASSEX wndClass = WNDCLASSEX();

	wndClass.cbSize = sizeof(WNDCLASSEX);
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = WndProc;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = this->hInstance;
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1);
	wndClass.lpszMenuName = nullptr;
	wndClass.lpszClassName = PROGRAM_NAME;
	wndClass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	
	RegisterClassEx(&wndClass);
	
	if (GetLastError() != 0) {
		return E_FAIL;
	}
	else {
		return S_OK;
	}
}

HRESULT Window::FloatWindow() {
	this->hWnd = CreateWindowEx(WS_EX_APPWINDOW, PROGRAM_NAME, PROGRAM_NAME,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1920, 1080,
		nullptr, nullptr, hInstance, nullptr);

	ShowWindow(this->hWnd, nCmdShow);

	if (GetLastError() != 0) {
		return E_FAIL;
	}
	else {
		return S_OK;
	}
}

void Window::WindowLoop() {
	
}

HWND* Window::getWindowHandle() {
	return &this->hWnd;
}