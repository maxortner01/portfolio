#include "Perceus/Core/Graphics/Rendering/Shaders/Shader.h"

#include <fstream>

namespace pcs
{
    Shader::Shader(ShaderType t) :
        type(t)
    {
        getValues() = {
            "Compilation Failed",
            "Compilation Succeeded",
            "File does not exist"
        };

        rendAPI()->makeShader(this);
    }

    Shader::~Shader()
    {
        rendAPI()->destroyShader(this);
    }

    int Shader::loadFromFile(std::string filename)
    {
        std::string contents;

        std::ifstream f(filename);
        
        if (!f.good())
        {
            setStatus(ShaderStatus::FileDoesNotExist);
        }
        else
        {
            for (std::string line; std::getline(f, line);)
                contents += line + "\n";

            const char* s = contents.c_str();
            setStatus( (ShaderStatus)rendAPI()->compileShader(this, s) );
        }
        
        return (int)getStatus();
    }

    int Shader::loadFromString(const std::string &str)
    {
        const char* s = str.c_str();
        return rendAPI()->compileShader(this, s);
    }
} 
