#include "pch.h"
#include "Device.h"

Device::Device() {

}

Device::~Device() {

}

void Device::Render() {
    d3dContext->OMSetRenderTargets(1, d3dRenderTargetView.GetAddressOf(), nullptr);
    d3dContext->ClearRenderTargetView(d3dRenderTargetView.Get(), DirectX::Colors::MidnightBlue);

    d2dContext->BeginDraw();
    d2dContext->EndDraw();

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

    const D3D_DRIVER_TYPE driverTypes[] =
    {
        D3D_DRIVER_TYPE_HARDWARE,
        D3D_DRIVER_TYPE_WARP,
        D3D_DRIVER_TYPE_REFERENCE,
    };
    UINT numDriverTypes = ARRAYSIZE(driverTypes);

    const D3D_FEATURE_LEVEL featureLevels[] =
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
            D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, d3dContext.GetAddressOf());

        if (hr == E_INVALIDARG)
        {
            hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, &featureLevels[1], numFeatureLevels - 1,
                D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, d3dContext.GetAddressOf());
        }

        if (SUCCEEDED(hr)) {
            break;
        }
    }
    if (FAILED(hr)) {
        return hr;
    }

    WRL::ComPtr<IDXGIDevice> dxgiDevice;
    WRL::ComPtr<IDXGIFactory> dxgiFactory;

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
            d3dContext.As(&d3dContext);
        }

        DXGI_SWAP_CHAIN_DESC1 sd = {};
        sd.Width = width;
        sd.Height = height;
        sd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
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
        sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
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

    hr = d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, d3dRenderTargetView.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }

    D3D11_VIEWPORT vp = D3D11_VIEWPORT();
    vp.Width = static_cast<FLOAT>(width);
    vp.Height = static_cast<FLOAT>(height);
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;

    d3dContext->RSSetViewports(1, &vp);

    return S_OK;
}

HRESULT Device::InitD2DDevice(HWND hWnd) {
    HRESULT hr = HRESULT();

    WRL::ComPtr<IDXGIDevice> dxgiDevice;
    hr = d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));
    if (FAILED(hr)) {
        return hr;
    }

    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, d2dFactory.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }

    hr = d2dFactory->CreateDevice(dxgiDevice.Get(), d2dDevice.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }

    hr = d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, d2dContext.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }

    WRL::ComPtr<IDXGISurface> dxgiSurface;
    hr = swapChain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void **>(dxgiSurface.GetAddressOf()));
    if (FAILED(hr)) {
        return hr;
    }

    D2D1_RENDER_TARGET_PROPERTIES renderTargetProps = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96.0f, 96.0f
    );

    hr = d2dFactory->CreateDxgiSurfaceRenderTarget(dxgiSurface.Get(), &renderTargetProps, d2dRenderTarget.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }
    return S_OK;
}