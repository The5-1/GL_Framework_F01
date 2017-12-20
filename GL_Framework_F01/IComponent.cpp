#include "IComponent.h"
#include "IComponentProcessor.h"

#include "Entity.h"

namespace The5 {

	IComponent::IComponent(Entity* entity) : mParentEntity(entity) 
	{
		registerAtComponentProcessor();
	}

	Entity* IComponent::getEntity()
	{
		return mParentEntity;
	}

	void IComponent::destroy()
	{
		removeFromComponentProcessor();
		//all owned entities destructors are called due to unique_ptr!
	}

	IComponent::~IComponent()
	{
		destroy();
	}
}