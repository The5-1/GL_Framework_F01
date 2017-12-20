#pragma once

#include "ForwardDeclarations.h"

#include "IComponentProcessor.h"
#include "RenderableC.h"

///go over all entities in the scene
///get their component
///if it has a renderable/model component, draw it

namespace The5 {

	class RendererCP : IComponentProcessor
	{
	public:

	private:

		std::vector<RenderableC_uptr> mComponents;

	};

}