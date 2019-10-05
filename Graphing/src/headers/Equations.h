#pragma once

#include <Ansel/Ansel.h>

namespace gs
{
	class Equation3D
	{
	protected:
		float(*func)(float, float, float) = nullptr;

	public:
		Equation3D(float(*f)(float, float, float) = NULL)
		{
			func = f;

			if (!f)
				func = [](float, float, float) { return 0.f; };
		}

		virtual float get(float x, float y, float z)
		{
			return func(x, y, z);
		}
	};

	class Equation2D
	{
	protected:
		float(*func)(float, float) = nullptr;

	public:
		Equation2D(float(*f)(float, float))
		{
			func = f;
		}

		virtual float get(float x, float y)
		{
			return func(x, y);
		}
	};

	class Equation
	{
	protected:
		float (*func)(float) = nullptr;

	public:
		Equation(float (*f)(float))
		{
			func = f;
		}

		virtual float get(float x)
		{
			return func(x);
		}
	};
	
	class EquationVector
	{
		Equation3D* equations[3];

	public:
		EquationVector(
				Equation3D eq1 = Equation3D(),
				Equation3D eq2 = Equation3D(),
				Equation3D eq3 = Equation3D()
			)
		{
			equations[0] = new Equation3D(eq1);
			equations[1] = new Equation3D(eq2);
			equations[2] = new Equation3D(eq3);
		}

		age::Vec3f get(float x, float y, float z = 0.f)
		{
			return age::Vec3f(equations[0]->get(x, y, z), equations[1]->get(x, y, z), equations[2]->get(x, y, z));
		}
	};

	class EquationParametric2D : public Equation
	{
		float(*func2)(float) = nullptr;

	public:
		EquationParametric2D(float(*f1)(float), float(*f2)(float)) :
			Equation(f1)
		{
			func2 = f2;
		}

		age::Vec2f getPosition(float t)
		{
			return age::Vec2f(func(t), func2(t));
		}
	};
}