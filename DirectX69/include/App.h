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
	void ShowModelWindow();

private:
	ImGuiManager imgui;
	Window wnd;
	Timer timer;
	Camera camera;
	PointLight light;
	float speedFactor = 1.0f;
	Model nano{ wnd.GetGraphics(),"models\\nanosuit.obj" };
	struct
	{
		float roll = 0.0f;
		float pitch = 0.0f;
		float yaw = 0.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
	} pos;
};