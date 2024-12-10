#pragma once
#include "pch.h"

#define TextureManagerInstance TextureManager::getInstance()

class TextureManager {
private:
	// Singleton Pattern Safety
	TextureManager() = default;
	// Remove Copy Constructor
	TextureManager(const TextureManager&) = delete;
	// Remove Substitution Operator
	TextureManager& operator=(const TextureManager&) = delete;

	IWICImagingFactory* wicFactory = nullptr;

	std::unordered_map<std::filesystem::path, WRL::ComPtr<ID2D1Bitmap>> d2dTextureMap;
	std::unordered_map<std::filesystem::path, WRL::ComPtr<ID3D11ShaderResourceView>> d3dTextureMap;

	// When Instance is Initialized, Changed to true
	bool isInit = false;

	// Get Raw Pointer from Device
	ID2D1DeviceContext* d2dContext = nullptr;
	ID3D11Device* d3dDevice = nullptr;

public:
	~TextureManager();

	// Get TextureManager's Instance
	static TextureManager* getInstance();

	// Initialize TextureManager Instance *Must Called Before Using Any Functions*
	void Init(ID2D1DeviceContext* d2dContext, ID3D11Device* d3dDevice);

	WRL::ComPtr<ID2D1Bitmap> LoadD2DTextureFromFile(const std::filesystem::path& path);
	WRL::ComPtr<ID3D11ShaderResourceView> LoadD3DTextureFromFile(const std::filesystem::path& path);
};