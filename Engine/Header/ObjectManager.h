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

	// Get raw pointer from device
	ID3D11Device* d3dDevice = nullptr;

public:
	~ObjectManager();

	static ObjectManager* getInstance();

	void Init(ID3D11Device* d3dDevice);

	void CreateObject(Object* object);
	void CreateCamera(Camera* camera);
};