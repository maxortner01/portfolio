#include "../../../include/Ansel/Data/Loaders/RawModelLoader.h"

#include <string>
#include <cstring>
#include <fstream>

namespace age
{
	void RawModelLoader::saveToFile(const char* destination, VertexList3D* model) const
	{
		std::string str(destination);
		str += ".ansm";

		std::ofstream out(str, std::ios::binary);
		out.clear();

		unsigned int vertices, indices;
		vertices = model->vertices.size();
		indices  = model->indices.size();

		out.write((char*)&vertices, sizeof(unsigned int));

		for (int i = 0; i < vertices; i++)
		{
			out.write((char*)&model->vertices.at(i), sizeof(Vertex3D));
		}

		out.write((char*)&indices, sizeof(unsigned int));

		for (int i = 0; i < indices; i++)
		{
			out.write((char*)&model->indices.at(i), sizeof(unsigned int));
		}

		out.close();
	}

	void RawModelLoader::loadFromFile(const char* filename, RawModel* model, bool store) const
	{
		std::string str(filename);
		if (str.substr(str.length() - 5, str.length()) != ".ansm")
		{
			str += ".ansm";
		}

		VertexList3D vertices;

		std::ifstream in(str, std::ios::binary);

		unsigned int vertex_count;
		in.read(reinterpret_cast<char*>(&vertex_count), sizeof(unsigned int));

		for (int i = 0; i < vertex_count; i++)
		{
			Vertex3D vertex;
			in.read(reinterpret_cast<char*>(&vertex), sizeof(Vertex3D));
			vertices.addVertex(vertex);
		}

		unsigned int index_count;
		in.read(reinterpret_cast<char*>(&index_count), sizeof(unsigned int));

		for (int i = 0; i < index_count; i++)
		{
			unsigned int index;
			in.read(reinterpret_cast<char*>(&index), sizeof(unsigned int));
			vertices.addIndex(index);
		}

		in.close();

		model->loadVertexList3D(vertices, store);
	}
}