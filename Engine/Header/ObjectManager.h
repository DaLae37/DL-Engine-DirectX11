#pragma once
#include "pch.h"
#include "Object.h"

#define ObjectManagerInstance ObjectManager::getInstance()

class ObjectManager {
private:
	// Singleton Pattern Safety
	ObjectManager() = default;
	// Remove Copy Constructor
	ObjectManager(const ObjectManager&) = delete;
	// Remove Substitution Operator
	ObjectManager& operator=(const ObjectManager&) = delete;

	WRL::ComPtr<ID3D11SamplerState> samplerState = nullptr;

	// When Instance is Initialized, Changed to true
	bool isInit = false;

	// Get Raw Pointer from Device
	ID3D11Device* d3dDevice = nullptr;

public:
	~ObjectManager();

	// Get ObjectManager's Instance
	static ObjectManager* getInstance();

	// Initialize ObjectManager Instance *Must Called Before Using Any Functions*
	void Init(ID3D11Device* d3dDevice);

	void CreateObject(Object* object);
	void CreateCamera(Camera* camera);
	void CreateLight(Light* light);
};