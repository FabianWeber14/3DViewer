#pragma once
#include <d3d11_1.h>
#include <wrl/client.h>

class D3DDeviceContext
{
public:
	D3DDeviceContext();

	ID3D11Device1* getD3D11Device() { return d3d11Device.Get(); }
	ID3D11DeviceContext1* getD3D11DeviceContext() { return d3d11DeviceContext.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11Device1> d3d11Device;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext1> d3d11DeviceContext;
};

