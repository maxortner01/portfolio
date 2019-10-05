#pragma once

#include "../../DLL/dll.h"
#include "../../Data/Matrix.h"
#include "../../Data/Transformation.h"

namespace age
{
	class Camera : public Transformation3D
	{
		Mat4f view;
		Mat4f projection;

	public:
		enum Direction
		{
			FORWARD,
			BACKWARD,
			LEFT,
			RIGHT
		};

		ANSEL_API Camera();

		ANSEL_API void generateProjection(float zNear, float zFar, float FOV, float aspectRatio);

		ANSEL_API void move(Direction direction, float speed = 1.f);

		ANSEL_API Mat4f getView();
		Mat4f getProjection() const { return projection; }
	};
}