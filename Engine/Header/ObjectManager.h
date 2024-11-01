#pragma once
#include "pch.h"
#include "Object.h"

#define ObjectManagerInstance ObjectManager::getInstance()

class ObjectManager
{
private:
	bool isInit = false;

	// Get pointer from device
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;
public:
	ObjectManager();
	~ObjectManager();

	static ObjectManager* getInstance();

	void Init(ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext);

	Object* CreateObject(Object* object);
};