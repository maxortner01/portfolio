#pragma once

#include "Engine.h"

#include "Perceus/Data/Status.h"
#include "Perceus/Data/Inc.h"

namespace pcs
{
    
    // Exit Code
    enum class ExitCode
    {
        EndOfProgram,
        NoScenes
    };

    /**
     * @brief Handles and runs the entire engine process.
     * This is where the main loop is, this holds the engine.
     * 
     */
    class PERC_API Application : public Data::Status<ExitCode>
    {
        friend class Scene;

        // Engine instance
        Engine* engine;

        // Stack of scenes to render, only renders the
        // first item in this list
        std::stack<Scene*> scenes;

    protected:
        void pushScene(Scene* s);

    public:
        Application();

        // Handle engine and scene deletion
        virtual ~Application();

        // Initialize the engine and run the application
        int run();

        Window &getCurrentWindow() { return *engine->getWindow(); }
    };

    // To be defined by the client
    Application* CreateApplication();
}