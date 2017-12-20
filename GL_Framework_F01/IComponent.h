#pragma once

#include "ForwardDeclarations.h"

namespace The5 {

	///The Entity owns the Component
	class IComponent
	{
	public:

		IComponent(Entity* entity);

		virtual ComponentType getType() = 0;

		Entity* getParent();

		virtual void update() = 0;

	private:
		Entity* mParentEntity;
	};

}