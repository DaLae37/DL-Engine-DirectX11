#pragma once
#include "pch.h"

class Device {
private :
	WRL::ComPtr<ID3D11Device> d3dDevice = nullptr;
	WRL::ComPtr<ID3D11Device1> d3dDevice1 = nullptr;

	WRL::ComPtr<ID3D11DeviceContext> immediateContext = nullptr;
	WRL::ComPtr<ID3D11DeviceContext1> immediateContext1 = nullptr;

	WRL::ComPtr<IDXGISwapChain> swapChain = nullptr;
	WRL::ComPtr<IDXGISwapChain1> swapChain1 = nullptr;

	WRL::ComPtr<ID3D11RenderTargetView> renderTargetView = nullptr;

	D3D_DRIVER_TYPE driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;
public :
	Device();
	~Device();

	void Render();

	HRESULT InitD3D11Device(HWND hWnd);
	HRESULT InitD3D11Context();
	HRESULT InitSwapChain();
	HRESULT InitD3D11RenderTargetView();
};