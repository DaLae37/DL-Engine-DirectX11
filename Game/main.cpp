#include "pch.h"
#include "Application.h"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, INT nCmdShow) {
	srand(static_cast<unsigned int>(GetTickCount64()));

	std::unique_ptr<Application> application = std::make_unique<Application>(hInstance, nCmdShow);

	HRESULT result = application->InitApplication();

	if (result == S_OK) {
		INT msg = application->DoMainLoop();
		return msg;
	}
	else {
		return 0;
	}
}