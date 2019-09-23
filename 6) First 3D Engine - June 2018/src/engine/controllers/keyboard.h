#ifndef KEYBOARD_H_
#define KEYBOARD_H_

#include <vector>

#include "engine/window.h"
#include <GLFW/glfw3.h>

namespace Controllers {
    
    /**
     * @brief Basic handler to beautify keyboard event calls
     * 
     */
    struct Keyboard
    {
        static const unsigned int K_W = GLFW_KEY_W;
        static const unsigned int K_A = GLFW_KEY_A;
        static const unsigned int K_S = GLFW_KEY_S;
        static const unsigned int K_D = GLFW_KEY_D;

        static const unsigned int K_UP    = GLFW_KEY_UP;
        static const unsigned int K_DOWN  = GLFW_KEY_DOWN;
        static const unsigned int K_RIGHT = GLFW_KEY_RIGHT;
        static const unsigned int K_LEFT  = GLFW_KEY_LEFT;

        static const unsigned int K_SPACE = GLFW_KEY_SPACE;
        static const unsigned int K_LCTRL = GLFW_KEY_LEFT_CONTROL;
        static const unsigned int K_LSHIFT = GLFW_KEY_LEFT_SHIFT;
        
        static const unsigned int TAB = GLFW_KEY_TAB;

        static const unsigned int K_ESCAPE = GLFW_KEY_ESCAPE;

        /**
         * @brief Get the keydown status
         * 
         * @param key Keyboard const value
         * @return true key is down
         * @return false key is not down
         */
        static bool getKey(unsigned int key);
    };

}

#endif /* KEYBOARD_H_ */