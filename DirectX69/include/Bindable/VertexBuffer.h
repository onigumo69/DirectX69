#pragma once
#include "Bindable/Bindable.h"
#include "Macros/GraphicsThrowMacros.h"
#include "Vertex.h"

class VertexBuffer : public Bindable
{
public:
	template<class V>
	VertexBuffer(Graphics& gfx, const std::vector<V>& vertices)
		:
		stride(sizeof(V))
	{
		INFO_MANAGER(gfx);

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(sizeof(V) * vertices.size());
		bd.StructureByteStride = sizeof(V);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vertices.data();
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer));
	}
	VertexBuffer(Graphics& gfx, const meta::VertexBuffer& vbuf)
		:
		stride((UINT)vbuf.GetLayout().Size())
	{
		INFO_MANAGER(gfx);

		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.CPUAccessFlags = 0u;
		bd.MiscFlags = 0u;
		bd.ByteWidth = UINT(vbuf.SizeBytes());
		bd.StructureByteStride = stride;
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = vbuf.GetData();
		GFX_THROW_INFO(GetDevice(gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer));
	}
	void Bind(Graphics& gfx) noexcept override;
protected:
	UINT stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};
