#pragma once
#include "pch.h"
#include "Window.h"
#include "Device.h"
#include "SceneManager.h"

class Application {
private:
	std::unique_ptr<Window> window = nullptr;
	std::unique_ptr<Device> device = nullptr;

	LARGE_INTEGER beforeInterval, currentInterval, frequency;
public:
	Application(HINSTANCE hInstance, INT nCmdShow);
	~Application();

	HRESULT InitApplication();

	INT DoMainLoop();

	void InitDeltaTime();
	float getDeltaTime();
};