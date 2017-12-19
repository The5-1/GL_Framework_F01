#pragma once
#include "stl_include.h"
#include "assimp_include.h"

namespace The5 {

	class Texture {
		unsigned int id;
		std::string type;
		aiString path;
	};
}
