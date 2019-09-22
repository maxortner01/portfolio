#include "Perceus/Core/Graphics/Rendering/Shaders/ShaderProgram.h"

namespace pcs
{
    void ShaderProgram::destroyShaders()
    {
        for (int i = 0; i < shaders.size(); i++)
            delete shaders[i];
    }

    ShaderProgram::ShaderProgram()
    {
        shaders.reserve((int)ShaderType::Count);

        rendAPI()->makeProgram(this);

        for (int i = 0; i < (int)ShaderType::Count; i++)
            shaders.push_back(new Shader((ShaderType)i));
    }

    ShaderProgram::~ShaderProgram()
    {
        rendAPI()->destroyProgram(this);
    }

    Shader &ShaderProgram::getShader(ShaderType type) {
        return *shaders[(int)type];
    }

    bool ShaderProgram::link()
    {   
        bool r = rendAPI()->linkProgram(this);

        destroyShaders();

        return r;
    }

    bool ShaderProgram::setUniform(const char* name, const Mat4f &matrix)
    {
        return rendAPI()->setUniform(this, name, matrix);
    }

    bool ShaderProgram::setUniform(const char* name, const Vec3f &var)
    {
        return rendAPI()->setUniform(this, name, var);
    }

    bool ShaderProgram::setUniform(const char* name, const int &var)
    {
        return rendAPI()->setUniform(this, name, var);
    }
}