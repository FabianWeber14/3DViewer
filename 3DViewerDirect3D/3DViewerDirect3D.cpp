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
#include "IndexBuffer.h"
#include "MeshImporter.h"
#include "SwapChain.h"
#include "Window.h"
#include "VertexBuffer.h"
#include "Vertex.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nShowCmd*/)
{

    Window win{ hInstance };

    D3DDeviceContext deviceContext;

    // Create Swap Chain
    SwapChain swapChain{ win.hwnd, deviceContext.getD3D11Device(), deviceContext.getD3D11DeviceContext(), 0, 0 };

    // Define Input Layout
    std::array inputElementDesc =
    {
        D3D11_INPUT_ELEMENT_DESC{ "POS", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        D3D11_INPUT_ELEMENT_DESC{ "COL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        D3D11_INPUT_ELEMENT_DESC{ "NOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    // Create Shader
    VertexShader vertexShader{ deviceContext.getD3D11Device(),inputElementDesc };
    PixelShader pixelShader{ deviceContext.getD3D11Device() };

    // Create Vertex Buffer

    auto cube = MeshImporter::getCube();


    VertexBuffer vertexBuffer(deviceContext.getD3D11Device(), std::span<Vertex>(cube.m_vertices));
    IndexBuffer indexBuffer(deviceContext.getD3D11Device(), std::span<unsigned int>(cube.m_indices));

	DirectX::XMMATRIX modelTransform = DirectX::XMMatrixScaling(0.5,0.5,0.5)* DirectX::XMMatrixRotationX(0.3);
    Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer{ nullptr };

    D3D11_BUFFER_DESC cbd;
    cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    cbd.Usage = D3D11_USAGE_DYNAMIC;
    cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    cbd.MiscFlags = 0u;
    cbd.ByteWidth = sizeof(modelTransform);
    cbd.StructureByteStride = 0u;
    D3D11_SUBRESOURCE_DATA csd = {};
    csd.pSysMem = &modelTransform;
    deviceContext.getD3D11Device()->CreateBuffer(&cbd, &csd, &pConstantBuffer);

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

        modelTransform  *= DirectX::XMMatrixRotationY(0.01);
        D3D11_MAPPED_SUBRESOURCE data;
        deviceContext.getD3D11DeviceContext()->Map(pConstantBuffer.Get(), 0u, D3D11_MAP_WRITE_DISCARD, 0u, &data);

        auto newTra = modelTransform * DirectX::XMMatrixTranslation(0.f, 0.f, 0.5f);
        memcpy(data.pData, &newTra, sizeof(modelTransform));
        deviceContext.getD3D11DeviceContext()->Unmap(pConstantBuffer.Get(), 0u);
		deviceContext.getD3D11DeviceContext()->VSSetConstantBuffers(0, 1, pConstantBuffer.GetAddressOf());


        ID3D11Buffer* vertexBufferData{ vertexBuffer.getVertexBuffer() };
        deviceContext.getD3D11DeviceContext()->IASetVertexBuffers(0, 1, &vertexBufferData, &vertexBuffer.stride, &vertexBuffer.offset);


        deviceContext.getD3D11DeviceContext()->IASetIndexBuffer(indexBuffer.get(), indexBuffer.m_dxgiFormat, 0u);
        deviceContext.getD3D11DeviceContext()->DrawIndexed(indexBuffer.getBufferSize(), 0, 0);

        swapChain.present();
    }

    return 0;
}