#include "ComponentManager.h"

#include "RenderableC.h"
//#include "MoveableC.h"

namespace The5
{
	ComponentManager::ComponentManager(Application * application) : application(application)
	{

	}

	IComponent* The5::ComponentManager::createComponent(ComponentType type, Entity* entity)
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

	IComponentProcessor<IComponent>* ComponentManager::getComponentProcessor(ComponentType type)
	{
		switch (type) {
		default:
		{
			return nullptr;
		}
		case (ComponentType::RenderableType):
		{
			return mRendererCP.get();
		}
		case (ComponentType::MoveableType):
			return nullptr;
		}
	}
}