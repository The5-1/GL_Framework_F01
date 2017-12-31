#if 0

#include "MoveableC.h"

namespace The5
{
	MoveableC::MoveableC(Entity * entity) : IComponent(entity)
	{

	}

	ComponentType MoveableC::getType()
	{
		return ComponentType::RenderableCType;
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

#endif
