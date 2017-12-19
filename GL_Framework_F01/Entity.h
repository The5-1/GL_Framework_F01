#pragma once

#include "stl_include.h"
#include "GL_include.h"

#include "IComponent.h"


namespace The5 {

	/********************
	For now:
	- we only have one scene
	- if i were to load multiple levels later on, that would be unloading/loading stuff into that one scene
	- fiddling with cache coherency and unloading comes WAY later
	********************/
	
	typedef std::unique_ptr<IComponent> Component_uptr;
	typedef std::vector<Component_uptr> Component_uptrList;

	class Entity;
	typedef std::unique_ptr<Entity> Entity_uptr;
	typedef std::vector<Entity_uptr> Entity_uptrList;

	class Entity
	{
	public:

		std::string name; //some non-unique name

		glm::mat4 transformation; //every entity exists in our scene, but must not be renderable (everything that does not is a global manager)

		Entity(std::string name, Entity* parent);
		Entity* getParent();
		Entity* getChild(unsigned int i);

		void addComponent(IComponent* component);
		IComponent* getComponent(ComponentType type);

	private:
		Entity* mParent;
		Entity_uptrList mChilds; //a entity owns its children, children are destroyed when parent is destroyed

		std::map<ComponentType,Component_uptr> mComponents;

	};

}