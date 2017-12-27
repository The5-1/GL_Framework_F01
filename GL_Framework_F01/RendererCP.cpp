#include "RenderableC.h"
#include "Logging.h"
#include "RendererCP.h"
#include "Entity.h"
#include "IComponent.h"
#include "RenderableC.h"

namespace The5 
{
	RendererCP::RendererCP(Application * application) : IComponentProcessor(application, initRequiredComponentBitmask())
	{

	}

	ComponentBitmask RendererCP::initRequiredComponentBitmask()
	{
		ComponentBitmask mask;
		mask.addComponentType(ComponentType::RenderableType);
		return mask;
	}

	void RendererCP::processEntity(Entity * entity)
	{
		if (checkComponentsCompatible(entity))
		{
			//casts into a sub-class must be explicit -> "downcast", upcasts are implicit
			RenderableC* renderable = (RenderableC*)(entity->getComponent(ComponentType::RenderableType));
			draw(renderable);
		}
	}

	void RendererCP::processScene(Scene * scene)
	{
		//for each entity in scene processEntity(e);
	}

	void RendererCP::draw(RenderableC * renderableC)
	{

	}
}