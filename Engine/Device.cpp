#include "pch.h"
#include "Device.h"

Device::Device() {

}

Device::~Device() {

}

void Device::RenderStart() {
    d3dContext->ClearRenderTargetView(d3dRenderTargetView.Get(), DirectX::Colors::White);

    d2dContext->BeginDraw();
    d2dContext->Clear(D2D1::ColorF(D2D1::ColorF::White));
}

void Device::RenderEnd() {
    d2dContext->EndDraw();
    dxgiSwapChain->Present(1, 0);
}

HRESULT Device::InitD3D11Device(HWND hWnd) {
    HRESULT hr = HRESULT();

    RECT rect = RECT();
    GetClientRect(hWnd, &rect);
    UINT width = static_cast<UINT>(rect.right - rect.left);
    UINT height = static_cast<UINT>(rect.bottom - rect.top);

    // Create D3D11 Device
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
        hr = D3D11CreateDevice(nullptr, driverType, nullptr, createDeviceFlags, featureLevels, numFeatureLevels, D3D11_SDK_VERSION, d3dDevice.GetAddressOf(), &featureLevel, d3dContext.GetAddressOf());
        if (SUCCEEDED(hr)) {
            break;
        }
    }
    if (FAILED(hr)) {
        return hr;
    }

    // Create DXGI Device with D3D11 Device
    hr = d3dDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));
    if (FAILED(hr)) {
        return hr;
    }

    // Setting SwapChain
    DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWnd;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;

    // Create SwapChain
    CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgiFactory.GetAddressOf()));
    hr = dxgiFactory->CreateSwapChain(d3dDevice.Get(), &swapChainDesc, dxgiSwapChain.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }

    // Create D3DRenderTarget
    WRL::ComPtr<ID3D11Texture2D> backBuffer;
    hr = dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
    if (FAILED(hr)) {
        return hr;
    }

    hr = d3dDevice->CreateRenderTargetView(backBuffer.Get(), nullptr, d3dRenderTargetView.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }
    
    // Setting D3DRenderTarget
    d3dContext->OMSetRenderTargets(1, d3dRenderTargetView.GetAddressOf(), nullptr);

    // Setting ViewPort
    D3D11_VIEWPORT viewPort = D3D11_VIEWPORT();
    viewPort.Width = static_cast<FLOAT>(width);
    viewPort.Height = static_cast<FLOAT>(height);
    viewPort.MinDepth = 0.0f;
    viewPort.MaxDepth = 1.0f;
    viewPort.TopLeftX = 0;
    viewPort.TopLeftY = 0;

    d3dContext->RSSetViewports(1, &viewPort);

    return S_OK;
}

HRESULT Device::InitD2DDevice(HWND hWnd) {
    HRESULT hr = HRESULT();

    // Create D2D Factory
    const D2D1_FACTORY_OPTIONS opts = { D2D1_DEBUG_LEVEL_INFORMATION };
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_MULTI_THREADED, __uuidof(ID2D1Factory1), &opts, reinterpret_cast<void**>(d2dFactory.GetAddressOf()));
    if (FAILED(hr)) {
        return hr;
    }

    // Create D2D Device
    hr = d2dFactory->CreateDevice(dxgiDevice.Get(), d2dDevice.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }

    // Create D2D Context
    hr = d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, d2dContext.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }

    // Create D2DRenderTarget
    WRL::ComPtr<IDXGISurface> backBuffer;
    hr = dxgiSwapChain->GetBuffer(0, __uuidof(IDXGISurface), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
    if (FAILED(hr)) {
        return hr;
    }

    const D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)
    );

    hr = d2dContext->CreateBitmapFromDxgiSurface(backBuffer.Get(), &bitmapProperties, d2dRenderTarget.GetAddressOf());
    if (FAILED(hr)) return hr;

    // Setting D2D RenderTarget
    d2dContext->SetTarget(d2dRenderTarget.Get());

    // Create WICFactory
    hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wicFactory));
    if (FAILED(hr)) {
        return hr;
    }

    return S_OK;
}

ID2D1DeviceContext* Device::getD2DContext() {
    return this->d2dContext.Get();
}

IWICImagingFactory* Device::getWicFactory() {
    return this->wicFactory.Get();
}