#include "Bindable/TransformCBuffer.h"

TransformCBuffer::TransformCBuffer(Graphics& gfx, const Drawable& parent, UINT slot)
	:
	parent{ parent }
{
	if (!pVCBuffer)
	{
		pVCBuffer = std::make_unique<VertexConstantBuffer<Transform>>(gfx, slot);
	}
}

void TransformCBuffer::Bind(Graphics& gfx) noexcept
{
	const auto model = parent.GetTransformXM();
	const Transform tf =
	{
		DirectX::XMMatrixTranspose(model),
		DirectX::XMMatrixTranspose(
			model *
			gfx.GetCamera() *
			gfx.GetProjection())
	};

	pVCBuffer->Update(gfx, tf);
	pVCBuffer->Bind(gfx);
}

std::unique_ptr<VertexConstantBuffer<TransformCBuffer::Transform>> TransformCBuffer::pVCBuffer;