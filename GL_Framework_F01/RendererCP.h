#pragma once

#include "ForwardDeclarations.h"
#include "IComponentProcessor.h"
#include "RenderTarget.h"
#include "RenderPass.h"

namespace The5 {

	/** the main renderer class, inherits from Component Processor */
	class RendererCP : public IComponentProcessor
	{
	public:

		RendererCP(Application* application);

		ComponentProcessorType getType() {return ComponentProcessorType::RendererCPType;};

		void setFlagRecompileAllShaders();
		
		
		/** Render Target factory */
		RenderTarget* createRenderTarget(std::string name);

		/** Render Pass factory */
		RenderPass* createRenderPass(std::string name);

		/** get const Onscreen RenderTarget */
		const RenderTarget* const getOnscreenTarget() const;

	private:
		/** owned onscreen target fboID = 0, const getter */
		RenderTarget_uptr onscreenRenderTarget;
		/** owned offscreen RenderTargets */
		std::vector<RenderTarget_uptr> offscreenRenderTargets;
		/** owned Render Passes*/
		std::vector<RenderPass_uptr> renderPasses;

		ComponentBitmask initRequiredComponentBitmask() override;
		
		void doProcessing(Entity* entity, double deltaTime) override;

		void draw(RenderableC* renderableC, Entity* entity, double deltaTime);
	};

}