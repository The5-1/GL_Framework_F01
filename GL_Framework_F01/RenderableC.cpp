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
	RenderableC::RenderableC(RendererCP* processor, Entity* parentEntity): IComponent(processor,parentEntity)
	{

	}

	ComponentType RenderableC::getType()
	{
		return ComponentType::RenderableType;
	}
}