#include "pch.h"
#include "Scene.h"

Scene::Scene() {
	mainCamera = std::make_unique<Camera>();
	ObjectManagerInstance->CreateCamera(mainCamera.get());
}

Scene::~Scene() {

}

void Scene::Update(float deltaTime) {
	mainCamera->Update(deltaTime);
	for (Object* object : objectList) {
		object->Update(deltaTime);
	}
	for (UI* ui : uiList) {
		ui->Update(deltaTime);
	}
}

void Scene::RenderObject(ID3D11DeviceContext* d3dContext) {
	mainCamera->Render(d3dContext);
	for (Object* object : objectList) {
		object->Render(d3dContext, mainCamera.get());
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