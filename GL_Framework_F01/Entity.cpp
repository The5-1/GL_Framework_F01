#include "Entity.h"

#include "stl_include.h"
#include "IComponent.h"
#include "GL_include.h"

namespace The5 {

	Entity::Entity(std::string name, Entity* parent) : name(name), mParent(parent)
	{
		transformation = glm::mat4(1.0f);

		parent = nullptr;
		mComponents = std::map<ComponentType, Component_uptr>();
		mChilds = Entity_uptrList();
	}

	void Entity::addComponent(IComponent* component)
	{
		this->mComponents.insert(std::make_pair(component->getType(),Component_uptr(component)));
	}

	IComponent* Entity::getComponent(ComponentType type)
	{
		return this->mComponents.at(type).get();
	}

	Entity* Entity::getParent()
	{
		return this->mParent;
	}

	Entity* Entity::getChild(unsigned int i)
	{
		return this->mChilds.at(i).get();
	}



}