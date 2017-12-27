#pragma once

#include "stl_include.h"
#include "GL_include.h"

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
		~Entity();

		///transformation
		/** every node got a local transformation */
		mat4 transformation;
		/** the combined resulting transformation matrix, only updated when a parent changes */
		mat4 transformation_cached;

		///Methods: Entity Tree
		/** get the parent Entity in the tree */
		Entity* getParent();
		/** add a new Entity to this Entities childs list */
		Entity* addChild(std::string name);
		/** get child Entity by index */
		Entity* getChild(unsigned int i);
		/** get number of childs */
		unsigned int getCildCount();
		/** get a readonly uptr list of all childs */
		std::vector<Entity_uptr> const& getChilds() const; //https://stackoverflow.com/a/25507647
		/** Entity to string with depth parameter for formated printing */
		static std::string getEntityInfo(Entity * e, unsigned int depth);

		///Methods: Components
		/** check if the given bitmaks matches the components on this Entity */
		bool checkComponentBitmaskCompatible(ComponentBitmask mask);
		/** get a readonly reference of the bitmask*/
		ComponentBitmask& const getComponentBitmask();
		/** add a new coponent to this entity*/
		IComponent* addComponent(ComponentType type);
		/** destroy a existing component on this entity*/
		void destroyComponent(ComponentType type);
		/** get the number of components on this entity*/
		unsigned int getComponentCount();
		/** get a pointer to the component of the given type*/
		IComponent* getComponent(ComponentType type);

		///Methods: Application
		/** get parent application (to traverse to other systems from there on*/
		Application* getApplication();
		/** get the component manager to create components*/
		ComponentManager* getComponentManager();

	private:
		///friend classes
		friend Scene;
		///private Constructor
		/** A Scene may construct one root node, otherwise the constructor is private */
		Entity(std::string name, Entity* parent, Application* application, Scene* Scene);

		///private Methods
		/** updates the Scenes Entity List, called when Entities are added or removed */
		void updateSceneEntityTree();

		///private Fields
		/** bitmask updated when components are added */
		ComponentBitmask componentBitmask;
		/** dirty flag if entity or components have changed */
		bool mDirty = true;
		/** Bitmask signature of components on this Entity */
		ComponentBitmask mComponentBitmask;
		/** parent Appliaction */
		Application* mApplication;
		/** Scene */
		Scene* mScene;
		/** parent Entity of this Entity */
		Entity* mParent;
		/** child Entities owned by this Entity */
		std::vector<Entity_uptr> mChilds;
		/** attached components */
		std::map<ComponentType,IComponent_uptr> mComponents;

	};

}

