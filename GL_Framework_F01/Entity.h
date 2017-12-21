#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "ForwardDeclarations.h"
#include "IComponent.h"


namespace The5 {

	/********************
	For now:
	- we only have one scene
	- if i were to load multiple levels later on, that would be unloading/loading stuff into that one scene
	- fiddling with cache coherency and unloading comes WAY later
	********************/
	
	class Entity
	{
	public:
		friend Scene;

		unsigned int ID; //

		std::string name; //some non-unique name	

		mat4 transformation; //every entity exists in our scene, but must not be renderable (everything that does not is a global manager)

		Entity* addChild(std::string name);
		void addChild(Entity* entity);
		Entity* getParent();
		Entity* getChild(unsigned int i);
		unsigned int getCildCount();

		static std::string getEntityInfo(Entity * e, unsigned int depth);

		IComponent* addComponent(ComponentType type);
		IComponent* getComponent(ComponentType type);
		unsigned int getComponentCount();
		void destroyComponent(ComponentType type);

	private:

		///A Scene may construct one root node, otherwise the constructor is private
		Entity(std::string name, Entity* parent);

		Entity* mParent;
		std::vector<Entity_uptr> mChilds; //a entity owns its children, children are destroyed when parent is destroyed

		std::map<ComponentType,IComponent_uptr> mComponents;


		void addComponent(IComponent* component);

	};

}