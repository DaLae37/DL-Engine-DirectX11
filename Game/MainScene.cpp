#include "MainScene.h"

MainScene::MainScene() {
	ui = new ImageUI(L"Resources/Images/dl-logo.png");
	AddUI(ui);
	ui->SetPosition({ 100,100 });

	cube = new Cube();
	ObjectManagerInstance->CreateObject(cube);
	AddObject(cube);
	cube->SetRotation({ 0,1,0 });

	model = new Model(L"Resources/Models/mouse.obj");
	ObjectManagerInstance->CreateObject(model);
	AddObject(model);
	model->SetPosition({ 0,-10,50 });
	model->SetRotation({ 0,45,0 });
}

MainScene::~MainScene() {
	SAFE_DELETE(ui);
	SAFE_DELETE(cube);
	SAFE_DELETE(model);
}

void MainScene::Update(float deltaTime){
	Scene::Update(deltaTime);
	model->Rotate({ 0,1 * deltaTime,0 });
}