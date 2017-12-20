#pragma once

#include "ForwardDeclarations.h"

#include "IComponent.h"
#include "GL_include.h"

namespace The5
{

	class MoveableC: public IComponent
	{
	public:
		friend ComponentFactory;
		ComponentType getType();

	private:
		MoveableC(Entity* entity);

		void registerAtComponentProcessor();
		void removeFromComponentProcessor();

		glm::vec3 mVelocity;	
	};
}

