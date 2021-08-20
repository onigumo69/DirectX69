#include "App.h"
#include <iomanip>

App::App()
	:
	wnd(800, 600, "DirectX 69")
{}

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
	const float a = sin(timer.Peek()) / 2.0f + 0.5f;
	const float b = cos(timer.Peek()) / 2.0f + 0.5f;
	const float c = tan(timer.Peek()) / 2.0f + 0.5f;
	wnd.GetGraphics().ClearBuffer(a, b, c);
	wnd.GetGraphics().DrawTestTriangle(
		-timer.Peek(),
		0.0f,
		0.0f
	);
	wnd.GetGraphics().EndFrame();
}