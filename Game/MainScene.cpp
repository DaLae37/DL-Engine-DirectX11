#include "MainScene.h"

MainScene::MainScene() {
	ui = new ImageUI(L"Resources/Images/dl-logo.png");
	AddUI(ui);
	ui->SetPosition({ 10,10 });
	ui->SetScale({ 0.5f,0.5f });

	cube = new Cube();
	ObjectManagerInstance->CreateObject(cube);
	AddObject(cube);
	cube->SetRotation({ 0,1,0 });

	model1 = new Model(L"Resources/3DModels/cat.obj", "Resources/3DModels/cat.png");
	ObjectManagerInstance->CreateObject(model1);
	AddObject(model1);
	model1->SetPosition({ 10,-10,10 });
	model1->SetScale({ 0.5f,0.5f,0.5f });

	model2 = new Model(L"Resources/3DModels/mouse.obj", "Resources/3DModels/mouse.png");
	ObjectManagerInstance->CreateObject(model2);
	AddObject(model2);
	model2->SetPosition({ -10,-10,10 });
	model2->SetScale({ 0.5f,0.5f,0.5f });
}

MainScene::~MainScene() {
	SAFE_DELETE(ui);
	SAFE_DELETE(cube);
	SAFE_DELETE(model1);
	SAFE_DELETE(model2);
}

void MainScene::Update(float deltaTime) {
	Scene::Update(deltaTime);
	model1->Rotate({ 0,1 * deltaTime,0 });

	if (InputManagerInstance->GetKeyState(VK_LBUTTON) == KEY_ON) {
		model1->Translate({ -100 * deltaTime, 0, 0 });
	}
	if (InputManagerInstance->GetKeyState(VK_RBUTTON) == KEY_ON) {
		model1->Translate({ 100 * deltaTime, 0, 0 });
	}

	if (InputManagerInstance->GetKeyState(VK_UP) == KEY_ON) {
		mainCamera->Translate({ 0, 50 * deltaTime, 0 });
	}
	if (InputManagerInstance->GetKeyState(VK_DOWN) == KEY_ON) {
		mainCamera->Translate({ 0, -50 * deltaTime, 0 });
	}
	if (InputManagerInstance->GetKeyState(VK_LEFT) == KEY_ON) {
		mainCamera->Rotate({ -50 * deltaTime, 0, 0 });
	}
	if (InputManagerInstance->GetKeyState(VK_RIGHT) == KEY_ON) {
		mainCamera->Rotate({ 50 * deltaTime, 0, 0 });
	}
}