#pragma once

namespace age
{
	struct Color
	{
		float r, g, b, a;

		explicit Color(const float _r = 0.f, const float _g = 0.f, const float _b = 0.f, const float _a = 1.f) :
			r(_r), g(_g), b(_b), a(_a)
		{

		}

		explicit Color(const int _r, const int _g = 0, const int _b = 0, const int _a = 255) :
			r((float)_r / 255.f), g((float)_g / 255.f), b((float)_b / 255.f), a((float)_a / 255.f)
		{

		}
	};
}