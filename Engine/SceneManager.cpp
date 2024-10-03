#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager() {

}

SceneManager::~SceneManager() {
	SAFE_DELETE(currentScene);
}

SceneManager* SceneManager::getInstance() {
	static SceneManager instance;
	return &instance;
}

void SceneManager::Update(float dTime) {
	currentScene->Update(dTime);
}

void SceneManager::Render() {
	currentScene->Render();
}

void SceneManager::ChangeScene(Scene* nextScene) {
	SAFE_DELETE(currentScene);
	this->currentScene = nextScene;
}