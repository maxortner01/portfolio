#include "../../../include/Ansel/Graphics/Shapes/VertexList.h"
#include "../../../include/Ansel/Data/Loaders/RawModelLoader.h"

#include <GL/glew.h>

namespace age
{

	VertexList2D::VertexList2D(unsigned int size)
	{
		vertices.resize(size);
	}

	void VertexList2D::draw()
	{
		switch (type)
		{
		case Triangles:
			glBegin(GL_TRIANGLES);
			break;

		case Quads:
			glBegin(GL_QUADS);
			break;

		case Lines:
			glBegin(GL_LINE_STRIP);
			break;

		case Points:
			glBegin(GL_POINTS);
			break;
		}

		for (Vertex2D &vertex : vertices)
		{
			glColor4f(vertex.color.r, vertex.color.g, vertex.color.b, vertex.color.a);
			glVertex2f(vertex.position.x, vertex.position.y);
		}

		glEnd();
	}

	void VertexList2D::addVertex(Vertex2D vertex)
	{
		vertices.push_back(vertex);
	}

	Vertex2D &VertexList2D::getVertex(unsigned int index)
	{
		return vertices.at(index);
	}

	VertexList3D::VertexList3D(const unsigned int size)
	{
		setSize(size);
	}

	void VertexList3D::setSize(const unsigned int size)
	{
		vertices.resize(size);
	}

	void VertexList3D::addVertex(Vertex3D vertex)
	{
		vertices.push_back(vertex);
	}

	Vertex3D &VertexList3D::getVertex(unsigned int index)
	{
		return vertices.at(index);
	}

	void VertexList3D::addIndex(unsigned int index)
	{
		indices.push_back(index);
	}

	unsigned int &VertexList3D::getIndex(unsigned int index)
	{
		return indices.at(index);
	}
	
	std::vector<unsigned int> VertexList3D::getIndices(bool real)
	{
		if (indices.size() == 0 && !real)
		{
			std::vector<unsigned int> r;

			for (int i = 0; i < vertices.size(); i++)
			{
				r.push_back(i);
			}

			return r;
		}

		return indices;
	}

	std::vector<Vertex3D> &VertexList3D::getVertices()
	{
		return vertices;
	}

	void VertexList3D::saveToFile(const char* filename)
	{
		RawModelLoader::get().saveToFile(filename, this);
	}
}