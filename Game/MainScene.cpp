#include "MainScene.h"

MainScene::MainScene() {
	ui = new ImageUI(L"Resources/Images/dl-logo.png");
	AddUI(ui);
	ui->SetPos(D2D_POINT_2F{ 100,100 });

	cube = new Cube();
	ObjectManagerInstance->CreateObject(cube);
	AddObject(cube);

	model = new Model(L"Resources/Models/cat.obj");
	ObjectManagerInstance->CreateObject(model);
	AddObject(model);
}

MainScene::~MainScene() {
	SAFE_DELETE(ui);
	SAFE_DELETE(cube);
	SAFE_DELETE(model);
}

void MainScene::Update(float dTime){
	Scene::Update(dTime);
}