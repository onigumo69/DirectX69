#include "App.h"
#include "Drawable/Box.h"
#include <memory>
#include <iomanip>

App::App()
	:
	wnd(800, 600, "DirectX 69")
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 2.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 1.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.08f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 180; i++)
	{
		boxes.push_back(std::make_unique<Box>(
			wnd.GetGraphics(), rng, adist,
			ddist, odist, rdist
			));
	}
	wnd.GetGraphics().SetProjection(DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 40.0f));
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
	auto dt = timer.Mark();
	wnd.GetGraphics().ClearBuffer(0.07f, 0.0f, 0.12f);
	for (auto& box : boxes)
	{
		box->Update(dt);
		box->Draw(wnd.GetGraphics());
	}
	wnd.GetGraphics().EndFrame();
}