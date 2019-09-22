#include "shader.h"

inline bool Controllers::Shader::fileExists(std::string filename) {
    std::ifstream f(filename);
    return f.good();
}

std::string Controllers::Shader::readFile(std::string filename) {
    std::string line, end;

    std::ifstream infile(filename);
    while ( std::getline(infile, line) ) {
        end += line + "\n";
    }

    return end;
}

Controllers::Shader::Shader(std::string shadername) {
    std::cout << "\nCreating shader: " << shadername << std::endl;

    //by default the shader is to read the shader file
    std::string directory        = "src/engine/shaders/";
    std::string shaderNames  [2] { directory + "shader.vert.glsl", directory + "shader.frag.glsl" };
    
    //add directory to shadername
    shadername = directory + shadername;

    //set shader contents to default shader names
    std::string shaderContent[2] { 
        readFile(shaderNames[VERTEX]),
        readFile(shaderNames[FRAGMENT])
    };

    //VERTEX:   name and contents
    if ( fileExists(shadername + ".vert.glsl") ) {
        shaderNames  [VERTEX]   = shadername + ".vert.glsl";
        shaderContent[VERTEX]   = readFile(shadername + ".vert.glsl");
    }

    //FRAGMENT: name and contents
    if ( fileExists(shadername + ".frag.glsl") ) {
        shaderNames  [FRAGMENT] = shadername + ".frag.glsl";
        shaderContent[FRAGMENT] = readFile(shadername + ".frag.glsl");
    }

    //Create shader and program
    program  = glCreateProgram();
    vertex   = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    std::cout << "  Program  ID: " << program << std::endl;
    std::cout << "  Vertex   ID: " << vertex << std::endl;
    std::cout << "  Fragment ID: " << fragment << std::endl;

    const char* v = shaderContent[VERTEX].c_str();
    const char* f = shaderContent[FRAGMENT].c_str();

    //Set shader source
    glShaderSource(vertex,   1, &v, NULL);
    glShaderSource(fragment, 1, &f, NULL);

    //Compile shaders
    glCompileShader(vertex);
    glCompileShader(fragment);

    //Error checking for shaders
    GLint status;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &status);
    if ( !status ) {
        GLchar infoLog[BUFF_SIZE];
        glGetShaderInfoLog(vertex, BUFF_SIZE, NULL, infoLog);

        std::cout << "Error in vertex compilation!" << std::endl;
        std::cout << "Info log:" << infoLog << std::endl;
    }

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &status);
    if ( !status ) {
        GLchar infoLog[BUFF_SIZE];
        glGetShaderInfoLog(fragment, BUFF_SIZE, NULL, infoLog);

        std::cout << "Error in fragment compilation!" << std::endl;
        std::cout << "Info log: " << infoLog << std::endl;
    }
    
    //Attach shader to program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    //Create attributes
    glBindAttribLocation(program, 0, "vertices");

    //Link and validate program
    glLinkProgram(program);

    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if ( !status ) {
        GLchar infoLog[BUFF_SIZE];
        glGetProgramInfoLog(program, BUFF_SIZE, NULL, infoLog);

        std::cout << "Error in program linkage!" << std::endl;
        std::cout << "Info log: " << infoLog << std::endl;
    }

    glValidateProgram(program);

    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    if ( !status ) {
        GLchar infoLog[BUFF_SIZE];
        glGetProgramInfoLog(program, BUFF_SIZE, NULL, infoLog);

        std::cout << "Error in program validation!" << std::endl;
        std::cout << "Info log: " << infoLog << std::endl;
    }
}

void Controllers::Shader::setMatrix(glm::mat4 matrix) {
    int location = glGetUniformLocation(program, "matrix");

    //matrix->setScale(new vert3f(.5, .5, 0));
    //matrix->rotate(new vert3f(.2, .3, 0));


    /*float floats[16] = {0};
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            floats[(y * 4) + x] = matrix->get(x, y);
        }
    } */

    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Controllers::Shader::setUniform(const char* name, const float value) {
    int location = glGetUniformLocation(program, name);
    glUniform1f(location, value);
}