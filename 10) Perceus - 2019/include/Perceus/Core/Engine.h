#pragma once

#include "Perceus/Data/Singleton.h"
#include "Perceus/Data/Status.h"
#include "Perceus/Core/Scene.h"
#include "Perceus/Core/Graphics/Rendering/Renderer.h"

namespace pcs
{
    /**
     * @brief Enum that describes the state of a rendered frame.
     */
    enum class RenderStatus
    {
        Good,
        Failed
    };

    /**
     * @brief Enum for choosing a renderer
     */
    enum class CurrentRenderer
    {
        ForwardRenderer
    };

    /**
     * @brief Handles rendering and holds the window instance.
     */
    class PERC_API Engine : 
        public rend::RenderObject, public Data::Status<RenderStatus>
    {
        Renderer* renderer() const;

        /// Window on which to render to
        Window* window;

        unsigned int fpsLimit;
        
    public:
        /**
         * @brief Constructs a new Engine object.
         */
        Engine();
        /**
         * @brief Destroys the Engine object.
         */
        ~Engine();

        void setFrameLimit(const unsigned int f) { fpsLimit = f; }

        /**
         * @brief Renders a given scene to the window.
         * 
         * @param scene Pointer to a scene to render
         * @return RenderStatus Status of the render
         */
        RenderStatus renderScene(Scene* scene) const;

        /**
         * @brief Get the Window instance associated with this engine
         * 
         * @return Window* Pointer to a window instance
         */
        Window* getWindow() { return window; }

        static CurrentRenderer &currentRenderer() { static CurrentRenderer r = CurrentRenderer::ForwardRenderer; return r; }
    };
}