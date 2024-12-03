#pragma once
#include "Light.h"

struct DirectionalLightBuffer : PhongLightBuffer {
	DirectX::XMFLOAT4 lightDirection;
};

class DirectionalLight : public Light {
private :
	DirectionalLightBuffer directionalLightBuffer;
public :
	explicit DirectionalLight();
	~DirectionalLight();

	HRESULT CreateConstantBuffer(ID3D11Device* d3dDevice);

	void Update(float deltaTime);
	void Render(ID3D11DeviceContext* d3dContext);
};