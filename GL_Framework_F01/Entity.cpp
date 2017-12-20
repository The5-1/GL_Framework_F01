#include "Entity.h"

#include "stl_include.h"
#include "IComponent.h"
#include "GL_include.h"

#include "ComponentFactory.h"

namespace The5 {

	Entity::Entity(std::string name, Entity* parent) : name(name), mParent(parent)
	{
		transformation = glm::mat4(1.0f);

		parent = nullptr;
		mComponents = std::map<ComponentType, IComponent_uptr>();
		mChilds = std::vector<Entity_uptr>();
	}

	Entity* Entity::addChild(std::string name)
	{
		Entity* entity = new Entity(name, this);
		mChilds.push_back(Entity_uptr(entity));
		return entity;
	}

	void Entity::addComponent(IComponent* component)
	{
		this->mComponents.insert(std::make_pair(component->getType(),IComponent_uptr(component)));
	}

	IComponent* Entity::addComponent(ComponentType type)
	{
		return ComponentFactory::createComponent(type,this);
	}

	IComponent* Entity::getComponent(ComponentType type)
	{
		return this->mComponents.at(type).get();
	}

	void Entity::destroyComponent(ComponentType type)
	{
		this->mComponents.erase(type); //underlying component-object will be deleted by unique_ptr;
	}

	Entity* Entity::getParent()
	{
		return this->mParent;
	}

	void Entity::addChild(Entity* entity)
	{
		mChilds.push_back(Entity_uptr(entity));
	}

	Entity* Entity::getChild(unsigned int i)
	{
		return this->mChilds.at(i).get();
	}



}