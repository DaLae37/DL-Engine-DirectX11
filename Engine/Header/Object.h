#pragma once
#include "pch.h"
#include "Camera.h"
#include "TextureManager.h"

struct Vertex {
	DirectX::XMFLOAT4 color;
};

struct PolygonVertex : Vertex{
	DirectX::XMFLOAT4 position;
};

struct ModelVertex : Vertex
{
	DirectX::XMFLOAT2 uv;
	DirectX::XMFLOAT3 normal;
};

struct ObjectBuffer {
	DirectX::XMMATRIX world = DirectX::XMMatrixIdentity();
};

class Object {
private :
	bool isChangedTransform = false;

protected :
	WRL::ComPtr<ID3D11VertexShader> vertexShader = nullptr;
	WRL::ComPtr<ID3D11PixelShader> pixelShader = nullptr;
	WRL::ComPtr<ID3D11InputLayout> vertexLayout = nullptr;

	WRL::ComPtr<ID3D11Buffer> vertexBuffer = nullptr;
	WRL::ComPtr<ID3D11Buffer> indexBuffer = nullptr;
	WRL::ComPtr<ID3D11Buffer> constantBuffer = nullptr;

	std::vector<UINT> indices;
	std::vector<std::unique_ptr<Vertex>> vertices;
	std::vector<ID3D11ShaderResourceView*> textures;

	// Get raw pointer from object manager
	ID3D11SamplerState* samplerState = nullptr;
public :
	explicit Object();
	virtual ~Object();

	virtual void Update(float deltaTime);
	virtual void Render(ID3D11DeviceContext* d3dContext, Camera* camera) = 0;

	virtual HRESULT CreatePipeline(ID3D11Device* d3dDevice) = 0;
	virtual HRESULT CreateData(ID3D11Device* d3dDevice) = 0;
	void setSamplerState(ID3D11SamplerState* samplerState);

	HRESULT CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** blob);

//Transform
protected :
	ObjectBuffer objectBuffer;

	DirectX::XMFLOAT3 scale;
	DirectX::XMFLOAT3 rotation;
	DirectX::XMFLOAT3 position;
public :	
	void SetScale(DirectX::XMFLOAT3 newScale);
	void Scaling(DirectX::XMFLOAT3 scaleOffset);

	void SetRotation(DirectX::XMFLOAT3 newRotation);
	void Rotate(DirectX::XMFLOAT3 rotationOffset);

	void SetPosition(DirectX::XMFLOAT3 newPosition);
	void Translate(DirectX::XMFLOAT3 positionOffset);

};