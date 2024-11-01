#pragma once
#include "Scene.h"
#include "Cube.h"
#include "ImageUI.h"
#include "ObjectManager.h"

class MainScene : public Scene
{
public :
	MainScene();
	~MainScene();

	void Update(float dTime);

	ImageUI *ui1;

	Cube* cube;
};