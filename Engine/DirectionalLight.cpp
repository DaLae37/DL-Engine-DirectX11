#include "pch.h"
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight() {
	position = DirectX::XMFLOAT3(0.0f, 5.0f, -10.0f);

	directionalLightBuffer.diffuseColor = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLightBuffer.specularColor = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	directionalLightBuffer.ambientColor = DirectX::XMFLOAT4(0.1f, 0.1f, 0.1f, 1.0f);

	directionalLightBuffer.lightDirection = DirectX::XMFLOAT4(0.0f, -1.0f, 0.0f, 1.0f);
}

DirectionalLight::~DirectionalLight() {

}

HRESULT DirectionalLight::CreateConstantBuffer(ID3D11Device* d3dDevice) {
	HRESULT hr = HRESULT();
	D3D11_BUFFER_DESC lightBufferDesc = D3D11_BUFFER_DESC();

	lightBufferDesc.ByteWidth = sizeof(DirectionalLightBuffer);
	lightBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	lightBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	lightBufferDesc.CPUAccessFlags = 0;
	hr = d3dDevice->CreateBuffer(&lightBufferDesc, nullptr, constantBuffer.GetAddressOf());
	if (FAILED(hr)) {
		return hr;
	}
}

void DirectionalLight::Update(float deltaTime) {
	
}

void DirectionalLight::Render(ID3D11DeviceContext* d3dContext) {
	d3dContext->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &directionalLightBuffer, 0, 0);
}