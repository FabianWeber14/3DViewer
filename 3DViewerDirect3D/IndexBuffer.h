#pragma once
#include <dxgiformat.h>
#include <span>
#include <wrl/client.h>
#include <d3d11_1.h>

class IndexBuffer
{
public:
	IndexBuffer(ID3D11Device1* d3d11Device, std::span<unsigned int> indices);
	DXGI_FORMAT m_dxgiFormat;
	UINT m_strides;

	ID3D11Buffer* get() const { return m_pIndexBuffer.Get(); }
	unsigned int getBufferSize() const
	{
		return m_size;
	}
private:
	unsigned int m_size;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pIndexBuffer{ nullptr };
};

