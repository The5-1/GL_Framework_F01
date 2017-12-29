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
		IComponentProcessor(Application* application, ComponentBitmask mask, double updateRate);

		virtual ComponentProcessorType getType() = 0;

		/** checks wether the component bitmask of an entity matches the one required by this Processor */
		bool checkComponentsCompatible(Entity* entity);

		/** iterates the scene, checks entities and processes them */
		void processScene(Scene* scene, double deltaTime);

		/** performs the check and if it passes, processes the entity */
		void processEntity(Entity* entity, double deltaTime);

	protected:
		///private Fields
		/** the time in seconds at witch this processor is supposed to update e.g. 1.0/60.0. !!! 0.0 means always !!! */
		double updateRate = 0.0;
		/** timer that stores the deltas, only set when updateRate != 0.0 */
		double accumulatedUpdateTime = 0.0;
		/** pointer to owning application */
		Application* mApplication;
		/** the bitmask that needs to be present on the Entity */
		const ComponentBitmask mRequiredComponentBitmask;
		///private Methods
		/** upon construction init the constant bitmask for this Processor */
		virtual ComponentBitmask initRequiredComponentBitmask() = 0;
		/** processes a compatible entity */
		virtual void doProcessing(Entity* entity, double deltaTime) {};

	};
}

