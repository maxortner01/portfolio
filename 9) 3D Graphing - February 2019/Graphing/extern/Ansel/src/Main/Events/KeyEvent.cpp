#include "../../../include/Ansel/Main/Events/KeyEvent.h"

#include <iostream>
#include <GLFW/glfw3.h>

namespace age
{
	std::vector<KeyState>* states = nullptr;

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (!states) return;

		if (action == GLFW_PRESS)
			states->at(key) = { true, true };
		else if (action == GLFW_RELEASE)
			states->at(key) = { false, false };

		//std::cout << key << std::endl;
	}

	KeyEvent::KeyEvent(void* window) :
		_Event(window)
	{
		setCallbacks();
		keyStates.resize(Key::TOTAL);
	}

	void KeyEvent::updateKeyStates()
	{
		states = &keyStates;

		for (int i = 0; i < keyStates.size(); i++)
		{
			keyStates.at(i).pressed = false;
		}
	}

	bool KeyEvent::isKeyDown(Key key)
	{
		return keyStates.at(key).down;
	}

	bool KeyEvent::isKeyPressed(Key key)
	{
		return keyStates.at(key).pressed;
	}

	void KeyEvent::setCallbacks()
	{
		glfwSetKeyCallback((GLFWwindow*)window_ptr, keyCallback);
	}
}