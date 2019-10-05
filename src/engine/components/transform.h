#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#include "component.h"

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>

using namespace glm;
using namespace Components;

namespace Components {

    class Transform : public Component
    {
    private:
        vec3 position;
        vec3 scale    = vec3(1, 1, 1);
        vec3 rotation = vec3(0, 0, 0);

    public:
        Transform();
        Transform(float x);
        Transform(float x, float y);
        Transform(float x, float y, float z);
        Transform(vec3 pos);

        mat4 getModelMatrix() const;

        void setTranslation(vec3 t);
        void addTranslation(vec3 amt);

        void setScale(vec3 s);
        void addScale(vec3 amt);
        
        void setRotation(vec3 s);
        void addRotation(vec3 amt);

        inline vec3 getPosition() const { return position; }
        inline vec3 getRotation() const { return rotation; }
        inline vec3 getScale()    const { return scale;    }

        void update();  
    };

}

#endif /* TRANSFORM_H_ */