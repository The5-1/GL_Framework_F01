#include "IComponent.h"
#include "IComponentProcessor.h"

#include "Entity.h"

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
		return nullptr;
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