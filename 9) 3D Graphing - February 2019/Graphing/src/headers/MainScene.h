#pragma once

#include <Ansel/Ansel.h>

namespace gs
{
	class MainScene : public age::Scene3D
	{
		friend class Graph;

		age::RawModel* rawModel;
		age::Model* model;

	protected:
		void render(age::Event &event) override;
		void create() override;

	public:
		void* graph;
		void(*function)(std::vector<age::VertexList3D>&, void* graph) = nullptr;

		using age::Scene3D::Scene3D;
	};
}