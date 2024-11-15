#include "pch.h"
#include "Model.h"

Model::Model(const std::filesystem::path &path) {
	this->path = path;
}

Model::~Model() {

}

HRESULT Model::CreatePipeline(ID3D11Device* d3dDevice) {
	HRESULT hr = HRESULT();

	WRL::ComPtr<ID3DBlob> vertexShaderBlob = nullptr;
	hr = CompileShaderFromFile(L"../Engine/Shader/Model_VS.hlsl", "main", "vs_5_0", vertexShaderBlob.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(vertexShaderBlob);
		return hr;
	}

	hr = d3dDevice->CreateVertexShader(vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), nullptr, vertexShader.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(vertexShader);
		return hr;
	}

	D3D11_INPUT_ELEMENT_DESC layouts[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	UINT numElements = ARRAYSIZE(layouts);

	hr = d3dDevice->CreateInputLayout(layouts, numElements, vertexShaderBlob->GetBufferPointer(), vertexShaderBlob->GetBufferSize(), vertexLayout.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(vertexLayout);
		return hr;
	}

	WRL::ComPtr<ID3DBlob> pixelShaderBlob = nullptr;
	hr = CompileShaderFromFile(L"../Engine/Shader/Model_PS.hlsl", "main", "ps_5_0", pixelShaderBlob.GetAddressOf());
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

HRESULT Model::CreateData(ID3D11Device* d3dDevice) {
	HRESULT hr = HRESULT();
	D3D11_BUFFER_DESC bufferDesc = D3D11_BUFFER_DESC();
	D3D11_SUBRESOURCE_DATA initData = D3D11_SUBRESOURCE_DATA();

	Assimp::Importer importer;

	const aiScene* scene = importer.ReadFile(static_cast<std::string>(path.string()), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	if (!scene || !scene->HasMeshes()) {
		OutputDebugStringA(importer.GetErrorString());
		return E_FAIL;
	}

	// Create Vertex Buffer
	std::vector<ModelVertex> vertices;

	for (int i = 0; i < scene->mMeshes[0]->mNumVertices; i++) {
		aiVector3D pos = scene->mMeshes[0]->mVertices[i];
		aiVector3D texCoord = (scene->mMeshes[0]->HasTextureCoords(0)) ? scene->mMeshes[0]->mTextureCoords[0][i] : aiVector3D(0.0f, 0.0f, 0.0f);
		aiVector3D normal = scene->mMeshes[0]->mNormals[i];

		vertices.push_back(ModelVertex{
			DirectX::XMFLOAT4(pos.x, pos.y, pos.z, 0),
			DirectX::XMFLOAT2(texCoord.x, texCoord.y),
			DirectX::XMFLOAT3(normal.x, normal.y, normal.z)
		});
	}

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(PolygonVertex) * vertices.size();
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	initData.pSysMem = vertices.data();

	hr = d3dDevice->CreateBuffer(&bufferDesc, &initData, vertexBuffer.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(vertexBuffer);
		return hr;
	}

	// Create Index Buffer
	for (int i = 0; i < scene->mMeshes[0]->mNumFaces; i++) {
		aiFace face = scene->mMeshes[0]->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	
	bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(WORD) * indices.size();
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

	objectBuffer.world = DirectX::XMMatrixRotationY(45.0f);
	objectBuffer.world *= DirectX::XMMatrixTranslation(0, 0, 50);
	objectBuffer.world = DirectX::XMMatrixTranspose(objectBuffer.world);

	return S_OK;
}

void Model::Update(float deltaTime) {

}

void Model::Render(ID3D11DeviceContext* d3dContext, Camera* camera) {
	UINT stride = sizeof(ModelVertex);
	UINT offset = 0;

	d3dContext->IASetInputLayout(vertexLayout.Get());
	d3dContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
	d3dContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);

	d3dContext->UpdateSubresource(constantBuffer.Get(), 0, nullptr, &objectBuffer, 0, 0);

	d3dContext->VSSetShader(vertexShader.Get(), nullptr, 0);
	d3dContext->VSSetConstantBuffers(0, 1, camera->getConstantBuffer().GetAddressOf());
	d3dContext->VSSetConstantBuffers(1, 1, constantBuffer.GetAddressOf());

	d3dContext->PSSetShader(pixelShader.Get(), nullptr, 0);

	d3dContext->DrawIndexed(indices.size(), 0, 0);
}