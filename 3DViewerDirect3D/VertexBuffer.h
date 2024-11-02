#pragma once
#include <d3d11_1.h>
#include <wrl/client.h>
#include <span>


class VertexBuffer
{
public:
	template<typename VertexType>
	VertexBuffer(ID3D11Device1* d3d11Device, std::span<VertexType> vertexData);

	ID3D11Buffer* getVertexBuffer() { return m_pVertexBuffer.Get(); }

    UINT stride{};
    UINT offset{};
    UINT numVerts{};
private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_pVertexBuffer;
};


template<typename VertexType>
inline VertexBuffer::VertexBuffer(ID3D11Device1* d3d11Device, std::span<VertexType> vertexData)
{
    stride =  sizeof(VertexType);
    numVerts = static_cast<UINT>(vertexData.size());
    offset = 0;

    D3D11_BUFFER_DESC vertexBufferDesc = {};
    vertexBufferDesc.ByteWidth = static_cast<UINT>(vertexData.size_bytes());
    vertexBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA vertexSubresourceData = { vertexData.data() };

    d3d11Device->CreateBuffer(&vertexBufferDesc, &vertexSubresourceData, &m_pVertexBuffer);
}
