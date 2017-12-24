#pragma once

#include "stl_include.h"
#include "ForwardDeclarations.h"

namespace The5
{

	//template definitions must be in the header
	//https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c

	///The Entity owns the Component
	///A Component signs itself up with a Component Processor
	template<typename T>
	class IComponentProcessor
	{
	public:

		IComponentProcessor(Application* application);

		T* getComponent(unsigned int i);

		void registerComponentPointer(T* component);
		void removeComponentPointer(T* component);

		Application* application;

	protected:

		///The Entity owns the component! No unique_ptr here!
		std::vector<T*> mComponentPointers;
	};
}