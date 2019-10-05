#include "Ansel/Main/Window.h"

#include <GLFW/glfw3.h>

namespace age
{
	Window::Window(ContextSettings settings) :
		context(settings)
	{
		context.makeCurrent();
		dimensions = { (unsigned int)settings.width, (unsigned int)settings.height };
		event_handler = new Event(context.getContext());
	}

	Window::~Window()
	{
		context.destroy();
	}

	void Window::pollEvents()
	{

	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose((GLFWwindow*)context.getContext());
	}

	void Window::close() const
	{
		glfwSetWindowShouldClose((GLFWwindow*)context.getContext(), 1);
	}
}