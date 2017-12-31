#pragma once
#include "ForwardDeclarations.h"
#include "GL_include.h"
#include "IComponentProcessor.h"

namespace The5 {

	/** Proecessor that walks over all timer Components and increments them */
	class TimerCP : public IComponentProcessor
	{
	public:

		///public Fields
		/** name */
		std::string name;
		/** documentation */

		///Constructor / Destructor
		/** Constructor */
		TimerCP() = default;
		/** Destructor */
		~TimerCP() = default;

		///Getters / Setters
		/** implement pure virtual get Type */
		ComponentProcessorType getType() override { return ComponentProcessorType::TimerCPType; };

		///Methods
		/** documentation */

	protected:
		///friend classes
		/** documentation */

		///private Constructor
		/** documentation */

		///private Fields
		/** documentation */

		///private Methods
		/** upon construction init the constant bitmask for this Processor */
		ComponentBitmask initRequiredComponentBitmask() override;
		/** processes a compatible entity */
		void doProcessing(Entity* entity, double deltaTime) override;

	};
}