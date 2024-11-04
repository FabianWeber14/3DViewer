#pragma once
#include <d3d11_1.h>
#include <wrl/client.h>

class PixelShader
{
public:
	PixelShader(ID3D11Device1* d3d11Device);

	ID3D11PixelShader* getPixelShader() { return m_pPixelShader.Get(); }

private:

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pPixelShader;
};

