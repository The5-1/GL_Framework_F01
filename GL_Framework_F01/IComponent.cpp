#include "IComponent.h"

#include "Entity.h"


namespace The5 {

	IComponent::IComponent(Entity* entity) : parentEntity(entity) 
	{

	}

}