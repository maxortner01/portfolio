#include <iostream>

#include "headers/Graph.h"

age::Vec2f position;
void func(std::vector<age::VertexList3D> &v, void* graph)
{
	static float frame;
	v.push_back(age::VertexList3D());

	using namespace gs;

	Graph* g = (Graph*)graph;

	g->plotVectorField(
		EquationVector({
			Equation3D([](float x, float y, float z) { return (-1.f * 1.f / (powf(x + position.x, 2) + powf(y + position.y, 2))) * cosf(atan2f(y + position.y, x + position.x)); }),
			Equation3D([](float x, float y, float z) { return (-1.f * 1.f / (powf(x + position.x, 2) + powf(y + position.y, 2))) * sinf(atan2f(y + position.y, x + position.x)); }),
			Equation3D([](float x, float y, float z) { return 0.f; })
			})
		,
		4.f, -2.f, -2.f, age::Color(255, 0, 0), .1f, &v.at(0)
	);

	g->plotVectorField(
		EquationVector({
			Equation3D([](float x, float y, float z) { return 0.f; }),
			Equation3D([](float x, float y, float z) { return 0.f; }),
			Equation3D([](float x, float y, float z) { return (2.f * (x + position.x) + 2.f * (y + position.y)) / powf(powf(x + position.x, 2) + powf(y + position.y, 2), 2); })
			})
		,
		4.f, -2.f, -2.f, age::Color(0, 0, 255), .1f, &v.at(0)
	);

	position.x = sinf(frame / 70.f);
	position.y = cosf(frame / 70.f);

	frame++;
}

int main()
{
	using namespace gs;

	Graph graph = Graph();
	graph.function = func;

	//Equation square      = Equation([](float x) { return powf(x, 2); });
	//Equation square_root = Equation([](float x) { return sqrtf(x); });
	//
	//graph.plot(Equation2D([](float x, float y) { return powf(sinf(x * 2.f) + y, 10); }), 4.f, -2.f, -2.f, age::Color(255, 0, 0, 100));

	

	//graph.plotVectorField(
	//	EquationVector({
	//		Equation3D([](float x, float y, float z) { return 0.f; }),
	//		Equation3D([](float x, float y, float z) { return 0.f; }),
	//		Equation3D([](float x, float y, float z) { return 3.f * powf(x, 2) - 3.f * powf(y, 2); })
	//		})
	//	,
	//	4.f, -2.f, -2.f, age::Color(0, 0, 255, 100), .1f
	//);

	//graph.plot(square_root, 0.f, 1.f, age::Color(255, 0, 0));
	//graph.drawDifference(square, square_root, 0.f, 1.f, age::Color(0, 0, 255));

	//graph.plot(EquationParametric2D([](float t) { return cosf(t * 10.f); }, [](float t) { return t; }), 0, 2.f, age::Color(255, 0, 0));

	graph.run();
}