#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "IComponent.h"
#include "Mesh.h"
#include "Material.h"
#include "Texture.h"
#include "Shader.h"

namespace The5 {

	class Renderable: IComponent
	{
	public:

		std::vector<Mesh> meshes;
		std::vector<Material> materials;

	};

}