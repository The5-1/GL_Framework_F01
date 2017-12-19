#pragma once

#include "ForwardDeclarations.h"


namespace The5 {


	enum ComponentType { Renderable };

	class IComponent
	{
	public:

		IComponent(Entity* entity);

		//pure virtual
		virtual ComponentType getType() = 0;
		virtual void update() = 0;

		Entity* parentEntity;
	};

}