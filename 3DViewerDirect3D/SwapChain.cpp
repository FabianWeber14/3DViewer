#include "SwapChain.h"

SwapChain::SwapChain(HWND hwnd, ID3D11Device1* d3d11Device, ID3D11DeviceContext1* d3d11DeviceContext)
{


    // Get DXGI Factory (needed to create Swap Chain)
    IDXGIFactory2* dxgiFactory;
    {
        IDXGIDevice1* dxgiDevice;
        HRESULT hResult = d3d11Device->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgiDevice);

        IDXGIAdapter* dxgiAdapter;
        hResult = dxgiDevice->GetAdapter(&dxgiAdapter);
        dxgiDevice->Release();

        DXGI_ADAPTER_DESC adapterDesc;
        dxgiAdapter->GetDesc(&adapterDesc);

        OutputDebugStringA("Graphics Device: ");
        OutputDebugStringW(adapterDesc.Description);

        hResult = dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&dxgiFactory);
        dxgiAdapter->Release();
    }

    DXGI_SWAP_CHAIN_DESC1 d3d11SwapChainDesc = {};
    d3d11SwapChainDesc.Width = 0; // use window width
    d3d11SwapChainDesc.Height = 0; // use window height
    d3d11SwapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;
    d3d11SwapChainDesc.SampleDesc.Count = 1;
    d3d11SwapChainDesc.SampleDesc.Quality = 0;
    d3d11SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    d3d11SwapChainDesc.BufferCount = 2;
    d3d11SwapChainDesc.Scaling = DXGI_SCALING_STRETCH;
    d3d11SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    d3d11SwapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
    d3d11SwapChainDesc.Flags = 0;

    HRESULT hResult = dxgiFactory->CreateSwapChainForHwnd(d3d11Device, hwnd, &d3d11SwapChainDesc, 0, 0, &m_pSwapChain);

    dxgiFactory->Release();



	// Create Frame Buffer
    Microsoft::WRL::ComPtr<ID3D11Texture2D> d3d11FrameBuffer;
    hResult = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &d3d11FrameBuffer);

    hResult = d3d11Device->CreateRenderTargetView(d3d11FrameBuffer.Get(), nullptr, m_pFrameBuffer.ReleaseAndGetAddressOf());
    d3d11FrameBuffer->Release();

}

void SwapChain::clearRenderTarget(ID3D11DeviceContext1* d3d11DeviceContext, float clearColor[4])
{
	d3d11DeviceContext->ClearRenderTargetView(m_pFrameBuffer.Get(), clearColor);
}

void SwapChain::present()
{
    m_pSwapChain->Present(1, 0);
}

void SwapChain::resize(ID3D11Device1* d3d11Device, ID3D11DeviceContext1* d3d11DeviceContext)
{
    d3d11DeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
    m_pFrameBuffer.Reset();
    HRESULT res = m_pSwapChain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0);


    Microsoft::WRL::ComPtr<ID3D11Texture2D> d3d11FrameBuffer;
    res = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&d3d11FrameBuffer);

    res = d3d11Device->CreateRenderTargetView(d3d11FrameBuffer.Get(), nullptr,
        m_pFrameBuffer.GetAddressOf());


}
