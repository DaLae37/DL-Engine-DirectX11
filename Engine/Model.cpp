#include "pch.h"
#include "Model.h"

Model::Model(const std::filesystem::path& path) {
	this->path = path;
	this->texturePath = L"Resources/Default/texture.png";
}

Model::Model(const std::filesystem::path &path, const std::filesystem::path& texturePath) {
	this->path = path;
	this->texturePath = texturePath;
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

	const aiScene* scene = importer.ReadFile(static_cast<std::string>(path.string()), ASSIMP_LOAD_FLAGS);
	if (!scene || !scene->HasMeshes()) {
		OutputDebugStringA(importer.GetErrorString());
		return E_FAIL;
	}

	// Create Vertex Buffer
	std::vector<ModelVertex> vertices;

	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		for (int j = 0; j < mesh->mNumVertices; j++) {
			aiVector3D position = mesh->mVertices[j];
			aiVector3D uv = (mesh->HasTextureCoords(0)) ? mesh->mTextureCoords[0][j] : aiVector3D(0.0f, 0.0f, 0.0f);
			aiVector3D normal = (mesh->HasNormals()) ? mesh->mNormals[j] : aiVector3D(0.0f, 0.0f, 0.0f);

			vertices.push_back(ModelVertex{
				DirectX::XMFLOAT4(position.x, position.y, position.z, 1),
				DirectX::XMFLOAT2(uv.x, uv.y),
				DirectX::XMFLOAT3(normal.x, normal.y, normal.z)
				});
		}
	}

	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(ModelVertex) * vertices.size();
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
	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[i];
		for (int j = 0; j < mesh->mNumFaces; j++) {
			aiFace face = mesh->mFaces[j];
			for (int k = 0; k < face.mNumIndices; k++) {
				indices.push_back(face.mIndices[k]);
			}
		}
	}
	
	bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(UINT) * indices.size();
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;

	initData = {};
	initData.pSysMem = indices.data();

	hr = d3dDevice->CreateBuffer(&bufferDesc, &initData, indexBuffer.GetAddressOf());
	if (FAILED(hr)) {
		SAFE_RELEASE(indexBuffer);
		return hr;
	}

	// Create Constant Buffer
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

	// Createa Texture
	if (texturePath != "") {
		textures.push_back(TextureManagerInstance->LoadD3DTextureFromFile(texturePath).Get());
	}

	return S_OK;
}

void Model::Update(float deltaTime) {
	Object::Update(deltaTime);
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
	d3dContext->PSSetShaderResources(0, 1, &textures[0]);
	d3dContext->PSSetSamplers(0, 1, &samplerState);

	d3dContext->DrawIndexed(indices.size(), 0, 0);
}