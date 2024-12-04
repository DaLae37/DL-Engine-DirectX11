#pragma once
#include "pch.h"

#define ShaderManagerInstance ShaderManager::getInstance()

#define SHADER_DIRECTORY "Shaders"

class ShaderManager
{
private :
	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
	
	bool isInit = false;

	std::unordered_map<std::filesystem::path, std::vector<char>> shaderMap;

	HRESULT CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** shaderBlob);
public :
	~ShaderManager();

	static ShaderManager* getInstance();

	void Init();
	const std::vector<char>* GetCompiledShader(const wchar_t* path, const char* entryPoint, const char* shaderModel);
};