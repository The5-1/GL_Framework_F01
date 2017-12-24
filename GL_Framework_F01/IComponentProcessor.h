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

		IComponentProcessor(Application* application) : mApplication(application) 
		{		
		}

		T* IComponentProcessor<T>::getComponent(unsigned int i)
		{
			return mComponentPointers.at(i);
		}

		void registerComponentPointer(T* component)
		{
			mComponentPointers.push_back(component); //TODO this here crashes, maybe because i cast stuff where calling this
		}

		void removeComponentPointer(T* component)
		{
			//https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
			//https://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
			mComponentPointers.erase(std::remove(mComponentPointers.begin(), mComponentPointers.end(), component), mComponentPointers.end());
		}

	protected:

		///The Entity owns the component! No unique_ptr here!
		Application* mApplication;
		std::vector<T*> mComponentPointers;
	};
}

