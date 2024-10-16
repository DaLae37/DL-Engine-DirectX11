#pragma once
#include "Scene.h"
#include "ImageUI.h"

class MainScene : public Scene
{
public :
	MainScene();
	~MainScene();

	void Update(float dTime);
	void Render();

	ImageUI *ui;
};