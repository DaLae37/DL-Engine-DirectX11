#pragma once
#include "pch.h"
#include "Scene.h"

#define SceneManagerInstance SceneManager::getInstance()

class SceneManager {
private:
	// Singleton Pattern Safety
	SceneManager() = default;
	// Remove Copy Constructor
	SceneManager(const SceneManager&) = delete;
	// Remove Substitution Operator
	SceneManager& operator=(const SceneManager&) = delete;

	Scene* currentScene = nullptr;

	// When Instance is Initialized, Changed to true
	bool isInit = false;

	// Get Raw Pointer from Device
	ID2D1DeviceContext* d2dContext = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;

public:
	~SceneManager();

	// Get SceneManger's Instances
	static SceneManager* getInstance();

	void Update(float dTime);
	void Render();

	// Initialize SceneManger Instance *Must Called Before Using Any Functions*
	void Init(ID3D11DeviceContext* d3dContext, ID2D1DeviceContext* d2dContext);
	void ChangeScene(Scene* nextScene);
};