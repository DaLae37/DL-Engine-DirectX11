#pragma once
#include "pch.h"
#include "Camera.h"
#include "Light.h"

#include "ObjectManager.h"
#include "Object.h"
#include "UI.h"

class Scene
{
private :
	std::vector<Object*> objectList;
	std::vector<UI*> uiList;

protected :
	std::unique_ptr<Camera> mainCamera;
	std::unique_ptr<Light> mainLight;

public:
	Scene();
	virtual ~Scene();

	virtual void Update(float deltaTime);

	void RenderObject(ID3D11DeviceContext* d3dContext);
	void RenderUI(ID2D1DeviceContext* d2dContext);

	void AddObject(Object* object);
	void AddUI(UI* ui);
};