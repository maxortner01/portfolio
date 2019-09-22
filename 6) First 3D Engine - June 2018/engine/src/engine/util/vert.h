#ifndef VERT_H_
#define VERT_H_

#include <vector>
#include <math.h>
#include <glm.hpp>


enum types {
    TRIANGLE,
    RECTANGLE
};

class VERT
{
private:
    static const std::vector<std::vector<float>> vertices;

public:
    static inline std::vector<float> getVertices(int type) { return vertices.at(type); }

    static std::vector<float> getTile    (float y1, float y2, float y3, float y4);
    static std::vector<float> getCylinder(glm::vec3 position, int precision, float radius, float height);
    static std::vector<float> getSphere  (glm::vec3 position, int precision, float radius);
};

#endif /* VERT_H_ */