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

	Entity * Scene::createEntity(std::string name)
	{
		Entity* e = new Entity(name, getApplication(), this);
		return e;
	}

	void Scene::init(std::string name)
	{
		std::string rootname = name;
		rootname += "_root";
		Entity* root = createEntity(rootname);

		//mSceneTree = SceneTree_uptr(new SceneTree(The5::Entity_uptr(root)));
		mSceneTree = SceneTree_uptr(new SceneTree(root));
		mRoot = getSceneTree()->begin();
	}

	SceneTree::iterator Scene::findEntity(Entity* entity)
	{
		SceneTree* s = getSceneTree();
		//SceneTree::iterator location = std::find_if(s->begin(), s->end(), [&](Entity_uptr const& e) {return e.get() == entity;});
		SceneTree::iterator location = std::find(s->begin(), s->end(), entity);
		return location;
	}

	Entity * Scene::addChild(Entity * parent, std::string name)
	{
		SceneTree::iterator location = findEntity(parent);
		Entity* e = createEntity(name);
		getSceneTree()->append_child(location, e);
		return e;
	}

	void Scene::removeChilds(Entity * entity)
	{
		//TODO: ??? i hope this library actually calls the destructor ???
		SceneTree::iterator location = findEntity(entity);
		getSceneTree()->erase_children(location); //only removes childs
	}

	void Scene::removeEntityAndChilds(Entity * entity)
	{
		//TODO: ??? i hope this library actually calls the destructor ???
		SceneTree::iterator location = findEntity(entity);
		getSceneTree()->erase(location); //removes parent and childs
	}

	Entity * Scene::getParent(Entity * entity)
	{
		SceneTree::iterator location = findEntity(entity);
		if (location == getSceneTree()->begin()) return entity;
		else
		{
			location--;
			return getEntityFromIterator(location);
		}
	}

	Entity * Scene::getEntityFromIterator(SceneTree::iterator iter)
	{
		//return iter.node->data.get();
		return iter.node->data;
	}

	SceneTree* Scene::getSceneTree()
	{
		return mSceneTree.get();
	}

	Entity* Scene::getRoot()
	{
		return getEntityFromIterator(mRoot);
	}

	Application * Scene::getApplication()
	{
		return mApplication;
	}

	std::string Scene::getInfo(bool showComponents)
	{
		//printing unicode requires wstring and wcout
		//https://en.wikipedia.org/wiki/Box-drawing_character
		//const wchar_t TB = L'\x2550';
		//const wchar_t LR = L'\x2551';
		//const wchar_t TL = L'\x2554';
		//const wchar_t TR = L'\x2557';
		//const wchar_t BL = L'\x255A';
		//const wchar_t BR = L'\x255D';

		std::stringstream ss;
		std::string header("Tree for Scene: \"" + name + "\"");
		unsigned int headerSize = header.size()+4;
		//ss << "Tree for Scene: \"" << name << "\"" << std::endl;
		//unsigned int headerSize = ss.str().size() - 1;
		ss << std::endl;
		ss << std::string(headerSize, '=') << std::endl;
		ss << "| " << header << " |" <<std::endl;
		ss << std::string(headerSize, '-') << std::endl;
		for (SceneTree::iterator it = getSceneTree()->begin(); it != getSceneTree()->end(); ++it)
		{
			unsigned int depth = SceneTree::depth(it);
			unsigned int children = it.number_of_children();

			Entity* e = it.node->data;
			std::string connector;
#if 0
			if (depth > 0)
			{

				connector = std::string(depth - 1, ' ');
				if (it.node->next_sibling != nullptr) connector += "+";
				else connector += "-";

				if (children > 0) connector += "+";
				else connector += "-";
			}
#elif 0
			connector += std::to_string(depth);
			connector += ") ";
#else
			connector = std::string(depth, ' ');
#endif
			
			std::string components;
			if (showComponents)
			{
				components = ":[";
				for (auto compIt = e->getComponents()->begin(); compIt != e->getComponents()->end(); ++compIt)
				{
					components += compIt._Ptr->_Myval.second.get()->name;
					if(compIt != std::prev(e->getComponents()->end())) components += ", ";
				}
				components += "]";
			}
			ss << "| " << connector << it.node->data->name << components << std::endl;
		}
		ss << std::string(headerSize, '=') << std::endl;
		return ss.str();
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

