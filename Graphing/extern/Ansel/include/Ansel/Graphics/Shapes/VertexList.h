#pragma once

#include "../Renderable.h"
#include "../../Data/Vertex.h"

#include <vector>

namespace age
{
	enum
	{
		Triangles,
		Quads,
		Lines,
		Points
	} typedef DrawType;

	class VertexList2D : public Renderable
	{
		std::vector<Vertex2D> vertices;
		DrawType type = Triangles;

	public:
		ANSEL_API VertexList2D(unsigned int size = 0);

		ANSEL_API void draw() override;

		void      setDrawType(DrawType t) { type = t; }

		ANSEL_API void     addVertex(Vertex2D vertex);
		ANSEL_API Vertex2D &getVertex(unsigned int index);

		Vertex2D &operator[](int index) { return getVertex(index); }
	};

	class VertexList3D
	{
		friend class RawModelLoader;

		std::vector<unsigned int> indices;
		std::vector<Vertex3D> vertices;

		DrawType type = Triangles;

	public:
		ANSEL_API VertexList3D(const unsigned int size = 0);

		ANSEL_API void setSize(const unsigned int size);
		
		void		setDrawType(DrawType t) { type = t;    }
		DrawType	getDrawType()	  const { return type; }

		ANSEL_API void		addVertex(Vertex3D vertex);
		ANSEL_API Vertex3D &getVertex(unsigned int index);

		ANSEL_API void			   addIndex(unsigned int index);
		ANSEL_API unsigned int	  &getIndex(unsigned int index);

		ANSEL_API std::vector<Vertex3D>     &getVertices();
		ANSEL_API std::vector<unsigned int> getIndices(bool real = false);

		ANSEL_API void saveToFile(const char* filename);

		Vertex3D &operator[](int index) { return getVertex(index); }
	};
}