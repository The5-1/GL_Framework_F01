#pragma once

//#include "stl_include.h"
//#include "GL_include.h"

#include "ForwardDeclarations.h"
#include "IComponent.h"
#include "IMaterial.h"

namespace The5 {

	//public Base inheritance = allows casting and automatically calls base constructor

	class RenderableC: public IComponent
	{
	public:
		IMaterial* material;
		Mesh* mesh;
		//Shader* shader;

		void setMesh(Mesh* mesh);
		//void setShader(Shader* shader);
		void setMaterial(IMaterial* material);

		RenderableC(Entity* parentEntity);

		ComponentType getType();
	
		void draw(double deltaTime);
		void setRecompileShader();

	private:
		friend ComponentFactory;
		friend RendererCP;


		bool flagRecompileShader = false;
		void checkRecompileShader();

		/** parent Appliation */
		Application* mApplication;
	};

}