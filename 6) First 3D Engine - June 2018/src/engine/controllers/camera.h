#ifndef CAMERA_H_
#define CAMERA_H_

#include "engine/controllers/mouse.h"
#include "engine/controllers/keyboard.h"
#include "engine/components/transform.h"
#include "engine/util/Geometry.h"
#include "engine/util/CML.h"
#include "engine/engine.h"

#include <glm.hpp>

#include <gtc/matrix_transform.hpp>
#include <GL/glew.h>

using namespace CML;
using namespace glm;

using namespace Controllers;

namespace Controllers {

    /**
     * @brief Main controller for player's camera
     * 
     * Pretty much just the player class. Handles any sort of camera parameters
     * as well as movement and rotation. Meant to be Screen specific.
     * 
     */
    class Camera
    {
    private:
        ///Current camera fall speed
        float camera_fall_speed;

        ///Camera perspective data
        float     zNear, zFar, FOV, aspectRatio;
        ///Factor to multiply mouse position delta with
        float     mouse_sensitivity;

        ///Distance fog starts to render, passed to shader
        float     fog_start;
        ///How long the fog lasts, also passed to shader
        float     fog_distance;
        ///Uninitialized matrix used to minimize generating several matrices every frame
        mat4 projectionMatrix;

    public:
        ///Used for camera position
        Transform* transform;

        /**
         * @brief Construct a new Camera object
         * Contructs camera object, initializes various camera variables and 
         * creates projectionMatrix.
         */
        Camera();

        /**
         * @brief Poll keyboard events and movement
         * Updates camera transformation according to keypress data.
         */
        void Pollevents();

        /**
         * @brief Get the fog_start object
         * 
         * @return float 
         */
        inline float getFogStart()    const { return fog_start; }
        /**
         * @brief Get the fog_distance object
         * 
         * @return float 
         */
        inline float getFogDistance() const { return fog_distance; }
        /**
         * @brief Get the Fall Speed object
         * 
         * @return float Current fall speed
         */
        inline float getFallSpeed()   const { return camera_fall_speed; }
        /**
         * @brief Set the Fall Speed object
         * 
         * @param speed Camera fall speed
         */
        inline void  setFallSpeed(float speed) { camera_fall_speed = speed; }


        /**
         * @brief Generates projection matrix
         * Uses defined variables to create and set projectionMatrix to a new mat4.
         * @return mat4 
         */
        mat4 genProjection();
        /**
         * @brief Get the Projection object
         * 
         * @return mat4 
         */
        mat4 getProjection() { return projectionMatrix; }
        /**
         * @brief Get the View Matrix object
         * 
         * @return mat4 
         */
        mat4 getViewMatrix();

        ///Move camera forward
        void moveForward    (float speed);
        ///Move camera backward
        void moveBackward   (float speed);
        ///Move camera left
        void moveLeft       (float speed);
        ///Move camera right
        void moveRight      (float speed);
    };

}

#endif /* CAMERA_H_ */