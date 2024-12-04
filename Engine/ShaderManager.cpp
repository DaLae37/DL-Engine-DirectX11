#include "pch.h"
#include "ShaderManager.h"

ShaderManager::~ShaderManager() {

}

ShaderManager* ShaderManager::getInstance() {
	static ShaderManager instance;
	return &instance;
}

void ShaderManager::Init() {
	if (std::filesystem::exists(SHADER_DIRECTORY) && std::filesystem::is_directory(SHADER_DIRECTORY)) {
		for (const auto& file : std::filesystem::directory_iterator(SHADER_DIRECTORY)) {
			if (file.is_regular_file() && file.path().extension() == ".cso") {
				std::string fileName = file.path().stem().string();

				std::ifstream binaryShader(file.path(), std::ios::binary);
				if (!binaryShader) {
					continue;
				}
				std::vector<char> binaryData((std::istreambuf_iterator<char>(binaryShader)), std::istreambuf_iterator<char>());
				shaderMap[fileName] = binaryData;
			}
		}
	}
}

const std::vector<char>* ShaderManager::GetCompiledShader(const wchar_t* path, const char* entryPoint, const char* shaderModel) {
	if (shaderMap.find(path) == shaderMap.end()) {
		WRL::ComPtr<ID3DBlob> shaderBlob;
		HRESULT hr = CompileShaderFromFile(path, entryPoint, shaderModel, shaderBlob.GetAddressOf());
		
		char* bufferStart = reinterpret_cast<char*>(shaderBlob->GetBufferPointer());
		shaderMap[path].assign(bufferStart, bufferStart + shaderBlob->GetBufferSize());
	}

	return &shaderMap[path];
}

HRESULT ShaderManager::CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** shaderBlob) {
	HRESULT hr = HRESULT();
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#ifdef _DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	dwShaderFlags |= D3DCOMPILE_OPTIMIZATION_LEVEL3;
#endif

	WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	hr = D3DCompileFromFile(
		static_cast<LPCWSTR>(path), // Shader File Name
		nullptr, // Shader Macros
		D3D_COMPILE_STANDARD_FILE_INCLUDE, // Include Files
		static_cast<LPCSTR>(entryPoint), // Entry Point
		static_cast<LPCSTR>(shaderModel), // Shader Target
		dwShaderFlags, // Flag1
		0, // Flag2
		shaderBlob, // ID3DBlob out 
		errorBlob.GetAddressOf() // Error Blob out
	);
	if (FAILED(hr)) {
		if (errorBlob != nullptr) {
			OutputDebugStringA(static_cast<LPCSTR>(errorBlob->GetBufferPointer()));
			SAFE_RELEASE(errorBlob);
		}
		return hr;
	}
}