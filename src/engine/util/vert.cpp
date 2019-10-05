#include "vert.h"

const std::vector<std::vector<float>> VERT::vertices {
    std::vector<float> { //TRIANGLE
        -.5, -.5, 1,
         .5, -.5, 1,
          0,  .5, 1
    },
    std::vector<float> { //RECTANGLE
        -.5, -.5, 2,     //Bottom left
         .5, -.5, 2,     //Bottom right
         .5, -.5, 1,     //Top right

         .5, -.5, 1,     //Top right
        -.5, -.5, 2,     //Bottom left
        -.5, -.5, 1      //Top left
    }
};

std::vector<float> VERT::getSphere  (glm::vec3 position, int precision, float radius) {
    std::vector<float> sphere;

    float increment = 360.0 / precision;

    for (int i = 0; i < precision; i++) {
        
    }

    return sphere;
}

std::vector<float> VERT::getCylinder(glm::vec3 position, int precision, float radius, float height) {
    std::vector<float> cylinder;

    float increment = 360.0 / precision;

    //Create two circles: top and bottom
    for (int i = 0; i < (precision * 2) + 1; i++) {
        /* <---------- Create Circles ----------> */

        //VERTEX 1: (0, 0, 0) Center
        cylinder.push_back(position.x);

        if (i > precision) {
            cylinder.push_back(position.y + height);
        } else {
            cylinder.push_back(position.y);
        }

        cylinder.push_back(position.z);

        const float x1 = radius * std::sin(glm::radians(increment * i));
        const float z1 = radius * std::cos(glm::radians(increment * i));

        //VERTEX 2: increment * i
        cylinder.push_back(position.x + x1);
        
        if (i > precision) {
            cylinder.push_back(position.y + height);
        } else {
            cylinder.push_back(position.y);
        }

        cylinder.push_back(position.z + z1);

        const float x2 = radius * std::sin(glm::radians(increment * (i + 1)));
        const float z2 = radius * std::cos(glm::radians(increment * (i + 1)));

        //VERTEX 3: increment * (i + 1)
        cylinder.push_back(position.x + x2);
        
        if (i > precision) {
            cylinder.push_back(position.y + height);
        } else {
            cylinder.push_back(position.y);
        }
        
        cylinder.push_back(position.z + z2);

        if (i < precision) {
            /* <---------- Create Walls ----------> */
            //TRIANGLE 1
            {
                //VERTEX 2: increment * i
                cylinder.push_back(position.x + x1);
                cylinder.push_back(position.y);
                cylinder.push_back(position.z + z1);

                //VERTEX 3: increment * (i + 1)
                cylinder.push_back(position.x + x2);
                cylinder.push_back(position.y);
                cylinder.push_back(position.z + z2);

                //VERTEX 2: (increment * i) + height
                cylinder.push_back(position.x + x1);
                cylinder.push_back(position.y + height);
                cylinder.push_back(position.z + z1);
            }

            //TRIANGLE 2
            {
                //VERTEX 2: increment * i
                cylinder.push_back(position.x + x1);
                cylinder.push_back(position.y + height);
                cylinder.push_back(position.z + z1);

                //VERTEX 3: increment * (i + 1)
                cylinder.push_back(position.x + x2);
                cylinder.push_back(position.y + height);
                cylinder.push_back(position.z + z2);

                //VERTEX 3: increment * (i + 1)
                cylinder.push_back(position.x + x2);
                cylinder.push_back(position.y);
                cylinder.push_back(position.z + z2);
            }
        }
    }
    
    return cylinder;
}

std::vector<float> VERT::getTile(float y1, float y2, float y3, float y4) {
    std::vector<float> tile = vertices[RECTANGLE];

    //Bottom left
    tile[(0 * 3) + 1] = y1;
    tile[(4 * 3) + 1] = y1;

    //Bottom right
    tile[(1 * 3) + 1] = y2;

    //Top left
    tile[(5 * 3) + 1] = y3;

    //Top right
    tile[(2 * 3) + 1] = y4;
    tile[(3 * 3) + 1] = y4;

    return tile;
}