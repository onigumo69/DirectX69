#include "Bindable/TransformCBuffer.h"

namespace Bind
{
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
	const auto modelView = parent.GetTransformXM() * gfx.GetCamera();
	const Transform tf =
	{
		DirectX::XMMatrixTranspose(modelView),
		DirectX::XMMatrixTranspose(
			modelView *
			gfx.GetProjection()
		)
	};
	pVCBuffer->Update(gfx, tf);
	pVCBuffer->Bind(gfx);
}

std::unique_ptr<VertexConstantBuffer<TransformCBuffer::Transform>> TransformCBuffer::pVCBuffer;

}