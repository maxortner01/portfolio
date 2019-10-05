#include "Ansel/Graphics/Context.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace age
{
	Context* Context::current = nullptr;

	Context::Context(ContextSettings settings) :
		_settings(settings)
	{
		if (!glfwInit())
			return;
		
		context = (void*)glfwCreateWindow(settings.width, settings.height, "", NULL, NULL);
		makeCurrent();

		const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		int init = glewInit();
		if (init)
			return;

	}

	Context &Context::getCurrentContext()
	{
		return *current;
	}

	Context::~Context()
	{
		destroy();
	}

	void Context::destroy()
	{
		if (!destroyed) {
			glfwDestroyWindow((GLFWwindow*)context);
			destroyed = true;
		}
	}

	void Context::makeSettings()
	{
		if (!_settings.normalized)
		{
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glOrtho(0.f, _settings.width, _settings.height, 0.f, 0, 1.f);
		}
	}

	void Context::makeCurrent()
	{
		glfwMakeContextCurrent((GLFWwindow*)context);
		makeSettings();
		current = this;
	}

	void Context::close()
	{
		glfwSetWindowShouldClose((GLFWwindow*)context, true);
	}
}