#include "color.h"

Color::Color(float r, float g, float b) {
    color = vec3(r, g, b);
    alpha = 1;
}

Color::Color(float r, float g, float b, float a) {
    color = vec3(r, g, b);
    alpha = a;
}

void Color::update() {

}