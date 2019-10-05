#pragma once

#include "Equations.h"

#include <Ansel/Ansel.h>

namespace gs
{
	class Graph
	{
		age::VertexList3D vertices;

		void drawVector(age::Vec3f base, age::Vec3f end, age::Color color, age::VertexList3D *v = nullptr);

		void renderGridLines();

		float scale = 100.f;

		const unsigned int length = 2;

	public:
		Graph(unsigned int l = 2);

		void run();

		void(*function)(std::vector<age::VertexList3D>&, void*) = nullptr;

		void plot(Equation2D equation, float bounds, float left, float bottom, age::Color color, float step = .01f);
		void plot(Equation equation, float x0, float x1, age::Color color, float step = .01f);
		void plot(EquationParametric2D equation, float x0, float x1, age::Color color, float step = .01f);

		void plotVectorField(EquationVector equation, float bounds, float left, float bottom, age::Color color, float step = .01f, age::VertexList3D *v = nullptr);

		void drawDifference(Equation equation1, Equation equation2, float x0, float x1, age::Color color, float step = .01f);

		age::VertexList3D &getVertices() { return vertices; }
	};
}