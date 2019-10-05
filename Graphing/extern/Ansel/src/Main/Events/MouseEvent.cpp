#include "../../../include/Ansel/Main/Events/MouseEvent.h"

#include <GLFW/glfw3.h>

namespace age
{
	Vec2f* cursor = nullptr;

	void cursor_position(GLFWwindow* window, double xpos, double ypos)
	{
		if (!cursor) return;

		cursor->x = xpos;
		cursor->y = ypos;
	}

	MouseEvent::MouseEvent(void* window) :
		_Event(window)
	{
		setCallbacks();
	}

	void MouseEvent::setCallbacks() 
	{
		glfwSetCursorPosCallback((GLFWwindow*)window_ptr, cursor_position);
	}

	void MouseEvent::updateMouseState()
	{
		last_position = pos;
		cursor = &pos;
	}

	Vec2f MouseEvent::getDelta()
	{
		return pos - last_position;
	}

	void MouseEvent::setPosition(Vec2f position)
	{
		glfwSetCursorPos((GLFWwindow*)window_ptr, position.x, position.y);
	}
}