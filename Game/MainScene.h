#pragma once
#include "Scene.h"

class MainScene : public Scene
{
public :
	MainScene();
	~MainScene();

	void Update(float dTime);
	void Render();
};