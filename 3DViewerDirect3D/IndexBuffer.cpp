#include "IndexBuffer.h"

#include <d3d11_1.h>

IndexBuffer::IndexBuffer(ID3D11Device1* d3d11Device, std::span<unsigned int> indices):m_size(static_cast<unsigned int>(indices.size()))
{
	D3D11_BUFFER_DESC ibd = {};
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.CPUAccessFlags = 0u;
	ibd.MiscFlags = 0u;

	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices.data();

	ibd.StructureByteStride = 4;
	ibd.ByteWidth = 4 * m_size;

	m_dxgiFormat = DXGI_FORMAT_R32_UINT;
	m_strides = ibd.StructureByteStride;
	d3d11Device->CreateBuffer(&ibd, &isd, m_pIndexBuffer.ReleaseAndGetAddressOf());
}
