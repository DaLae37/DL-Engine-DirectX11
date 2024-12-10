#pragma once
#include "pch.h"

class Window {
private:
	HINSTANCE hInstance;
	INT nCmdShow;

	// Windows Handler
	HWND hWnd;

public:
	Window() = delete;
	Window(HINSTANCE hInstance, INT nCmdShow);
	~Window();

	// Window Procedure Function
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Initialize Window
	HRESULT InitWindow();
	// Float Window *Do Not Call Before Window Initialized*
	HRESULT FloatWindow();

	void WindowLoop();
	// Get WindowsHandler Pointer
	HWND* getWindowHandle();
};