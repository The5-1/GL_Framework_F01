#include "IComponent.h"
#include "IComponentProcessor.h"
#include "ComponentManager.h"

#include "Entity.h"
#include "Application.h"

namespace The5 {

	IComponent::IComponent(Entity* entity) : mParentEntity(entity)
	{
		init();
	}

	Entity* IComponent::getEntity()
	{
		return mParentEntity;
	}

	ComponentType IComponent::getType()
	{
		return ComponentType::none;
	}

	IComponentProcessor<IComponent>* IComponent::getComponentProcessor()
	{
		return mApplication->getComponentManager()->getComponentProcessor(getType()); //TODO: implement
	}

	void IComponent::init()
	{
		mApplication = mParentEntity->getApplication();
		registerAtComponentProcessor();
	}

	void IComponent::registerAtComponentProcessor()
	{
		getComponentProcessor()->registerComponentPointer(this);
	}

	void IComponent::removeFromComponentProcessor()
	{
		getComponentProcessor()->removeComponentPointer(this);
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