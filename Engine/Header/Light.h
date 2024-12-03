#pragma once
#include "pch.h"

struct PhongLightBuffer {
	DirectX::XMFLOAT4 diffuseColor;
	DirectX::XMFLOAT4 specularColor;
	DirectX::XMFLOAT4 ambientColor;
};

class Light {
protected :
	WRL::ComPtr<ID3D11Buffer> constantBuffer;

public :
	explicit Light();
	virtual ~Light();

	virtual void Update(float deltaTime) = 0;
	virtual void Render(ID3D11DeviceContext* d3dDevice) = 0;

	virtual HRESULT CreateConstantBuffer(ID3D11Device* d3dDevice) = 0;

	WRL::ComPtr<ID3D11Buffer> getConstantBuffer();

//Transform
protected :
	DirectX::XMFLOAT3 position;
};