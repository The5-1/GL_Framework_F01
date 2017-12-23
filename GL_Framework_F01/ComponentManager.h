#pragma once

#include "ForwardDeclarations.h"

#include "IComponent.h"
#include "IComponentProcessor.h"

namespace The5
{

	class ComponentManager
	{
	public:

		ComponentManager(Application* application);

		Application* application;

		IComponent* createComponent(ComponentType type, Entity* entity);

	private:


		RendererCP_uptr mRendererCP;
	};

}