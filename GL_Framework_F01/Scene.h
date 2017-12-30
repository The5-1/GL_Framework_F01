#pragma once

#include "stl_include.h"

#include "ForwardDeclarations.h"

namespace The5 {

	enum SceneTraversal { Depth = 1, Breadth = 2 };

	//Iterate over sets of unique_ptr -> double dereference
	//https://stackoverflow.com/questions/8237502/iterating-over-a-container-of-unique-ptrs
	//using std::find_if on a set of unique_ptr
	//https://stackoverflow.com/questions/16767623/searching-a-set-of-unique-pointers

	/** Tree structure using tree.hh library */
	class Scene
	{
	public:
		///public fields
		/** User defined object name */
		std::string name;

		///Constructor / Destructor
		/** Constructor requires pointer to parent application */
		Scene(std::string name, Application* application);

		///Methods	
		SceneTree::iterator findEntity(Entity* entity);
		Entity* getEntityFromIterator(SceneTree::iterator iter);

		Entity* addChild(Entity * parent, std::string name);
		void removeEntityAndChilds(Entity* entity);
		void removeChilds(Entity* entity);
		Entity* getParent(Entity* entity);

		///Getter / Setter
		/** get pointer to SceneTree */
		SceneTree* getSceneTree();
		/** get pointer to root Entity */
		Entity* getRoot();
		/** get pointer to owning Appliaction */
		Application* getApplication();

		///Helper Methods
		/** writes the sceneTree hirarcy to a std::String */
		std::string getInfo(bool showComponents = true);

		/*
		class iterator : public std::iterator<std::forward_iterator_tag, Entity*>
		{
			Entity* currentNode;
			std::deque<Entity*> nodesToVisit;
			SceneTraversal traversalMode;

		public:
			explicit iterator(Entity* start, SceneTraversal mode) :traversalMode(mode) 
			{
				nodesToVisit.push_back(start);
			};

			iterator& operator++()
			{
				currentNode = nodesToVisit.front(); //take first
				nodesToVisit.pop_front(); //and delete it

				if (traversalMode == SceneTraversal::Depth)
				{
					//depth first = prepend
					nodesToVisit.insert(nodesToVisit.begin(), currentNode->getChilds().begin(), currentNode->getChilds().end());
				}
				else if (traversalMode == SceneTraversal::Breadth)
				{
					//breadth first = append
					nodesToVisit.insert(nodesToVisit.end(), currentNode->getChilds().begin(), currentNode->getChilds().end());
				}
				return *this;
			};

			bool operator==(iterator other) const 
			{
				return currentNode == other.currentNode;
			}

			reference operator*() const { 
				return currentNode; 
			}
		};

		iterator begin() { return iterator(getRoot(),traversalMode); };
		iterator end() { return iterator(nullptr,traversalMode); };
		*/

	private:
		friend Entity;

		///private Fields
		/** Tree Structure from tree.hh*/
		SceneTree_uptr mSceneTree;
		/** shortcut to root entity */
		SceneTree::iterator mRoot;
		/** TODO: possibly provide a separate root for different types of entities*/
		SceneTree::iterator mRootDynamic;
		SceneTree::iterator mRootStatic;
		SceneTree::iterator mRootManagers;
		/** pointer to this Scenes the owning application */
		Application* mApplication;
		/** Breadth or Depth first traversal */
		SceneTraversal traversalMode;
		/** flat Entity List for fast iteration*/
		std::vector<Entity*> mEntitiesList;

		///private methods
		/** init the defaults */
		void init(std::string name);
		/** creates a new entity */
		Entity* createEntity(std::string name);

	};
}