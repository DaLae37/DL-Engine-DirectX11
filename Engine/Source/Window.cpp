#include "pch.h"
#include "Window.h"

Window::Window(HINSTANCE hInstance, INT nCmdShow) {
	this->hInstance = hInstance;
	this->nCmdShow = nCmdShow;

	InitWindow();
}

Window::~Window() {

}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

void Window::InitWindow() {
	WNDCLASS wndClass = WNDCLASS();

	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH
	);
	wndClass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndClass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndClass.hInstance = this->hInstance;
	wndClass.lpfnWndProc = WndProc;
	wndClass.lpszClassName = PROGRAM_NAME;
	wndClass.lpszMenuName = nullptr;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndClass);
}

void Window::FloatWindow() {
	this->hWnd = CreateWindow(PROGRAM_NAME, PROGRAM_NAME,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		1920, 720,
		nullptr, (HMENU)nullptr, hInstance, nullptr);
	ShowWindow(this->hWnd, nCmdShow);
}

void Window::WindowLoop() {
	DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
	WINDOWPLACEMENT m_wpPrev = WINDOWPLACEMENT();

	SetWindowLong(hWnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
	SetWindowPlacement(hWnd, &m_wpPrev);
	SetWindowPos(hWnd, NULL, 0, 0, 0, 0,
		SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
		SWP_NOOWNERZORDER | SWP_FRAMECHANGED);
}