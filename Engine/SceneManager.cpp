#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager() {
	isInit = false;
}

SceneManager::~SceneManager() {
	SAFE_DELETE(currentScene);
}

SceneManager* SceneManager::getInstance() {
	static SceneManager instance;
	return &instance;
}

void SceneManager::Init(ID2D1DeviceContext* d2dContext) {
	this->d2dContext = d2dContext;

	this->isInit = true;
}

void SceneManager::Update(float dTime) {
	currentScene->Update(dTime);
}

void SceneManager::Render() {
	currentScene->RenderUI(this->d2dContext);
}

void SceneManager::ChangeScene(Scene* nextScene) {
	SAFE_DELETE(currentScene);
	this->currentScene = nextScene;
}