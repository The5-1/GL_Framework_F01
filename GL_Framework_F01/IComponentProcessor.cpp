#include "IComponentProcessor.h"

#include "IComponent.h"

namespace The5
{
	IComponentProcessor::IComponentProcessor()
	{

	}

	IComponent* IComponentProcessor::getComponent(unsigned int i)
	{
		return mComponentPointers.at(i);
	}
}