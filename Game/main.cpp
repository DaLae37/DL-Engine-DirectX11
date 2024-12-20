#include "pch.h"
#include "Application.h"
#include "SceneManager.h"

// Include First Scene's Header File
// #include "FirstScene.h"
#include "MainScene.h"

INT WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, INT nCmdShow) {
	srand(static_cast<unsigned int>(GetTickCount64()));

	std::unique_ptr<Application> application = std::make_unique<Application>(hInstance, nCmdShow);

	if (application->InitApplication() == S_OK && application->InitManager() == S_OK) {
		// Input First Scene's Class
		// SceneManagerInstance->ChangeScene(new FirstScene());
		SceneManagerInstance->ChangeScene(new MainScene());

		INT msg = application->DoMainLoop();
		return msg;
	}
	else {
		// If Application Initialize Failed
		return 0;
	}
}