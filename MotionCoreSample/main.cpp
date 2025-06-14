
#include <chrono>

#include "window.hpp"
#include "core/motion_core_engine.hpp"
#include "primitive/ray_cast.hpp"

#include <gl/GL.h>

#include "renderer.h"
#include "data_structure/aabb_tree.hpp"


MotionCore::MotionCoreEngine m;




int main()
{
	MotionCore::MotionCoreEngine mEngine;

	mEngine.Init()
	
	Window w;
	Renderer renderer;

	Camera camera;

	float deltatime = 0.0f;
	float lastframe = 0.0f;
	
	while (!w.ShouldClose())
	{

		auto time = std::chrono::system_clock::now();
		std::chrono::duration<float> timeInSeconds = time.time_since_epoch();
		float currentFrame = timeInSeconds.count();

		deltatime = currentFrame - lastframe;
		lastframe = currentFrame;
		w.PoolEvents();

		
		glViewport(0, 0 ,w.GetWidth(), w.GetHeight());
		camera.Update();
		renderer.Draw(camera);
		
		glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		w.SwapBuffer();
	}

	return 0;
}
