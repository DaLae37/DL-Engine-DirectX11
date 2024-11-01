#pragma once
#include "pch.h"

class Device {
private :
	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_1;

	WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
	WRL::ComPtr<IDXGISwapChain> dxgiSwapChain = nullptr;
	WRL::ComPtr<IDXGIFactory> dxgiFactory = nullptr;
	WRL::ComPtr<IDXGIAdapter> dxgiAdapter = nullptr;

	WRL::ComPtr<ID3D11Device> d3dDevice = nullptr;
	WRL::ComPtr<ID3D11DeviceContext> d3dContext = nullptr;
	WRL::ComPtr<ID3D11RenderTargetView> d3dRenderTargetView = nullptr;
	WRL::ComPtr<ID3D11Texture2D> depthStencil = nullptr;
	WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;


	WRL::ComPtr<ID2D1Factory1> d2dFactory = nullptr;
	WRL::ComPtr<ID2D1Device> d2dDevice = nullptr;
	WRL::ComPtr<ID2D1DeviceContext> d2dContext = nullptr;
	WRL::ComPtr<ID2D1Bitmap1> d2dRenderTarget = nullptr;
	WRL::ComPtr<IWICImagingFactory> wicFactory = nullptr;
public :
	Device();
	~Device();

	void RenderStart();
	void RenderEnd();

	HRESULT InitD3D11Device(HWND hWnd);
	HRESULT InitD2DDevice(HWND hWnd);

	ID3D11Device* getD3DDevice();
	ID3D11DeviceContext* getD3DContext();

	ID2D1DeviceContext* getD2DContext();
	IWICImagingFactory* getWicFactory();
};