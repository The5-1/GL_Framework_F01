#include "IComponentProcessor.h"

#include "IComponent.h"

namespace The5
{
	//template class definitions must be in the header
	//https://stackoverflow.com/questions/1639797/template-issue-causes-linker-error-c

	/*
	template <typename T> IComponentProcessor<T>::IComponentProcessor(Application* application): application(application)
	{
		//static_assert(std::is_base_of<BaseClass, Derived>::value, "IComponentPocessor must use a Type derived from IComponent!");
	}

	//TODO: Fix these, understand inheritance: how do i make a derived class call the base classes function but in its own derived context

	template <typename T> T* IComponentProcessor<T>::getComponent(unsigned int i)
	{
		return IComponentProcessor<T>::mComponentPointers.at(i);
	}

	template <typename T> void IComponentProcessor<T>::registerComponentPointer(T* component)
	{
		IComponentProcessor<T>::mComponentPointers.push_back(component);
	}

	template <typename T> void IComponentProcessor<T>::removeComponentPointer(T* component)
	{
		//https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
		//https://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
		IComponentProcessor<T>::mComponentPointers.erase(std::remove(mComponentPointers.begin(), mComponentPointers.end(), component), mComponentPointers.end());
	}
	*/
}