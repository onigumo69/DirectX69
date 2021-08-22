#include "Bindable/TransformCBuffer.h"

TransformCBuffer::TransformCBuffer(Graphics& gfx, const Drawable& parent)
	:
	parent{ parent }
{
	if (!pVCBuffer)
	{
		pVCBuffer = std::make_unique<VertexConstantBuffer<DirectX::XMMATRIX>>(gfx);
	}
}

void TransformCBuffer::Bind(Graphics& gfx) noexcept
{
	pVCBuffer->Update(
		gfx,
		DirectX::XMMatrixTranspose(parent.GetTransformXM() * gfx.GetProjection()
	));

	pVCBuffer->Bind(gfx);
}

std::unique_ptr<VertexConstantBuffer<DirectX::XMMATRIX>> TransformCBuffer::pVCBuffer;