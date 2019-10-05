#include "../headers/Graph.h"

#include "../headers/MainScene.h"

namespace gs
{
	Graph::Graph(unsigned int l) :
		length(l)
	{
		renderGridLines();
	}

	void Graph::renderGridLines()
	{
		using namespace age;
		Vertex3D line1, line2;

		// Y axis
		line1.color = Color(150, 0, 0);
		line2.color = Color(150, 0, 0);
		line1.postion = Vec3f(0,  (float)length * scale, 0);
		line2.postion = Vec3f(0, -(float)length * scale, 0);

		vertices.addVertex(line1);
		vertices.addVertex(line2);

		// X axis
		line1.color = Color(0, 150, 0);
		line2.color = Color(0, 150, 0);
		line1.postion = Vec3f((float)length * scale, 0, 0);
		line2.postion = Vec3f(-(float)length * scale, 0, 0);

		vertices.addVertex(line1);
		vertices.addVertex(line2);

		// Z axis
		line1.color = Color(0, 0, 150);
		line2.color = Color(0, 0, 150);
		line1.postion = Vec3f(0, 0, (float)length * scale);
		line2.postion = Vec3f(0, 0, -(float)length * scale);

		vertices.addVertex(line1);
		vertices.addVertex(line2);

		// Drawing Grid
		{
			// Y Grid
			int alpha = 35;
			int base_per_unit = 40;
			int amount = base_per_unit * length;

			for (int y = 0; y < amount + 1; y++)
			{
				Vertex3D line1, line2;

				float prop = ((y - ((float)base_per_unit * (float)length / 2.f)) / (float)amount);
				float y_pos = prop * 2.f * (float)length * (float)scale;

				line1.color = Color(0, 0, 0, alpha);
				line2.color = Color(0, 0, 0, alpha);

				line1.postion.y = y_pos;
				line1.postion.x = -(float)length * (float)scale;
				line2.postion.y = y_pos;
				line2.postion.x = (float)length * (float)scale;

				vertices.addVertex(line1);
				vertices.addVertex(line2);
			}

			// X Grid
			for (int x = 0; x < amount + 1; x++)
			{
				Vertex3D line1, line2;

				float prop = ((x - ((float)base_per_unit * (float)length / 2.f)) / (float)amount);
				float x_pos = prop * 2.f * (float)length * (float)scale;

				line1.color = Color(0, 0, 0, alpha);
				line2.color = Color(0, 0, 0, alpha);

				line1.postion.x = x_pos;
				line1.postion.y = -(float)length * (float)scale;
				line2.postion.x = x_pos;
				line2.postion.y = (float)length * (float)scale;

				vertices.addVertex(line1);
				vertices.addVertex(line2);
			}
		}
	}

	void Graph::plot(Equation equation, float x0, float x1, age::Color color, float step)
	{
		using namespace age;

		float range = x1 - x0;
		float increment = range / step;

		for (int i = 0; i < (int)(increment); i++)
		{
			age::Vertex3D vertex1, vertex2;

			float val = equation.get((float)(i)* step + x0);
			float next_val = equation.get((float)(i + 1) * step + x0);

			vertex1.postion = Vec3f(((float)i * step + x0) * scale, val * scale);
			vertex1.color = color;

			vertex2.postion = Vec3f(((float)(i + 1) * step + x0) * scale, next_val * scale);
			vertex2.color = color;

			vertices.addVertex(vertex1);
			vertices.addVertex(vertex2);
		}
	}

	void Graph::plot(Equation2D equation, float bounds, float left, float bottom, age::Color color, float step)
	{
		using namespace age;

		float range = bounds;
		float increment = range / step;

		left *= scale;
		bottom *= scale;

		for (int y = 0; y < (int)increment; y++)
		{
			for (int x = 0; x < (int)increment; x++)
			{
				float val;

				age::Vertex3D vertex;
				vertex.color = color;

				{
					// Bottom line
					val = equation.get((float)(x + left) * step, (float)(y + bottom) * step);
					vertex.postion = Vec3f(((float)(x + left) * step) * scale, ((float)(y + bottom) * step) * scale, val * scale);
					vertices.addVertex(vertex);

					val = equation.get((float)(x + 1 + left) * step, (float)(y + bottom) * step);
					vertex.postion = Vec3f(((float)(x + 1 + left) * step) * scale, ((float)(y + bottom) * step) * scale, val * scale);
					vertices.addVertex(vertex);

					// Top Line
					val = equation.get((float)(x + 1 + left) * step, (float)(y + 1 + bottom)* step);
					vertex.postion = Vec3f(((float)(x + 1 + left) * step) * scale, ((float)(y + 1 + bottom) * step) * scale, val * scale);
					vertices.addVertex(vertex);

					val = equation.get((float)(x + left) * step, (float)(y + 1 + bottom)* step);
					vertex.postion = Vec3f(((float)(x + left) * step) * scale, ((float)(y + 1 + bottom) * step) * scale, val * scale);
					vertices.addVertex(vertex);

					// Left line
					val = equation.get((float)(x + left)* step, (float)(y + 1 + bottom)* step);
					vertex.postion = Vec3f(((float)(x + left) * step) * scale, ((float)(y + 1 + bottom) * step) * scale, val * scale);
					vertices.addVertex(vertex);

					val = equation.get((float)(x + left) * step, (float)(y + 1 + bottom)* step);
					vertex.postion = Vec3f(((float)(x + left) * step) * scale, ((float)(y + 1 + bottom) * step) * scale, val * scale);
					vertices.addVertex(vertex);

					// Right Line
					val = equation.get((float)(x + 1 + left) * step, (float)(y + bottom)* step);
					vertex.postion = Vec3f(((float)(x + 1 + left) * step) * scale, ((float)(y + bottom) * step) * scale, val * scale);
					vertices.addVertex(vertex);

					val = equation.get((float)(x + 1 + left)* step, (float)(y + 1 + bottom)* step);
					vertex.postion = Vec3f(((float)(x + 1 + left) * step) * scale, ((float)(y + 1 + bottom) * step) * scale, val * scale);
					vertices.addVertex(vertex);
				}
			}
		}
	}

