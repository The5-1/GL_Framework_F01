#pragma once

#include "stl_include.h"
#include "ForwardDeclarations.h"

namespace The5
{

	///The Entity owns the Component
	///A Component signs itself up with a Componentn Processor
	class IComponentProcessor
	{
	public:

		IComponentProcessor();

		IComponent* getComponent(unsigned int i);

	private:

		///The Entity owns the component! No unique_ptr here!
		std::vector<IComponent*> mComponentPointers;
	};
}