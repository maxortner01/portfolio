#ifndef MOUSE_H_
#define MOUSE_H_

#include "engine/window.h"
#include "engine/util/CML.h"

#include <glm.hpp>
#include <GLFW/glfw3.h>

using namespace glm;

namespace Controllers {
    
    /**
     * @brief Basic handling of mouse position
     * 
     */
    struct Mouse
    {
        /**
         * @brief Set the Mouse's position
         * 
         * @param x Desired x position in the window.
         * @param y Desired y position in the window.
         */
        static void    setMousePos(int x, int y);
        /**
         * @brief Get Mouse's position
         * 
         * @return vec2 Mouse position
         */
        static vec2 getMousePos();

        ///Hide mouse
        static void    hide();
        ///Show mouse
        static void    show();
    };
    
}

#endif /* MOUSE_H_ */