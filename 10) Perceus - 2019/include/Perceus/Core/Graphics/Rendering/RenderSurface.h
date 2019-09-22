#pragma once

#include "RenderObject.h"
#include "Perceus/Data/Sizable.h"

namespace pcs
{
namespace rend
{
    /**
     * @brief Class that handles basic rendering functionality.
     * 
     * @tparam T Type which Sizable is to be
     */
    template<typename T>
    class RenderSurface :
        public RenderObject, public Sizable<T>
    {

    protected:
        /// Type-independant pointer to an object needed by the render api
        void* apiPTR = nullptr;

    public: 
        /**
         * @brief Constructs a new Render Surface object.
         * 
         * @param width  Width of the surface (in px)
         * @param height Height of the surface (in px)
         */
        RenderSurface(const T width, const T height) :
            Sizable<T>({ width, height })
        {
            
        }

        /**
         * @brief Clears the current context.
         * 
         * @param color color which to clear the buffer to
         */
        void clear(Color color = Color(0, 0, 0)) const
        {
            rendAPI()->clear(color);
        }

        /// Binds the current surface.
        virtual void bind()   /***/ = 0;
        /// Unbinds the current surface
        virtual void unbind() const = 0;

        /// Returns the api pointer
        void** getAPILoc() { return &apiPTR; }       
    };
}
}