#pragma once

#include "Perceus/Data/Status.h"
#include "Perceus/Data/ObjectID.h"

#include "Rendering/Events.h"
#include "Rendering/RenderSurface.h"

#include "Perceus/Data/Inc.h"

namespace pcs
{
    class Camera;

    /**
     * An enum that represents the status of a window object.
     */
    enum class WindowStatus
    {
        Ok,
        APIInitFailure,
        CreationFailure,
        None
    };

    /**
     * @brief Class that handles window functionality.
     * Uses the specified RenderAPI to construct a window as well
     * as manipulate the size and location.
     */
    class Window : 
        public rend::RenderSurface<unsigned int>, public Data::Status<WindowStatus>, public Data::ObjectUID
    {
        friend class Engine;

        static List<Window*> windows;

        /// List of independent-typed pointers which each point to a camera
        /// associated with this engine.
        List<Camera*> camera_directory;

        /**
         * @brief Constructs a new Window object.
         * This constructor is only to be accessed through the Create
         * method.
         * 
         * @param width Width (in px) of the window
         * @param height Height (in px) of the window
         */
        Window(const unsigned int, const unsigned int);

    public:

        /**
         * @brief Destroys the Window instance and renderapi object.
         */
        virtual ~Window();

        /**
         * @brief Creates a new window object.
         * 
         * @param width Width (in px) of the window
         * @param height Height (in px) of the window
         * @return Window* Pointer to the window instance
         */
        static PERC_API Window* Create(const unsigned int width, const unsigned int height);

        static PERC_API Window* get(void* const ptr);

        static PERC_API Window* get(const int index);

        /**
         * @brief Method to check whether the window is open.
         * 
         * @return true The window is open
         * @return false The window is not open
         */
        bool PERC_API isOpen();

        /**
         * @brief Swaps the buffer attached to the window.
         * 
         * @return true Render was successful
         * @return false Render was unsuccessful
         */
        bool PERC_API render();

        void PERC_API bind()   /***/ override;
        void PERC_API unbind() const override;

        /**
         * @brief 
         * 
         * @return true Polling was successful
         * @return false Polling was unsuccessful
         */
        bool PERC_API pollEvents();

        bool PERC_API resize(unsigned int width, unsigned int height);
        
        /**
         * @brief Push a camera to the directory
         * 
         * @param camera Camera instance to register
         */
        void PERC_API pushCamera(Camera* camera);
    };
}