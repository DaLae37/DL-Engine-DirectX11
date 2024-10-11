#pragma once
#include "pch.h"

class Device {
private :
	WRL::ComPtr<ID3D11Device> d3dDevice = nullptr;
	WRL::ComPtr<ID3D11Device1> d3dDevice1 = nullptr;

	WRL::ComPtr<ID3D11DeviceContext> d3dContext = nullptr;
	WRL::ComPtr<ID3D11DeviceContext1> d3dContex1 = nullptr;

	WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	WRL::ComPtr<IDXGISwapChain1> swapChain1 = nullptr;

	WRL::ComPtr<ID3D11RenderTargetView> d3dRenderTargetView = nullptr;

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

	WRL::ComPtr<ID2D1Factory1> d2dFactory = nullptr;
	WRL::ComPtr<ID2D1Device> d2dDevice = nullptr;
	WRL::ComPtr<ID2D1DeviceContext> d2dContext = nullptr;
	WRL::ComPtr<ID2D1RenderTarget> d2dRenderTarget = nullptr;
	WRL::ComPtr<IWICImagingFactory> wicFactory = nullptr;
public :
	Device();
	~Device();

	void Render();

	HRESULT InitD3D11Device(HWND hWnd);
	HRESULT InitD3D11Context();
	HRESULT InitSwapChain();
	HRESULT InitD3D11RenderTargetView();

	HRESULT InitD2DDevice(HWND hWnd);
};