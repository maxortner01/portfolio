#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#define PI 3.14159

#include <math.h>

struct Geometry
{
    static float coTangent(float angle);
    static float degreesToRadians(float degrees);
};

#endif /* GEOMETRY_H_ */