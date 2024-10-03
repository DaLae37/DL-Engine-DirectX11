#pragma once
#include "pch.h"
#include "Scene.h"

#define SceneManagerInstance SceneManager::getInstance()

class SceneManager
{
private :
	Scene *currentScene = nullptr;
public :
	SceneManager();
	~SceneManager();

	static SceneManager* getInstance();

	void Update(float dTime);
	void Render();

	void ChangeScene(Scene* nextScene);
};