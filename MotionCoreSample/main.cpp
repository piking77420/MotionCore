
#include <chrono>

#include "renderer.h"
#include "window.hpp"
#include "core/motion_core_engine.hpp"
#include "primitive/ray_cast.hpp"



MotionCore::MotionCoreEngine m;


int main()
{
	MotionCore::MotionCoreEngine mEngine;
	Window w;
	w.EnableCursor(false);
	Renderer renderer;

	Camera camera;
	camera.SetAspectRatio(w.GetWidth() / w.GetHeight());

	float deltaTime = 0.0f;
	float lastFrame = 0.0f;

	while (!w.ShouldClose())
	{
		auto time = std::chrono::high_resolution_clock::now();
		float currentFrame = std::chrono::duration<float>(time.time_since_epoch()).count();

		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		w.PoolEvents();
		camera.Update(deltaTime);

		glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glViewport(0, 0 ,w.GetWidth(), w.GetHeight());
		renderer.Draw(camera);
		w.SwapBuffer();
	}

	return 0;
}
