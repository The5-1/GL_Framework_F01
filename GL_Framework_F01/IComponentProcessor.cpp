#include "IComponentProcessor.h"

#include "IComponent.h"

namespace The5
{

	///Static variables need to be declared and initialized in the cpp file!!! https://stackoverflow.com/questions/16049306/error-lnk2001-unresolved-external-symbol-private-static-class
	//std::vector<IComponent*> IComponentProcessor::mComponentPointers = std::vector<IComponent*>();

	template <typename T> IComponentProcessor<T>::IComponentProcessor(Application* application): application(application)
	{
		//static_assert(std::is_base_of<BaseClass, Derived>::value, "IComponentPocessor must use a Type derived from IComponent!");
	}

	//TODO: Fix these, understand inheritance: how do i make a derived class call the base classes function but in its own derived context

	template <typename T> T* IComponentProcessor<T>::getComponent(unsigned int i)
	{
		return IComponentProcessor<T>::mComponentPointers.at(i);
	}

	template <typename T> void IComponentProcessor::registerComponentPointer(T* component)
	{
		IComponentProcessor<T>::mComponentPointers.push_back(component);
	}

	template <typename T> void IComponentProcessor::removeComponentPointer(T* component)
	{
		//https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
		//https://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
		IComponentProcessor<T>::mComponentPointers.erase(std::remove(mComponentPointers.begin(), mComponentPointers.end(), component), mComponentPointers.end());
	}
}