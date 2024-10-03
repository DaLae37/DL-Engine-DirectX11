#include "pch.h"
#include "Device.h"

Device::Device() {

}

Device::~Device() {

}

void Device::Render() {
    immediateContext->ClearRenderTargetView(renderTargetView.Get(), DirectX::Colors::MidnightBlue);
    swapChain->Present(0, 0);
}

HRESULT Device::InitD3D11Device(HWND hWnd) {
    HRESULT hr = HRESULT();

    RECT rc = RECT();
    GetClientRect(hWnd, &rc);
    UINT width = static_cast<UINT>(rc.right - rc.left);
    UINT height = static_cast<UINT>(rc.bottom - rc.top);

    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
    };
    UINT numFeatureLevels = ARRAYSIZE(featureLevels);

    for (UINT driverTypeIndex = 0; driverTypeIndex < numDriverTypes; driverTypeIndex++)
    {
        driverType = driverTypes[driverTypeIndex];
        hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels,
            D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, immediateContext.GetAddressOf());

        if (hr == E_INVALIDARG)
        {
            hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, immediateContext.GetAddressOf());
        }

        if (SUCCEEDED(hr)) {
            break;
        }
    }
    if (FAILED(hr)) {
        return hr;
    }

    WRL::ComPtr<IDXGIDevice> dxgiDevice;
    WRL::ComPtr<IDXGIFactory1> dxgiFactory;

    hr = d3dDevice.As(&dxgiDevice);
    if (SUCCEEDED(hr))
    {
        WRL::ComPtr<IDXGIAdapter> adapter;
        hr = dxgiDevice->GetAdapter(&adapter);
        if (SUCCEEDED(hr))
        {
            hr = adapter->GetParent(IID_PPV_ARGS(&dxgiFactory));
        }
    }
    if (FAILED(hr)) {
        return hr;
    }

    WRL::ComPtr<IDXGIFactory2> dxgiFactory2;
    hr = dxgiFactory.As(&dxgiFactory2);
    if (SUCCEEDED(hr))
    {
        hr = d3dDevice.As(&d3dDevice1);
        if (SUCCEEDED(hr))
        {
            immediateContext.As(&immediateContext1);
        }

        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 1;

        hr = dxgiFactory2->CreateSwapChainForHwnd(d3dDevice.Get(), hWnd, &sd, nullptr, nullptr, swapChain1.GetAddressOf());
        if (SUCCEEDED(hr))
        {
            hr = swapChain1.As(&swapChain);
        }
    }
    else
    {
        DXGI_SWAP_CHAIN_DESC sd = {};
        sd.BufferCount = 1;
        sd.BufferDesc.Width = width;
        sd.BufferDesc.Height = height;
        sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        sd.BufferDesc.RefreshRate.Numerator = 60;
        sd.BufferDesc.RefreshRate.Denominator = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.OutputWindow = hWnd;
        sd.SampleDesc.Count = 1;
        sd.SampleDesc.Quality = 0;
        sd.Windowed = TRUE;

        hr = dxgiFactory->CreateSwapChain(d3dDevice.Get(), &sd, swapChain.GetAddressOf());
    }
    if (FAILED(hr)) {
        return hr;
    }

    WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    if (FAILED(hr)) {
        return hr;
    }

    hr = d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, renderTargetView.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }


    immediateContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), nullptr);

    D3D11_VIEWPORT vp = D3D11_VIEWPORT();
    vp.Width = static_cast<FLOAT>(width);
    vp.Height = static_cast<FLOAT>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    immediateContext->RSSetViewports(1, &vp);

    return S_OK;
}