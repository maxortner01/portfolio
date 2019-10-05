#pragma once

#include "../DLL/dll.h"
#include "Vector.h"
#include "Rect.h"

namespace age
{
	template<typename T>
	class Transformation
	{
	protected:
		T origin;
		T position;
		T rotation;
		T scale;

	public:
		void translate(T amt)
		{
			position = position + amt;
		}

		void rotate(T amt)
		{
			rotation = rotation + amt;
		}

		void setPosition(T pos)
		{
			position = pos;
		}

		void setRotation(T rot)
		{
			rotation = rot;
		}

		void setScale(T sc)
		{
			scale = sc;
		}

		void setOrigin(T orig)
		{
			origin = orig;
		}

		T getGlobalLocation() const
		{
			return getPosition() - (getOrigin() * getScale());
		}

		T getPosition() const { return position; }
		T getRotation() const { return rotation; }
		T getOrigin()   const { return origin;   }
		T getScale()    const { return scale;    }
	};

	class Transformation2D : public Transformation<Vec2f>
	{
	public:
		Transformation2D()
		{
			scale = { 1, 1 };
		}

		using Transformation<Vec2f>::setPosition;
		using Transformation<Vec2f>::setRotation;
		using Transformation<Vec2f>::setOrigin;
		using Transformation<Vec2f>::setScale;

		ANSEL_API void setPosition(float x, float y);
		ANSEL_API void setRotation(float x, float y);
		ANSEL_API void setOrigin(float x, float y);
		ANSEL_API void setScale(float x, float y);

	};

	class Transformation3D : public Transformation<Vec3f>
	{
	public:
		Transformation3D()
		{
			scale = { 1, 1, 1 };
		}

		using Transformation<Vec3f>::setPosition;
		using Transformation<Vec3f>::setRotation;
		using Transformation<Vec3f>::setOrigin;
		using Transformation<Vec3f>::setScale;

		ANSEL_API void setPosition(float x, float y, float z);
		ANSEL_API void setRotation(float x, float y, float z);
		ANSEL_API void setOrigin(float x, float y, float z);
		ANSEL_API void setScale(float x, float y, float z);

	};
}