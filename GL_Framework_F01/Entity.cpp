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
		IComponent* comp = ComponentManager::createComponent(type,this);
		mComponents.insert(std::make_pair(comp->getType(), IComponent_uptr(comp)));
		return comp;
	}

	IComponent* Entity::getComponent(ComponentType type)
	{
		return this->mComponents.at(type).get();
	}

	unsigned int Entity::getComponentCount()
	{
		return this->mComponents.size();
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

	unsigned int Entity::getCildCount()
	{
		return this->mChilds.size();
	}

	std::string Entity::getEntityInfo(Entity* e, unsigned int indent)
	{
		if (e != nullptr)
		{
			std::string info = "";

			info += std::string(indent, ' ') + e->name + " [Entity] : ";
			info += std::to_string(e->getComponentCount()) + " [Components]";
			info += "\n";
			
			/*
			for (auto const& c : e->mComponents)
			{
				info += std::string(indent+1, ' ') + static_cast<IComponent>(c);
			}
			*/

			for (unsigned int i = 0; i < e->getCildCount(); i++)
			{
				info += getEntityInfo(e->getChild(i),indent+1);
			}


			return info;
		}
	}


}