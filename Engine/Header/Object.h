#pragma once
#include "pch.h"

struct Vertex {
	DirectX::XMFLOAT4 pos;
	DirectX::XMFLOAT4 color;
};

struct ConstantBuffer {
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX view = DirectX::XMMatrixIdentity();
	DirectX::XMMATRIX projection = DirectX::XMMatrixIdentity();
};

class Object {
protected :
	WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	WRL::ComPtr<ID3D11InputLayout> vertexLayout = nullptr;

	WRL::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	WRL::ComPtr<ID3D11Buffer> indexBuffer = nullptr;
	WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	ConstantBuffer constantMatrix;
public :
	Object();
	virtual ~Object();

	virtual void Update(float dTime) = 0;
	virtual void Render(ID3D11DeviceContext* d3dContext) = 0;

	virtual HRESULT CreatePipeline(ID3D11Device* d3dDevice) = 0;
	virtual HRESULT CreateData(ID3D11Device* d3dDevice) = 0;
	virtual void BindData(ID3D11DeviceContext* d3dContext) = 0;
	
	HRESULT CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** blob);
};