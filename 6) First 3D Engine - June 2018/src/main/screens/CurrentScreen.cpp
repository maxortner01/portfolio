#include "CurrentScreen.h"

CurrentScreen::CurrentScreen() {
    std::cout << "Creating camera... ";
    camera = new Camera();
    std::cout << "done" << std::endl;

    std::cout << "Creating terrain... ";
    terrain = new Terrain(camera);
    std::cout << "done" << std::endl;

    model = new Model(VERT::getSphere(vec3(0, 0, 10), 20, 2), std::vector<float> {});
}

void CurrentScreen::render() {
    //terrain->render();
    model->render(shader, glm::mat4(1.0), camera);
}

void CurrentScreen::update() {
    camera->Pollevents();
    
    /*
    float height = 4;
    Transform* transform = camera->transform;

    transform->setTranslation(vec3(

        transform->getPosition().x,
        Terrain::getval(transform->getPosition().x, transform->getPosition().z) + height,
        transform->getPosition().z

    )); 
    */

    /* <------------  PHYSICS ENGINE  ------------> */

    float height = 2;

    if (Keyboard::getKey(Keyboard::K_LCTRL)) {
        height = 1.6;
    }

    float gravity = .012;

    if (camera->transform->getPosition().y < 0) {
        gravity /= 5;
    } 

    float currentspeed = camera->getFallSpeed();

    vec3  change = vec3(camera->transform->getPosition().x, 0, camera->transform->getPosition().z);

    float terrainHeight = Entities::Terrain::getval(
        camera->transform->getPosition().x, camera->transform->getPosition().z) + height;

    //Apply physics
    float next_location = camera->transform->getPosition().y - currentspeed;

    //If player is on ground, make fallspeed 0 and make y the terrain
    //Otherwise, apply gravity to fall speed and move player down
    if (next_location <= terrainHeight) {
        camera->setFallSpeed(0.0);
        change.y = terrainHeight;
    } else {
        camera->setFallSpeed(currentspeed + gravity);
        change.y = next_location;
    }

    camera->transform->setTranslation(change);

    /* <------------------------------------------> */

    if ( Keyboard::getKey(Keyboard::K_ESCAPE) ) {
        glfwSetWindowShouldClose(Window::getWindow(), true);
    }
}