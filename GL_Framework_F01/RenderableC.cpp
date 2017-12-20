#include "RenderableC.h"

#include "GL_include.h"

#include "Entity.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"



namespace The5 {

	RenderableC::RenderableC(Entity* entity) : IComponent(entity)
	{
		
	}

	ComponentType RenderableC::getType()
	{
		return ComponentType::RenderableType;
	}

	void RenderableC::update()
	{
		//TODO
	}

	void RenderableC::draw()
	{

	}
}