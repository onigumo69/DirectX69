#include "Bindable/VertexBuffer.h"
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
	nano2.Draw(wnd.GetGraphics());
	light.Draw(wnd.GetGraphics());

	while (const auto e = wnd.kbd.ReadKey())
	{
		if (!e->IsPress())
		{
			continue;
		}

		switch (e->GetCode())
		{
		case VK_ESCAPE:
			if (wnd.CursorEnabled())
			{
				wnd.DisableCursor();
				wnd.mouse.EnableRaw();
			}
			else
			{
				wnd.EnableCursor();
				wnd.mouse.DisableRaw();
			}
			break;
		case VK_F1:
			showDemoWindow = true;
			break;
		}
	}
	if (!wnd.CursorEnabled())
	{
		if (wnd.kbd.KeyIsPressed('W'))
		{
			camera.Translate({ 0.0f, 0.0f, dt });
		}
		if (wnd.kbd.KeyIsPressed('A'))
		{
			camera.Translate({ -dt, 0.0f, 0.0f });
		}
		if (wnd.kbd.KeyIsPressed('S'))
		{
			camera.Translate({ 0.0f, 0.0f, -dt });
		}
		if (wnd.kbd.KeyIsPressed('D'))
		{
			camera.Translate({ dt, 0.0f, 0.0f });
		}
		if (wnd.kbd.KeyIsPressed('R'))
		{
			camera.Translate({ 0.0f, dt, 0.0f });
		}
		if (wnd.kbd.KeyIsPressed('F'))
		{
			camera.Translate({ 0.0f, -dt, 0.0f });
		}
	}

	while (const auto delta = wnd.mouse.ReadRawDelta())
	{
		if (!wnd.CursorEnabled())
		{
			camera.Rotate((float)delta->x, (float)delta->y);
		}
	}

	// imgui windows
	camera.SpawnControlWindow();
	light.SpawnControlWindow();
	ShowImGuiDemoWindow();
	nano.ShowWindow("Model 1");
	nano2.ShowWindow("Model 2");

	// present
	wnd.GetGraphics().EndFrame();
}

void App::ShowImGuiDemoWindow()
{
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
}