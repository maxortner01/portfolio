#include "../../include/Ansel/Data/File.h"

#include <fstream>

namespace age
{
	File::File() { }

	File::File(std::string path)
	{
		std::fstream f(path);

		for (std::string line; std::getline(f, line);)
		{
			data += line + "\n";
		}

		f.close();
	}
}