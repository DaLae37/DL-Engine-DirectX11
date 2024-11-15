#include "pch.h"
#include "ObjectManager.h"

ObjectManager::ObjectManager() {
	isInit = false;
}

ObjectManager::~ObjectManager() {

}

ObjectManager* ObjectManager::getInstance() {
	static ObjectManager instance;
	return &instance;
}

void ObjectManager::Init(ID3D11Device* d3dDevice) {
	this->d3dDevice = d3dDevice;

	this->isInit = true;
}

void ObjectManager::CreateObject(Object* object) {
	object->CreatePipeline(d3dDevice);
	object->CreateData(d3dDevice);
}

void ObjectManager::CreateCamera(Camera* camera) {
	camera->CreateConstantBuffer(d3dDevice);
}