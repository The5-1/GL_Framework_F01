#include "ComponentFactory.h"

#include "RenderableC.h"

//#include "RendererCP.h"
//#include "MoveableC.h"

namespace The5
{
	ComponentFactory::ComponentFactory(Application * application) : mApplication(application)
	{

	}

	IComponent* The5::ComponentFactory::createComponent(ComponentType type, Entity* entity)
	{
		switch (type) {
		default:
		{
			return nullptr;
		}
		case (ComponentType::RenderableType):
		{
			return new RenderableC(entity);
		}
		case (ComponentType::MoveableType):
			return nullptr;
			//return new MoveableC(entity);
		}

	}
	
	/*
	//TODO: Problem: Templates are differenc classes at runtime! IComponentProcessor<IComponent> got nothing to do with IComponentProcessor<RenderableC>
	IComponentProcessor<IComponent*>* ComponentFactory::getComponentProcessor(ComponentType type)
	{
		switch (type) {
		default:
		{
			return nullptr;
		}
		case (ComponentType::RenderableType):
		{
			return (IComponentProcessor<IComponent*>*)mRendererCP.get();
		}
		case (ComponentType::MoveableType):
			return nullptr;
		}
	}
	*/
}