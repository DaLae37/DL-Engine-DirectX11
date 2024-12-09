#pragma once
#include "pch.h"
#include "Window.h"
#include "Device.h"

// Manager Headers
#include "SceneManager.h"
#include "ObjectManager.h"
#include "TextureManager.h"
#include "InputManager.h"
#include "ShaderManager.h"

class Application {
private:
	std::unique_ptr<Window> window = nullptr;
	std::unique_ptr<Device> device = nullptr;

	// Delta Time Timers
	std::unique_ptr<LARGE_INTEGER> beforeInterval = nullptr, currentInterval = nullptr;
	// High Quality Counter
	// *If Installed Hardware Doesn't Support Performance Counters This Values Can Be Initialized to Zero(0)*
	std::unique_ptr<LARGE_INTEGER> frequency = nullptr;

public:
	Application() = delete;
	Application(HINSTANCE hInstance, INT nCmdShow);
	~Application();

	// Initalize WindowsAPI & DirectX Devices
	HRESULT InitApplication();
	// Initialize System Managers *Do Not Call Before Application Initialized*
	HRESULT InitManager();

	// Main Loop
	INT DoMainLoop();

	// Initialize LARGE_INTEGER values
	void InitDeltaTime();
	// Get System Delta Time
	FLOAT getDeltaTime();
};