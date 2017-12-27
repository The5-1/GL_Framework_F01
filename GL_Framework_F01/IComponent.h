#pragma once

#include "ForwardDeclarations.h"
#include "ComponentCommon.h"
#include "ComponentManager.h"

namespace The5 {

	//The Entity owns the Component

	//https://stackoverflow.com/questions/4030224/whats-the-use-of-the-derived-class-as-a-template-parameter
	//this class accepts its own derivate as template parameter


	/** generic Component Interface */
	class IComponent
	{
	public:

		///public fields
		/** User defined object name */
		std::string name;
		
		///Constructor / Destructor
		/** Destructor */
		~IComponent();

		///Methods

		///Getters / Setters
		/** get the pointer to parent Entity */
		Entity* getEntity();
		/** get the Component type of this Component, implemented by derived classes */
		virtual ComponentType getType();

		//virtual IComponentProcessor<IComponent*>* getComponentProcessor();

	protected:

		///friend classes
		/** Entity may call a components constructor to create an component on itself */
		friend class Entity;

		///private Constructor
		/** Constructor requires parent Entity */
		IComponent(Entity* parentEntity);

		///private Fields
		/** pointer to parent Entity this Component resides on */
		Entity* mParentEntity; 
		/** pointer to parent Appliaction to access Systems, derived from mParentEntity */
		Application* mApplication;
		/** relevant bit for this component type */
		ComponentBitmask mComponentBitmask;
		/** Dirty flag if component settings have changed */
		bool mDirty = true;

		///private methods
		/** init the defaults */
		void init();
		/** cleanup for destruction */
		void destroy();
		/** inits this components bitmask once */
		void initBitmask();


		//void registerAtComponentProcessor();
		//void removeFromComponentProcessor();
	};
}
