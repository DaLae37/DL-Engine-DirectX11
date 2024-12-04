#pragma once
#include "pch.h"

#define TextureManagerInstance TextureManager::getInstance()

class TextureManager
{
private:
	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	bool isInit = false;

	IWICImagingFactory* wicFactory = nullptr;

	std::unordered_map<std::filesystem::path, WRL::ComPtr<ID2D1Bitmap>> d2dTextureMap;
	std::unordered_map<std::filesystem::path, WRL::ComPtr<ID3D11ShaderResourceView>> d3dTextureMap;

	// Get raw pointer from device
	ID2D1DeviceContext* d2dContext = nullptr;
	ID3D11Device* d3dDevice = nullptr;

public:
	~TextureManager();

	static TextureManager* getInstance();

	void Init(ID2D1DeviceContext* d2dContext, ID3D11Device* d3dDevice);

	WRL::ComPtr<ID2D1Bitmap> LoadD2DTextureFromFile(const std::filesystem::path& path);
	WRL::ComPtr<ID3D11ShaderResourceView> LoadD3DTextureFromFile(const std::filesystem::path& path);
};