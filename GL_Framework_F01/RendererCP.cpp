#include "Logging.h"

#include "Application.h"
#include "IComponent.h"
#include "Scene.h"
#include "RendererCP.h"
#include "RenderableC.h"
#include "Entity.h"


namespace The5 
{
	RendererCP::RendererCP(Application * application) : IComponentProcessor(ComponentProcessorTypeString.at(this->getType()), application, initRequiredComponentBitmask(), 0.0)
	{

	}

	void RendererCP::setFlagRecompileAllShaders()
	{
		//LOG("Test printing Tree:\n"<< mApplication->getScene()->getInfo(true));	
		SceneTree* sceneTree = mApplication->getScene()->getSceneTree();
		for (SceneTree::iterator it = sceneTree->begin(); it != sceneTree->end(); ++it)
		{		
			Entity* entity = it.node->data;
			//LOG("? Set flag on " << entity->name);
			if (entity->getComponent(ComponentType::RenderableType) == nullptr) continue;
			RenderableC* renderable = (RenderableC*)(entity->getComponent(ComponentType::RenderableType));
			//LOG("! Set flag on " << renderable->name);
			renderable->setRecompileShader();
		}
	}

	ComponentBitmask RendererCP::initRequiredComponentBitmask()
	{
		ComponentBitmask mask;
		mask.addComponentType(ComponentType::RenderableType);
		return mask;
	}

	void RendererCP::doProcessing(Entity * entity, double deltaTime)
	{
		//if (entity->getComponent(ComponentType::RenderableType) == nullptr) return; //! the bitmask check takes care of this!
		RenderableC* renderable = (RenderableC*)(entity->getComponent(ComponentType::RenderableType));
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