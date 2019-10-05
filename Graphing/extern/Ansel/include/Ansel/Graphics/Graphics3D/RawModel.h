#pragma once

#include "../../Data/Vector.h"
#include "../../Data/Color.h"

#include "../Shapes/VertexList.h"

#include "VertexArray.h"

#include <vector>

namespace age
{
	class RawModel
	{
		typedef std::vector<Vec3f>	      NormalData;
		typedef std::vector<Vec4f>		  VertexData;
		typedef std::vector<Color>        ColorData;
		typedef std::vector<Vertex3D>	  VertexList;
		typedef std::vector<unsigned int> IndexData;

		VertexList3D _vertices;

		VertexArray vao;

	public:
		/*******/ RawModel() {}
		ANSEL_API RawModel(const char* filename, bool store = false);
		ANSEL_API RawModel(VertexList3D vertices);
		ANSEL_API RawModel(VertexData vertices, IndexData indices = {}, ColorData colors = {});

		ANSEL_API void loadData(Buffer::BufferTypes type, DataType data, bool static_draw = true, bool divisor = false);
		ANSEL_API void loadColors(ColorData colors);
		ANSEL_API void loadNormals(NormalData normals);
		ANSEL_API void loadVertices(VertexData vertices);
		ANSEL_API void loadIndices(IndexData indices);
		ANSEL_API void loadVertexList(VertexList vertices);
		ANSEL_API void loadTransformation(VertexData t, VertexData r, VertexData s, VertexData o);
		ANSEL_API void loadVertexList3D(VertexList3D vertexlist, bool store_vertices = false);
		ANSEL_API void update();

		ANSEL_API void loadFromFile(const char* filename, bool store = false);

		VertexList3D &getVertices() { return _vertices; }
		VertexArray &getVAO() { return vao; }
	};
}