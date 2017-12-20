#include "IComponent.h"

#include "Entity.h"

namespace The5 {

	IComponent::IComponent(Entity* entity) : mParentEntity(entity) {}


	Entity* IComponent::getParent()
	{
		return mParentEntity;
	}

}