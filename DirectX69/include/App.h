#pragma once
#include "ImGuiManager.h"
#include "Window.h"
#include "Timer.h"
#include "Camera.h"
#include "PointLight.h"

class App
{
public:
	App();
	~App();
	
	int Go();

private:
	void DoFrame();

private:
	ImGuiManager imgui;
	Window wnd;
	Timer timer;
	Camera camera;
	PointLight light;
	float speedFactor = 1.0f;
	std::vector<std::unique_ptr<class Drawable>> drawables;
	static constexpr size_t nDrawables = 180;
};