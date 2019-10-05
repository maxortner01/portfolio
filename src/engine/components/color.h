#ifndef COLOR_H_
#define COLOR_H_

#include <glm.hpp>
#include "component.h"

using namespace glm;
using namespace Components;

namespace Components {    

    /**
     * @brief Simple handler for storing color information
     */
    class Color : public Component
    {
    private:
        ///Alpha value of the color
        float   alpha;
        ///Color value
        vec3    color;

    public:
        /**
         * @brief Construct a new Color object
         * 
         * @param r Red value (0 - 1)
         * @param g Green value (0 - 1)
         * @param b Blue value (0 - 1)
         */
        Color(float r, float g, float b);
        /**
         * @brief Construct a new Color object
         * 
         * @param r Red value (0 - 1)
         * @param g Green value (0 - 1)
         * @param b Blue value (0 - 1)
         * @param a Alpha value (0 - 1)
         */
        Color(float r, float g, float b, float a);

        /**
         * @brief Set the alpha
         * 
         * @param a Alpha value
         */
        inline void  setAlpha(float a) { alpha = a;    }
        /**
         * @brief Get the alpha
         * 
         * @return float Value to set alpha to
         */
        inline float getAlpha(void)    { return alpha; }

        /**
         * @brief Set the color
         * 
         * @param c Color value0
         */
        inline void  setColor(vec3 c)                     { color = c; }
        /**
         * @brief Set the color
         * 
         * @param r Red value (0 - 1)
         * @param g Green value (0 - 1)
         * @param b Blue value (0 - 1)
         */
        inline void  setColor(float r, float g, float b)  { color = vec3(r, g, b); }
        /**
         * @brief Get the color
         * 
         * @return vec3 Color
         */
        inline vec3  getColor(void)                       { return color; }

        /**
         * @brief Definition of Model class's abstract update function
         * Definition of Model class's abstract update function. Unused in this implementation.
         */
        void update();
    };

}

#endif /* COLOR_H_ */