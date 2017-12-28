#pragma once

#include "stl_include.h"
#include "GL_include.h"
#include "tree_include.h"

#include "ForwardDeclarations.h"
#include "ComponentCommon.h"
#include "IComponent.h"


namespace The5 {

	/********************
	For now:
	- we only have one scene
	- if i were to load multiple levels later on, that would be unloading/loading stuff into that one scene
	- fiddling with cache coherency and unloading comes WAY later
	********************/
	
	/** Entity / Node of the SceneTree, holds Components */
	class Entity
	{
	public:
		///public Fields
		/** unique ID*/
		unsigned int ID;
		/** user defined name for the entity*/
		std::string name;	

		///Destructor
		/** destructor triggers the scene to update */
		//~Entity();
		//Entity(const Entity&) = delete;
		//Entity& operator=(const Entity&) = delete;
		//~Entity() = default;


		///transformation
		/** every node got a local transformation */
		mat4 transformation;
		/** the combined resulting transformation matrix, only updated when a parent changes */
		mat4 transformation_cached;

		///Methods: Components
		/** return a raw pointer to the components map */
		std::map<ComponentType, IComponent_uptr>* getComponents();
		/** get the number of components on this entity*/
		unsigned int getComponentCount();
		/** get a pointer to the component of the given type*/
		IComponent* getComponent(ComponentType type);
		/** add a new coponent to this entity*/
		IComponent* addComponent(ComponentType type);
		/** destroy a existing component on this entity*/
		void destroyComponent(ComponentType type);
		/** get a readonly reference of the bitmask*/
		ComponentBitmask& const getComponentBitmask();
		/** check if the given bitmaks matches the components on this Entity */
		bool checkComponentBitmaskCompatible(ComponentBitmask mask);

		///Methods: Application
		/** get parent application (to traverse to other systems from there on*/
		Application* getApplication();
		/** get the component manager to create components*/
		ComponentManager* getComponentManager();

	protected:
		///friend classes
		friend Scene;
		///private Constructor
		/** A Scene may construct one root node, otherwise the constructor is private */
		Entity(std::string name, Application* application, Scene* Scene);
		///private Methods
		/** updates the Scenes Entity List, called when Entities are added or removed */
		//void updateSceneEntityTree();

		///private Fields
		/** dirty flag if entity or components have changed */
		bool mDirty = true;
		/** Bitmask signature of components on this Entity, updated when components are added or removed */
		ComponentBitmask mComponentBitmask;
		/** parent Appliaction */
		Application* mApplication;
		/** Scene */
		Scene* mScene;
		/** pointer to parent scene tree */
		//SceneTree* sceneTree;
		/** attached components */
		std::unique_ptr<std::map<ComponentType,IComponent_uptr>> mComponents;

	};

}

