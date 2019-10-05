#pragma once

#include "../Renderable.h"
#include "RawModel.h"
#include "../../Data/Transformation.h"
#include "../../Data/Matrix.h"
#include "../../Graphics/Shader.h"
#include "../../Graphics/Graphics3D/Camera.h"

namespace age
{
	class Model : public Transformation3D, public Object3D
	{
		RawModel* rawModel;

	public:
		ANSEL_API Model(RawModel* model);

		ANSEL_API void render(Shader &shader, Camera &camera) override;

		RawModel &getRawModel()    { return *rawModel; }
	};
}