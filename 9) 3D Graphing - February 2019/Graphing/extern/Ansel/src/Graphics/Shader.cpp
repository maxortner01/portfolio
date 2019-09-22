#include "../../include/Ansel/Graphics/Shader.h"
#include "../../include/Ansel/Data/File.h"

#include <iostream>
#include <GL/glew.h>

namespace age
{
	const char* vertex_header =
		"#version 330 core						   \n"
		"										   \n"
		"layout(location = 0) in vec3 vertex;	   \n"
		"layout(location = 1) in vec4 color;	   \n"
		"										   \n"
		"layout(location = 3) in vec4 translation; \n"
		"layout(location = 4) in vec4 rotation;    \n"
		"layout(location = 5) in vec4 scale;       \n"
		"										   \n"
		"uniform mat4 projection;				   \n"
		"uniform mat4 view;						   \n"
		"										   \n"
		"out vec4 vertColor;					   \n"
		"										   \n"
		"mat4 makeTransformMatrix(vec4 loc) {	   \n"
		"return mat4(							   \n"
		"	1, 0, 0, loc.x,						   \n"
		"	0, 1, 0, loc.y,						   \n"
		"	0, 0, 1, loc.z,						   \n"
		"	0, 0, 0, 1							   \n"
		");										   \n"
		"}										   \n"
		"mat4 makeRotationMatrix(vec4 rot) {	   \n"
		"	mat4 rot_x = mat4(					   \n"
		"		1, 0, 0, 0,						   \n"
		"		0, 1, 0, 0,	   \n"
		"		0, 0, 1, 0,	   \n"
		"		0, 0, 0, 1						   \n"
		"	);									   \n"
		"										   \n"
		"	mat4 rot_y = mat4(					   \n"
		"		cos(rot.y), 0, sin(rot.y), 0,	   \n"
		"		0, 1, 0, 0,						   \n"
		"		-sin(rot.y), 0, cos(rot.y), 0,	   \n"
		"		0, 0, 0, 1						   \n"
		"	);									   \n"
		"										   \n"
		"	mat4 rot_z = mat4(					   \n"
		"		1, 0, 0, 0,	   \n"
		"		0, 1, 0, 0,	   \n"
		"		0, 0, 1, 0,						   \n"
		"		0, 0, 0, 1						   \n"
		"	);									   \n"
		"										   \n"
		"	return rot_x * rot_y * rot_z;		   \n"
		"}										   \n"
		"mat4 makeScaleMatrix(vec4 sc) {		   \n"
		"	return mat4(						   \n"
		"		sc.x, 0, 0, 0,					   \n"
		"		0, sc.y, 0, 0,					   \n"
		"		0, 0, sc.z, 0,					   \n"
		"		0, 0, 0, 1						   \n"
		"	);									   \n"
		"}										   \n"
		"																					 \n"
		"																					 \n"
		"mat4 makeModel(vec4 loc, vec4 rot, vec4 sc) {										 \n"
		"	return makeScaleMatrix(sc) * makeRotationMatrix(rot) * makeTransformMatrix(loc); \n"
		"}                                                                                   \n"
		"                                                                                    \n"
		"mat4 model = makeModel(translation, rotation, scale);                               \n";

	void Shader::loadFromFile(std::string directory, ShaderType type)
	{
		File file(directory);
		std::string prefix = "";

		switch (type)
		{
		case VERTEX:
			prefix = vertex_header;
			shaders[type] = glCreateShader(GL_VERTEX_SHADER);
			break;

		case GEOMETRY:
			shaders[type] = glCreateShader(GL_GEOMETRY_SHADER);
			break;

		case FRAGMENT:
			shaders[type] = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}

		std::string source  = /*prefix + */file.getData();
		const char* csource = source.c_str();

		glShaderSource(shaders[type], 1, &csource, NULL);
		glCompileShader(shaders[type]);

		int success;
		char infoLog[512];
		glGetShaderiv(shaders[type], GL_COMPILE_STATUS, &success);
		if (!success)
		{
			std::string t = "vertex";

			switch (type)
			{
			case GEOMETRY:
				t = "geometry";
				break;

			case FRAGMENT:
				t = "fragment";
				break;
			}

			glGetShaderInfoLog(shaders[type], 512, NULL, infoLog);
			std::cout << "Error compiling " << t << " shader!\n" << infoLog << std::endl;
		}
	}
	
	void Shader::make() 
	{
		id() = glCreateProgram();

		for (int i = 0; i < 3; i++)
			glAttachShader(id(), shaders[i]);

		glLinkProgram(id());

		int success;
		char infoLog[512];
		glGetProgramiv(id(), GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id(), 512, NULL, infoLog);
			std::cout << "Error linking program!\n" << infoLog << std::endl;
		}

		for (int i = 0; i < 3; i++)
			glDeleteShader(shaders[i]);
	}

	void Shader::bind()
	{
		glUseProgram(id());
	}

	void Shader::unbind() const
	{
		glUseProgram(0);
	}

	bool Shader::setUniform(const Mat4f &mat, std::string name)
	{
		int location = glGetUniformLocation(id(), name.c_str());

		if (location != -1)
		{
			glUniformMatrix4fv(location, 1, GL_FALSE, *mat.m);
			return true;
		}

		return false;
	}
}