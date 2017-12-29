#pragma once

#include "ForwardDeclarations.h"
#include "IComponentProcessor.h"

namespace The5 {

	class RendererCP : public IComponentProcessor
	{
	public:
		RendererCP(Application* application);
		ComponentProcessorType getType() {return ComponentProcessorType::RendererType;};

		void setFlagRecompileAllShaders();

	private:
		ComponentBitmask initRequiredComponentBitmask() override;
		
		void doProcessing(Entity* entity, double deltaTime) override;

		void draw(RenderableC* renderableC, Entity* entity, double deltaTime);
	};

}