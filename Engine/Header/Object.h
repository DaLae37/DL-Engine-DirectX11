#pragma once
#include "pch.h"
#include "Camera.h"

struct Vertex {
	DirectX::XMFLOAT4 pos;
	DirectX::XMFLOAT4 color;
};

struct ObjectBuffer {
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
};

class Object {
protected :
	WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	WRL::ComPtr<ID3D11InputLayout> vertexLayout = nullptr;

	WRL::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	WRL::ComPtr<ID3D11Buffer> indexBuffer = nullptr;
	WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	ObjectBuffer objectBuffer;
public :
	Object();
	virtual ~Object();

	virtual void Update(float deltaTime) = 0;
	virtual void Render(ID3D11DeviceContext* d3dContext, Camera* camera) = 0;

	virtual HRESULT CreatePipeline(ID3D11Device* d3dDevice) = 0;
	virtual HRESULT CreateData(ID3D11Device* d3dDevice) = 0;
	virtual void BindData(ID3D11DeviceContext* d3dContext) = 0;
	
	HRESULT CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** blob);
};