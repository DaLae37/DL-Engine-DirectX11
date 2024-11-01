#include "pch.h"
#include "Object.h"

Object::Object() {

}

Object::~Object() {

}

HRESULT Object::CompileShaderFromFile(const wchar_t* path, const char* entryPoint, const char* shaderModel, ID3DBlob** blob) {
	HRESULT hr = HRESULT();

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	WRL::ComPtr<ID3DBlob> errorBlob = nullptr;
	hr = D3DCompileFromFile(
		static_cast<LPCWSTR>(path), // Shader File Name
		nullptr, // Shader Macros
		nullptr, // Include Files
		static_cast<LPCSTR>(entryPoint), // Entry Point
		static_cast<LPCSTR>(shaderModel), // Shader Target
		dwShaderFlags, // Flag1
		0, // Flag2
		blob, // ID3DBlob out 
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