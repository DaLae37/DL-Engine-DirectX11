#include "pch.h"
#include "Camera.h"

Camera::Camera() {

}

Camera::~Camera() {

}

HRESULT Camera::CreateConstantBuffer(ID3D11Device* d3dDevice) {
    HRESULT hr = HRESULT();
    D3D11_BUFFER_DESC bufferDesc = D3D11_BUFFER_DESC();

    bufferDesc.Usage = D3D11_USAGE_DEFAULT;
    bufferDesc.ByteWidth = sizeof(CameraBuffer);
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    bufferDesc.CPUAccessFlags = 0;
    hr = d3dDevice->CreateBuffer(&bufferDesc, nullptr, constantBuffer.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }
}

void Camera::Update(float deltaTime) {
    if (isChangedTransform) {
        pitch = DirectX::XMConvertToRadians(rotation.x);
        yaw = DirectX::XMConvertToRadians(rotation.y);
        roll = DirectX::XMConvertToRadians(rotation.z);

        DirectX::XMMATRIX rotationMatrix = DirectX::XMMatrixRotationRollPitchYaw(pitch, yaw, roll);

        DirectX::XMVECTOR eye = DirectX::XMVectorSet(position.x, position.y, position.z, 1.0f);
        DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, 0.0f, 1.0f, 1.0f);
        DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

        at = DirectX::XMVectorAdd(DirectX::XMVector3TransformCoord(at, rotationMatrix), eye);
        up = DirectX::XMVector3TransformCoord(up, rotationMatrix);

        cameraBuffer.viewMatrix = DirectX::XMMatrixLookAtLH(eye, at, up);
        cameraBuffer.viewMatrix = DirectX::XMMatrixTranspose(cameraBuffer.viewMatrix);

        cameraBuffer.projectionMatrix = DirectX::XMMatrixPerspectiveFovLH
        (
            DirectX::XM_PIDIV2,
            DEFAULT_WIDTH / (float)DEFAULT_HEIGHT,
            0.01f,
            100.0f
        );
        cameraBuffer.projectionMatrix = DirectX::XMMatrixTranspose(cameraBuffer.projectionMatrix);

        isChangedTransform = false;
    }
}

void Camera::Render(ID3D11DeviceContext* d3dContext) {
    d3dContext->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &cameraBuffer, 0, 0);
}

WRL::ComPtr<ID3D11Buffer> Camera::getConstantBuffer() {
    return this->constantBuffer;
}

const CameraBuffer* Camera::getCameraBuffer() {
    return &this->cameraBuffer;
}

void Camera::SetRotation(DirectX::XMFLOAT3 newRotation) {
    this->rotation = newRotation;

    isChangedTransform = true;
}

void Camera::SetRotation(float yaw, float pitch, float roll) {
    this->yaw = yaw;
    this->pitch = pitch;
    this->roll = roll;

    rotation = DirectX::XMFLOAT3(yaw, pitch, roll);

    isChangedTransform = true;
}

void Camera::Rotate(DirectX::XMFLOAT3 rotationOffset) {
    this->rotation.x += rotationOffset.x;
    this->rotation.y += rotationOffset.y;
    this->rotation.z += rotationOffset.z;

    isChangedTransform = true;
}

void Camera::SetPosition(DirectX::XMFLOAT3 newPosition) {
    this->position = newPosition;

    isChangedTransform = true;
}

void Camera::Translate(DirectX::XMFLOAT3 positionOffset) {
    this->position.x += positionOffset.x;
    this->position.y += positionOffset.y;
    this->position.z += positionOffset.z;

    isChangedTransform = true;
}