#pragma once
#include "Object.h"

//ASSIMP
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#define ASSIMP_LOAD_FLAGS (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices | aiProcess_ConvertToLeftHanded)

class Model : public Object
{
private:
	std::filesystem::path path;
	
public :
	Model(const std::filesystem::path &path);
	~Model();

	void Update(float deltaTime);
	void Render(ID3D11DeviceContext* d3dContext, Camera* camera);

	HRESULT CreatePipeline(ID3D11Device* d3dDevice);
	HRESULT CreateData(ID3D11Device* d3dDevice);
};