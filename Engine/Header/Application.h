#pragma once
#include "pch.h"
#include "Window.h"
#include "Device.h"

//Manager
#include "SceneManager.h"
#include "TextureManager.h"

class Application {
private:
	std::unique_ptr<Window> window = nullptr;
	std::unique_ptr<Device> device = nullptr;

	LARGE_INTEGER beforeInterval, currentInterval, frequency;
public:
	Application(HINSTANCE hInstance, INT nCmdShow);
	~Application();

	HRESULT InitApplication();
	HRESULT InitManager();

	INT DoMainLoop();

	void InitDeltaTime();
	float getDeltaTime();
};