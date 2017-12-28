#include "Entity.h"
#include "Scene.h"

#include "stl_include.h"
#include "IComponent.h"
#include "GL_include.h"

#include "Application.h"
#include "ComponentManager.h"


namespace The5 {

	Entity::Entity(std::string name, Application* application, Scene* scene) : name(name), mApplication(application), mScene(scene)
	{
		transformation = glm::mat4(1.0f);

		mComponents = std::unique_ptr<std::map<ComponentType, IComponent_uptr>>(new std::map<ComponentType, IComponent_uptr>());
	}

	std::map<ComponentType, IComponent_uptr>* Entity::getComponents()
	{
		return mComponents.get();
	}

	bool Entity::checkComponentBitmaskCompatible(ComponentBitmask mask)
	{
		return mComponentBitmask.isCompatible(mask);
	}

	IComponent* Entity::addComponent(ComponentType type)
	{
		IComponent* comp = getComponentManager()->createComponent(type,this);
		getComponents()->insert(std::make_pair(comp->getType(), IComponent_uptr(comp)));
		mComponentBitmask.addComponentType(type);
		return comp;
	}

	IComponent* Entity::getComponent(ComponentType type)
	{
		return getComponents()->at(type).get();
	}

	ComponentBitmask & const Entity::getComponentBitmask()
	{
		return mComponentBitmask;
	}

	unsigned int Entity::getComponentCount()
	{
		return getComponents()->size();
	}

	void Entity::destroyComponent(ComponentType type)
	{
		getComponents()->erase(type); //underlying component-object will be deleted by unique_ptr;
		mComponentBitmask.removeComponentType(type);
	}

	ComponentManager * Entity::getComponentManager()
	{
		return mApplication->getComponentManager();
	}

	Application * Entity::getApplication()
	{
		return mApplication;
	}



	
}

/*
	void Entity::updateSceneEntityTree()
	{
		mScene->updateEntityList();
	}

	Entity::~Entity()
	{
		updateSceneEntityTree();
	}


	Entity* Entity::getParent()
	{
		return this->mParent;
	}

	Entity* Entity::addChild(std::string name)
	{
	Entity* entity = new Entity(name, this, mApplication, mScene);
	mChilds.push_back(Entity_uptr(entity));
	updateSceneEntityTree();
	return entity;
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
			
			
			//for (auto const& c : e->mComponents)
			//{
			//	info += std::string(indent+1, ' ') + static_cast<IComponent>(c);
			//}
			

			for (unsigned int i = 0; i < e->getCildCount(); i++)
			{
				info += getEntityInfo(e->getChild(i),indent+1);
			}


			return info;
		}
	}
*/