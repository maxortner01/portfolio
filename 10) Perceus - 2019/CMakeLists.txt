cmake_minimum_required(VERSION 2.8.9)
project(perceus)
set(CMAKE_BUILD_TYPE Release)

if(UNIX)
    if(APPLE)
        # Apple

    else(APPLE) 
        # Linux
		set(WINDOWS 0)
    endif(APPLE)
else(UNIX)
    if(WIN32)
        # Windows
		set(WINDOWS 1)
    endif(WIN32)

endif(UNIX)

# Include and link directories
include_directories(include extern/glew-2.1.0/include extern/glfw-3.3/include)

add_compile_definitions(_PERCEUS_BUILD)
add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

if(WINDOWS)

link_directories(extern/glew-2.1.0/lib/windows extern/glfw-3.3/lib/windows)
add_compile_definitions(GLEW_STATIC)

else(WINDOWS)

link_directories(extern/glew-2.1.0/lib extern/glfw-3.3/lib)

endif(WINDOWS)

# Load the cpp files from the src directory
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Generate shared library
add_library(perceus SHARED ${SOURCES})

if(WINDOWS)
        target_link_libraries(perceus glew32s glfw3 opengl32)
else(WINDOWS)
        target_link_libraries(perceus glew glfw3 X11 GL)
endif(WINDOWS)

# Install library
install(TARGETS perceus DESTINATION lib)

