#ifndef SHADER_H_
#define SHADER_H_

#define BUFF_SIZE 1024

#include <iostream>
#include <sstream>
#include <fstream>

#include <string>

#include <GL/glew.h>

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <glm.hpp>

#include "engine/util/CML.h"

using namespace CML;

namespace Controllers {

    /**
     * @brief Creates, compiles, and manages specific shaders
     * Initializes shader functions and applies them to current OpenGL context.
     */
    class Shader
    {
    private:
        ///ID's for OpenGL
        int program, vertex, fragment;

        ///Types of shaders
        enum shaderType { VERTEX, FRAGMENT };

        /**
         * @brief Reads file
         * 
         * @param filename Name of file to read contents of.
         * @return std::string Contents of specified file.
         */
        std::string readFile  ( std::string filename );
        /**
         * @brief Checks whether or not file exists
         * 
         * @param filename Name of file to check.
         * @return true File exists.
         * @return false File does not exist.
         */
        inline bool fileExists( std::string filename );

    public:
        /**
         * @brief Construct a new Shader object, defaults to "shader" if none is found
         * 
         * @param filename Name of shader (without extentions).
         */
        Shader(std::string filename);

        ///Use this program
        inline void bind()   { glUseProgram(program); }
        //Reset current program to none
        inline void unbind() { glUseProgram(program); }

        /**
         * @brief Pass matrix object to uniform location
         * 
         * @param matrix Matrix to pass to shader.
         */
        void setMatrix(glm::mat4 matrix);

        /**
         * @brief Set the specific uniform to value in shader
         * 
         * @param name Name of uniform in the shader.
         * @param value Float value to set the uniform as.
         */
        void setUniform(const char* name, const float value);
    };

}
#endif /* SHADER_H_ */