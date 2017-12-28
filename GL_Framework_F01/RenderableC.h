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
		Mesh* mesh;
		Shader* shader;

		void setMesh(Mesh* mesh);
		void setShader(Shader* shader);

		RenderableC(Entity* parentEntity);
		ComponentType getType();
	

		void draw(double deltaTime);

	private:
		friend ComponentFactory;
		friend RendererCP;

		Application* mApplication;

		///Assets used by renderable are owned by global Asset Manager
		//std::vector<Mesh> mMeshes;
		//std::vector<Material> mMaterials;

	};

}