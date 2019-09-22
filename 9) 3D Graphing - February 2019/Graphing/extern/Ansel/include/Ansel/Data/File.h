#pragma once

#include "../DLL/dll.h"

#include <string>

namespace age
{
	class File
	{
		std::string data;

	public:
		ANSEL_API File();
		ANSEL_API File(std::string path);

		std::string &getData() { return data; }
	};
}