#pragma once

#include <string>

#include "../DLL/dll.h"
#include "GLObjects.h"

#include "../Data/Vector.h"
#include "../Data/Matrix.h"

namespace age
{
	class Shader : public GLObject
	{
		int shaders[3];

	public:
		enum
		{
			VERTEX,
			GEOMETRY,
			FRAGMENT
		} typedef ShaderType;

		ANSEL_API void loadFromFile(std::string directory, ShaderType type);
		ANSEL_API void make();

		ANSEL_API bool setUniform(const Mat4f &mat, std::string name);

		ANSEL_API void bind() override;
		ANSEL_API void unbind() const override;
	};
}