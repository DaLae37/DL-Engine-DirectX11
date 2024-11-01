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

void ObjectManager::Init(ID3D11Device* d3dDevice, ID3D11DeviceContext* d3dContext) {
	this->d3dDevice = d3dDevice;
	this->d3dContext = d3dContext;

	this->isInit = true;
}

Object* ObjectManager::CreateObject(Object* object) {
	object->CreatePipeline(d3dDevice);
	object->CreateData(d3dDevice);
	
	object->BindData(d3dContext);

	return object;
}