#pragma once

#include "ForwardDeclarations.h"
#include "IComponentProcessor.h"

namespace The5 {

	class RendererCP : public IComponentProcessor
	{
	public:
		RendererCP(Application* application);

	private:
		ComponentBitmask initRequiredComponentBitmask() override;
		
		void doProcessing(Entity* entity, double deltaTime) override;

		void draw(RenderableC* renderableC, Entity* entity, double deltaTime);
	};

}