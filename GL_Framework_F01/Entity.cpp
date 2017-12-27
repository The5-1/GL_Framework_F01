#include "Entity.h"
#include "Scene.h"

#include "stl_include.h"
#include "IComponent.h"
#include "GL_include.h"

#include "Application.h"
#include "ComponentManager.h"


namespace The5 {

	Entity::Entity(std::string name, Entity* parent, Application* application, Scene* scene) : name(name), mParent(parent), mApplication(application), mScene(scene)
	{
		transformation = glm::mat4(1.0f);

		parent = nullptr;
		mComponents = std::map<ComponentType, IComponent_uptr>();
		mChilds = std::vector<Entity_uptr>();
	}

	Entity* Entity::addChild(std::string name)
	{
		Entity* entity = new Entity(name, this, mApplication, mScene);
		mChilds.push_back(Entity_uptr(entity));
		updateSceneEntityTree();
		return entity;
	}

	bool Entity::checkComponentBitmaskCompatible(ComponentBitmask mask)
	{
		return componentBitmask.isCompatible(mask);
	}

	IComponent* Entity::addComponent(ComponentType type)
	{
		IComponent* comp = getComponentManager()->createComponent(type,this);
		mComponents.insert(std::make_pair(comp->getType(), IComponent_uptr(comp)));
		componentBitmask.addComponentType(type);
		return comp;
	}

	IComponent* Entity::getComponent(ComponentType type)
	{
		return this->mComponents.at(type).get();
	}

	ComponentBitmask & const Entity::getComponentBitmask()
	{
		return componentBitmask;
	}

	unsigned int Entity::getComponentCount()
	{
		return this->mComponents.size();
	}

	void Entity::destroyComponent(ComponentType type)
	{
		this->mComponents.erase(type); //underlying component-object will be deleted by unique_ptr;
		componentBitmask.removeComponentType(type);
	}

	ComponentManager * Entity::getComponentManager()
	{
		return mApplication->getComponentManager();
	}

	void Entity::updateSceneEntityTree()
	{
		mScene->updateEntityList();
	}

	Application * Entity::getApplication()
	{
		return mApplication;
	}

	Entity::~Entity()
	{
		updateSceneEntityTree();
	}

	Entity* Entity::getParent()
	{
		return this->mParent;
	}

	std::vector<Entity_uptr> const & Entity::getChilds() const
	{
		return mChilds;
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