#include "Renderable.h"

#include "Entity.h"

#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"

#include "GL_include.h"

namespace The5 {

	Renderable::Renderable(Entity* entity) : IComponent(entity)
	{
		
	}

	ComponentType Renderable::getType()
	{
		return ComponentType::Renderable;
	}

	void Renderable::update()
	{
		//TODO
	}

	void Renderable::draw()
	{

	}
}