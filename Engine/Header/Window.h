#pragma once
#include "pch.h"

class Window {
private :
	HINSTANCE hInstance;
	HWND hWnd;
	INT nCmdShow;

public :
	Window(HINSTANCE hInstance, INT nCmdShow);
	~Window();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	HRESULT InitWindow();
	HRESULT FloatWindow();

	void WindowLoop();
};