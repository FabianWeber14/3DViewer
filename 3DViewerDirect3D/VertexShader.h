#pragma once
#include <d3d11_1.h>
#include <wrl/client.h>
#include <span>

class VertexShader
{
public:
	VertexShader(ID3D11Device1* d3d11Device, std::span<D3D11_INPUT_ELEMENT_DESC> inputElementDesc);

	ID3D11InputLayout* getInputLayout() { return inputLayout.Get(); }
	ID3D11VertexShader* getVertexShader() { return m_pVertexShader.Get(); }

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
};

