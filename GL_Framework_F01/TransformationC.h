#pragma once

#include "ForwardDeclarations.h"
#include "IComponent.h"

namespace The5 {

	/** Component that provides transformation matrices 
	* not sure if this is makes sense...
	* e.g. when parents dont have transformations but children do
	* i would need to multiply temporary mat4(1.0) to a node if only a child got a transformation!
	*/
	class TransformationC : public IComponent
	{
	public:
		/** localTransformation */
		mat4 localTransformation;
		/** the combined resulting transformation matrix, only updated when dirty */
		mat4 globalTransformation;


		/* Inherited via IComponent */
		ComponentType getType() override {return ComponentType::TimerCType;};

	protected:
		bool mDirty = false;

	};
}