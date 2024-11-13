#include "pch.h"
#include "TextureManager.h"

TextureManager::TextureManager() {

}

TextureManager::~TextureManager() {
	d2dTextureMap.clear();
	d3dTextureMap.clear();

	SAFE_RELEASE(wicFactory);

	CoUninitialize();
}

TextureManager* TextureManager::getInstance() {
	static TextureManager instance;
	return &instance;
}

void TextureManager::Init(ID2D1DeviceContext* d2dContext) {
	this->d2dContext = d2dContext;

	if (wicFactory == nullptr) {
		HRESULT hr = HRESULT();
		hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		// Create WICFactory
		hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));
		if (FAILED(hr)) {
			return;
		}
	}

	this->isInit = true;
}

WRL::ComPtr<ID2D1Bitmap> TextureManager::LoadD2DTextureFromFile(const wchar_t* path) {
	HRESULT hr = HRESULT();

	if (d2dTextureMap[path] == nullptr) {
		WRL::ComPtr<ID2D1Bitmap> texture = nullptr;
		WRL::ComPtr<IWICBitmapDecoder> wicDecoder = nullptr;
		WRL::ComPtr<IWICBitmapFrameDecode> wicFrame = nullptr;
		WRL::ComPtr<IWICFormatConverter> wicConverter = nullptr;

		hr = wicFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, wicDecoder.GetAddressOf());
		if (SUCCEEDED(hr)) {
			hr = wicDecoder->GetFrame(0, wicFrame.GetAddressOf());
		}
		if (SUCCEEDED(hr)) {
			hr = wicFactory->CreateFormatConverter(wicConverter.GetAddressOf());
		}
		if (SUCCEEDED(hr)) {
			hr = wicConverter->Initialize(wicFrame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
		}
		if (SUCCEEDED(hr)) {
			hr = d2dContext->CreateBitmapFromWicBitmap(wicConverter.Get(), nullptr, texture.GetAddressOf());
		}
		if (SUCCEEDED(hr)) {
			d2dTextureMap[path].Attach(texture.Detach());
		}
	}

	return d2dTextureMap[path];
}

WRL::ComPtr<ID3D11Texture2D> TextureManager::LoadD3DTextureFromFile(const wchar_t* path) {
	HRESULT hr = HRESULT();

	if (d3dTextureMap[path] == nullptr) {
		WRL::ComPtr<ID3D11Texture2D> texture = nullptr;
		WRL::ComPtr<IWICBitmapDecoder> wicDecoder = nullptr;
		WRL::ComPtr<IWICBitmapFrameDecode> wicFrame = nullptr;
		WRL::ComPtr<IWICFormatConverter> wicConverter = nullptr;

		hr = wicFactory->CreateDecoderFromFilename(path, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, wicDecoder.GetAddressOf());
		if (SUCCEEDED(hr)) {
			hr = wicDecoder->GetFrame(0, wicFrame.GetAddressOf());
		}
		if (SUCCEEDED(hr)) {
			hr = wicFactory->CreateFormatConverter(wicConverter.GetAddressOf());
		}
		if (SUCCEEDED(hr)) {
			hr = wicConverter->Initialize(wicFrame.Get(), GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.f, WICBitmapPaletteTypeCustom);
		}
		UINT width, height;
		if (SUCCEEDED(hr)) {
			hr = wicConverter->GetSize(&width, &height);
		}
		std::vector<BYTE> buffer(width * height * 4);  // 4바이트(BGRA)
		if (SUCCEEDED(hr)) {
			hr = wicConverter->CopyPixels(nullptr, width * 4, static_cast<UINT>(buffer.size()), buffer.data());
		}

		// D3D11 텍스처2D 생성
		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1;
		textureDesc.ArraySize = 1;
		textureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SUBRESOURCE_DATA initData = {};
		initData.pSysMem = buffer.data();
		initData.SysMemPitch = width * 4;
	}

	return d3dTextureMap[path];	
}