#pragma once
#include "pch.h"

class Scene
{
public :
	Scene();
	virtual ~Scene();

	virtual void Update(float dTime);
	virtual void Render();
};