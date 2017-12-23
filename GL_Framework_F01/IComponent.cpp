#include "IComponent.h"
#include "IComponentProcessor.h"

#include "Entity.h"

namespace The5 {

	IComponent::IComponent(IComponentProcessor<IComponent>* processor, Entity* entity) : mProcessor(processor), mParentEntity(entity)
	{
		init();
	}

	Entity* IComponent::getEntity()
	{
		return mParentEntity;
	}

	void IComponent::init()
	{
		registerAtComponentProcessor();
	}

	void IComponent::registerAtComponentProcessor()
	{
		mProcessor->registerComponentPointer(this);
	}

	void IComponent::removeFromComponentProcessor()
	{
		mProcessor->removeComponentPointer(this);
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