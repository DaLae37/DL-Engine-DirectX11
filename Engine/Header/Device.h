#pragma once
#include "pch.h"

class Device {
private:
	// DXGI Devices
	WRL::ComPtr<IDXGIDevice> dxgiDevice = nullptr;
	WRL::ComPtr<IDXGISwapChain> dxgiSwapChain = nullptr;
	WRL::ComPtr<IDXGIFactory> dxgiFactory = nullptr;

	// D3D Devices
	WRL::ComPtr<ID3D11Device> d3dDevice = nullptr;
	WRL::ComPtr<ID3D11DeviceContext> d3dContext = nullptr;
	WRL::ComPtr<ID3D11RenderTargetView> d3dRenderTargetView = nullptr;

	WRL::ComPtr<ID3D11Texture2D> depthStencil = nullptr;
	WRL::ComPtr<ID3D11DepthStencilView> depthStencilView = nullptr;
	WRL::ComPtr<ID3D11RasterizerState> rasterState = nullptr;

	// D2D Devices
	WRL::ComPtr<ID2D1Factory1> d2dFactory = nullptr;
	WRL::ComPtr<ID2D1Device> d2dDevice = nullptr;
	WRL::ComPtr<ID2D1DeviceContext> d2dContext = nullptr;
	WRL::ComPtr<ID2D1Bitmap1> d2dRenderTarget = nullptr;

public:
	Device();
	~Device();

	void RenderStart();
	void RenderEnd();

	// Initialize D3DDevices
	HRESULT InitD3D11Device(HWND hWnd);
	// Initialize D2DDevices *Do Not Call Before D3D Initialized*
	HRESULT InitD2DDevice(HWND hWnd);

	// Get d3dDevice Pointer
	WRL::ComPtr<ID3D11Device> getD3DDevice();
	// Get d3dContext Pointer
	WRL::ComPtr<ID3D11DeviceContext> getD3DContext();
	// Get d2dContext Pointer
	WRL::ComPtr<ID2D1DeviceContext> getD2DContext();
};