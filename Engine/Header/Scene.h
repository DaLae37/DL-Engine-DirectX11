#pragma once
#include "pch.h"
#include "Object.h"
#include "UI.h"

class Scene
{
private:
	std::vector<Object*> objectList;
	std::vector<UI*> uiList;
public:
	Scene();
	virtual ~Scene();

	virtual void Update(float dTime);
	void RenderObject();
	void RenderUI(ID2D1DeviceContext* d2dContext);

	void AddUI(UI* ui);
};