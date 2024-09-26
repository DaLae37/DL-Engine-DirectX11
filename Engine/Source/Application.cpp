#include "pch.h"
#include "Application.h"

Application::Application(HINSTANCE hInstance, INT nCmdShow) {
	this->window = std::make_unique<Window>(hInstance, nCmdShow);
	this->device = std::make_unique<Device>();
}

Application::~Application() {

}

HRESULT Application::InitApplication() {
	InitDeltaTime();

	window->InitWindow();
	window->FloatWindow();
}

int Application::DoMainLoop() {
	MSG Message = { 0, };

	while (Message.message != WM_QUIT) {
		if (PeekMessage(&Message, nullptr, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		
		window->WindowLoop();
	}

	return (int)Message.wParam;
}

void Application::InitDeltaTime() {
	QueryPerformanceCounter(&beforeInterval);
	QueryPerformanceCounter(&currentInterval);
	QueryPerformanceFrequency(&frequency);
}

double Application::getDeltaTime() {
	QueryPerformanceCounter(&currentInterval);

	LONGLONG interval = (currentInterval.QuadPart - beforeInterval.QuadPart);
	DOUBLE deltaTime = static_cast<DOUBLE>(interval) / static_cast<DOUBLE>(frequency.QuadPart);

	beforeInterval = currentInterval;

	return deltaTime;
}