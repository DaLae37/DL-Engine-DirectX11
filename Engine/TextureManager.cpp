#include "pch.h"
#include "TextureManager.h"

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {

}

TextureManager* TextureManager::getInstance() {
	static TextureManager instance;
	return &instance;
}

void TextureManager::Init(ID2D1DeviceContext* d2dContext, IWICImagingFactory* wicFactory) {
	this->d2dContext = d2dContext;
	this->wicFactory = wicFactory;

	this->isInit = true;
}

std::weak_ptr<ID2D1Bitmap> TextureManager::LoadD2DTextureFromFile(const wchar_t* path) {
	HRESULT hr = HRESULT();

	WRL::ComPtr<IWICBitmapDecoder> pDecoder = nullptr;
	WRL::ComPtr<IWICBitmapFrameDecode> pFrame = nullptr;
	WRL::ComPtr<IWICFormatConverter> pConverter = nullptr;
	ID2D1Bitmap* originTexture = nullptr;

	if (d2dTextureMap[path] == nullptr) {
		hr = wicFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, pDecoder.GetAddressOf());
		if (SUCCEEDED(hr)) {
			hr = pDecoder->GetFrame(0, pFrame.GetAddressOf());
		}
		if (SUCCEEDED(hr)) {
			hr = wicFactory->CreateFormatConverter(&pConverter);
		}
		if (SUCCEEDED(hr)) {
			hr = pConverter->Initialize(pFrame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
		}
		if (SUCCEEDED(hr)) {
			hr = d2dContext->CreateBitmapFromWicBitmap(pConverter.Get(), nullptr, &originTexture);
		}
		if (SUCCEEDED(hr)) {
			std::shared_ptr<ID2D1Bitmap> texture(originTexture);
			d2dTextureMap[path] = texture;
		}
	}

	return d2dTextureMap[path];
}