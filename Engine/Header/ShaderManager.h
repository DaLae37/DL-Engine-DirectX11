#pragma once
#include "pch.h"

// Singleton Pattern
#define ShaderManagerInstance ShaderManager::getInstance()

#define SHADER_DIRECTORY "Shaders"

class ShaderManager {
private:
	// Singleton Pattern Safety
	ShaderManager() = default;
	// Remove Copy Constructor
	ShaderManager(const ShaderManager&) = delete;
	// Remove Substitution Operator
	ShaderManager& operator=(const ShaderManager&) = delete;

	std::unordered_map<std::filesystem::path, std::vector<char>> shaderMap;

	// When Instance is Initialized, Changed to true
	bool isInit = false;

	// Compile Shader from Local
	HRESULT CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** shaderBlob);
public:
	~ShaderManager();

	// Get ShaderManager's Instances
	static ShaderManager* getInstance();

	// Initialize ShaderManager Instance *Must Called Before Using Any Functions*
	void Init();
	const std::vector<char>* GetCompiledShader(const wchar_t* path, const char* entryPoint, const char* shaderModel);
};