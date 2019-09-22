#include "transform.h"

Transform::Transform() {
    position = vec3(0, 0, 0);
}

Transform::Transform(float x) {
    position = vec3(x, 0, 0);
}

Transform::Transform(float x, float y) {
    position = vec3(x, y, 0);
}

Transform::Transform(float x, float y, float z) {
    position = vec3(x, y, z);
}

Transform::Transform(vec3 pos) {
    position = pos;
}

mat4 Transform::getModelMatrix() const {
    mat4 model(1.0);

     model = rotate(model, rotation.x, 
        vec3(1, 0, 0)
    );

    model = rotate(model, rotation.y, 
        vec3(0, 1, 0)
    );

    model = rotate(model, rotation.z, 
        vec3(0, 0, 1)
    );

    model = glm::scale( model, vec3(scale.x, scale.y, scale.z) );
    model = translate ( model, vec3(position.x, position.y, position.z) );

    return model;
}

void Transform::setScale(vec3 s) {
    scale = s;
}

void Transform::addScale(vec3 amt) {
    scale += amt;
}

void Transform::setRotation(vec3 s) {
    rotation = s;
}

void Transform::addRotation(vec3 amt) {
    rotation += amt;
}

void Transform::setTranslation(vec3 t) {
    position = t;
}

void Transform::addTranslation(vec3 amt) {
    position += amt;
}

void Transform::update() {

}