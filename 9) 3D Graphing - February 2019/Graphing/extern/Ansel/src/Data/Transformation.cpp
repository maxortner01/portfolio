#include "../../include/Ansel/Data/Transformation.h"

namespace age
{
	void Transformation2D::setPosition(float x, float y)
	{
		Transformation<Vec2f>::setPosition({ x, y });
	}

	void Transformation2D::setRotation(float x, float y) 
	{
		Transformation<Vec2f>::setRotation({ x, y });
	}

	void Transformation2D::setScale(float x, float y)
	{
		Transformation<Vec2f>::setScale({ x, y });
	}

	void Transformation2D::setOrigin(float x, float y)
	{
		Transformation<Vec2f>::setOrigin({ x, y });
	}

	void Transformation3D::setPosition(float x, float y, float z)
	{
		Transformation<Vec3f>::setPosition({ x, y, z });
	}

	void Transformation3D::setRotation(float x, float y, float z)
	{
		Transformation<Vec3f>::setRotation({ x, y, z });
	}

	void Transformation3D::setScale(float x, float y, float z)
	{
		Transformation<Vec3f>::setScale({ x, y, z });
	}

	void Transformation3D::setOrigin(float x, float y, float z)
	{
		Transformation<Vec3f>::setOrigin({ x, y, z });
	}
}