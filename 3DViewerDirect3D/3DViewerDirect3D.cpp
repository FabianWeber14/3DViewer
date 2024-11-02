#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <d3d11_1.h>
#pragma comment(lib, "d3d11.lib")
#include <d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include <assert.h>
#include "VertexShader.h"
#include "PixelShader.h"
#include "D3DDeviceContext.h"
#include "SwapChain.h"
#include "Window.h"
#include "VertexBuffer.h"
#include <DirectXMath.h>




int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
{

    Window win{ hInstance };

    D3DDeviceContext deviceContext;

    // Create Swap Chain
    SwapChain swapChain{ win.hwnd, deviceContext.getD3D11Device(), deviceContext.getD3D11DeviceContext(), 0, 0 };

    // Define Input Layout
    std::array inputElementDesc =
    {
        D3D11_INPUT_ELEMENT_DESC{ "POS", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        D3D11_INPUT_ELEMENT_DESC{ "COL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // Create Shader
    VertexShader vertexShader{ deviceContext.getD3D11Device(),inputElementDesc };
    PixelShader pixelShader{ deviceContext.getD3D11Device() };

    // Create Vertex Buffer

    struct Vertex
    {
        DirectX::XMFLOAT2 pos;
        DirectX::XMFLOAT4 col;
    };

    std::array vertexData = { // x, y, r, g, b, a
        Vertex {.pos{  0.0f,  0.5f}, .col{ 0.f, 1.f, 0.f, 1.f }},
        Vertex {.pos{  0.5f, -0.5f}, .col{ 1.f, 0.f, 0.f, 1.f }},
        Vertex {.pos{ -0.5f, -0.5f}, .col{ 0.f, 0.f, 1.f, 1.f }}
    };

    VertexBuffer vertexBuffer(deviceContext.getD3D11Device(), std::span<Vertex>(vertexData));

    // Main Loop
    bool isRunning = true;
    while (isRunning)
    {
        MSG msg = {};
        while (PeekMessageW(&msg, 0, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                isRunning = false;
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }

        if (win.needResize())
        {
            swapChain.resize(deviceContext.getD3D11Device(), deviceContext.getD3D11DeviceContext());
            win.resetNeedResize();
        }

        FLOAT backgroundColor[4] = { 0.1f, 0.2f, 0.6f, 1.0f };
        swapChain.clearRenderTarget(deviceContext.getD3D11DeviceContext(), backgroundColor);

        RECT winRect;
        GetClientRect(win.hwnd, &winRect);
        D3D11_VIEWPORT viewport = { 0.0f, 0.0f, (FLOAT)(winRect.right - winRect.left), (FLOAT)(winRect.bottom - winRect.top), 0.0f, 1.0f };
        deviceContext.getD3D11DeviceContext()->RSSetViewports(1, &viewport);

        auto* frameBuffer{ swapChain.getFrameBuffer() };
        deviceContext.getD3D11DeviceContext()->OMSetRenderTargets(1, &frameBuffer, nullptr);

        deviceContext.getD3D11DeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        deviceContext.getD3D11DeviceContext()->IASetInputLayout(vertexShader.getInputLayout());

        deviceContext.getD3D11DeviceContext()->VSSetShader(vertexShader.getVertexShader(), nullptr, 0);
        deviceContext.getD3D11DeviceContext()->PSSetShader(pixelShader.getPixelShader(), nullptr, 0);

        ID3D11Buffer* vertexBufferData{ vertexBuffer.getVertexBuffer() };
        deviceContext.getD3D11DeviceContext()->IASetVertexBuffers(0, 1, &vertexBufferData, &vertexBuffer.stride, &vertexBuffer.offset);

        deviceContext.getD3D11DeviceContext()->Draw(vertexBuffer.numVerts, 0);

        swapChain.present();
    }

    return 0;
}