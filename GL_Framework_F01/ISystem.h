#pragma once

#include "ForwardDeclarations.h"
#include "ComponentCommon.h"
#include "IComponent.h"

namespace The5 {

	/** System is everything not working on components*/
	class ISystem
	{
	public:
		///public Fields
		/** User defined object name */
		std::string name;

		///Constructor / Destructor
		/** Constructor */
		ISystem(Application* application);
		/** Destructor */
		//~ISystem();

		///Getters / Setters
		/** documentation */

		///Methods

	protected:
		///friend classes
		/** documentation */

		///private Constructor
		/** documentation */

		///private Fields
		/** appliation this system belongs to */
		Application* mApplication;

		///private Methods
		/** documentation */

	};
}

