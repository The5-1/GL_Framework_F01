#include "RenderableC.h"
#include "RendererCP.h"

#include "GL_include.h"

#include "Entity.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"


namespace The5 
{
	RenderableC::RenderableC(Entity* parentEntity): IComponent(parentEntity)
	{
		name = "RenderableC";
		mDirty = true; //renderables are always dirty
		init();
	}

	ComponentType RenderableC::getType()
	{
		return ComponentType::RenderableType;
	}

	void RenderableC::setMesh(Mesh * mesh)
	{
		this->mesh = mesh;
	}

	void RenderableC::setShader(Shader * shader)
	{
		this->shader = shader;
	}


	void RenderableC::draw(double deltaTime)
	{
		if(shader != nullptr) shader->use();
		if(mesh != nullptr) mesh->draw();
	}
}