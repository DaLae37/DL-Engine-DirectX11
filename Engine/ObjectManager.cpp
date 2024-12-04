#include "pch.h"
#include "ObjectManager.h"

ObjectManager::~ObjectManager() {

}

ObjectManager* ObjectManager::getInstance() {
	static ObjectManager instance;
	return &instance;
}

void ObjectManager::Init(ID3D11Device* d3dDevice) {
	this->d3dDevice = d3dDevice;

	if (samplerState == nullptr) {
        // Create Sample State
        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MaxAnisotropy = 1;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        samplerDesc.BorderColor[0] = 0.0f;
        samplerDesc.BorderColor[1] = 0.0f;
        samplerDesc.BorderColor[2] = 0.0f;
        samplerDesc.BorderColor[3] = 0.0f;
        samplerDesc.MinLOD = 0;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

        HRESULT hr = d3dDevice->CreateSamplerState(&samplerDesc, samplerState.GetAddressOf());
        if (FAILED(hr)) {
            return;
        }
	}

	this->isInit = true;
}

void ObjectManager::CreateObject(Object* object) {
	object->CreatePipeline(d3dDevice);
	object->CreateData(d3dDevice);

    object->setSamplerState(samplerState.Get());
}

void ObjectManager::CreateCamera(Camera* camera) {
	camera->CreateConstantBuffer(d3dDevice);
}

void ObjectManager::CreateLight(Light* light) {
    light->CreateConstantBuffer(d3dDevice);
}