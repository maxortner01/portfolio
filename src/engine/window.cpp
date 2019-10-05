#include "window.h"

GLFWwindow* Window::window = NULL;

int Window::width  = 0;
int Window::height = 0;

void print(std::string val, bool breakline) {
    std::cout << val;
    if ( breakline ) { std::cout << std::endl; }
}

//Initialized width, height, and title variables. Calls init
Window::Window(int w, int h, std::string t) {
    width = w; height = h; title = t;

    //Set to true for fullscreen
    fullscreen = false;
    frame      = 0;

    init();
}

//Sets up initial glfw and opengl context creation
void Window::init() {
    //Initialize glfw

    print("Initializing GLFW... ", false);

    if ( !glfwInit() ) {
        throw new std::runtime_error("GLFW initialsation failed!");
    }
    
    print("done", true);
    print("Setting window hints... ", false);

    //Make window invisible during creation
    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);

    print("done", true);
    print("Fullscreen... ", false);

    //Check monitor value for fullscreen
    GLFWmonitor* monitor;
    if ( fullscreen ) {
        print("true", true);
        monitor = glfwGetPrimaryMonitor();

    } else { 
        print("false", true); 
        monitor = NULL;
    }

    print("Creating window instance... ", false);

    //Create glfw window instance
    window = glfwCreateWindow(width, height, title.c_str(), monitor, 0);
    if ( !window ) {
        throw new std::runtime_error("GLFW failed to create window!");
    }

    print("done", true); 
    print("Evaluating primary monitor... ", false);

    //Move window to center of screen
    GLFWvidmode videomode = *glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (videomode.width - width) / 2, (videomode.height  - height) / 2);

    print("done", true); 

    glfwShowWindow(window);
    glfwMakeContextCurrent(window);

    print("Initializing GLEW... ", false);

    //Initializing GLEW
    if ( glewInit() != GLEW_OK ) {
        throw new std::runtime_error("GLEW initialization failed!");
    }

    print("done", true);

    //GL.createCapabilities();
}

void Window::update() {
    glfwPollEvents();
}

void Window::render(Screen* currentScreen) {
    currentScreen->update();
    currentScreen->render();
    glfwSwapBuffers(window);
    frame++;
}

Window::~Window() {
    
}