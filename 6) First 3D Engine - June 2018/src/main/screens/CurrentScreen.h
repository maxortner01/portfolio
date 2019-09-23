#ifndef CURRENTSCREEN_H_
#define CURRENTSCREEN_H_

#include <vector>

#include "engine/controllers/keyboard.h"
#include "engine/controllers/camera.h"
#include "engine/controllers/screen.h"

#include "engine/entities/terrain.h"

using namespace Controllers;

class CurrentScreen : public Screen 
{
private:
    /* Screen-specific variables */
    Terrain* terrain;
    Shader*  shader = new Shader("shader");
    Model*   model;

    Camera*   camera;
    Matrix4f* test;

public:
    CurrentScreen();

    void render();
    void update();
};

#endif /* CURRENTSCREEN_H_ */