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
		unsigned int ID;

		std::string name; //some non-unique name	

		mat4 transformation; //every entity exists in our scene, but must not be renderable (everything that does not is a global manager)
		mat4 transformation_cached; //every entity exists in our scene, but must not be renderable (everything that does not is a global manager)

		Entity* addChild(std::string name);
		void addChild(Entity* entity);

		Entity* getParent();
		std::vector<Entity_uptr> const& getChilds() const; //https://stackoverflow.com/a/25507647
		Entity* getChild(unsigned int i);
		unsigned int getCildCount();

		static std::string getEntityInfo(Entity * e, unsigned int depth);

		IComponent* addComponent(ComponentType type);
		IComponent* getComponent(ComponentType type);
		unsigned int getComponentCount();
		void destroyComponent(ComponentType type);

		Application* getApplication();
		ComponentManager* getComponentManager();

	private:
		///friend classes
		friend Scene;
		///private Constructor
		/** A Scene may construct one root node, otherwise the constructor is private */
		Entity(std::string name, Entity* parent, Application* application, Scene* Scene);

		///private Fields
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

