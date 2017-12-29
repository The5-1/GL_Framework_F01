#include "Logging.h"
#include "IComponent.h"
#include "IComponentProcessor.h"
#include "ComponentFactory.h"

#include "Entity.h"
#include "Application.h"

namespace The5 {

	IComponent::IComponent(Entity* entity) : mParentEntity(entity)
	{
		/** !! init must not be called here but in the derived class!! */
	}

	Entity* IComponent::getEntity()
	{
		return mParentEntity;
	}

	/*
	ComponentType IComponent::getType()
	{
		return ComponentType::none;
	}
	*/

	//IComponentProcessor<IComponent*>* IComponent::getComponentProcessor()
	//{
	//	return mApplication->getComponentFactory()->getComponentProcessor(getType()); //TODO: implement
	//}

	void IComponent::init()
	{
		mApplication = mParentEntity->getApplication();
		initBitmask();
		//registerAtComponentProcessor();
	}

	//void IComponent::registerAtComponentProcessor()
	//{
	//	getComponentProcessor()->registerComponentPointer(this);
	//}
	
	//void IComponent::removeFromComponentProcessor()
	//{
	//	getComponentProcessor()->removeComponentPointer(this);
	//}

	void IComponent::destroy()
	{
		//removeFromComponentProcessor();
		//all owned entities destructors are called due to unique_ptr!
	}

	void IComponent::initBitmask()
	{
		mComponentBitmask |= getType();
		//LOG(mComponentBitmask.to_string());
	}

	IComponent::~IComponent()
	{
		destroy();
	}
}