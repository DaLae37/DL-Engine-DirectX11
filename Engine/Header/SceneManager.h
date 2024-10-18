#pragma once
#include "pch.h"
#include "Scene.h"

#define SceneManagerInstance SceneManager::getInstance()

class SceneManager
{
private :
	bool isInit = false;

	Scene *currentScene = nullptr;
	
	ID2D1DeviceContext* d2dContext = nullptr;
public :
	SceneManager();
	~SceneManager();

	static SceneManager* getInstance();

	void Update(float dTime);
	void Render();

	void Init(ID2D1DeviceContext* d2dContext);
	void ChangeScene(Scene* nextScene);
};