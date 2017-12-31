#include "Logging.h"

#include "Application.h"
#include "IComponent.h"
#include "Scene.h"
#include "RendererCP.h"
#include "RenderableC.h"
#include "Entity.h"
#include "RenderTarget.h"
#include "RenderPass.h"

namespace The5 
{
	RendererCP::RendererCP(Application * application) : 
		IComponentProcessor(ComponentProcessorTypeString.at(this->getType()), application, initRequiredComponentBitmask(), 0.0)
	{
		this->onscreenRenderTarget = RenderTarget_uptr(new RenderTarget("OnScreen RenderTarget"));
	}

	//https://stackoverflow.com/questions/5503352/const-before-or-const-after/5503442#5503442 !!!
	//C compiler parsed input from left-to-right and finished processing each token as it consumed that. 
	//Consuming the * token changes the state of the current declaration to a pointer type.
	//Encountering const after * means the const qualifier is applied to a pointer declaration; encountering it prior to the * means the qualifier is applied to the data pointed to."
	const RenderTarget* const RendererCP::getOnscreenTarget() const
	{
		return onscreenRenderTarget.get();
	}

	void RendererCP::setFlagRecompileAllShaders()
	{
		//LOG("Test printing Tree:\n"<< mApplication->getScene()->getInfo(true));	
		SceneTree* sceneTree = mApplication->getScene()->getSceneTree();
		for (SceneTree::iterator it = sceneTree->begin(); it != sceneTree->end(); ++it)
		{		
			Entity* entity = it.node->data;
			//LOG("? Set flag on " << entity->name);
			if (entity->getComponent(ComponentType::RenderableCType) == nullptr) continue;
			RenderableC* renderable = (RenderableC*)(entity->getComponent(ComponentType::RenderableCType));
			//LOG("! Set flag on " << renderable->name);
			renderable->setRecompileShader();
		}
	}

	ComponentBitmask RendererCP::initRequiredComponentBitmask()
	{
		ComponentBitmask mask;
		mask.addComponentType(ComponentType::RenderableCType);
		return mask;
	}

	void RendererCP::doProcessing(Entity * entity, double deltaTime)
	{
		//if (entity->getComponent(ComponentType::RenderableCType) == nullptr) return; //! the bitmask check takes care of this!
		RenderableC* renderable = (RenderableC*)(entity->getComponent(ComponentType::RenderableCType));
		draw(renderable, entity, deltaTime);
	}

	/*
	void RendererCP::processScene(Scene * scene)
	{
		//for each entity in scene processEntity(e);
	}
	*/

	void RendererCP::draw(RenderableC * renderableC, Entity* entity, double deltaTime)
	{
		renderableC->draw(deltaTime);
		//LOG("Rendering Entity \"" << entity->name << "\"");
	}
}