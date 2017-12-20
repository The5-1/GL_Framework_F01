#include "IComponentProcessor.h"

#include "IComponent.h"

namespace The5
{
	IComponentProcessor::IComponentProcessor()
	{

	}

	//TODO: Fix these, understand inheritance: how do i make a derived class call the base classes function but in its own derived context

	IComponent* IComponentProcessor::getComponent(unsigned int i)
	{
		//return IComponentProcessor::mComponentPointers.at(i);
		return nullptr;
	}

	void IComponentProcessor::registerComponentPointer(IComponent* component)
	{
		//IComponentProcessor::mComponentPointers.push_back(component);
	}

	void IComponentProcessor::removeComponentPointer(IComponent* component)
	{
		//https://en.wikipedia.org/wiki/Erase%E2%80%93remove_idiom
		//https://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value
		//IComponentProcessor::mComponentPointers.erase(std::remove(mComponentPointers.begin(), mComponentPointers.end(), component), mComponentPointers.end());
	}
}