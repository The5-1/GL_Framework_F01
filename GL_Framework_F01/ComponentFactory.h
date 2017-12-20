#pragma once

#include "ForwardDeclarations.h"

#include "IComponent.h"
#include "IComponentProcessor.h"

namespace The5
{

	class ComponentFactory
	{
	public:
		static IComponent* createComponent(ComponentType type, Entity* entity);
	private:

	};

}
