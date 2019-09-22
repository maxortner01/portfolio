#include "mouse.h"

vec2 Mouse::getMousePos() {
    double xpos, ypos;
    glfwGetCursorPos(Window::getWindow(), &xpos, &ypos);

    return vec2(xpos, ypos);
}

void Mouse::setMousePos(int x, int y) {
    glfwSetCursorPos(Window::getWindow(), x, y);
}

void Mouse::hide() {
    glfwSetInputMode(Window::getWindow(), GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Mouse::show() {
    glfwSetInputMode(Window::getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}