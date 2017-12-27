#include "Scene.h"

#include "stl_include.h"

#include "Application.h"
#include "Entity.h"

namespace The5 {

	Scene::Scene(std::string name, Application* application) : name(name), mApplication(application)
	{
		init(name);
	}

	Entity* Scene::getRoot()
	{
		return this->mRoot.get();
	}

	Application * Scene::getApplication()
	{
		return mApplication;
	}

	void Scene::init(std::string name)
	{
		std::string rootname = name;
		rootname += "_root";
		mRoot = The5::Entity_uptr(new Entity(rootname, nullptr, mApplication, this));
	}

	void Scene::updateEntityList()
	{
		mEntitiesList.clear();

		std::deque<Entity*> nodesToVisit;
		nodesToVisit.push_back(getRoot());

		while (!nodesToVisit.empty()) {

			Entity* current = nodesToVisit.front(); //take first
			nodesToVisit.pop_front(); //and delete it

			//https://techoverflow.net/2012/09/17/c11-iterate-over-smart-pointers-using-foreach-loop/

			if (traversalMode == SceneTraversal::Depth)
			{
				//depth first = prepend
				for (unsigned int i = current->getChilds().size(); i >= 0; i--)
				{
					nodesToVisit.push_front(current->getChild(i));
				}
				//nodesToVisit.insert(nodesToVisit.begin(), current->getChilds().begin(), current->getChilds().end());
			}
			else if (traversalMode == SceneTraversal::Breadth)
			{
				//breadth first = append
				for (unsigned int i = 0; i < current->getChilds().size(); i++)
				{
					nodesToVisit.push_back(current->getChild(i));
				}
				//nodesToVisit.insert(nodesToVisit.end(), current->getChilds().begin(), current->getChilds().end());
			}

			mEntitiesList.push_back(current);
		}
	}

	

}
