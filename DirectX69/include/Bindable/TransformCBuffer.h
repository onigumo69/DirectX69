#pragma once
#include "Bindable/ConstantBuffer.h"
#include "Drawable/Drawable.h"
#include <DirectXMath.h>

class TransformCBuffer : public Bindable
{
private:
	struct Transform
	{
		DirectX::XMMATRIX modelViewProj;
		DirectX::XMMATRIX model;
	};

public:
	TransformCBuffer(Graphics& gfx, const Drawable& parent, UINT slot = 0u);

	void Bind(Graphics& gfx) noexcept override;

private:
	static std::unique_ptr<VertexConstantBuffer<Transform>> pVCBuffer;
	const Drawable& parent;
};