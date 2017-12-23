#pragma once

//#include "stl_include.h"
//#include "GL_include.h"

#include "ForwardDeclarations.h"
#include "IComponent.h"

namespace The5 {

	//public Base inheritance = allows casting and automatically calls base constructor

	class RenderableC: public IComponent
	{
	public:
		friend ComponentManager;

		RenderableC(IComponentProcessor<IComponent>* processor, Entity* parentEntity);

		ComponentType getType();

		Mesh* mesh;
		Shader* shader;

		void draw();

	private:

		///Assets used by renderable are owned by global Asset Manager
		//std::vector<Mesh> mMeshes;
		//std::vector<Material> mMaterials;

	};

}