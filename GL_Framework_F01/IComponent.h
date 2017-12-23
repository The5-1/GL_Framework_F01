#pragma once

#include "ForwardDeclarations.h"
#include "ComponentManager.h"

namespace The5 {

	//The Entity owns the Component

	//https://stackoverflow.com/questions/4030224/whats-the-use-of-the-derived-class-as-a-template-parameter
	//this class accepts its own derivate as template parameter

	class IComponent
	{
	public:
		friend ComponentManager;

		std::string name; //TODO: use this if i need more than one component of a type

		IComponent(IComponentProcessor<IComponent>* processor, Entity* parentEntity);

		Entity* getEntity();
		virtual ComponentType getType() = 0; //pure virtual, must be overridden

		~IComponent();

	protected:

		void init();

		void registerAtComponentProcessor();
		void removeFromComponentProcessor();

		void destroy();

		IComponentProcessor<IComponent>* mProcessor;
		Entity* mParentEntity;

		//IComponentProcessor* mProcessor; //static instead
	};
}