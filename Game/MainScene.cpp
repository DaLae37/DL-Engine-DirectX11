#include "MainScene.h"

MainScene::MainScene() {
	ui1 = new ImageUI(L"Resources/Images/dl-logo.png");
	AddUI(ui1);
	ui1->SetPos(D2D_POINT_2F{ 100,100 });

	cube = dynamic_cast<Cube*>(ObjectManagerInstance->CreateObject(new Cube()));
	AddObject(cube);
}

MainScene::~MainScene() {

}

void MainScene::Update(float dTime){
	Scene::Update(dTime);
}