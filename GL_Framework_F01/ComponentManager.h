#pragma once

#include "ForwardDeclarations.h"

#include "IComponent.h"

namespace The5
{
	/** factory for components, managing where applicable */
	class ComponentManager
	{
	protected:
		friend Application;
		friend Entity;
		friend IComponent;

		/** Component Factory*/
		IComponent* createComponent(ComponentType type, Entity* entity);

		/** private constructor*/
		ComponentManager(Application* application);

		/** pointer to parent appliaction to get other systems from*/
		Application* mApplication;
	};

}
