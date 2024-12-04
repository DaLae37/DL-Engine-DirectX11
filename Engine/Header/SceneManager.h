#pragma once
#include "pch.h"
#include "Scene.h"

#define SceneManagerInstance SceneManager::getInstance()

class SceneManager {
private :
	SceneManager() = default;
	SceneManager(const SceneManager&) = delete;
	SceneManager& operator=(const SceneManager&) = delete;

	bool isInit = false;

	Scene *currentScene = nullptr;
	
	// Get raw pointer from device
	ID2D1DeviceContext* d2dContext = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;
public :
	~SceneManager();

	static SceneManager* getInstance();

	void Update(float dTime);
	void Render();	

	void Init(ID3D11DeviceContext* d3dContext, ID2D1DeviceContext* d2dContext);
	void ChangeScene(Scene* nextScene);
};