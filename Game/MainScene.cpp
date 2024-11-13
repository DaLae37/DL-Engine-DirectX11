#include "MainScene.h"

MainScene::MainScene() {
	ui1 = new ImageUI(L"Resources/Images/dl-logo.png");
	AddUI(ui1);
	ui1->SetPos(D2D_POINT_2F{ 100,100 });

	cube = new Cube();
	ObjectManagerInstance->CreateObject(cube);
	AddObject(cube);
}

MainScene::~MainScene() {
	SAFE_DELETE(ui1);
	SAFE_DELETE(cube);
}

void MainScene::Update(float dTime){
	Scene::Update(dTime);
}