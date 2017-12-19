#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "IComponent.h"

//#include "Mesh.h"
//#include "Material.h"
//#include "Texture.h"
//#include "Shader.h"

namespace The5 {

	class Mesh;
	class Material;
	class Shader;
	class Entity;

	class Renderable: IComponent
	{
	public:

		Renderable(Entity* entity);

		ComponentType getType();

		void update();
		void draw();

	private:

		std::vector<Mesh> mMeshes;
		std::vector<Material> mMaterials;

	};

}