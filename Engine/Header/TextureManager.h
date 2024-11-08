#pragma once
#include "pch.h"

#define TextureManagerInstance TextureManager::getInstance()

class TextureManager
{
private :
	TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	bool isInit = false;

	WRL::ComPtr<IWICBitmapDecoder> wicDecoder = nullptr;
	WRL::ComPtr<IWICBitmapFrameDecode> wicFrame = nullptr;
	WRL::ComPtr<IWICFormatConverter> wicConverter = nullptr;

	std::unordered_map<std::wstring, WRL::ComPtr<ID2D1Bitmap>> d2dTextureMap;
	std::unordered_map<std::wstring, WRL::ComPtr<ID3D11Texture2D>> d3dTextureMap;

	ID2D1DeviceContext* d2dContext = nullptr;
	IWICImagingFactory* wicFactory = nullptr;
public :
	~TextureManager();

	static TextureManager* getInstance();

	void Init(ID2D1DeviceContext* d2dContext, IWICImagingFactory* wicFactory);

	ID2D1Bitmap* LoadD2DTextureFromFile(const wchar_t* path);
	ID3D11Texture2D* LoadD3DTextureFromFile(const wchar_t* path);
};

