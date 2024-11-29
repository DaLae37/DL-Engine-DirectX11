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

public :
	Camera();
	~Camera();

	virtual void Update(float deltaTime);
	virtual void Render(ID3D11DeviceContext* d3dDevice);

	virtual HRESULT CreateConstantBuffer(ID3D11Device* d3dDevice);

	WRL::ComPtr<ID3D11Buffer> getConstantBuffer();
	const CameraBuffer* getCameraBuffer();

//Transform
private:
	bool isChangedTransform = true;

protected:
	DirectX::XMFLOAT3 position = DirectX::XMFLOAT3(0.0f, 5.0f, -10.0f);
	DirectX::XMFLOAT3 rotation = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);

	float yaw = 0;
	float pitch = 0;
	float roll = 0;

public:
	void SetRotation(DirectX::XMFLOAT3 newRotation);
	void SetRotation(float yaw, float pitch, float roll);

	void Rotate(DirectX::XMFLOAT3 rotationOffset);

	void SetPosition(DirectX::XMFLOAT3 newPosition);
	void Translate(DirectX::XMFLOAT3 positionOffset);
};