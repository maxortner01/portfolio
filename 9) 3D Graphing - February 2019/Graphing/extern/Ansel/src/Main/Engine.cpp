#include "../../include/Ansel/Main/Engine.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace age
{
	std::vector<Window*> Engine::windows;

	Engine::Engine(Window* _window, Scene* scene)
	{
		current_scene = scene;

		windows.push_back(_window);
		window = _window;
	}

	void Engine::run()
	{
		current_scene->dimensions = {
			window->getDimensions().x,
			window->getDimensions().y
		};

		current_scene->create();

		while (!window->shouldClose())
		{
			window->getContext().makeCurrent();

			if (window->getContext().getSettings().normalized)
				glEnable(GL_DEPTH_TEST);

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			window->event_handler->update();
			glfwPollEvents();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			current_scene->render(*window->event_handler);

			glfwSwapBuffers((GLFWwindow*)window->getContext().getContext());
		}

		current_scene->destroy();
	}

	Window &Engine::getWindow(unsigned int index)
	{
		return *windows.at(index);
	}
}