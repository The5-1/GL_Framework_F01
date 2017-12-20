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

		static IComponent* getComponent(unsigned int i);

		static void registerComponentPointer(IComponent* component);
		static void removeComponentPointer(IComponent* component);

	private:

		///The Entity owns the component! No unique_ptr here!
		static std::vector<IComponent*> mComponentPointers;
	};
}