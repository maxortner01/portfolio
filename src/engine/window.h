/**
 * \class Window
 * 
 * \breif Class that handles window initialization and OpenGL context.
 * 
 * Contains functions that reduce the usage of calling GLFW
 * directly. It also handles the initialization of OpenGL and GLFW
 * as well as window creation.
 * 
 **/

#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "controllers/screen.h"

using namespace Controllers;

class Window
{
private:
    ///Width and height of window
    static int  width, height;
    int         frame;

    ///Determines whether or not window is fullscreen
    bool        fullscreen;

    ///Title at top of the screen
    std::string title;

    ///GLFW window instance
    static GLFWwindow* window;

    ///Calls the unending amount of glfw initialization functions
    void init();

public:
    /**
     * \brief Creates window
     * \param w Width of window
     * \param h Height of window
     * \param t Title of window
     * 
     * Initialized variables and call init function.
     * 
     **/
    Window(int w, int h, std::string t);

    ///Destroys various pointers
    ~Window();

    ///Calls glfwPollEvents in order to allow event catching
    void update();

    /**
     * \brief Renders Screen instance
     * \param currentScreen Screen to be rendered
     * 
     * To be called from Engine. Renders Screen argument and flips buffer. 
     **/
    void render(Screen* currentScreen);

    ///
    inline bool shouldClose() { return glfwWindowShouldClose(window); }

    /* GET / SET */
    static int  getWidth()          { return width;  }
    static int  getHeight()         { return height; }
    static GLFWwindow* getWindow()  { return window; }
};

#endif /* WINDOW_H_ */