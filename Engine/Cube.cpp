#include "pch.h"
#include "Cube.h"

Cube::Cube() {

}

Cube::~Cube() {

}

HRESULT Cube::CreatePipeline(ID3D11Device* d3dDevice) {
	HRESULT hr = HRESULT();

	WRL::ComPtr<ID3DBlob> vertexShaderBlob = nullptr;
	hr = CompileShaderFromFile(L"Shaders/Cube_VS.hlsl", "main", "vs_5_0", vertexShaderBlob.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(vertexShaderBlob);
		return hr;
	}

	hr = d3dDevice->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(vertexShader);
		return hr;
	}

	D3D11_INPUT_ELEMENT_DESC layouts[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layouts);

	hr = d3dDevice->CreateInputLayout(layouts, numElements, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), vertexLayout.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(vertexLayout);
		return hr;
	}

	WRL::ComPtr<ID3DBlob> pixelShaderBlob = nullptr;
	hr = CompileShaderFromFile(L"Shaders/Cube_PS.hlsl", "main", "ps_5_0", pixelShaderBlob.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(pixelShaderBlob);
		return hr;
	}

	hr = d3dDevice->CreatePixelShader(pixelShaderBlob->GetBufferPointer(), pixelShaderBlob->GetBufferSize(), nullptr, pixelShader.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(pixelShader);
		return hr;
	}
}

HRESULT Cube::CreateData(ID3D11Device* d3dDevice) {
	HRESULT hr = HRESULT();
	D3D11_BUFFER_DESC bufferDesc = D3D11_BUFFER_DESC();
	D3D11_SUBRESOURCE_DATA initData = D3D11_SUBRESOURCE_DATA();

	std::vector<PolygonVertex> vertices = {
		// Front
		PolygonVertex{DirectX::XMFLOAT4(-1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		PolygonVertex{DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
		PolygonVertex{DirectX::XMFLOAT4(-1.0f, -1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 1.0f, 1.0f)},
		PolygonVertex{DirectX::XMFLOAT4(1.0f, -1.0f, 1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 1.0f, 1.0f)},

		// Back
		PolygonVertex{DirectX::XMFLOAT4(-1.0f, 1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)},
		PolygonVertex{DirectX::XMFLOAT4(1.0f, 1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
		PolygonVertex{DirectX::XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)},
		PolygonVertex{DirectX::XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f), DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f)}
	};

	bufferDesc.ByteWidth = sizeof(PolygonVertex) * vertices.size();
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	initData.pSysMem = vertices.data();

	hr = d3dDevice->CreateBuffer(&bufferDesc, &initData, vertexBuffer.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(vertexBuffer);
		return hr;
	}

	indices = {
		//Front
		0, 1, 2, 2, 1, 3,
		//Up
		1, 5, 3, 3, 5, 7,
		//Right
		2, 3, 7, 7, 6, 2,
		//Down
		4, 0, 2, 2, 6, 4,
		//Left
		5, 1, 0, 0, 4, 5,
		//Back
		4, 6, 5, 5, 6, 7
	};

	bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(UINT) * indices.size();
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	initData = {};
	initData.pSysMem = indices.data();

	hr = d3dDevice->CreateBuffer(&bufferDesc, &initData, indexBuffer.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(indexBuffer);
		return hr;
	}

	bufferDesc = {};
	bufferDesc.ByteWidth = sizeof(ObjectBuffer);
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	hr = d3dDevice->CreateBuffer(&bufferDesc, nullptr, constantBuffer.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(constantBuffer);
		return hr;
	}
}

void Cube::Update(float deltaTime) {
	Object::Update(deltaTime);
}

void Cube::Render(ID3D11DeviceContext* d3dContext, Camera* camera, Light* light) {
	UINT stride = sizeof(PolygonVertex);
	UINT offset = 0;

	d3dContext->IASetInputLayout(vertexLayout.Get());
	d3dContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	d3dContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	d3dContext->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &objectBuffer, 0, 0);

	d3dContext->VSSetShader(vertexShader.Get(), nullptr, 0);
	d3dContext->VSSetConstantBuffers(0, 1, camera->getConstantBuffer().GetAddressOf());
	d3dContext->VSSetConstantBuffers(1, 1, light->getConstantBuffer().GetAddressOf());
	d3dContext->VSSetConstantBuffers(2, 1, constantBuffer.GetAddressOf());

	d3dContext->PSSetShader(pixelShader.Get(), nullptr, 0);

	d3dContext->DrawIndexed(indices.size(), 0, 0);
}