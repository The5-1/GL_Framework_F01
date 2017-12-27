#pragma once

#include "stl_include.h"

#include "ForwardDeclarations.h"

namespace The5 {

	enum SceneTraversal { Depth = 1, Breadth = 2 };

	/** Tree structure with root Entity */
	class Scene
	{
	public:
		///public fields
		/** User defined object name */
		std::string name;

		///Constructor / Destructor
		/** Constructor requires pointer to parent application */
		Scene(std::string name, Application* application);

		///Getter / Setter
		/** get pointer to root Entity */
		Entity* getRoot();
		/** get pointer to owning Appliaction */
		Application* getApplication();

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
		/** fixed root entity */
		Entity_uptr mRoot;
		/** a separate root for purely static entities */
		Entity_uptr mRootStatic;
		/** pointer to this Scenes the owning application */
		Application* mApplication;
		/** Breadth or Depth first traversal */
		SceneTraversal traversalMode;
		/** flat Entity List for fast iteration*/
		std::vector<Entity*> mEntitiesList;

		///private methods
		/** init the defaults */
		void init(std::string name);
		/** update the flat list */
		void updateEntityList();


	};
}