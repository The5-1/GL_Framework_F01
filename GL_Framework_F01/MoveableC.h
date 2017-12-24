#if 0

#pragma once

#include "ForwardDeclarations.h"

#include "IComponent.h"
#include "GL_include.h"

namespace The5
{

	class MoveableC: public IComponent
	{
	public:
		friend ComponentManager;
		ComponentType getType();

	private:
		MoveableC(MoveableCP* processor, Entity* parentEntity);

		void registerAtComponentProcessor();
		void removeFromComponentProcessor();

		glm::vec3 mVelocity;	
	};
}

#endif

