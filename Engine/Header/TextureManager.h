#pragma once
#include "pch.h"

#define TextureManagerInstance TextureManager::getInstance()

class TextureManager
{
private :
	bool isInit = false;

	std::unordered_map<const wchar_t*, std::shared_ptr<ID2D1Bitmap>> d2dTextureMap;
	std::unordered_map<const wchar_t*, std::shared_ptr<ID3D11Texture2D>> d3dTextureMap;

	ID2D1DeviceContext* d2dContext = nullptr;
	IWICImagingFactory* wicFactory = nullptr;
public :
	TextureManager();
	~TextureManager();

	static TextureManager* getInstance();

	void Init(ID2D1DeviceContext* d2dContext, IWICImagingFactory* wicFactory);

	std::weak_ptr<ID2D1Bitmap> LoadD2DTextureFromFile(const wchar_t* path);
	std::weak_ptr<ID3D11Texture2D> LoadD3DTextureFromFile(const wchar_t* path);
};

