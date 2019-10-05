#include "keyboard.h"

bool Keyboard::getKey(unsigned int key)  {
    return glfwGetKey(Window::getWindow(), key);
}