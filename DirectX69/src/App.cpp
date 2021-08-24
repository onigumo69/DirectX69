#include "App.h"
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
	wnd{ 1280, 720, "DirectX 69" },
	light{ wnd.GetGraphics() }
{
	wnd.GetGraphics().SetProjection(dx::XMMatrixPerspectiveLH(1.0f, 9.0f / 16.0f, 0.5f, 40.0f));
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

	nano.Draw(wnd.GetGraphics());
	light.Draw(wnd.GetGraphics());

	// imgui windows
	camera.SpawnControlWindow();
	light.SpawnControlWindow();
	ShowImGuiDemoWindow();
	nano.ShowWindow();

	// present
	wnd.GetGraphics().EndFrame();
}

void App::ShowImGuiDemoWindow()
{
	static bool show_demo_window = true;
	if (show_demo_window)
	{
		ImGui::ShowDemoWindow(&show_demo_window);
	}
}