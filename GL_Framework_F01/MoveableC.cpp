#include "MoveableC.h"

namespace The5
{
	MoveableC::MoveableC(Entity * entity) : IComponent(entity)
	{

	}

	ComponentType MoveableC::getType()
	{
		return ComponentType::RenderableType;
	}

	void MoveableC::registerAtComponentProcessor()
	{
		//RendererCP::registerComponentPointer(this);
	}

	void MoveableC::removeFromComponentProcessor()
	{
		//RendererCP::removeComponentPointer(this);
	}

}
