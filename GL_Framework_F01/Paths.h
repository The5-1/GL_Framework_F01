#pragma once

#include "stl_include.h"


namespace The5
{
	static class Path
	{
	public:
		static std::string getDirectory(std::string filepath)
		{
			std::string directory = filepath.substr(0, filepath.find_last_of('/'));
			return directory;
		}

		static std::string getFile(std::string filepath)
		{
			std::string file = "";
			return file;
		}

	};
}
