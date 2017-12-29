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
		IMaterial* material;
		Mesh* mesh;
		Shader* shader;

		void setMesh(Mesh* mesh);
		void setShader(Shader* shader);

		RenderableC(Entity* parentEntity);
		ComponentType getType();
	
		void draw(double deltaTime);
		void setFlagRecompileShader();

	private:
		friend ComponentFactory;
		friend RendererCP;


		bool flagRecompileShader = false;
		void checkRecompileShader();

		/** parent Appliation */
		Application* mApplication;
	};

}