	void Graph::plot(EquationParametric2D equation, float x0, float x1, age::Color color, float step)
	{
		using namespace age;

		float range = x1 - x0;
		float increment = range / step;

		for (int i = 0; i < (int)(increment); i++)
		{
			age::Vertex3D vertex1, vertex2;

			age::Vec2f loc1 = equation.getPosition((float)(i)* step + x0);
			age::Vec2f loc2 = equation.getPosition((float)(i + 1) * step + x0);

			vertex1.postion = Vec3f(loc1.x * scale, loc1.y * scale);
			vertex1.color = color;

			vertex2.postion = Vec3f(loc2.x * scale, loc2.y * scale);
			vertex2.color = color;

			vertices.addVertex(vertex1);
			vertices.addVertex(vertex2);
		}
	}

	void Graph::drawDifference(Equation equation1, Equation equation2, float x0, float x1, age::Color color, float step)
	{
		using namespace age;

		float range = x1 - x0;
		float increment = range / step;

		for (int i = 0; i < (int)(increment); i++)
		{
			age::Vertex3D vertex1, vertex2;

			float val1 = equation1.get((float)(i)* step + x0);
			float val2 = equation2.get((float)(i) * step + x0);

			vertex1.postion = Vec3f(((float)i * step + x0) * scale, val1 * scale);
			vertex1.color = color;

			vertex2.postion = Vec3f(((float)i * step + x0) * scale, val2 * scale);
			vertex2.color = color;

			vertices.addVertex(vertex1);
			vertices.addVertex(vertex2);
		}
	}

	void Graph::drawVector(age::Vec3f base, age::Vec3f end, age::Color color, age::VertexList3D *v)
	{
		if (v == nullptr) v = &vertices;

		base.z += .01f;
		end.z  += .01f;

		const float max_length = 6.f;
		const float length = .2f;

		const float distance = sqrtf(
			powf(base.x - end.x, 2) +
			powf(base.y - end.y, 2) +
			powf(base.z - end.z, 2)
		);

		float absangle = atan2f(end.y - base.y, end.x - base.x);
		float angle = absangle + (3.14159f / 4.f);

		if (distance > max_length)
		{
			age::Vec3f new_end = end - base;

			new_end = new_end / distance;
			new_end = new_end * max_length;

			end = new_end + base;
		}

		age::Vertex3D b, e, p1, p2, p3, p4;
		b.color = color;
		e.color = color;
		p1.color = color;
		p2.color = color;
		p3.color = color;
		p4.color = color;

		b.postion = base;
		e.postion = end;

		p1.postion = e.postion;
		p2.postion = e.postion;
		p3.postion = e.postion;
		p4.postion = e.postion;

		p1.postion.x -= cosf(angle) * length;
		p1.postion.y -= sinf(angle) * length;

		angle = atan2f(e.postion.y - b.postion.y, e.postion.x - b.postion.x) - (3.14159f / 4.f);
		p3.postion.x -= cosf(angle) * length;
		p3.postion.y -= sinf(angle) * length;

		v->addVertex(b);
		v->addVertex(e);
		v->addVertex(p1);
		v->addVertex(p2);
		v->addVertex(p3);
		v->addVertex(p4);
	}

	void Graph::plotVectorField(EquationVector equation, float bounds, float left, float bottom, age::Color color, float step, age::VertexList3D *v)
	{
		using namespace age;

		if (v == nullptr) v = &vertices;

		float range = bounds;
		float increment = range / step;

		left   *= scale / 10.f;
		bottom *= scale / 10.f;

		int z = 0;

		for (int y = 0; y < (int)(increment) + 1; y++)
		{
			for (int x = 0; x < (int)(increment) + 1; x++)
			{

				Vec3f val = equation.get((float)(x + left) * step, (float)(y + bottom) * step, z) * step;

				drawVector(
					Vec3f((float)(x + left) * step * scale, (float)(y + bottom) * step * scale, (float)(z) * step * scale),
					Vec3f((float)(x + val.x + left) * step * scale, (float)(y + val.y + bottom) * step * scale, (float)(z + val.z) * step * scale),
					color, v
				);
			}
		}
	}

	void Graph::run()
	{
		age::Window window({ 1920, 1080 });
		gs::MainScene mainScene = gs::MainScene();

		mainScene.graph = this;
		mainScene.function = function;

		mainScene.rawModel = new age::RawModel(vertices);

		age::Engine engine = age::Engine::get(&window, &mainScene);
		engine.run();
	}
}