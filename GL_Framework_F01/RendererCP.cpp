#include "Logging.h"

#include "IComponent.h"
#include "RendererCP.h"
#include "RenderableC.h"
#include "Entity.h"


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

	void RendererCP::doProcessing(Entity * entity)
	{
		if (entity->getComponent(ComponentType::RenderableType) == nullptr) return;
		RenderableC* renderable = (RenderableC*)(entity->getComponent(ComponentType::RenderableType));
		draw(renderable, entity);
	}

	/*
	void RendererCP::processScene(Scene * scene)
	{
		//for each entity in scene processEntity(e);
	}
	*/

	void RendererCP::draw(RenderableC * renderableC, Entity* entity)
	{
		LOG("Rendering Entity \"" << entity->name << "\"");
	}
}