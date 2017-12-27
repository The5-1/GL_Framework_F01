#pragma once

#include "stl_include.h"
#include "ForwardDeclarations.h"


namespace The5
{

	/** Abstract Interface for ComponentProcessors
	* - Iterate over all Entities of the Scene
	* - Check if required components are present
	* - Do something with the entity/component
	*/
	class IComponentProcessor
	{
	public:
		///Constructor
		/** constructor*/
		IComponentProcessor(Application* application, ComponentBitmask mask);

		bool checkComponentsCompatible(Entity* entity);

		virtual void processEntity(Entity* entity) = 0;

		virtual void processScene(Scene* scene) = 0;

	protected:
		///private Fields
		/** pointer to owning application */
		Application* mApplication;
		/** the bitmask that needs to be present on the Entity */
		const ComponentBitmask mRequiredComponentBitmask;

		///private Methods
		/** upon construction init the constant bitmask for this Processor */
		virtual ComponentBitmask initRequiredComponentBitmask() = 0;
	};
}

