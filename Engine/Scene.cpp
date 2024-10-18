#include "pch.h"
#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::Update(float dTime) {

}

void Scene::RenderObject() {

}

void Scene::RenderUI(ID2D1DeviceContext* d2dContext) {
	for (UI* ui : uiList) {
		ui->Render(d2dContext);
	}
}

void Scene::AddUI(UI* ui) {
	uiList.push_back(ui);
}