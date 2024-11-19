#include "pch.h"
#include "Object.h"

Object::Object() {
	scale = DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f);
	rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	position = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
}

Object::~Object() {

}

void Object::Update(float deltaTime) {
	if (isChangedTransform) {
		objectBuffer.world = DirectX::XMMatrixIdentity();

		objectBuffer.world *= DirectX::XMMatrixScalingFromVector(XMLoadFloat3(&scale));
		objectBuffer.world *= DirectX::XMMatrixRotationRollPitchYawFromVector(XMLoadFloat3(&rotation));
		objectBuffer.world *= DirectX::XMMatrixTranslationFromVector(XMLoadFloat3(&position));

		objectBuffer.world = DirectX::XMMatrixTranspose(objectBuffer.world);
		isChangedTransform = false;
	}
}

HRESULT Object::CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** blob) {
	HRESULT hr = HRESULT();

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	hr = D3DCompileFromFile(
		static_cast<LPCWSTR>(path), // Shader File Name
		nullptr, // Shader Macros
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // Include Files
		static_cast<LPCSTR>(entryPoint), // Entry Point
		static_cast<LPCSTR>(shaderModel), // Shader Target
		dwShaderFlags, // Flag1
		0, // Flag2
		blob, // ID3DBlob out 
		errorBlob.GetAddressOf() // Error Blob out
	);
	if (FAILED(hr)) {
		if (errorBlob != nullptr) {
			OutputDebugStringA(static_cast<LPCSTR>(errorBlob->GetBufferPointer()));
			SAFE_RELEASE(errorBlob);
		}
		return hr;
	}
}

void Object::setSamplerState(ID3D11SamplerState* samplerState) {
	this->samplerState = samplerState;
}

void Object::SetScale(DirectX::XMFLOAT3 newScale) {
	this->scale = newScale;

	isChangedTransform = true;
}

void Object::Scaling(DirectX::XMFLOAT3 scaleOffset) {
	this->scale.x += scaleOffset.x;
	this->scale.y += scaleOffset.y;
	this->scale.z += scaleOffset.z;

	isChangedTransform = true;
}

void Object::SetRotation(DirectX::XMFLOAT3 newRotation) {
	this->rotation = newRotation;

	isChangedTransform = true;
}

void Object::Rotate(DirectX::XMFLOAT3 rotationOffset) {
	this->rotation.x += rotationOffset.x;
	this->rotation.y += rotationOffset.y;
	this->rotation.z += rotationOffset.z;

	isChangedTransform = true;
}

void Object::SetPosition(DirectX::XMFLOAT3 newPosition) {
	this->position = newPosition;

	isChangedTransform = true;
}

void Object::Translate(DirectX::XMFLOAT3 positionOffset) {
	this->position.x += positionOffset.x;
	this->position.y += positionOffset.y;
	this->position.z += positionOffset.z;

	isChangedTransform = true;
}