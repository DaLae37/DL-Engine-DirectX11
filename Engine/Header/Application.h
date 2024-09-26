#pragma once
#include "pch.h"

#include "Window.h"
#include "Device.h"

class Application {
private:
	std::unique_ptr<Window> window;
	std::unique_ptr<Device> device;

	LARGE_INTEGER beforeInterval, currentInterval, frequency;
public:
	Application(HINSTANCE hInstance, INT nCmdShow);
	~Application();

	HRESULT InitApplication();

	int DoMainLoop();

	void InitDeltaTime();
	double getDeltaTime();
};