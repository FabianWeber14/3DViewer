#include "VertexShader.h"
#include "VertexShader.hlsl_h"

#include <assert.h>

VertexShader::VertexShader(ID3D11Device1* d3d11Device, std::span<D3D11_INPUT_ELEMENT_DESC> inputElementDesc)
{
    HRESULT hResult = d3d11Device->CreateVertexShader(g_vertexShader, sizeof(g_vertexShader), nullptr, m_pVertexShader.ReleaseAndGetAddressOf());

    hResult = d3d11Device->CreateInputLayout(inputElementDesc.data(), static_cast<UINT>(inputElementDesc.size()), g_vertexShader, sizeof(g_vertexShader), inputLayout.ReleaseAndGetAddressOf());
}
