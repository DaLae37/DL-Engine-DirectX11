#pragma once
#include "Scene.h"

#include "Cube.h"
#include "ImageUI.h"
#include "Model.h"
class MainScene : public Scene
{
public :
	MainScene();
	~MainScene();

	void Update(float deltaTime);

	ImageUI *ui;
	Cube* cube;
	Model* model;
};