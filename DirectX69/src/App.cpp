#include "App.h"
#include "Drawable/AssTest.h"
#include "Surface.h"
#include "GDIPlusManager.h"
#include "CleanMath.h"
#include "ImGui/imgui.h"
#include <memory>
#include <iomanip>
#include <algorithm>

namespace dx = DirectX;

GDIPlusManager gdipm;

App::App()
	:
	wnd{ 800, 600, "DirectX 69" },
	light{ wnd.GetGraphics() }
{
	wnd.GetGraphics().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
}

App::~App()
{

}

int App::Go()
{
	while (true)
	{
		// process all messages pending, but to not block for new messages
		if (const auto ecode = Window::ProcessMessages())
		{
			// if return optional has value, means we're quitting so return exit code
			return *ecode;
		}
		DoFrame();
	}
}

void App::DoFrame()
{
	const auto dt = timer.Mark() * speedFactor;
	wnd.GetGraphics().BeginFrame(0.07f, 0.0f, 0.12f);
	wnd.GetGraphics().SetCamera(camera.GetMatrix());
	light.Bind(wnd.GetGraphics(), camera.GetMatrix());

	const auto transform =
		dx::XMMatrixRotationRollPitchYaw(pos.roll, pos.pitch, pos.yaw) *
		dx::XMMatrixTranslation(pos.x, pos.y, pos.z);

	nano.Draw(wnd.GetGraphics(), transform);
	light.Draw(wnd.GetGraphics());

	// imgui windows
	camera.SpawnControlWindow();
	light.SpawnControlWindow();
	ShowModelWindow();

	// present
	wnd.GetGraphics().EndFrame();
}

void App::ShowModelWindow()
{
	if (ImGui::Begin("Model"))
	{
		using namespace std::string_literals;

		ImGui::Text("Orientation");
		ImGui::SliderAngle("Roll", &pos.roll, -180.0f, 180.0f);
		ImGui::SliderAngle("Pitch", &pos.pitch, -180.0f, 180.0f);
		ImGui::SliderAngle("Yaw", &pos.yaw, -180.0f, 180.0f);

		ImGui::Text("Position");
		ImGui::SliderFloat("X", &pos.x, -20.0f, 20.0f);
		ImGui::SliderFloat("Y", &pos.y, -20.0f, 20.0f);
		ImGui::SliderFloat("Z", &pos.z, -20.0f, 20.0f);
	}
	ImGui::End();
}