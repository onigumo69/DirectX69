#pragma once
#include "ImGuiManager.h"
#include "Window.h"
#include "Timer.h"
#include "Camera.h"
#include "PointLight.h"
#include "Mesh.h"
#include <set>

class App
{
public:
	App();
	~App();
	
	int Go();

private:
	void DoFrame();
	void ShowImGuiDemoWindow();

private:
	bool showDemoWindow = false;
	ImGuiManager imgui;
	Window wnd;
	Timer timer;
	Camera camera;
	PointLight light;
	float speedFactor = 1.0f;
	Model nano{ wnd.GetGraphics(), "Models\\nano_hierarchy.gltf" };
};