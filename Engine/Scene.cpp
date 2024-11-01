#include "pch.h"
#include "Scene.h"

Scene::Scene() {

}

Scene::~Scene() {

}

void Scene::Update(float dTime) {

}

void Scene::RenderObject(ID3D11DeviceContext* d3dContext) {
	for (Object* object : objectList) {
		object->Render(d3dContext);
	}
}

void Scene::RenderUI(ID2D1DeviceContext* d2dContext) {
	for (UI* ui : uiList) {
		ui->Render(d2dContext);
	}
}

void Scene::AddObject(Object* object) {
	objectList.push_back(object);
}

void Scene::AddUI(UI* ui) {
	uiList.push_back(ui);
}