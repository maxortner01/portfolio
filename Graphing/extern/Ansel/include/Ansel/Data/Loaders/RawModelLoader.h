#pragma once

#include "../../Graphics/Graphics3D/RawModel.h"
#include "../../Main/Singleton.h"
#include "../../DLL/dll.h"

namespace age
{
	class RawModelLoader : public Singleton<RawModelLoader>
	{
	public:
		//ANSEL_API void convertObj(const char* source, const char* destination) const;
		ANSEL_API void saveToFile(const char* destination, VertexList3D* model) const;
		ANSEL_API void loadFromFile(const char* filename, RawModel* model, bool store = false) const;
	};
}