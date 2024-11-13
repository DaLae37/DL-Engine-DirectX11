#include "pch.h"
#include "Camera.h"

Camera::Camera() {
    eye = DirectX::XMVectorSet(0.0f, 1.0f, -5.0f, 0.0f);
    at = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
    up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
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
    cameraBuffer.viewMatrix = DirectX::XMMatrixLookAtLH(eye, at, up);
    cameraBuffer.viewMatrix = DirectX::XMMatrixTranspose(cameraBuffer.viewMatrix);

    cameraBuffer.projectionMatrix = DirectX::XMMatrixPerspectiveFovLH
    (
        DirectX::XM_PIDIV2,
        1920 / (FLOAT)1080,
        0.01f,
        100.0f
    );
    cameraBuffer.projectionMatrix = DirectX::XMMatrixTranspose(cameraBuffer.projectionMatrix);
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