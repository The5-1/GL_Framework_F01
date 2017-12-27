#pragma once

#include "ForwardDeclarations.h"
#include "ComponentCommon.h"
#include "IComponent.h"

namespace The5 {

	/** generic System Interface for checking bitmasks of Component groups on entities*/
	class ISystem
	{
	public:

		///public Fields
		/** User defined object name */
		std::string name;

		///Constructor / Destructor
		/** Constructor */
		//ISystem();
		/** Destructor */
		//~ISystem();

		///Getters / Setters
		/** documentation */

		///Methods
		/** check if the required bitmask of this system and the bitmask on the given entity are compatible */
		bool checkComponentsCompatible(Entity* entity);

	protected:
		///friend classes
		/** documentation */

		///private Constructor
		/** documentation */

		///private Fields
		/** pointer to parent Appliaction to access other Systems*/
		Application* mApplication;
		/** relevant Bitmask bit for this system, identical mask is required on Entities*/
		ComponentBitmask mRequiredBitmask;

		///private Methods
		/** documentation */

	};
}

