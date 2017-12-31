#include "RenderableC.h"
#include "RendererCP.h"

#include "GL_include.h"

#include "Entity.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "IMaterial.h"


namespace The5 
{
	RenderableC::RenderableC(Entity* parentEntity): IComponent(parentEntity)
	{
		name += "_" + ComponentTypeString.at(getType());
		mFlagDoProcessing = true;
		init();
	}

	ComponentType RenderableC::getType()
	{
		return ComponentType::RenderableType;
	}

	void RenderableC::setMesh(Mesh * mesh)
	{
		this->mesh = mesh;
	}

	void RenderableC::setMaterial(IMaterial* material)
	{
		this->material = material;
	}

	//void RenderableC::setShader(Shader * shader)
	//{
	//	this->shader = shader;
	//}


	void RenderableC::draw(double deltaTime)
	{
		checkRecompileShader();

		if(material != nullptr) material->useShader();
		//if(shader != nullptr) shader->use();
		if(mesh != nullptr) mesh->draw();
	}

	void RenderableC::setRecompileShader()
	{
		if (material != nullptr)
		{
			flagRecompileShader = true;
			material->setRecompileShader();
		}
	}

	IMaterial* RenderableC::getRenderpassMaterial(RenderPass * renderpass)
	{
		auto it = renderPasses.find(renderpass);
		if (it == renderPasses.end()) return nullptr;
		else return it->second;
	}

	void RenderableC::checkRecompileShader()
	{
		if (flagRecompileShader)
		{
			if(material != nullptr) material->checkRecompileShader();
			this->flagRecompileShader = false;
		}
	}
}