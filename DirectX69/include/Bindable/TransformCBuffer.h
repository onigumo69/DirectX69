#pragma once
#include "Bindable/ConstantBuffer.h"
#include "Drawable/Drawable.h"
#include <DirectXMath.h>

class TransformCBuffer : public Bindable
{
public:
	TransformCBuffer(Graphics& gfx, const Drawable& parent);

	void Bind(Graphics& gfx) noexcept override;

private:
	VertexConstantBuffer<DirectX::XMMATRIX> vcBuffer;
	const Drawable& parent;
};