#include "Geometry.h"

float Geometry::coTangent(float angle) {
    return float(1.0 / tan(angle));
}

float Geometry::degreesToRadians(float degrees) {
    return degrees * float(PI / 180.0);
}