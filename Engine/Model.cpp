#include "pch.h"
#include "Model.h"

Model::Model(const std::filesystem::path &path) {
	this->path = path;

	Assimp::Importer importer;
	
	const aiScene* scene = importer.ReadFile(static_cast<std::string>(path.string()), aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	static CHAR debugMSG[256];
	sprintf_s(debugMSG, "Number of meshes found in file: % d\nNumber of verticies in first mesh : % d\n", scene->mNumMeshes, scene->mMeshes[0]->mNumVertices);
	OutputDebugStringA(debugMSG);
}

Model::~Model() {

}

void Model::Update(float deltaTime) {

}

void Model::Render(ID3D11DeviceContext* d3dContext, Camera* camera) {

}

HRESULT Model::CreatePipeline(ID3D11Device* d3dDevice) {
	return S_OK;
}

HRESULT Model::CreateData(ID3D11Device* d3dDevice) {
	return S_OK;
}

void Model::BindData(ID3D11DeviceContext* d3dContext) {

}