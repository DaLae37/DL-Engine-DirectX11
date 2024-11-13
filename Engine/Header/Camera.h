#pragma once
#include "pch.h"

struct CameraBuffer
{
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixIdentity();
};

class Camera
{
private :
	WRL::ComPtr<ID3D11Buffer> constantBuffer;
	CameraBuffer cameraBuffer;

	float yaw;
	float pitch;

	DirectX::XMVECTOR eye;
	DirectX::XMVECTOR at;
	DirectX::XMVECTOR up;

	DirectX::XMMATRIX rotation;
	DirectX::XMMATRIX view;
public :
	Camera();
	~Camera();

	virtual void Update(float deltaTime);
	virtual void Render(ID3D11DeviceContext* d3dDevice);

	virtual HRESULT CreateConstantBuffer(ID3D11Device* d3dDevice);

	WRL::ComPtr<ID3D11Buffer> getConstantBuffer();
	const CameraBuffer* getCameraBuffer();
};