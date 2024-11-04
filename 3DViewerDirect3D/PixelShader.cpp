#include "PixelShader.h"
#include "PixelShader.hlsl_h"

PixelShader::PixelShader(ID3D11Device1* d3d11Device)
{
	HRESULT hResult = d3d11Device->CreatePixelShader(g_pixelShader, sizeof(g_pixelShader), nullptr, m_pPixelShader.ReleaseAndGetAddressOf());
}
