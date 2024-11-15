#pragma once
#include "pch.h"
#include "Camera.h"

struct PolygonVertex {
	DirectX::XMFLOAT4 pos;
	DirectX::XMFLOAT4 color;
};

struct ModelVertex
{
	DirectX::XMFLOAT4 Position;
	DirectX::XMFLOAT2 TexCoord;
	DirectX::XMFLOAT3 Normal;
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

	std::vector<UINT> indices;

	ObjectBuffer objectBuffer;
public :
	explicit Object();
	virtual ~Object();

	virtual void Update(float deltaTime) = 0;
	virtual void Render(ID3D11DeviceContext* d3dContext, Camera* camera) = 0;

	virtual HRESULT CreatePipeline(ID3D11Device* d3dDevice) = 0;
	virtual HRESULT CreateData(ID3D11Device* d3dDevice) = 0;
	
	HRESULT CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** blob);
};