#pragma once
#include "pch.h"
#include "Object.h"

#define ObjectManagerInstance ObjectManager::getInstance()

class ObjectManager
{
private:
	ObjectManager();
	ObjectManager(const ObjectManager&) = delete;
	ObjectManager& operator=(const ObjectManager&) = delete;

	bool isInit = false;

	// Get pointer from device
	ID3D11Device* d3dDevice = nullptr;
	ID3D11DeviceContext* d3dContext = nullptr;
public:
	~ObjectManager();

	static ObjectManager* getInstance();

	void Init(ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext);

	void CreateObject(Object* object);
	void CreateCamera(Camera* camera);
};