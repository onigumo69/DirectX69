#pragma once
#include "Graphics.h"
#include "Drawable/SolidSphere.h"
#include "Bindable/ConstantBuffer.h"

class PointLight
{
public:
	PointLight(Graphics& gfx, float radius = 0.5f);
	void SpawnControlWindow() noexcept;
	void Reset() noexcept;
	void Draw(Graphics& gfx) const noexcept(!IS_DEBUG);
	void Bind(Graphics& gfx) const noexcept;
private:
	struct PointLightCBuffer
	{
		alignas(16) DirectX::XMFLOAT3 pos;
		alignas(16) DirectX::XMFLOAT3 ambient;
		alignas(16) DirectX::XMFLOAT3 diffuseColor;
		float diffuseIntensity;
		float attConst;
		float attLin;
		float attQuad;
	};
private:
	PointLightCBuffer lightBuffer;
	mutable SolidSphere mesh;
	mutable PixelConstantBuffer<PointLightCBuffer> pixelBuffer;
};