#pragma once
#include <d3d11_1.h>
#include <wrl/client.h>
#include <array>

class SwapChain
{
public:
	SwapChain(HWND hwnd, ID3D11Device1* d3d11Device, ID3D11DeviceContext1* d3d11DeviceContext);

	void clearRenderTarget(ID3D11DeviceContext1* d3d11DeviceContext, float clearColor[4]);
	void present();
	void resize(ID3D11Device1* d3d11Device, ID3D11DeviceContext1* d3d11DeviceContext);

	ID3D11RenderTargetView* getFrameBuffer() { return m_pFrameBuffer.Get(); }
private:
	Microsoft::WRL::ComPtr<IDXGISwapChain1> m_pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pFrameBuffer;
};

