#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "ForwardDeclarations.h"
#include "IComponent.h"

namespace The5 {

	class Renderable: IComponent
	{
	public:

		Renderable(Entity* entity);

		ComponentType getType();

		void update();
		void draw();

	private:

		std::vector<Mesh> mMeshes;
		//std::vector<Material> mMaterials;

	};

}