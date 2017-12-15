#pragma once

#include "GL_include.h"
#include "assimp_include.h"
#include "stl_include.h"
#include "Shader.h"
#include "Logging.h"

#include "Mesh.h"

namespace The5 {

	static class Primitive
	{
	public:
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
	};

}