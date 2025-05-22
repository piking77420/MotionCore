
#include "window.hpp"
#include "core/motion_core_engine.hpp"
#include "primitive/ray_cast.hpp"




MotionCore::MotionCoreEngine m;




int main()
{
	Window w;

	while (!w.ShouldClose())
	{
		w.PoolEvents();

		glViewport(0, 0 ,w.GetWidth(), w.GetHeight());

		glClearColor(0.2f, 0.4f, 0.6f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		w.SwapBuffer();
	}

	return 0;
}
