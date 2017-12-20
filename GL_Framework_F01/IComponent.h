#pragma once

#include "ForwardDeclarations.h"
#include "ComponentFactory.h"

namespace The5 {

	///The Entity owns the Component
	class IComponent
	{
	public:
		friend ComponentFactory;

		std::string name; //TODO: use this if i need more than one component of a type

		Entity* getEntity();
		virtual ComponentType getType() = 0; //pure virtual, must be overridden

		~IComponent();

	protected:
		IComponent(Entity* entity);

		virtual void registerAtComponentProcessor() {}; //may not be pure virtual since we call it in the constructor
		virtual void removeFromComponentProcessor() {}; //may not be pure virutal since we call it in the destructor

		void destroy();

		Entity* mParentEntity;
		//IComponentProcessor* mProcessor; //static instead
	};
}