#include "Scene.h"

#include "stl_include.h"
#include "tree_include.h"

#include "Application.h"
#include "Entity.h"

namespace The5 {

	Scene::Scene(std::string name, Application* application) : name(name), mApplication(application)
	{
		init(name);
	}

	void Scene::init(std::string name)
	{
		std::string rootname = name;
		rootname += "_root";
		Entity* root = new Entity(rootname, mApplication, this);

		//mSceneTree = SceneTree_uptr(new SceneTree(The5::Entity_uptr(root)));
		mSceneTree = SceneTree_uptr(new SceneTree(root));
		mRoot = getSceneTree()->begin();
	}

	SceneTree::iterator Scene::findEntity(Entity * entity)
	{
		SceneTree* s = getSceneTree();
		//SceneTree::iterator location = std::find_if(s->begin(), s->end(), [&](Entity_uptr const& e) {return e.get() == entity;});
		SceneTree::iterator location = std::find(s->begin(), s->end(), entity);
		return location;
	}

	Entity * Scene::addChild(Entity * entity)
	{
		return nullptr;
	}

	Entity * Scene::getIteratorEntity(SceneTree::iterator iter)
	{
		//return iter.node->data.get();
		return iter.node->data;
	}

	SceneTree * Scene::getSceneTree()
	{
		return mSceneTree.get();
	}

	Entity* Scene::getRoot()
	{
		return getIteratorEntity(mRoot);
	}

	Application * Scene::getApplication()
	{
		return mApplication;
	}

}

/*
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
*/

