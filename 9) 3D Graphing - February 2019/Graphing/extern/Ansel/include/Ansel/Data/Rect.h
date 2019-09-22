#pragma once

namespace age
{
	template<typename T>
	struct Rect
	{
		T x, y, width, height;

		Rect(T _x = 0, T _y = 0, T _width = 0, T _height = 0) :
			x(_x), y(_y), width(_width), height(_height)
		{

		}
	};

	typedef Rect<int>          IntRect;
	typedef Rect<float>        FloatRect;
	typedef Rect<unsigned int> uIntRect;
}