#pragma once

#include "ForwardDeclarations.h"
#include "IComponentProcessor.h"

namespace The5 {

	class RendererCP : public IComponentProcessor
	{
	public:
		RendererCP(Application* application);

		void processEntity(Entity* entity) override;

		void processScene(Scene* scene) override;

		void draw(RenderableC* renderableC);

	private:
		ComponentBitmask initRequiredComponentBitmask() override;

	};

}