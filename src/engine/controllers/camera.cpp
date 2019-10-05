#include "camera.h"

Camera::Camera() {
    int width, height;
    width  = Engine::window->getWidth();
    height = Engine::window->getHeight();

    /* Changable settings */
    FOV               = 70.0; 
    mouse_sensitivity = .1;
    
    fog_start = 100;   //Fog end = fog_start + fog_distance
    fog_distance = 45;

    aspectRatio = float(width) / float(height);
    zNear = .1;

    projectionMatrix = genProjection();
    transform        = new Transform(0, 0, 0);

    transform->addTranslation(vec3(-.5, 50, 0));
    Mouse::setMousePos(Window::getWidth() / 2, Window::getHeight() / 2);
}

mat4 Camera::genProjection() {
    return infinitePerspective(FOV, aspectRatio, zNear);
}

mat4 Camera::getViewMatrix() {
    vec3 cameraTarget(0, 0, 0);
    vec3 front       (0, 0, 1);
    vec3 up          (0, 1, 0);
    mat4 view        (1.0);

    vec3 position = transform->getPosition();
    vec3 rotation = transform->getRotation();

    up.y += std::abs(position.y);

    vec3 direction = normalize(position - cameraTarget);

    vec3 cameraRight = normalize(cross(up, direction));
    vec3 cameraUp = cross(direction, cameraRight);

    front.x = std::cos(radians(rotation.y)) * std::cos(radians(rotation.x));
    front.y = std::sin(radians(rotation.y));
    front.z = std::cos(radians(rotation.y)) * std::sin(radians(rotation.x));

    front = normalize(front);

    view = lookAt(position, position + front, up);

    return view;
}

void Camera::moveForward(float speed) {
    vec3 rotation = transform->getRotation();

    float x = speed * std::cos(radians(rotation.x));
    float z = speed * std::sin(radians(rotation.x));

    vec3 movement = vec3(x, 0, z);

    transform->addTranslation(movement);
}

void Camera::moveBackward(float speed) {
    vec3 rotation = transform->getRotation();

    float x = speed * std::cos(radians(rotation.x + 180));
    float z = speed * std::sin(radians(rotation.x + 180));

    vec3 movement = vec3(x, 0, z);

    transform->addTranslation(movement);
}

void Camera::moveLeft(float speed) {
    vec3 rotation = transform->getRotation();

    float x = speed * std::cos(radians(rotation.x - 90));
    float z = speed * std::sin(radians(rotation.x - 90));

    vec3 movement = vec3(x, 0, z);

    transform->addTranslation(movement);
}

void Camera::moveRight(float speed) {
    vec3 rotation = transform->getRotation();

    float x = speed * std::cos(radians(rotation.x + 90));
    float z = speed * std::sin(radians(rotation.x + 90));

    vec3 movement = vec3(x, 0, z);

    transform->addTranslation(movement);
}

void Camera::Pollevents() {
    float speed = .12;

    //Check jump before sprint modifier
    if (Keyboard::getKey(Keyboard::K_SPACE)) {
        //Allow jump if not in air
        if (getFallSpeed() == 0) {
            setFallSpeed(-(speed * 2));
        }
        //Also allow jump at half speed if underwater
        else if (transform->getPosition().y < 0) {
            setFallSpeed(-(speed / 4));
        }
    }

    //If players legs in water walk slower
    if (transform->getPosition().y - 2 < -.5) {
        speed /= 2;
    }

    if (Keyboard::getKey(Keyboard::K_LSHIFT)) {
        speed *= 1.5;
    }

    if (Keyboard::getKey(Keyboard::K_W)) {
        moveForward(speed);
    }
    if (Keyboard::getKey(Keyboard::K_S)) {
        moveBackward(speed);
    }
    if (Keyboard::getKey(Keyboard::K_A)) {
        moveLeft(speed);
    }
    if (Keyboard::getKey(Keyboard::K_D)) {
        moveRight(speed);
    }

    //if (Keyboard::getKey(Keyboard::K_LCTRL)) {
        //transform->addTranslation(vec3(0, -speed, 0));
    //}

    Mouse::hide();

    vec2 mousepos = Mouse::getMousePos();
    vec2 deltapos = vec2(mousepos.x - (Window::getWidth() / 2), mousepos.y - (Window::getHeight() / 2));

    transform->addRotation(vec3(0, -deltapos.y * mouse_sensitivity, 0));
    transform->addRotation(vec3(deltapos.x    * mouse_sensitivity, 0, 0));

    Mouse::setMousePos(Window::getWidth() / 2, Window::getHeight() / 2);
}