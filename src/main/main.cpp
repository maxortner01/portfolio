#include <iostream>
#include <string>

#include "engine/engine.h"
#include "screens/CurrentScreen.h"
#include "engine/util/CML.h"
#include "engine/controllers/shader.h"
#include "engine/controllers/camera.h"

using namespace CML;

//TODO: help
void display() {
    vert3f* position = new vert3f(2, 4, 6);
    Matrix4f* matrix = new Matrix4f(MAT_INDENTITY);

    matrix->translate(new vert3f(2, 5, 7));
    //matrix->scale(new vert3f(2, 2, 2));
    matrix->rotate(new vert3f(.2, 15, 23));

    matrix = matrix->mul(position);

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            std::cout << matrix->get(x, y) << "\t\t";
        }
        std::cout << std::endl;
    }

    delete matrix;
    std::string input;
    std::cin >> input;
}

int main() {
    Engine engine(2560, 1440, "What up");
    engine.setScreen(new CurrentScreen());

    try { 
        engine.loop();
    } catch(...) {
        std::cout << "Error caught" << std::endl;
    }
    
    engine.clear();
}