#include "engine.h"

Window* Engine::window = NULL;
Screen* Engine::screen = NULL;

Engine::Engine(int width, int height, std::string title) {
    window = new Window(width, height, title);
}

void Engine::loop() {
    bool running = true;
    int second = 0;

    while ( running ) {
        window->update();

        if ( window->shouldClose() ) {
            running = false;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        window->render(screen);

        if (floor(glfwGetTime()) != second) {
            std::cout << frame << std::endl;
            second = floor(glfwGetTime());

            frame = 0;
            
        }

        

        frame++;
    }

    std::cout << "Closing..." << std::endl;
}

void Engine::clear() {
    delete screen;
    delete window;
    glfwTerminate();
}