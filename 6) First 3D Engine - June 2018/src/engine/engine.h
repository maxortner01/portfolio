/**
 * \class Engine
 * 
 * \brief Controls high level flow of engine
 * 
 * The Engine struct handles the creation
 * and destruction of the game process. It is is meant to be 
 * inherited by the main process in the "main" folder. Before 
 * loop can be called a Screen object must be set. 
 * 
 **/

#ifndef ENGINE_H_
#define ENGINE_H_

#include <iostream>
#include <string>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "controllers/screen.h"
#include "window.h"

using namespace Controllers;

struct Engine
{
    ///Set back to zero every second
    int frame = 0;

    ///Current window context
    static Window* window;

    ///Current working screen
    static Screen* screen;

    /**
     * \brief Creates engine and window instances.
     * \param width window width
     * \param height window height
     * \param title window title
     **/
    Engine(int width, int height, std::string title);
    
    ///Handles major high level engine movements
    void loop();

    ///Handles glfw termination as well as destruction of instances
    void clear();

    /**
     * Set the current engine's screen context
     * \param currentScreen screen to be set
     **/
    inline void setScreen(Screen* currentScreen) { screen = currentScreen; }
};

#endif /* ENGINE_H_ */