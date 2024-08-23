#pragma once


#include <iostream>
#include <Core/PhysicsEngine.h>
#include <raylib.h>
#include <vector>

#include <toolbox_typedef.hpp>

#include "rlImGui.h"

class App
{
public:
	int screenWidth = 800;
	int screenHeight = 450;

	int halfScreenWidth = screenWidth / 2;
	int halfScreenHeight = screenHeight / 2;

	float impulseRadius = 20.f;

	Camera3D cam;

	float cameraSpeed = 5.f;

	float pitch = 0.f;

	float yaw = 0.f;

	App();

	~App();

	void Run();

	void MousePush();

	void DrawParticules();

	void HandleResize();

	bool ShowImpulseRadius = false;

	void MoveCam(Camera3D* cam);
};

