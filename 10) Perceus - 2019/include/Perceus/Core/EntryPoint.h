#pragma once

#include <iostream>

#include "Perceus/Core/Application.h"
#include "Perceus/Util/Log.h"

extern pcs::Application* pcs::CreateApplication();

int main()
{
    pcs::Log::get().init();
    
    PS_CORE_DEBUG("Program initiation");
    // Create the application from client implementation
    pcs::Application* app = pcs::CreateApplication();

    PS_CORE_DEBUG("Application running");
    // Capture the exit code of run
    int exit_code = app->run();

    PS_CORE_DEBUG("Freeing application");
    // Delete the instance
    delete app;

    // Report the exit code to the logger
    PS_CORE_ERROR("Program exited with code {0}: {1}", 
        exit_code, app->getStatusFromEnum(exit_code));
}