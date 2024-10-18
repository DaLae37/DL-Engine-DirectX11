#include "MainScene.h"

MainScene::MainScene() {
	ui = new ImageUI(L"Resources/Images/dl-logo.png");
	AddUI(ui);
	ui->SetPos(D2D_POINT_2F{ 100,100 });
}

MainScene::~MainScene() {

}

void MainScene::Update(float dTime){
	Scene::Update(dTime);
}