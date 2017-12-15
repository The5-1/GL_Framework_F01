#pragma once
#include "stl_include.h"
#include "assimp_include.h"

namespace The5 {

	struct Texture {
		unsigned int id;
		std::string type;
		aiString path;
	};
}
