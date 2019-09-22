#include "../../../include/Ansel/Graphics/Graphics3D/Camera.h"

#include <iostream>

namespace age
{
	Camera::Camera()
	{
		// Flip 180 degrees z-axis
	}

	Mat4f Camera::getView()
	{
		Mat4f view;
		view.setIdentity();

		view = view * Mat4f::makeTranslation(-getPosition().x, -getPosition().y, -getPosition().z) * Mat4f::makeRotation(getRotation().x, getRotation().y, getRotation().z);

		return view;
	}

	void Camera::move(Direction direction, float speed)
	{
		switch (direction)
		{
		case age::Camera::FORWARD:
		{
			float x = sinf(-getRotation().y) * speed;
			float z = cosf(-getRotation().y) * speed;

			translate({ x, 0, z });
			break;
		}
		case age::Camera::BACKWARD:
		{
			float x = sinf(-getRotation().y) * -speed;
			float z = cosf(-getRotation().y) * -speed;

			translate({ x, 0, z });
			break;
		}
		case age::Camera::LEFT:
		{
			float x = sinf(-getRotation().y + (3.14159f / 2.f)) * -speed;
			float z = cosf(-getRotation().y + (3.14159f / 2.f)) * -speed;

			translate({ x, 0, z });
			break;
		}
		case age::Camera::RIGHT:
		{
			float x = sinf(-getRotation().y - (3.14159f / 2.f)) * -speed;
			float z = cosf(-getRotation().y - (3.14159f / 2.f)) * -speed;

			translate({ x, 0, z });
			break;
		}
		default:
			break;
		}
	}

	void Camera::generateProjection(float zNear, float zFar, float FOV, float aspectRatio)
	{
		float fFovRad = 1.f / tanf(FOV * .5f / 180.f * 3.14159f);

		projection.m[0][0] = aspectRatio * fFovRad;
		projection.m[1][1] = fFovRad;
		projection.m[2][2] = zFar / (zFar - zNear);
		projection.m[2][3] = (-zFar * zNear) / (zFar - zNear);
		projection.m[3][2] = 1.f;
		projection.m[3][3] = 1.f;
	}
}