#pragma once
#include "pch.h"

struct CameraBuffer {
	DirectX::XMMATRIX viewMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX projectionMatrix = DirectX::XMMatrixIdentity();
	DirectX::XMFLOAT4 cameraPosition;
};

class Camera {
private :
	WRL::ComPtr<ID3D11Buffer> constantBuffer;
	CameraBuffer cameraBuffer;

public :
	explicit Camera();
	virtual ~Camera();

	virtual HRESULT CreateConstantBuffer(ID3D11Device* d3dDevice);

	virtual void Update(float deltaTime);
	virtual void Render(ID3D11DeviceContext* d3dContext);

	WRL::ComPtr<ID3D11Buffer> getConstantBuffer();

//Transform
private:
	bool isChangedTransform = true;

protected:
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 rotation;

	float yaw;
	float pitch;
	float roll;

public:
	void SetRotation(DirectX::XMFLOAT3 newRotation);
	void SetRotation(float yaw, float pitch, float roll);

	void Rotate(DirectX::XMFLOAT3 rotationOffset);

	void SetPosition(DirectX::XMFLOAT3 newPosition);
	void Translate(DirectX::XMFLOAT3 positionOffset);
};