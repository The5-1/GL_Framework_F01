#include "ComponentFactory.h"

#include "RenderableC.h"
#include "MoveableC.h"

namespace The5
{
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
			return new MoveableC(entity);
		}

	}
}