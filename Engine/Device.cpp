#include "pch.h"
#include "Device.h"

Device::Device() {

}

Device::~Device() {
    SAFE_COMPTR_DELETE(dxgiDevice);
    SAFE_COMPTR_DELETE(dxgiSwapChain);
    SAFE_COMPTR_DELETE(dxgiFactory);

    SAFE_COMPTR_DELETE(d3dDevice);
    SAFE_COMPTR_DELETE(d3dContext);
    SAFE_COMPTR_DELETE(d3dRenderTargetView);
    SAFE_COMPTR_DELETE(depthStencil);
    SAFE_COMPTR_DELETE(depthStencilView);

    SAFE_COMPTR_DELETE(d2dFactory);
    SAFE_COMPTR_DELETE(d2dDevice);
    SAFE_COMPTR_DELETE(d2dContext);
    SAFE_COMPTR_DELETE(d2dRenderTarget);
}

void Device::RenderStart() {
    d3dContext->ClearRenderTargetView(d3dRenderTargetView.Get(), DirectX::Colors::MidnightBlue);
    d3dContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    d2dContext->BeginDraw();
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
    hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(dxgiFactory.GetAddressOf()));
    if (FAILED(hr)) {
        return hr;
    }

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

    // Setting Depth Stencil
    D3D11_TEXTURE2D_DESC descDepth = {};
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.SampleDesc.Quality = 0;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    descDepth.CPUAccessFlags = 0;
    descDepth.MiscFlags = 0;
    hr = d3dDevice->CreateTexture2D(&descDepth, nullptr, depthStencil.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }

    // Setting Depth Stencil View
    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    descDSV.Texture2D.MipSlice = 0;
    hr = d3dDevice->CreateDepthStencilView(depthStencil.Get(), &descDSV, depthStencilView.GetAddressOf());
    if (FAILED(hr)) {
        return hr;
    }
    d3dContext->OMSetRenderTargets(1, d3dRenderTargetView.GetAddressOf(), depthStencilView.Get());

    // Setting Primitive Type
    d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

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
    if (FAILED(hr)) {
        return hr;
    }

    // Setting D2D RenderTarget
    d2dContext->SetTarget(d2dRenderTarget.Get());

    return S_OK;
}

WRL::ComPtr<ID3D11Device> Device::getD3DDevice() {
    return this->d3dDevice;
}

WRL::ComPtr<ID3D11DeviceContext> Device::getD3DContext() {
    return this->d3dContext;
}

WRL::ComPtr<ID2D1DeviceContext> Device::getD2DContext() {
    return this->d2dContext;
}