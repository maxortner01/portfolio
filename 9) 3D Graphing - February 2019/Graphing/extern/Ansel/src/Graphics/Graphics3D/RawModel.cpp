#include "../../../include/Ansel/Graphics/Graphics3D/RawModel.h"

#include "../../../include/Ansel/Data/Loaders/RawModelLoader.h"

namespace age
{
	RawModel::RawModel(const char* filename, bool store) :
		vao()
	{
		loadFromFile(filename, store);
	}

	RawModel::RawModel(VertexList3D vertices) :
		vao()
	{
		loadVertexList3D(vertices);
	}

	void RawModel::loadVertexList3D(VertexList3D vertexlist, bool store_vertices)
	{
		auto indices = vertexlist.getIndices();

		loadVertexList(vertexlist.getVertices());
		loadIndices(indices);

		if (store_vertices) _vertices = vertexlist;
	}

	RawModel::RawModel(VertexData vertices, IndexData indices, ColorData colors) :
		vao()
	{
		if (indices.size() == 0)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				indices.push_back(i);
			}
		}

		if (colors.size() == 0)
		{
			for (int i = 0; i < vertices.size(); i++)
			{
				colors.push_back(Color( 1.f, 0.f, 0.f, 1.f ));
			}
		}

		loadVertices(vertices);
		loadIndices(indices);
		loadColors(colors);
	}

	void RawModel::update()
	{
		if (_vertices.getVertices().size() > 0)
			loadVertexList3D(_vertices);
	}

	void RawModel::loadData(Buffer::BufferTypes type, DataType data, bool static_draw, bool divisor)
	{
		vao.bind();

		vao.getBuffer(type).bindData(data, static_draw, divisor);

		vao.unbind();
	}

	void RawModel::loadColors(ColorData colors)
	{
		loadData(Buffer::COLOR, DataType(&colors[0], sizeof(Color), colors.size(), 4));
	}

	void RawModel::loadNormals(NormalData normals)
	{
		loadData(Buffer::NORMAL, DataType(&normals[0], sizeof(Vec3f), normals.size(), 3));
	}

	void RawModel::loadVertices(VertexData vertices)
	{
		loadData(Buffer::VERTEX, DataType(&vertices[0], sizeof(Vec4f), vertices.size(), 4));
	}

	void RawModel::loadIndices(IndexData indices)
	{
		loadData(Buffer::INDICES, DataType(&indices[0], sizeof(unsigned int), indices.size(), 1));
	}

	void RawModel::loadVertexList(VertexList vertices)
	{
		VertexData v;
		NormalData n;
		ColorData  c;

		for (int i = 0; i < vertices.size(); i++)
		{
			v.push_back(vertices.at(i).postion);
			c.push_back(vertices.at(i).color);
			n.push_back(vertices.at(i).normal);
		}

		loadVertices(v);
		loadColors(c);
		loadNormals(n);
	}

	void RawModel::loadTransformation(VertexData t, VertexData r, VertexData s, VertexData o)
	{

		loadData(Buffer::TRANSLATION, DataType(&t[0], sizeof(Vec4f), t.size(), 4), false, true);
		loadData(Buffer::ROTATION   , DataType(&r[0], sizeof(Vec4f), r.size(), 4), false, true);
		loadData(Buffer::ORIGIN     , DataType(&o[0], sizeof(Vec4f), o.size(), 4), false, true);
		loadData(Buffer::SCALE      , DataType(&s[0], sizeof(Vec4f), s.size(), 4), false, true);
	}

	void RawModel::loadFromFile(const char* filename, bool store)
	{
		RawModelLoader::get().loadFromFile(filename, this, store);
	}
}