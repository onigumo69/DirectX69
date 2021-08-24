#include "PointLight.h"
#include "ImGui/imgui.h"

PointLight::PointLight(Graphics& gfx, float radius)
	:
	mesh(gfx, radius),
	pixelBuffer(gfx)
{
	Reset();
}

void PointLight::SpawnControlWindow() noexcept
{
	if (ImGui::Begin("Light"))
	{
		ImGui::Text("Position");
		ImGui::SliderFloat("X", &lightBuffer.pos.x, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Y", &lightBuffer.pos.y, -60.0f, 60.0f, "%.1f");
		ImGui::SliderFloat("Z", &lightBuffer.pos.z, -60.0f, 60.0f, "%.1f");
		ImGui::Text("Intensity/Color");
		ImGui::SliderFloat("Intensity", &lightBuffer.diffuseIntensity, 0.01f, 2.0f, "%.2f", 2);
		ImGui::ColorEdit3("Diffuse Color", &lightBuffer.diffuseColor.x);
		ImGui::ColorEdit3("Ambient", &lightBuffer.ambient.x);

		ImGui::Text("Falloff");
		ImGui::SliderFloat("Constant", &lightBuffer.attConst, 0.05f, 10.0f, "%.2f", 4);
		ImGui::SliderFloat("Linear", &lightBuffer.attLin, 0.0001f, 4.0f, "%.4f", 8);
		ImGui::SliderFloat("Quadratic", &lightBuffer.attQuad, 0.0000001f, 10.0f, "%.7f", 10);
		if (ImGui::Button("Reset"))
		{
			Reset();
		}
	}
	ImGui::End();
}

void PointLight::Reset() noexcept
{
	lightBuffer =
	{
		{ 0.0f,0.0f,0.0f },
		{ 0.05f,0.05f,0.05f },
		{ 1.0f,1.0f,1.0f },
		1.0f,
		1.0f,
		0.045f,
		0.0075f,
	};
}

void PointLight::Draw(Graphics& gfx) const noxnd
{
	mesh.SetPos(lightBuffer.pos);
	mesh.Draw(gfx);
}

void PointLight::Bind(Graphics& gfx, DirectX::FXMMATRIX view) const noexcept
{
	auto light = lightBuffer;
	const auto pos = DirectX::XMLoadFloat3(&lightBuffer.pos);
	DirectX::XMStoreFloat3(&light.pos, DirectX::XMVector3Transform(pos, view));
	pixelBuffer.Update(gfx, light);
	pixelBuffer.Bind(gfx);
}